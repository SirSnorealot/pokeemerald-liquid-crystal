#include "global.h"
#include "config/quickstart.h"
#include "quickstart.h"
#include "title_screen.h"
#include "sprite.h"
#include "gba/m4a_internal.h"
#include "decompress.h"
#include "intro.h"
#include "m4a.h"
#include "main.h"
#include "main_menu.h"
#include "palette.h"
#include "sound.h"
#include "task.h"
#include "scanline_effect.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define PRESS_START_BG_SCREENBASE 24
#define PRESS_START_BG_ROW 16
#define PRESS_START_BG_COL 5
#define PRESS_START_BG_WIDTH 12
#define SUICUNE_BG_CHARBASE 0
#define SUICUNE_BG_SCREENBASE 23
#define SUICUNE_BG_X 18
#define SUICUNE_BG_Y 8
#define SUICUNE_BG_WIDTH 12
#define SUICUNE_BG_HEIGHT 12
#define SUICUNE_BLANK_TILE 831
#define SUICUNE_TILE_START 832
#define SUICUNE_PAL_SLOT 15
#define SUICUNE_FRAME_DELAY 6

static void MainCB2(void);
static void Task_TitleScreenPhase3(u8);
static void CB2_GoToMainMenu(void);
static void CB2_GoToCopyrightScreen(void);

static void SetPressStartBgTextVisible(bool8 visible);
static void InitSuicuneBgTilemap(void);
static void LoadSuicuneBgFrame(u8 frame);
static void UpdateSuicuneBgAnimation(u8 taskId);

