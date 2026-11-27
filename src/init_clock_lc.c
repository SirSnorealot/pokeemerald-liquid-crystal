#include "global.h"
#include "bg.h"
#include "clock.h"
#include "datetime.h"
#include "gpu_regs.h"
#include "init_clock.h"
#include "international_string_util.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "rtc.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

/*
 * Liquid Crystal new game clock
 * -----------------------------
 *
 * Crystal's InitClock scene: a message box on a black screen where the
 * player sets the day of the week and the time before the game starts.
 * It runs after the Oak speech (oak_speech_lc.c) has faded to black and
 * hands off to CB2_NewGame.
 *
 * Entry point: CB2_InitClockLc
 *
 * How the time is stored
 *  - gLocalTime is the cartridge clock minus gSaveBlock2Ptr->localTimeOffset.
 *    Its day count is the number of days since gGen3Epoch (Saturday,
 *    2000-01-01), which is what GetDayOfWeek and the other calendar
 *    functions in rtc.h are derived from. Setting the clock therefore means
 *    choosing a day count with the right day of the week.
 *  - CB2_NewGame wipes the save data after this scene, so the scene only
 *    records the chosen time. SetNewGameClockLc applies it once the new
 *    save has been set up.
 *
 * With the real RTC (OW_USE_FAKE_RTC is FALSE)
 *  - If the RTC isn't working, an error is shown and the game resets. The
 *    main menu makes the same check before starting the Oak speech.
 *  - Otherwise the player is shown the cartridge clock's day and time. If
 *    they confirm it, the game follows the cartridge clock exactly. If
 *    not, they set the day and time themselves and the difference is kept
 *    as an offset from the cartridge clock.
 *
 * With the fake RTC (OW_USE_FAKE_RTC is TRUE)
 *  - The player always sets the day and time themselves.
 *
 * The dialogue uses the standard message box (window 0 on BG 0) and the
 * standard yes/no menu.
 *
 * Task_InitClock_Start
 *  - Wait for the message box to fade in, then check the RTC.
 *
 * Task_InitClock_CheckClock
 *  - With the real RTC, ask if the cartridge clock is right
 *    (Task_InitClock_HandleClockYesNo). With the fake RTC, start asking.
 *
 * Task_InitClock_ShowPicker / Task_InitClock_HandlePicker
 *  - Ask for the day, the hour and the minutes in turn. Up and Down change
 *    the value and A selects it.
 *
 * Task_InitClock_HandleStepYesNo
 *  - Confirm the selected value. NO asks for it again.
 *
 * Task_InitClock_WaitForButton / Task_InitClock_Exit
 *  - Wait for A or B after the last message, fade to black and advance to
 *    CB2_NewGame, or reset the game if the RTC isn't working.
 */

enum
{
    WIN_MESSAGE, // The standard message box set up by InitStandardTextBoxWindows
};

enum
{
    STEP_DAY,
    STEP_HOUR,
    STEP_MINUTE,
    STEP_COUNT,
};

#define tStep           data[0]
#define tValue(step)    data[1 + (step)] // The day of the week, hour and minute
#define tPickerWindowId data[4]
#define tUseRtc         data[5] // The player confirmed the cartridge clock
#define tNoClock        data[6] // The RTC isn't working
// data[14] and data[15] hold the follow-up task func

#define PICKER_WIDTH 14

struct ClockStep
{
    const u8 *question;
    const u8 *confirmation;
    u8 numValues;
    u8 defaultValue;
};

static void Task_InitClock_Start(u8);
static void Task_InitClock_CheckClock(u8);
static void Task_InitClock_HandleClockYesNo(u8);
static void Task_InitClock_ShowPicker(u8);
static void Task_InitClock_HandlePicker(u8);
static void Task_InitClock_HandleStepYesNo(u8);
static void Task_InitClock_WaitForButton(u8);
static void Task_InitClock_Exit(u8);

