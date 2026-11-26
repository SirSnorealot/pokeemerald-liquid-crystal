#include "global.h"
#include "bg.h"
#include "gpu_regs.h"
#include "init_clock.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"

/*
 * Liquid Crystal new game dialogue
 * --------------------------------
 *
 * Crystal's InitClock scene: a message box on a black screen where the
 * player answers a few questions and sets the time before the game starts.
 * It runs after the Oak speech (oak_speech_lc.c) has faded to black and
 * hands off to CB2_NewGame.
 *
 * The clock itself is not implemented yet; for now this only shows a
 * placeholder message.
 *
 * Entry point: CB2_InitClockLc
 *
 * The dialogue uses the standard message box (window 0 on BG 0), so the
 * usual menu.h helpers such as the yes/no menu can be used here.
 *
 * Task_InitClock_PrintMessage
 *  - Wait for the message box to fade in, then print the message.
 *
 * Task_InitClock_WaitForMessage
 *  - Wait for the text to finish printing and then for A or B to be
 *    pressed, then fade to black.
 *
 * Task_InitClock_StartGame
 *  - Clean up and advance to CB2_NewGame.
 */

enum
{
    WIN_MESSAGE, // The standard message box set up by InitStandardTextBoxWindows
};

static void Task_InitClock_PrintMessage(u8);
static void Task_InitClock_WaitForMessage(u8);
static void Task_InitClock_StartGame(u8);

static const u8 sText_HelloWorld[] = _("Hello, world!");

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
        CreateTask(Task_InitClock_PrintMessage, 0);
        SetMainCallback2(CB2_InitClock);
        return;
    }

    gMain.state++;
}

static void Task_InitClock_PrintMessage(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        StringExpandPlaceholders(gStringVar4, sText_HelloWorld);
        AddTextPrinterForMessage(TRUE);
        gTasks[taskId].func = Task_InitClock_WaitForMessage;
    }
}

static void Task_InitClock_WaitForMessage(u8 taskId)
{
    if (!IsTextPrinterActiveOnWindow(WIN_MESSAGE) && JOY_NEW(A_BUTTON | B_BUTTON))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_InitClock_StartGame;
    }
}

static void Task_InitClock_StartGame(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        FreeAllWindowBuffers();
        gTextFlags.canABSpeedUpPrint = FALSE;
        DestroyTask(taskId);
        SetMainCallback2(CB2_NewGame);
    }
}