// const rom data
static const u32 sTitleScreenLCGfx[] = INCGFX_U32("graphics/title_screen/LC.png", ".8bpp.smol");
static const u32 sTitleScreenLCTilemap[] = INCGFX_U32("graphics/title_screen/LC.bin", ".smolTM");
static const u16 sTitleScreenLCPal[] = INCBIN_U16("graphics/title_screen/LC.gbapal");
static const u16 sTitleScreenSuicunePal[] = INCBIN_U16("graphics/title_screen/suicune.gbapal");
static const u32 sTitleScreenSuicuneGfx_00[] = INCGFX_U32("graphics/title_screen/suicune/BA0000_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_01[] = INCGFX_U32("graphics/title_screen/suicune/BA06B4_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_02[] = INCGFX_U32("graphics/title_screen/suicune/BA0D98_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_03[] = INCGFX_U32("graphics/title_screen/suicune/BA1464_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_04[] = INCGFX_U32("graphics/title_screen/suicune/BA1B24_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_05[] = INCGFX_U32("graphics/title_screen/suicune/BA21C0_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_06[] = INCGFX_U32("graphics/title_screen/suicune/BA2870_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_07[] = INCGFX_U32("graphics/title_screen/suicune/BA2F44_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_08[] = INCGFX_U32("graphics/title_screen/suicune/BA3600_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_09[] = INCGFX_U32("graphics/title_screen/suicune/BA3CCC_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_10[] = INCGFX_U32("graphics/title_screen/suicune/BA438C_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_11[] = INCGFX_U32("graphics/title_screen/suicune/BA4A60_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_12[] = INCGFX_U32("graphics/title_screen/suicune/BA5118_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_13[] = INCGFX_U32("graphics/title_screen/suicune/BA57D0_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_14[] = INCGFX_U32("graphics/title_screen/suicune/BA5E9C_4bpp_indexed.png", ".4bpp.smol");
static const u32 sTitleScreenSuicuneGfx_15[] = INCGFX_U32("graphics/title_screen/suicune/BA6570_4bpp_indexed.png", ".4bpp.smol");

static const u32 *const sTitleScreenSuicuneGfx[] =
{
    sTitleScreenSuicuneGfx_00,
    sTitleScreenSuicuneGfx_01,
    sTitleScreenSuicuneGfx_02,
    sTitleScreenSuicuneGfx_03,
    sTitleScreenSuicuneGfx_04,
    sTitleScreenSuicuneGfx_05,
    sTitleScreenSuicuneGfx_06,
    sTitleScreenSuicuneGfx_07,
    sTitleScreenSuicuneGfx_08,
    sTitleScreenSuicuneGfx_09,
    sTitleScreenSuicuneGfx_10,
    sTitleScreenSuicuneGfx_11,
    sTitleScreenSuicuneGfx_12,
    sTitleScreenSuicuneGfx_13,
    sTitleScreenSuicuneGfx_14,
    sTitleScreenSuicuneGfx_15,
};

// Used by the intro to blend the Game Freak name/logo in and out as they appear and disappear
const u16 gTitleScreenAlphaBlend[64] =
{
    BLDALPHA_BLEND(16, 0),
    BLDALPHA_BLEND(16, 1),
    BLDALPHA_BLEND(16, 2),
    BLDALPHA_BLEND(16, 3),
    BLDALPHA_BLEND(16, 4),
    BLDALPHA_BLEND(16, 5),
    BLDALPHA_BLEND(16, 6),
    BLDALPHA_BLEND(16, 7),
    BLDALPHA_BLEND(16, 8),
    BLDALPHA_BLEND(16, 9),
    BLDALPHA_BLEND(16, 10),
    BLDALPHA_BLEND(16, 11),
    BLDALPHA_BLEND(16, 12),
    BLDALPHA_BLEND(16, 13),
    BLDALPHA_BLEND(16, 14),
    BLDALPHA_BLEND(16, 15),
    BLDALPHA_BLEND(15, 16),
    BLDALPHA_BLEND(14, 16),
    BLDALPHA_BLEND(13, 16),
    BLDALPHA_BLEND(12, 16),
    BLDALPHA_BLEND(11, 16),
    BLDALPHA_BLEND(10, 16),
    BLDALPHA_BLEND(9, 16),
    BLDALPHA_BLEND(8, 16),
    BLDALPHA_BLEND(7, 16),
    BLDALPHA_BLEND(6, 16),
    BLDALPHA_BLEND(5, 16),
    BLDALPHA_BLEND(4, 16),
    BLDALPHA_BLEND(3, 16),
    BLDALPHA_BLEND(2, 16),
    BLDALPHA_BLEND(1, 16),
    BLDALPHA_BLEND(0, 16),
    [32 ... 63] = BLDALPHA_BLEND(0, 16)
};

// Task data for Task_TitleScreenPhase3
#define tCounter    data[0]
#define tSuicuneFrame data[5]
#define tSuicuneTimer data[6]

static void SetPressStartBgTextVisible(bool8 visible)
{
    static const u16 sPressStartTilemapEntries[PRESS_START_BG_WIDTH] =
    {
        0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,
        0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80
    };
    u16 *tilemap = (u16 *)BG_SCREEN_ADDR(PRESS_START_BG_SCREENBASE);
    u16 offset = PRESS_START_BG_ROW * 32 + PRESS_START_BG_COL;
    u8 i;

    for (i = 0; i < PRESS_START_BG_WIDTH; i++)
        tilemap[offset + i] = visible ? sPressStartTilemapEntries[i] : 0;
}

static void InitSuicuneBgTilemap(void)
{
    u16 *tilemap = (u16 *)BG_SCREEN_ADDR(SUICUNE_BG_SCREENBASE);
    u8 x;
    u8 y;

    DmaFill16(3, SUICUNE_BLANK_TILE | (SUICUNE_PAL_SLOT << 12), tilemap, 0x800);
    DmaFill16(3, 0, (void *)(BG_CHAR_ADDR(SUICUNE_BG_CHARBASE) + SUICUNE_BLANK_TILE * 32), 32);

    for (y = 0; y < SUICUNE_BG_HEIGHT; y++)
    {
        for (x = 0; x < SUICUNE_BG_WIDTH; x++)
        {
            u16 tile = SUICUNE_TILE_START + y * SUICUNE_BG_WIDTH + x;
            u16 offset = (SUICUNE_BG_Y + y) * 32 + SUICUNE_BG_X + x;

            tilemap[offset] = tile | (SUICUNE_PAL_SLOT << 12);
        }
    }
}

static void LoadSuicuneBgFrame(u8 frame)
{
    DecompressDataWithHeaderVram(
        sTitleScreenSuicuneGfx[frame],
        (void *)(BG_CHAR_ADDR(SUICUNE_BG_CHARBASE) + SUICUNE_TILE_START * 32));
}

static void UpdateSuicuneBgAnimation(u8 taskId)
{
    if (++gTasks[taskId].tSuicuneTimer < SUICUNE_FRAME_DELAY)
        return;

    gTasks[taskId].tSuicuneTimer = 0;
    if (++gTasks[taskId].tSuicuneFrame >= ARRAY_COUNT(sTitleScreenSuicuneGfx))
        gTasks[taskId].tSuicuneFrame = 0;

    LoadSuicuneBgFrame(gTasks[taskId].tSuicuneFrame);
}

static void VBlankCB(void)
{
    ScanlineEffect_InitHBlankDmaTransfer();
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitTitleScreen(void)
{
    if (IS_FRLG)
    {
        CB2_InitTitleScreenFrlg();
        return;
    }
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        *((u16 *)PLTT) = RGB_WHITE;
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
        DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16(3, 0, (void *)(PLTT + 2), PLTT_SIZE - 2);
        ResetPaletteFade();
        gMain.state = 1;
        break;
    case 1:
        // bg2
        DecompressDataWithHeaderVram(gTitleScreenPokemonLogoGfx, (void *)(BG_CHAR_ADDR(2)));
        DecompressDataWithHeaderVram(gTitleScreenPokemonLogoTilemap, (void *)(BG_SCREEN_ADDR(24)));
        LoadPalette(sTitleScreenLCPal, BG_PLTT_ID(0), PLTT_SIZE_8BPP);
        LoadPalette(sTitleScreenSuicunePal, BG_PLTT_ID(SUICUNE_PAL_SLOT), PLTT_SIZE_4BPP);
        // bg0
        DecompressDataWithHeaderVram(sTitleScreenLCGfx, (void *)(BG_CHAR_ADDR(0)));
        DecompressDataWithHeaderVram(sTitleScreenLCTilemap, (void *)(BG_SCREEN_ADDR(26)));
        InitSuicuneBgTilemap();
        LoadSuicuneBgFrame(0);
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 9;
        gMain.state = 2;
        break;
    case 2:
    {
        u8 taskId = CreateTask(Task_TitleScreenPhase3, 0);

        gTasks[taskId].tCounter = 0;
        gTasks[taskId].tSuicuneFrame = 0;
        gTasks[taskId].tSuicuneTimer = 0;
        gMain.state = 3;
        break;
    }
    case 3:
        BeginNormalPaletteFade(PALETTES_ALL, 1, 16, 0, RGB_WHITEALPHA);
        SetVBlankCallback(VBlankCB);
        gMain.state = 4;
        break;
    case 4:
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(26) | BGCNT_256COLOR | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(2) | BGCNT_CHARBASE(SUICUNE_BG_CHARBASE) | BGCNT_SCREENBASE(SUICUNE_BG_SCREENBASE) | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(24) | BGCNT_256COLOR | BGCNT_TXT256x256);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_BG2_ON);
        m4aSongNumStart(MUS_TITLE);
        gMain.state = 5;
        break;
    case 5:
        if (!UpdatePaletteFade())
            SetMainCallback2(MainCB2);
        break;
    }
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

// Process main title screen input and animate the Suicune background
static void Task_TitleScreenPhase3(u8 taskId)
{
    if (QUICKSTART && JOY_NEW(SELECT_BUTTON))
        Quickstart();

    if (JOY_NEW(A_BUTTON) || JOY_NEW(START_BUTTON))
    {
        PlayCryInternal(SPECIES_SUICUNE, 0, 120, 10, 0);
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
        SetMainCallback2(CB2_GoToMainMenu);
    }
    else
    {
        SetPressStartBgTextVisible((++gTasks[taskId].tCounter & 64) != 0);
        UpdateSuicuneBgAnimation(taskId);
        if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
            SetMainCallback2(CB2_GoToCopyrightScreen);
        }
    }
}

static void CB2_GoToMainMenu(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitMainMenu);
}

static void CB2_GoToCopyrightScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitCopyrightScreenAfterTitleScreen);
}