// Chosen in the scene, applied by SetNewGameClockLc
static EWRAM_DATA struct Time sNewGameTime = {0};
static EWRAM_DATA bool8 sNewGameTimeChosen = FALSE;

const u8 gText_ClockNotWorkingLc[] = _(
    "The game's clock isn't working.\n"
    "A new game can't be started.\p"
    "Please turn on the real-time clock\n"
    "of your emulator or flash cart.");

static const u8 sText_WokeMeUp[] = _(
    "…… …… …… …… …… ……\n"
    "…… …… …… …… …… ……\p"
    "Zzz… Hm? Wha…? You woke me up!\n"
    "Will you check the clock for me?\p");
static const u8 sText_ClockSays[] = _(
    "The clock says {STR_VAR_1},\n"
    "{STR_VAR_2}. Is that right?");
static const u8 sText_WhatDayIsIt[] = _("What day is it?");
static const u8 sText_ConfirmDay[] = _("{STR_VAR_1}, is it?");
static const u8 sText_WhatTimeIsIt[] = _("What time is it?");
static const u8 sText_ConfirmHour[] = _("What? {STR_VAR_1}?");
static const u8 sText_HowManyMinutes[] = _("How many minutes?");
static const u8 sText_ConfirmMinutes[] = _("Whoa! {STR_VAR_1}?");
static const u8 sText_TimeIsSet[] = _(
    "{STR_VAR_1}, {STR_VAR_2}!\n"
    "{STR_VAR_3}");

static const u8 sText_AM[] = _(" AM");
static const u8 sText_PM[] = _(" PM");
static const u8 sText_Minutes[] = _(" min.");
static const u8 sText_UpArrow[] = _("{UP_ARROW}");
static const u8 sText_DownArrow[] = _("{DOWN_ARROW}");

static const u8 *const sDayNames[WEEKDAY_COUNT] =
{
    [WEEKDAY_SUN] = COMPOUND_STRING("SUNDAY"),
    [WEEKDAY_MON] = COMPOUND_STRING("MONDAY"),
    [WEEKDAY_TUE] = COMPOUND_STRING("TUESDAY"),
    [WEEKDAY_WED] = COMPOUND_STRING("WEDNESDAY"),
    [WEEKDAY_THU] = COMPOUND_STRING("THURSDAY"),
    [WEEKDAY_FRI] = COMPOUND_STRING("FRIDAY"),
    [WEEKDAY_SAT] = COMPOUND_STRING("SATURDAY"),
};

static const u8 *const sTimeOfDayRemarks[TIMES_OF_DAY_COUNT] =
{
    [TIME_MORNING] = COMPOUND_STRING("I overslept!"),
    [TIME_DAY]     = COMPOUND_STRING("Yikes! I overslept!"),
    [TIME_EVENING] = COMPOUND_STRING("No wonder it's so dark!"),
    [TIME_NIGHT]   = COMPOUND_STRING("No wonder it's so dark!"),
};

static const struct ClockStep sSteps[STEP_COUNT] =
{
    [STEP_DAY] =
    {
        .question = sText_WhatDayIsIt,
        .confirmation = sText_ConfirmDay,
        .numValues = WEEKDAY_COUNT,
        .defaultValue = WEEKDAY_SUN,
    },
    [STEP_HOUR] =
    {
        .question = sText_WhatTimeIsIt,
        .confirmation = sText_ConfirmHour,
        .numValues = HOURS_PER_DAY,
        .defaultValue = 10,
    },
    [STEP_MINUTE] =
    {
        .question = sText_HowManyMinutes,
        .confirmation = sText_ConfirmMinutes,
        .numValues = MINUTES_PER_HOUR,
        .defaultValue = 0,
    },
};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    }
};

// Sits above the left side of the message box, clear of the yes/no menu
static const struct WindowTemplate sWindowTemplate_Picker =
{
    .bg = 0,
    .tilemapLeft = 2,
    .tilemapTop = 7,
    .width = PICKER_WIDTH,
    .height = 6,
    .paletteNum = 15,
    .baseBlock = 1
};

bool32 IsClockAvailableLc(void)
{
    return !(RtcGetErrorStatus() & (RTC_INIT_ERROR | RTC_ERR_FLAG_MASK));
}

static u32 GetDayOfWeekForDayCount(s32 days)
{
    return (gGen3Epoch.dayOfWeek + days) % WEEKDAY_COUNT;
}

static enum TimeOfDay GetTimeOfDayForHour(s32 hour)
{
    if (IsBetweenHours(hour, MORNING_HOUR_BEGIN, MORNING_HOUR_END))
        return TIME_MORNING;
    if (IsBetweenHours(hour, EVENING_HOUR_BEGIN, EVENING_HOUR_END))
        return TIME_EVENING;
    if (IsBetweenHours(hour, NIGHT_HOUR_BEGIN, NIGHT_HOUR_END))
        return TIME_NIGHT;
    return TIME_DAY;
}

// Reads the cartridge clock as a local time, i.e. counting days from gGen3Epoch.
static void GetCartridgeTime(struct Time *time)
{
    struct SiiRtcInfo rtc;

    RtcGetInfo(&rtc);
    time->days = RtcGetDayCount(&rtc) - 1; // RtcGetDayCount is 1 on gGen3Epoch
    if (time->days < 0)
        time->days = 0;
    time->hours = ConvertBcdToBinary(rtc.hour);
    time->minutes = ConvertBcdToBinary(rtc.minute);
    time->seconds = ConvertBcdToBinary(rtc.second);
}

static void GetChosenTime(struct Time *time, const s16 *data)
{
    s32 daysAhead;

    if (OW_USE_FAKE_RTC)
        time->days = 0;
    else
        GetCartridgeTime(time);

    // Use the date closest to the cartridge clock's that falls on the chosen day of the week.
    daysAhead = (tValue(STEP_DAY) + WEEKDAY_COUNT - GetDayOfWeekForDayCount(time->days)) % WEEKDAY_COUNT;
    if (daysAhead > WEEKDAY_COUNT / 2 && time->days + daysAhead >= WEEKDAY_COUNT)
        daysAhead -= WEEKDAY_COUNT;

    time->days += daysAhead;
    time->hours = tValue(STEP_HOUR);
    time->minutes = tValue(STEP_MINUTE);
    time->seconds = 0;
}

// Called by CB2_NewGame once the new save has been set up.
void SetNewGameClockLc(void)
{
    if (!sNewGameTimeChosen)
    {
        // The scene was skipped, e.g. by the quickstart.
        if (OW_USE_FAKE_RTC)
            sNewGameTime = (struct Time){ .hours = sSteps[STEP_HOUR].defaultValue };
        else
            GetCartridgeTime(&sNewGameTime);
    }
    sNewGameTimeChosen = FALSE;

    RtcCalcLocalTimeOffset(sNewGameTime.days, sNewGameTime.hours, sNewGameTime.minutes, sNewGameTime.seconds);
    InitTimeBasedEvents();
}

// Writes the hour on a 12-hour clock. The AM/PM suffix comes from GetMeridiem.
static u8 *FormatHour(u8 *dest, u32 hour)
{
    hour %= 12;
    if (hour == 0)
        hour = 12;
    return ConvertIntToDecimalStringN(dest, hour, STR_CONV_MODE_LEFT_ALIGN, 2);
}

static const u8 *GetMeridiem(u32 hour)
{
    return hour < 12 ? sText_AM : sText_PM;
}

static void FormatStepValue(u8 *dest, u32 step, u32 value)
{
    switch (step)
    {
    case STEP_DAY:
        StringCopy(dest, sDayNames[value]);
        break;
    case STEP_HOUR:
        StringCopy(FormatHour(dest, value), GetMeridiem(value));
        break;
    case STEP_MINUTE:
        StringCopy(ConvertIntToDecimalStringN(dest, value, STR_CONV_MODE_LEFT_ALIGN, 2), sText_Minutes);
        break;
    }
}

// Buffers the day, the time and a remark about the time in gStringVar1 to gStringVar3.
static void BufferDayAndTime(const s16 *data)
{
    u8 *dest;

    StringCopy(gStringVar1, sDayNames[tValue(STEP_DAY)]);
    dest = FormatHour(gStringVar2, tValue(STEP_HOUR));
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, tValue(STEP_MINUTE), STR_CONV_MODE_LEADING_ZEROS, 2);
    StringCopy(dest, GetMeridiem(tValue(STEP_HOUR)));
    StringCopy(gStringVar3, sTimeOfDayRemarks[GetTimeOfDayForHour(tValue(STEP_HOUR))]);
}

static void PrintMessage(const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    FillWindowPixelBuffer(WIN_MESSAGE, PIXEL_FILL(1));
    AddTextPrinterForMessage(TRUE);
}

static void Task_InitClock_WaitForMessage(u8 taskId)
{
    if (!IsTextPrinterActiveOnWindow(WIN_MESSAGE))
        SwitchTaskToFollowupFunc(taskId);
}

static void Task_InitClock_WaitForMessageThenYesNo(u8 taskId)
{
    if (!IsTextPrinterActiveOnWindow(WIN_MESSAGE))
    {
        DisplayYesNoMenuDefaultYes();
        SwitchTaskToFollowupFunc(taskId);
    }
}

static void PrintMessageThen(u8 taskId, const u8 *str, TaskFunc followupFunc)
{
    PrintMessage(str);
    SetTaskFuncWithFollowupFunc(taskId, Task_InitClock_WaitForMessage, followupFunc);
}

static void PrintMessageThenYesNo(u8 taskId, const u8 *str, TaskFunc followupFunc)
{
    PrintMessage(str);
    SetTaskFuncWithFollowupFunc(taskId, Task_InitClock_WaitForMessageThenYesNo, followupFunc);
}

static void PrintPickerRow(u8 windowId, const u8 *str, u32 row)
{
    u32 x = GetStringCenterAlignXOffset(FONT_NORMAL, str, PICKER_WIDTH * 8);

    AddTextPrinterParameterized(windowId, FONT_NORMAL, str, x, row * 16 + 1, TEXT_SKIP_DRAW, NULL);
}

static void DrawPicker(const s16 *data)
{
    FormatStepValue(gStringVar1, tStep, tValue(tStep));
    FillWindowPixelBuffer(tPickerWindowId, PIXEL_FILL(1));
    PrintPickerRow(tPickerWindowId, sText_UpArrow, 0);
    PrintPickerRow(tPickerWindowId, gStringVar1, 1);
    PrintPickerRow(tPickerWindowId, sText_DownArrow, 2);
    CopyWindowToVram(tPickerWindowId, COPYWIN_FULL);
}

static void VBlankCB_InitClock(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitClock(void)
{
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void CB2_InitClockLc(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        DmaFill16(3, 0, VRAM, VRAM_SIZE);
        DmaFill32(3, 0, OAM, OAM_SIZE);
        DmaFill16(3, RGB_BLACK, PLTT, PLTT_SIZE);
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        break;
    case 1:
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        break;
    case 2:
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        gSpriteCoordOffsetX = 0;
        gSpriteCoordOffsetY = 0;
        break;
    case 3:
        FillPalette(RGB_BLACK, 0, PLTT_SIZE);
        InitStandardTextBoxWindows();
        InitTextBoxGfxAndPrinters();
        break;
    case 4:
        DrawDialogueFrame(WIN_MESSAGE, TRUE);
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        SetVBlankCallback(VBlankCB_InitClock);
        taskId = CreateTask(Task_InitClock_Start, 0);
        gTasks[taskId].tPickerWindowId = AddWindow(&sWindowTemplate_Picker);
        SetMainCallback2(CB2_InitClock);
        return;
    }

    gMain.state++;
}

static void Task_InitClock_Start(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (IsClockAvailableLc())
        {
            PrintMessageThen(taskId, sText_WokeMeUp, Task_InitClock_CheckClock);
        }
        else
        {
            tNoClock = TRUE;
            PrintMessageThen(taskId, gText_ClockNotWorkingLc, Task_InitClock_WaitForButton);
        }
    }
}

static void AskStep(u8 taskId)
{
    PrintMessageThen(taskId, sSteps[gTasks[taskId].tStep].question, Task_InitClock_ShowPicker);
}

static void ShowTimeIsSet(u8 taskId)
{
    BufferDayAndTime(gTasks[taskId].data);
    PrintMessageThen(taskId, sText_TimeIsSet, Task_InitClock_WaitForButton);
}

static void Task_InitClock_CheckClock(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    struct Time time;
    u32 step;

    if (OW_USE_FAKE_RTC)
    {
        for (step = 0; step < STEP_COUNT; step++)
            tValue(step) = sSteps[step].defaultValue;
        tStep = STEP_DAY;
        AskStep(taskId);
    }
    else
    {
        // If the player ends up setting the time themselves, they start from the cartridge clock's.
        GetCartridgeTime(&time);
        tValue(STEP_DAY) = GetDayOfWeekForDayCount(time.days);
        tValue(STEP_HOUR) = time.hours;
        tValue(STEP_MINUTE) = time.minutes;
        BufferDayAndTime(data);
        PrintMessageThenYesNo(taskId, sText_ClockSays, Task_InitClock_HandleClockYesNo);
    }
}

static void Task_InitClock_HandleClockYesNo(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // YES
        tUseRtc = TRUE;
        ShowTimeIsSet(taskId);
        break;
    case 1: // NO
    case MENU_B_PRESSED:
        tStep = STEP_DAY;
        AskStep(taskId);
        break;
    }
}

static void Task_InitClock_ShowPicker(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    DrawStdWindowFrame(tPickerWindowId, FALSE);
    DrawPicker(data);
    gTasks[taskId].func = Task_InitClock_HandlePicker;
}

static void Task_InitClock_HandlePicker(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u32 numValues = sSteps[tStep].numValues;

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrame(tPickerWindowId, TRUE);
        FormatStepValue(gStringVar1, tStep, tValue(tStep));
        PrintMessageThenYesNo(taskId, sSteps[tStep].confirmation, Task_InitClock_HandleStepYesNo);
    }
    else if (JOY_REPEAT(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        tValue(tStep) = (tValue(tStep) + 1) % numValues;
        DrawPicker(data);
    }
    else if (JOY_REPEAT(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        tValue(tStep) = (tValue(tStep) + numValues - 1) % numValues;
        DrawPicker(data);
    }
}

static void Task_InitClock_HandleStepYesNo(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // YES
        if (++tStep == STEP_COUNT)
            ShowTimeIsSet(taskId);
        else
            AskStep(taskId);
        break;
    case 1: // NO
    case MENU_B_PRESSED:
        AskStep(taskId);
        break;
    }
}

static void Task_InitClock_WaitForButton(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_InitClock_Exit;
    }
}

static void Task_InitClock_Exit(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (tNoClock)
        {
            // The player's name and gender were already written over the loaded save, so start over.
            DoSoftReset();
            return;
        }

        if (tUseRtc)
            GetCartridgeTime(&sNewGameTime);
        else
            GetChosenTime(&sNewGameTime, data);
        sNewGameTimeChosen = TRUE;

        FreeAllWindowBuffers();
        gTextFlags.canABSpeedUpPrint = FALSE;
        DestroyTask(taskId);
        SetMainCallback2(CB2_NewGame);
    }
}
