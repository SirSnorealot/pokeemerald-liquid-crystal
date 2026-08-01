#include "global.h"
#include "main.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "task.h"
#include "title_screen.h"
#include "libgcnmultiboot.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "link.h"
#include "multiboot_pokemon_colosseum.h"
#include "load_save.h"
#include "save.h"
#include "new_game.h"
#include "m4a.h"
#include "decompress.h"
#include "constants/songs.h"
#include "trig.h"
#include "intro.h"
#include "graphics.h"
#include "sound.h"
#include "constants/rgb.h"

/*
    The intro is grouped into the following scenes
    Scene 0. Copyright screen
    Scene 1. Ditto/Game Freak logo drops in, LAZ presents
    Scene 2. Crystal intro (GBC port): Unowns, Suicune, "CRYSTAL" letters

    After this it progresses to the title screen
*/

// Scene 1 main tasks
static void Task_Scene1_DittoLogo(u8);
static void Task_Scene1_DittoAnimation(u8);
static void Task_Scene1_End(u8);

// Scene 1 supplemental functions
static void IntroResetGpuRegs(void);
static void ShowLazText(void);

// Crystal intro (GBC port) main task chain
static void Task_CrystalScene_UnownA_Load(u8);
static void Task_CrystalScene_UnownA(u8);
static void Task_CrystalScene_Panorama1_Load(u8);
static void Task_CrystalScene_Panorama1(u8);
static void Task_CrystalScene_UnownHI_Load(u8);
static void Task_CrystalScene_UnownHI(u8);
static void Task_CrystalScene_SuicuneRun_Load(u8);
static void Task_CrystalScene_SuicuneRun(u8);
static void Task_CrystalScene_Grass_Load(u8);
static void Task_CrystalScene_Grass(u8);
static void Task_CrystalScene_Unowns_Load(u8);
static void Task_CrystalScene_Unowns(u8);
static void Task_CrystalScene_Approach_Load(u8);
static void Task_CrystalScene_Approach(u8);
static void Task_CrystalScene_Jump_Load(u8);
static void Task_CrystalScene_Jump(u8);
static void Task_CrystalScene_Close_Load(u8);
static void Task_CrystalScene_Close(u8);
static void Task_CrystalScene_Back_Load(u8);
static void Task_CrystalScene_Back(u8);
static void Task_CrystalScene_Silhouette(u8);
static void Task_CrystalScene_CrystalUnowns_Load(u8);
static void Task_CrystalScene_CrystalUnowns(u8);

// Crystal intro sprite callbacks
static void SpriteCB_CrystalPulse(struct Sprite *);
static void SpriteCB_CrystalSuicune(struct Sprite *);
static void SpriteCB_CrystalHop(struct Sprite *);
static void SpriteCB_CrystalBob(struct Sprite *);


static void MainCB2_EndIntro(void);

enum {
    COPYRIGHT_INITIALIZE,
    COPYRIGHT_EMULATOR_BLEND,
    COPYRIGHT_START_FADE = 140,
    COPYRIGHT_START_INTRO,
};


#define TAG_DITTO_GAMEFREAK_TILESHEET 2004



#define COLOSSEUM_GAME_CODE 0x65366347 // "Gc6e" in ASCII

// Used by various tasks and sprites
#define tState data[0]
#define sState data[0]

/*
    gIntroFrameCounter is used as a persistent timer throughout the
    intro cinematic. At various points it's used to determine when
    to trigger actions or progress through the cutscene.
    The values for these are defined contiguously below.
*/
#define DITTO_FALL_START_Y              -64
#define DITTO_FALL_END_Y                 50
#define DITTO_FALL_DURATION              18
#define TIMER_LC_LOGO_END               300 // When the Ditto logo/LAZ screen fades into the Crystal intro
#define LAZ_BG_SCREENBASE                31
#define LAZ_BG_CHARBASE                   0
#define LAZ_TILE_START                    1
#define LAZ_PALETTE_SLOT                  1

COMMON_DATA u32 gIntroFrameCounter = 0;
COMMON_DATA struct GcmbStruct gMultibootProgramStruct = {0};



static const u16 sIntroDittoGamefreakTilesheet_Pal[] = INCGFX_U16("graphics/intro/ditto_gamefreak_tilesheet.png", ".gbapal");
static const u16 sIntroLaz_Pal[] = INCGFX_U16("graphics/intro/laz.png", ".gbapal");
static const u32 sIntroLaz_Gfx[] = INCGFX_U32("graphics/intro/laz.png", ".4bpp.smol");
static const u16 sIntroLaz_Tilemap[] = INCBIN_U16("graphics/intro/laz.bin");



static const struct CompressedSpriteSheet sSpriteSheet_ditto_gamefreak_tilesheet[] =
{
    {gIntroDittoGamefreakTilesheet_Gfx, 0x8000, TAG_DITTO_GAMEFREAK_TILESHEET},
    {},
};

static const struct SpritePalette sSpritePalette_DittoGamefreakTilesheet[] =
{
    {sIntroDittoGamefreakTilesheet_Pal, TAG_DITTO_GAMEFREAK_TILESHEET},
    {},
};

static const struct OamData sOamData_DittoGamefreak =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sAnim_DittoGamefreak[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(32, 6),
    ANIMCMD_FRAME(64, 6),
    ANIMCMD_FRAME(96, 6),
    ANIMCMD_FRAME(128, 6),
    ANIMCMD_FRAME(160, 6),
    ANIMCMD_FRAME(192, 6),
    ANIMCMD_FRAME(224, 6),
    ANIMCMD_FRAME(256, 6),
    ANIMCMD_FRAME(288, 6),
    ANIMCMD_FRAME(320, 6),
    ANIMCMD_FRAME(352, 6),
    ANIMCMD_FRAME(384, 6),
    ANIMCMD_FRAME(416, 6),
    ANIMCMD_FRAME(448, 6),
    ANIMCMD_FRAME(480, 6),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnims_DittoGamefreak[] =
{
    sAnim_DittoGamefreak,
};

static const struct SpriteTemplate sSpriteTemplate_DittoGamefreak =
{
    .tileTag = TAG_DITTO_GAMEFREAK_TILESHEET,
    .paletteTag = TAG_DITTO_GAMEFREAK_TILESHEET,
    .oam = &sOamData_DittoGamefreak,
    .anims = sAnims_DittoGamefreak,
    .callback = SpriteCallbackDummy,
};

static void ShowLazText(void)
{
    DmaClear16(3, (void *)BG_CHAR_ADDR(LAZ_BG_CHARBASE), 0x20);
    DecompressDataWithHeaderVram(sIntroLaz_Gfx, (void *)(BG_CHAR_ADDR(LAZ_BG_CHARBASE) + LAZ_TILE_START * 0x20));
    DmaCopy16(3, sIntroLaz_Tilemap, (void *)BG_SCREEN_ADDR(LAZ_BG_SCREENBASE), BG_SCREEN_SIZE);
    LoadPalette(sIntroLaz_Pal, BG_PLTT_ID(LAZ_PALETTE_SLOT), sizeof(sIntroLaz_Pal));

    SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(LAZ_BG_CHARBASE) | BGCNT_SCREENBASE(LAZ_BG_SCREENBASE) | BGCNT_16COLOR | BGCNT_TXT256x256);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG0_ON);
}

static void VBlankCB_Intro(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ScanlineEffect_InitHBlankDmaTransfer();
}

void MainCB2_Intro(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    if (gMain.newKeys != 0 && !gPaletteFade.active)
        SetMainCallback2(MainCB2_EndIntro);
    else if (gIntroFrameCounter != -1)
        gIntroFrameCounter++;
}

static void MainCB2_EndIntro(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitTitleScreen);
}

static void LoadCopyrightGraphics(u16 tilesetAddress, u16 tilemapAddress, u16 paletteOffset)
{
    DecompressDataWithHeaderVram(gIntroCopyright_Gfx, (void *)(VRAM + tilesetAddress));
    DecompressDataWithHeaderVram(gIntroCopyright_Tilemap, (void *)(VRAM + tilemapAddress));
    LoadPalette(gIntroCopyright_Pal, paletteOffset, PLTT_SIZE_4BPP);
}

static void SerialCB_CopyrightScreen(void)
{
    GameCubeMultiBoot_HandleSerialInterrupt(&gMultibootProgramStruct);
}

static u8 SetUpCopyrightScreen(void)
{
    switch (gMain.state)
    {
    case COPYRIGHT_INITIALIZE:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        *(u16 *)PLTT = RGB_WHITE;
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        CpuFill32(0, (void *)VRAM, VRAM_SIZE);
        CpuFill32(0, (void *)OAM, OAM_SIZE);
        CpuFill16(0, (void *)(PLTT + 2), PLTT_SIZE - 2);
        ResetPaletteFade();
        LoadCopyrightGraphics(0, 0x3800, BG_PLTT_ID(0));
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_WHITEALPHA);
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_SCREENBASE(7)
                                   | BGCNT_16COLOR
                                   | BGCNT_TXT256x256);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetVBlankCallback(VBlankCB_Intro);
        REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON;
        SetSerialCallback(SerialCB_CopyrightScreen);
        GameCubeMultiBoot_Init(&gMultibootProgramStruct);
    // REG_DISPCNT needs to be overwritten the second time, because otherwise the intro won't show up on VBA 1.7.2 and John GBA Lite emulators.
    // The REG_DISPCNT overwrite is NOT needed in m-GBA, No$GBA, VBA 1.8.0, My Boy and Pizza Boy GBA emulators.
    case COPYRIGHT_EMULATOR_BLEND:
        REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON;
    default:
        UpdatePaletteFade();
        gMain.state++;
        GameCubeMultiBoot_Main(&gMultibootProgramStruct);
        break;
    case COPYRIGHT_START_FADE:
        GameCubeMultiBoot_Main(&gMultibootProgramStruct);
        if (gMultibootProgramStruct.gcmb_field_2 != 1)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gMain.state++;
        }
        break;
    case COPYRIGHT_START_INTRO:
        if (UpdatePaletteFade())
            break;

        CreateTask(Task_Scene1_Load, 0);
        SetMainCallback2(MainCB2_Intro);

        if (gMultibootProgramStruct.gcmb_field_2 != 0)
        {
            if (gMultibootProgramStruct.gcmb_field_2 == 2)
            {
                // check the multiboot ROM header game code to see if we already did this
                if (*(u32 *)(EWRAM_START + 0xAC) == COLOSSEUM_GAME_CODE)
                {
                    CpuCopy16(&gMultiBootProgram_PokemonColosseum_Start, (void *)EWRAM_START, sizeof(gMultiBootProgram_PokemonColosseum_Start));
                    *(u32 *)(EWRAM_START + 0xAC) = COLOSSEUM_GAME_CODE;
                }
                GameCubeMultiBoot_ExecuteProgram(&gMultibootProgramStruct);
            }
        }
        else
        {
            GameCubeMultiBoot_Quit();
            SetSerialCallback(SerialCB);
        }
        return 0;
    }

    return 1;
}

void CB2_InitCopyrightScreenAfterBootup(void)
{
    if (!SetUpCopyrightScreen())
    {
        SetSaveBlocksPointers(GetSaveBlocksPointersBaseOffset());
        ResetMenuAndMonGlobals();
        Save_ResetSaveCounters();
        LoadGameSave(SAVE_NORMAL);
        if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
            Sav2_ClearSetDefault();
        SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
        InitHeap(gHeap, HEAP_SIZE);
    }
}

void CB2_InitCopyrightScreenAfterTitleScreen(void)
{
    SetUpCopyrightScreen();
}

#define tDittoSpriteId data[0]
#define tLazShown      data[1]

void Task_Scene1_Load(u8 taskId)
{
    SetVBlankCallback(NULL);
    IntroResetGpuRegs();

    LoadCompressedSpriteSheet(sSpriteSheet_ditto_gamefreak_tilesheet);
    LoadSpritePalettes(sSpritePalette_DittoGamefreakTilesheet);

    gTasks[taskId].func = Task_Scene1_DittoLogo;
}

static void Task_Scene1_DittoLogo(u8 taskId)
{
    // BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    // Clear the stale copyright-screen colors out of BG palette 0 so the
    // fade out of this scene starts from the black backdrop instead of
    // popping back to the copyright screen's gray background
    CpuFill16(RGB_BLACK, &gPlttBufferUnfaded[BG_PLTT_ID(0)], PLTT_SIZE_4BPP);
    CpuFill16(RGB_BLACK, &gPlttBufferFaded[BG_PLTT_ID(0)], PLTT_SIZE_4BPP);
    SetVBlankCallback(VBlankCB_Intro);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    gTasks[taskId].tDittoSpriteId = CreateSprite(&sSpriteTemplate_DittoGamefreak, DISPLAY_WIDTH / 2, DITTO_FALL_START_Y, 0);
    gTasks[taskId].tLazShown = FALSE;
    gTasks[taskId].func = Task_Scene1_DittoAnimation;
    gIntroFrameCounter = 0;
    // m4aSongNumStart(MUS_INTRO);
    ResetSerial();
}


static void Task_Scene1_DittoAnimation(u8 taskId)
{
    if (gIntroFrameCounter < DITTO_FALL_DURATION)
        gSprites[gTasks[taskId].tDittoSpriteId].y = DITTO_FALL_START_Y + ((DITTO_FALL_END_Y - DITTO_FALL_START_Y) * gIntroFrameCounter) / DITTO_FALL_DURATION;
    else
        gSprites[gTasks[taskId].tDittoSpriteId].y = DITTO_FALL_END_Y;

    if (!gTasks[taskId].tLazShown && gIntroFrameCounter >= DITTO_FALL_DURATION)
    {
        ShowLazText();
        gTasks[taskId].tLazShown = TRUE;
    }

    if (gIntroFrameCounter > TIMER_LC_LOGO_END)
    {
        // Fade out the logo and start the Crystal intro cinematic
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_Scene1_End;
    }
}

static void Task_Scene1_End(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_CrystalScene_UnownA_Load;
}

#undef tDittoSpriteId
#undef tLazShown

// GBC screen (160x144) centered on the GBA screen (240x160)
#define CI_SCREEN_X 40
#define CI_SCREEN_Y 8
#define CI_BG_HOFS ((u16)-CI_SCREEN_X)
#define CI_BG_VOFS ((u16)-CI_SCREEN_Y)

// Panorama parallax bands (GBA scanlines)
#define CI_PANORAMA_TOP        (CI_SCREEN_Y)
#define CI_PANORAMA_TREE_END   (CI_SCREEN_Y + 0x5F)
#define CI_PANORAMA_BOTTOM     (CI_SCREEN_Y + 144)

#define TAG_CI_SUICUNE 3000
#define TAG_CI_PICHU   3001
#define TAG_CI_WOOPER  3002
#define TAG_CI_UNOWN   3003
#define TAG_CI_PULSE   3004

// BG scene data
static const u32 sCI_UnownsTiles[]        = INCGFX_U32("graphics/intro/crystal/unowns_tiles.png", ".4bpp.smol");
static const u32 sCI_UnownAMap[]          = INCGFX_U32("graphics/intro/crystal/unown_a_map.bin", ".smolTM");
static const u32 sCI_UnownHIMap[]         = INCGFX_U32("graphics/intro/crystal/unown_hi_map.bin", ".smolTM");
static const u32 sCI_UnownsMap[]          = INCGFX_U32("graphics/intro/crystal/unowns_map.bin", ".smolTM");
static const u32 sCI_BackgroundTiles[]    = INCGFX_U32("graphics/intro/crystal/background_tiles.png", ".4bpp.smol");
static const u32 sCI_BackgroundMap[]      = INCGFX_U32("graphics/intro/crystal/background_map.bin", ".smolTM");
static const u16 sCI_BackgroundPal[]      = INCGFX_U16("graphics/intro/crystal/background.pal", ".gbapal");
static const u32 sCI_Grass1Gfx[]          = INCGFX_U32("graphics/intro/crystal/grass1.png", ".4bpp");
static const u32 sCI_Grass2Gfx[]          = INCGFX_U32("graphics/intro/crystal/grass2.png", ".4bpp");
static const u32 sCI_Grass3Gfx[]          = INCGFX_U32("graphics/intro/crystal/grass3.png", ".4bpp");
static const u32 sCI_SuicuneJumpTiles[]   = INCGFX_U32("graphics/intro/crystal/suicune_jump_tiles.png", ".4bpp.smol");
static const u32 sCI_SuicuneJumpMap[]     = INCGFX_U32("graphics/intro/crystal/suicune_jump_map.bin", ".smolTM");
static const u32 sCI_SuicuneJumpMap2[]    = INCGFX_U32("graphics/intro/crystal/suicune_jump_map2.bin", ".smolTM");
static const u16 sCI_SuicunePal[]         = INCGFX_U16("graphics/intro/crystal/suicune.pal", ".gbapal");
static const u32 sCI_SuicuneCloseTiles[]  = INCGFX_U32("graphics/intro/crystal/suicune_close_tiles.png", ".4bpp.smol");
static const u32 sCI_SuicuneCloseMap[]    = INCGFX_U32("graphics/intro/crystal/suicune_close_map.bin", ".smolTM");
static const u16 sCI_SuicuneClosePal[]    = INCGFX_U16("graphics/intro/crystal/suicune_close.pal", ".gbapal");
static const u32 sCI_SuicuneBackTiles[]   = INCGFX_U32("graphics/intro/crystal/suicune_back_tiles.png", ".4bpp.smol");
static const u32 sCI_SuicuneBackMap[]     = INCGFX_U32("graphics/intro/crystal/suicune_back_map.bin", ".smolTM");
static const u32 sCI_SuicuneBackMap2[]    = INCGFX_U32("graphics/intro/crystal/suicune_back_map2.bin", ".smolTM");
static const u32 sCI_CrystalUnownsTiles[] = INCGFX_U32("graphics/intro/crystal/crystal_unowns_tiles.png", ".4bpp.smol");
static const u32 sCI_CrystalUnownsMap[]   = INCGFX_U32("graphics/intro/crystal/crystal_unowns_map.bin", ".smolTM");
static const u16 sCI_CrystalUnownsPal[]   = INCGFX_U16("graphics/intro/crystal/crystal_unowns.pal", ".gbapal");

// Sprite data
static const u32 sCI_SuicuneRunGfx[]      = INCGFX_U32("graphics/intro/crystal/suicune_run.png", ".4bpp.smol");
static const u16 sCI_SuicuneRunPal[]      = INCGFX_U16("graphics/intro/crystal/suicune_run.png", ".gbapal");
static const u32 sCI_PichuGfx[]           = INCGFX_U32("graphics/intro/crystal/pichu.png", ".4bpp.smol");
static const u16 sCI_PichuPal[]           = INCGFX_U16("graphics/intro/crystal/pichu.png", ".gbapal");
static const u32 sCI_WooperGfx[]          = INCGFX_U32("graphics/intro/crystal/wooper.png", ".4bpp.smol");
static const u16 sCI_WooperPal[]          = INCGFX_U16("graphics/intro/crystal/wooper.png", ".gbapal");
static const u32 sCI_UnownBackGfx[]       = INCGFX_U32("graphics/intro/crystal/unown_back.png", ".4bpp.smol");
static const u16 sCI_UnownBackPal[]       = INCGFX_U16("graphics/intro/crystal/unown_back.png", ".gbapal");
static const u32 sCI_PulseGfx[]           = INCGFX_U32("graphics/intro/crystal/pulse.png", ".4bpp.smol");
static const u16 sCI_PulsePal[]           = INCGFX_U16("graphics/intro/crystal/pulse.png", ".gbapal");

static const struct CompressedSpriteSheet sCI_SpriteSheet_Suicune   = {sCI_SuicuneRunGfx, 0x2000, TAG_CI_SUICUNE};
static const struct CompressedSpriteSheet sCI_SpriteSheet_Pichu     = {sCI_PichuGfx, 0x1800, TAG_CI_PICHU};
static const struct CompressedSpriteSheet sCI_SpriteSheet_Wooper    = {sCI_WooperGfx, 0x200, TAG_CI_WOOPER};
static const struct CompressedSpriteSheet sCI_SpriteSheet_UnownBack = {sCI_UnownBackGfx, 0x600, TAG_CI_UNOWN};
static const struct CompressedSpriteSheet sCI_SpriteSheet_Pulse     = {sCI_PulseGfx, 0x3800, TAG_CI_PULSE};

static const struct SpritePalette sCI_SpritePalette_Suicune   = {sCI_SuicuneRunPal, TAG_CI_SUICUNE};
static const struct SpritePalette sCI_SpritePalette_Pichu     = {sCI_PichuPal, TAG_CI_PICHU};
static const struct SpritePalette sCI_SpritePalette_Wooper    = {sCI_WooperPal, TAG_CI_WOOPER};
static const struct SpritePalette sCI_SpritePalette_UnownBack = {sCI_UnownBackPal, TAG_CI_UNOWN};
static const struct SpritePalette sCI_SpritePalette_Pulse     = {sCI_PulsePal, TAG_CI_PULSE};

static const struct OamData sCI_OamData_64x64 =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 0,
};
static const struct OamData sCI_OamData_32x32 =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 0,
};

static const union AnimCmd sCI_Anim_SuicuneRun[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_FRAME(128, 4),
    ANIMCMD_FRAME(192, 4),
    ANIMCMD_JUMP(0),
};
static const union AnimCmd *const sCI_Anims_Suicune[] = {sCI_Anim_SuicuneRun};

static const union AnimCmd sCI_Anim_Pichu[] =
{
    ANIMCMD_FRAME(0, 24),
    ANIMCMD_FRAME(64, 6),
    ANIMCMD_FRAME(128, 6),
    ANIMCMD_END,
};
static const union AnimCmd *const sCI_Anims_Pichu[] = {sCI_Anim_Pichu};

static const union AnimCmd sCI_Anim_SingleFrame32[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};
static const union AnimCmd *const sCI_Anims_SingleFrame32[] = {sCI_Anim_SingleFrame32};

// One anim per pulse ring radius (7 frames of 64x64 = 64 tiles each)
#define CI_PULSE_FRAME(n) \
static const union AnimCmd sCI_Anim_Pulse##n[] = \
{ \
    ANIMCMD_FRAME((n) * 64, 8), \
    ANIMCMD_END, \
}
CI_PULSE_FRAME(0);
CI_PULSE_FRAME(1);
CI_PULSE_FRAME(2);
CI_PULSE_FRAME(3);
CI_PULSE_FRAME(4);
CI_PULSE_FRAME(5);
CI_PULSE_FRAME(6);
static const union AnimCmd *const sCI_Anims_Pulse[] =
{
    sCI_Anim_Pulse0,
    sCI_Anim_Pulse1,
    sCI_Anim_Pulse2,
    sCI_Anim_Pulse3,
    sCI_Anim_Pulse4,
    sCI_Anim_Pulse5,
    sCI_Anim_Pulse6,
};

static const struct SpriteTemplate sCI_SpriteTemplate_Suicune =
{
    .tileTag = TAG_CI_SUICUNE,
    .paletteTag = TAG_CI_SUICUNE,
    .oam = &sCI_OamData_64x64,
    .anims = sCI_Anims_Suicune,
    .callback = SpriteCB_CrystalSuicune,
};
static const struct SpriteTemplate sCI_SpriteTemplate_Pichu =
{
    .tileTag = TAG_CI_PICHU,
    .paletteTag = TAG_CI_PICHU,
    .oam = &sCI_OamData_64x64,
    .anims = sCI_Anims_Pichu,
    .callback = SpriteCB_CrystalHop,
};
static const struct SpriteTemplate sCI_SpriteTemplate_Wooper =
{
    .tileTag = TAG_CI_WOOPER,
    .paletteTag = TAG_CI_WOOPER,
    .oam = &sCI_OamData_32x32,
    .anims = sCI_Anims_SingleFrame32,
    .callback = SpriteCB_CrystalHop,
};
static const struct SpriteTemplate sCI_SpriteTemplate_UnownBack =
{
    .tileTag = TAG_CI_UNOWN,
    .paletteTag = TAG_CI_UNOWN,
    .oam = &sCI_OamData_32x32,
    .anims = sCI_Anims_SingleFrame32,
    .callback = SpriteCB_CrystalBob,
};
static const struct SpriteTemplate sCI_SpriteTemplate_Pulse =
{
    .tileTag = TAG_CI_PULSE,
    .paletteTag = TAG_CI_PULSE,
    .oam = &sCI_OamData_64x64,
    .anims = sCI_Anims_Pulse,
    .callback = SpriteCB_CrystalPulse,
};

static const u16 sCI_AppearUnownColors[4] =
{
    RGB(24, 12, 9), RGB(31, 31, 31), RGB(12, 0, 31), RGB(0, 0, 0),
};

// Task data
#define tTimer    data[1]
#define tTreeX    data[2]
#define tGrassX   data[3]
#define tSpriteId data[4]
#define tScroll   data[5]
#define tMapFrame data[6]

//--------------------------------------------------------------- BG helpers

#define CI_BGCNT_256 (BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(28) | BGCNT_16COLOR | BGCNT_TXT256x256)
#define CI_BGCNT_ALT (BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(29) | BGCNT_16COLOR | BGCNT_TXT256x256)
#define CI_BGCNT_512 (BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(28) | BGCNT_16COLOR | BGCNT_TXT512x256)

static void CrystalIntro_InitBg(u16 bgCnt)
{
    SetGpuReg(REG_OFFSET_BG0CNT, bgCnt);
    SetGpuReg(REG_OFFSET_BG0HOFS, CI_BG_HOFS);
    SetGpuReg(REG_OFFSET_BG0VOFS, CI_BG_VOFS);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_OBJ_ON);
}

static void CrystalIntro_LoadBg(const u32 *tiles, const u32 *map)
{
    DecompressDataWithHeaderVram(tiles, (void *)BG_CHAR_ADDR(0));
    DecompressDataWithHeaderVram(map, (void *)BG_SCREEN_ADDR(28));
}

// Set all 8 BG palettes used by the Unown scenes to black
static void CrystalIntro_BlackenBgPals(void)
{
    CpuFill16(RGB_BLACK, &gPlttBufferUnfaded[BG_PLTT_ID(0)], 8 * PLTT_SIZE_4BPP);
    CpuFill16(RGB_BLACK, &gPlttBufferFaded[BG_PLTT_ID(0)], 8 * PLTT_SIZE_4BPP);
}

static void CrystalIntro_UnownFadePal(u8 palNum, u8 val)
{
    u8 v = val & 63;

    if (v > 31)
        v = 63 - v;
    CrystalIntro_BlackenBgPals();
    gPlttBufferFaded[BG_PLTT_ID(palNum) + 2] = RGB(v, v, v);
    gPlttBufferFaded[BG_PLTT_ID(palNum) + 3] = RGB(0, v / 2, v);
    gPlttBufferFaded[BG_PLTT_ID(palNum) + 4] = RGB(0, 0, v);
}

static void CrystalIntro_UpdatePanoramaScroll(u16 treeX, u16 grassX)
{
    int i;

    for (i = 0; i < DISPLAY_HEIGHT; i++)
    {
        u16 x = 0;
        if (i >= CI_PANORAMA_TOP && i < CI_PANORAMA_TREE_END)
            x = treeX;
        else if (i >= CI_PANORAMA_TREE_END && i < CI_PANORAMA_BOTTOM)
            x = grassX;
        gScanlineEffectRegBuffers[0][i] = x;
        gScanlineEffectRegBuffers[1][i] = x;
    }
}

static void CrystalIntro_StartPanoramaScanlineEffect(void)
{
    struct ScanlineEffectParams params;

    ScanlineEffect_Clear();
    params.dmaDest = &REG_BG0HOFS;
    params.dmaControl = SCANLINE_EFFECT_DMACNT_16BIT;
    params.initState = 1;
    params.unused9 = 0;
    ScanlineEffect_SetParams(params);
}

static void CrystalIntro_LoadPanorama(u8 taskId)
{
    CrystalIntro_LoadBg(sCI_BackgroundTiles, sCI_BackgroundMap);
    LoadPalette(sCI_BackgroundPal, BG_PLTT_ID(0), sizeof(sCI_BackgroundPal));
    CrystalIntro_InitBg(CI_BGCNT_256);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0); // panorama wraps, use the full GBA width
    CrystalIntro_UpdatePanoramaScroll(gTasks[taskId].tTreeX, gTasks[taskId].tGrassX);
    CrystalIntro_StartPanoramaScanlineEffect();
}

//------------------------------------------------------------------ sprites

#define sTimer  data[1]
#define sMatrix data[2]
#define sRadius data[3]
#define sDelay  data[4]

#define CI_PULSE_MAX_DRAWN_RADIUS 28
#define CI_PULSE_MAX_RADIUS       56

static void SpriteCB_CrystalPulse(struct Sprite *sprite)
{
    if (sprite->sDelay != 0)
    {
        sprite->sDelay--;
        return;
    }
    if (sprite->sRadius == 0)
    {
        sprite->invisible = FALSE;
        sprite->oam.affineMode = ST_OAM_AFFINE_DOUBLE;
        sprite->oam.matrixNum = sprite->sMatrix;
        CalcCenterToCornerVec(sprite, SPRITE_SHAPE(64x64), SPRITE_SIZE(64x64), ST_OAM_AFFINE_DOUBLE);
        SetOamMatrix(sprite->sMatrix, 256, 0, 0, 256);
        sprite->sRadius = 4;
        return;
    }
    sprite->sRadius += 2;
    if (sprite->sRadius > CI_PULSE_MAX_RADIUS)
    {
        DestroySprite(sprite);
        return;
    }
    if (sprite->sRadius <= CI_PULSE_MAX_DRAWN_RADIUS)
    {
        if (((sprite->sRadius - 4) & 3) == 0)
            StartSpriteAnim(sprite, (sprite->sRadius - 4) / 4);
    }
    else
    {
        // 256 * CI_PULSE_MAX_DRAWN_RADIUS / radius
        u16 scale = 7168 / sprite->sRadius;
        SetOamMatrix(sprite->sMatrix, scale, 0, 0, scale);
    }
}

static void CrystalIntro_CreatePulse(s16 x, s16 y)
{
    u8 spriteId = CreateSprite(&sCI_SpriteTemplate_Pulse, x, y, 2);

    if (spriteId != MAX_SPRITES)
    {
        gSprites[spriteId].invisible = TRUE;
        gSprites[spriteId].sMatrix = 8;
    }
}

enum {
    CI_SUICUNE_IDLE,     // Runs in place
    CI_SUICUNE_RUN,      // Runs left across the screen
    CI_SUICUNE_RUN_SLOW, // Creeps left slowly
    CI_SUICUNE_DASH,     // Dashes off screen
};

static void SpriteCB_CrystalSuicune(struct Sprite *sprite)
{
    switch (sprite->sState)
    {
    case CI_SUICUNE_IDLE:
        break;
    case CI_SUICUNE_RUN:
    case CI_SUICUNE_DASH:
        sprite->x -= 8;
        break;
    case CI_SUICUNE_RUN_SLOW:
        sprite->x -= 2;
        break;
    }
    if (sprite->sState != CI_SUICUNE_IDLE && sprite->x < -64)
        DestroySprite(sprite);
}

// Single hop out of the grass for Pichu/Wooper
static void SpriteCB_CrystalHop(struct Sprite *sprite)
{
    if (sprite->sTimer < 128)
    {
        sprite->sTimer += 3;
        if (sprite->sTimer > 128)
            sprite->sTimer = 128;
        sprite->y2 = -Sin(sprite->sTimer, 8);
    }
    else
    {
        sprite->y2 = 0;
        sprite->callback = SpriteCallbackDummy;
    }
}

// Gentle floating for the Unown sprite
static void SpriteCB_CrystalBob(struct Sprite *sprite)
{
    sprite->sTimer += 2;
    sprite->y2 = Sin(sprite->sTimer & 0xFF, 3);
}

//------------------------------------------------- scene: Unown A fades in

static void Task_CrystalScene_UnownA_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_Pulse);
    LoadSpritePalette(&sCI_SpritePalette_Pulse);
    CrystalIntro_BlackenBgPals();
    CrystalIntro_LoadBg(sCI_UnownsTiles, sCI_UnownAMap);
    CrystalIntro_InitBg(CI_BGCNT_256);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_UnownA;
}

// Frames of black screen before the first Unown starts fading in
#define CI_UNOWN_A_START_DELAY 48

static void Task_CrystalScene_UnownA(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= CI_UNOWN_A_START_DELAY + 0x80)
    {
        gTasks[taskId].func = Task_CrystalScene_Panorama1_Load;
        return;
    }
    if (tTimer == CI_UNOWN_A_START_DELAY + 0x60)
        CrystalIntro_CreatePulse(CI_SCREEN_X + 80, CI_SCREEN_Y + 72); // on the Unown's eye
    if (tTimer >= CI_UNOWN_A_START_DELAY)
        CrystalIntro_UnownFadePal(0, tTimer - CI_UNOWN_A_START_DELAY);
    tTimer++;
}

//------------------------------------------------- scene: scrolling panorama

static void Task_CrystalScene_Panorama1_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    gTasks[taskId].tTreeX = 0;
    gTasks[taskId].tGrassX = 0;
    CrystalIntro_LoadPanorama(taskId);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Panorama1;
}

static void Task_CrystalScene_Panorama1(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    // Fade out to black before the next Unown scene
    if (tTimer == 0x80 - 32)
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    if (tTimer >= 0x80)
    {
        if (!gPaletteFade.active)
        {
            ScanlineEffect_Stop();
            gTasks[taskId].func = Task_CrystalScene_UnownHI_Load;
        }
        return;
    }
    if (tTimer & 1)
        tTreeX++;
    tGrassX += 2;
    CrystalIntro_UpdatePanoramaScroll(tTreeX, tGrassX);
    tTimer++;
}

//------------------------------------------------- scene: Unowns H and I

static void Task_CrystalScene_UnownHI_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_Pulse);
    LoadSpritePalette(&sCI_SpritePalette_Pulse);
    CrystalIntro_BlackenBgPals();
    CrystalIntro_LoadBg(sCI_UnownsTiles, sCI_UnownHIMap);
    CrystalIntro_InitBg(CI_BGCNT_256);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_UnownHI;
}

static void Task_CrystalScene_UnownHI(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0x80)
    {
        gTasks[taskId].func = Task_CrystalScene_SuicuneRun_Load;
        return;
    }
    if (tTimer == 0x20)
        CrystalIntro_CreatePulse(CI_SCREEN_X + 112, CI_SCREEN_Y + 40);
    if (tTimer == 0x60)
        CrystalIntro_CreatePulse(CI_SCREEN_X + 40, CI_SCREEN_Y + 96);
    if (tTimer < 0x40)
        CrystalIntro_UnownFadePal(0, tTimer);
    else
        CrystalIntro_UnownFadePal(1, tTimer);
    tTimer++;
}

//------------------------------------------------- scene: Suicune runs past

static void Task_CrystalScene_SuicuneRun_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_Suicune);
    LoadSpritePalette(&sCI_SpritePalette_Suicune);
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_Pichu);
    LoadSpritePalette(&sCI_SpritePalette_Pichu);
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_Wooper);
    LoadSpritePalette(&sCI_SpritePalette_Wooper);
    CrystalIntro_LoadPanorama(taskId);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_SuicuneRun;
}

static void Task_CrystalScene_SuicuneRun(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0x70)
    {
        gTasks[taskId].func = Task_CrystalScene_Grass_Load;
        return;
    }
    if (tTimer < 0x40)
    {
        // Keep scrolling until the camera "stops" to watch Suicune
        if (tTimer & 1)
            tTreeX++;
        tGrassX += 2;
        CrystalIntro_UpdatePanoramaScroll(tTreeX, tGrassX);
    }
    else if (tTimer == 0x40)
    {
        u8 spriteId = CreateSprite(&sCI_SpriteTemplate_Suicune, DISPLAY_WIDTH + 64, 107, 1);
        if (spriteId != MAX_SPRITES)
            gSprites[spriteId].sState = CI_SUICUNE_RUN;
    }
    tTimer++;
}

//------------------------------------------------- scene: Pichu and Wooper

static void Task_CrystalScene_Grass_Load(u8 taskId)
{
    // Same panorama stays loaded; the camera just sits still now
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Grass;
}

static void Task_CrystalScene_Grass(u8 taskId)
{
    static const u32 *const grassFrames[] = {sCI_Grass1Gfx, sCI_Grass2Gfx, sCI_Grass3Gfx, sCI_Grass2Gfx};
    s16 *data = gTasks[taskId].data;

    // Fade out to black before the Unown scene
    if (tTimer == 0xC0 - 32)
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    if (tTimer >= 0xC0)
    {
        if (!gPaletteFade.active)
            gTasks[taskId].func = Task_CrystalScene_Unowns_Load;
        return;
    }
    // Rustle the grass tiles as the Pokémon stir
    if (tTimer < 36 && (tTimer & 3) == 0)
        CpuCopy16(grassFrames[(tTimer >> 2) & 3], (void *)(BG_CHAR_ADDR(0) + 9 * TILE_SIZE_4BPP), 4 * TILE_SIZE_4BPP);
    if (tTimer == 0x20)
        CreateSprite(&sCI_SpriteTemplate_Wooper, 76, 132, 1);
    if (tTimer == 0x40)
        CreateSprite(&sCI_SpriteTemplate_Pichu, 172, 132, 1);
    tTimer++;
}

//------------------------------------------------- scene: many Unowns

static void Task_CrystalScene_Unowns_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    ScanlineEffect_Stop();
    CrystalIntro_BlackenBgPals();
    CrystalIntro_LoadBg(sCI_UnownsTiles, sCI_UnownsMap);
    CrystalIntro_InitBg(CI_BGCNT_256);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Unowns;
}

static void Task_CrystalScene_Unowns(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0xC0)
    {
        gTasks[taskId].func = Task_CrystalScene_Approach_Load;
        return;
    }
    if (tTimer < 0x80)
    {
        // One Unown at a time, palettes 0-3
        CrystalIntro_UnownFadePal((tTimer >> 5) & 3, (tTimer & 0x1F) << 1);
    }
    else
    {
        // Double speed, palettes 4-7
        CrystalIntro_UnownFadePal(4 + ((tTimer >> 4) & 3), (tTimer & 0xF) << 2);
    }
    tTimer++;
}

//------------------------------------------- scene: Suicune runs and jumps

static void Task_CrystalScene_Approach_Load(u8 taskId)
{
    u8 spriteId;

    ResetSpriteData();
    FreeAllSpritePalettes();
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_Suicune);
    LoadSpritePalette(&sCI_SpritePalette_Suicune);
    CrystalIntro_LoadBg(sCI_BackgroundTiles, sCI_BackgroundMap);
    LoadPalette(sCI_BackgroundPal, BG_PLTT_ID(0), sizeof(sCI_BackgroundPal));
    CrystalIntro_InitBg(CI_BGCNT_256);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    spriteId = CreateSprite(&sCI_SpriteTemplate_Suicune, CI_SCREEN_X + 88, 107, 1);
    if (spriteId != MAX_SPRITES)
        gSprites[spriteId].sState = CI_SUICUNE_IDLE;
    gTasks[taskId].tSpriteId = spriteId;
    gTasks[taskId].tScroll = 0;
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Approach;
}

static void Task_CrystalScene_Approach(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0x80)
    {
        gTasks[taskId].func = Task_CrystalScene_Jump_Load;
        return;
    }
    // The whole background rushes by while Suicune runs
    tScroll -= 10;
    SetGpuReg(REG_OFFSET_BG0HOFS, tScroll);
    if (tTimer == 0x40)
        gSprites[gTasks[taskId].tSpriteId].sState = CI_SUICUNE_RUN_SLOW;
    if (tTimer == 0x60)
        gSprites[gTasks[taskId].tSpriteId].sState = CI_SUICUNE_DASH;
    tTimer++;
}

//------------------------------------------------- scene: Suicune's leap

static void Task_CrystalScene_Jump_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    LoadCompressedSpriteSheet(&sCI_SpriteSheet_UnownBack);
    LoadSpritePalette(&sCI_SpritePalette_UnownBack);
    DecompressDataWithHeaderVram(sCI_SuicuneJumpTiles, (void *)BG_CHAR_ADDR(0));
    DecompressDataWithHeaderVram(sCI_SuicuneJumpMap, (void *)BG_SCREEN_ADDR(28));
    DecompressDataWithHeaderVram(sCI_SuicuneJumpMap2, (void *)BG_SCREEN_ADDR(29));
    LoadPalette(sCI_SuicunePal, BG_PLTT_ID(0), sizeof(sCI_SuicunePal));
    // Orange backdrop so transparent tiles match the scene's orange background
    gPlttBufferUnfaded[0] = RGB(24, 12, 9);
    gPlttBufferFaded[0] = RGB(24, 12, 9);
    CrystalIntro_InitBg(CI_BGCNT_256);
    CreateSprite(&sCI_SpriteTemplate_UnownBack, CI_SCREEN_X + 40, CI_SCREEN_Y + 64, 1);
    gTasks[taskId].tScroll = 136; // scene slides up into view
    SetGpuReg(REG_OFFSET_BG0VOFS, gTasks[taskId].tScroll);
    gTasks[taskId].tMapFrame = 0;
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Jump;
}

static void Task_CrystalScene_Jump(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0x80)
    {
        gTasks[taskId].func = Task_CrystalScene_Close_Load;
        return;
    }
    if (tTimer < 14)
    {
        tScroll += 8;
        SetGpuReg(REG_OFFSET_BG0VOFS, tScroll);
    }
    // Two-frame BG animation of Suicune leaping
    if ((tTimer & 3) == 0)
    {
        tMapFrame ^= 1;
        SetGpuReg(REG_OFFSET_BG0CNT, tMapFrame ? CI_BGCNT_ALT : CI_BGCNT_256);
    }
    tTimer++;
}

//------------------------------------------------- scene: close-up pan

// How far the close-up pans to the right as the artwork slides in (as GBC)
#define CI_CLOSE_PAN 96

static void Task_CrystalScene_Close_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    DecompressDataWithHeaderVram(sCI_SuicuneCloseTiles, (void *)BG_CHAR_ADDR(0));
    DecompressDataWithHeaderVram(sCI_SuicuneCloseMap, (void *)BG_SCREEN_ADDR(28));
    LoadPalette(sCI_SuicuneClosePal, BG_PLTT_ID(0), sizeof(sCI_SuicuneClosePal));
    // Orange backdrop so transparent tiles match the scene's orange background
    gPlttBufferUnfaded[0] = RGB(24, 12, 9);
    gPlttBufferFaded[0] = RGB(24, 12, 9);
    CrystalIntro_InitBg(CI_BGCNT_512);
    gTasks[taskId].tScroll = -CI_SCREEN_X;
    SetGpuReg(REG_OFFSET_BG0HOFS, gTasks[taskId].tScroll);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Close;
}

static void Task_CrystalScene_Close(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0x60)
    {
        gTasks[taskId].func = Task_CrystalScene_Back_Load;
        return;
    }
    if (tScroll < -CI_SCREEN_X + CI_CLOSE_PAN)
    {
        tScroll += 8;
        SetGpuReg(REG_OFFSET_BG0HOFS, tScroll);
    }
    tTimer++;
}

//------------------------------------------- scene: Suicune from behind

static void Task_CrystalScene_Back_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    DecompressDataWithHeaderVram(sCI_SuicuneBackTiles, (void *)BG_CHAR_ADDR(0));
    DecompressDataWithHeaderVram(sCI_SuicuneBackMap, (void *)BG_SCREEN_ADDR(28));
    DecompressDataWithHeaderVram(sCI_SuicuneBackMap2, (void *)BG_SCREEN_ADDR(29));
    LoadPalette(sCI_SuicunePal, BG_PLTT_ID(0), sizeof(sCI_SuicunePal));
    // Orange backdrop so transparent tiles match the scene's orange background
    gPlttBufferUnfaded[0] = RGB(24, 12, 9);
    gPlttBufferFaded[0] = RGB(24, 12, 9);
    CrystalIntro_InitBg(CI_BGCNT_256);
    gTasks[taskId].tScroll = -48; // pans up to center on Suicune
    SetGpuReg(REG_OFFSET_BG0VOFS, gTasks[taskId].tScroll);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_Back;
}

static void Task_CrystalScene_Back(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer >= 0x98)
    {
        gTasks[taskId].tTimer = 0;
        gTasks[taskId].tState = 0;
        gTasks[taskId].func = Task_CrystalScene_Silhouette;
        return;
    }
    if (tTimer < 0x28 && tScroll < (s16)-CI_SCREEN_Y)
    {
        tScroll++;
        SetGpuReg(REG_OFFSET_BG0VOFS, tScroll);
    }
    // Unowns materialize around Suicune, one palette at a time
    if (tTimer >= 0x40 && tTimer < 0x58 && (tTimer & 3) == 0)
    {
        u8 palNum = 2 + ((tTimer - 0x40) >> 2);
        u32 i;
        if (palNum <= 7)
        {
            for (i = 0; i < 4; i++)
            {
                gPlttBufferUnfaded[BG_PLTT_ID(palNum) + 1 + i] = sCI_AppearUnownColors[i];
                gPlttBufferFaded[BG_PLTT_ID(palNum) + 1 + i] = sCI_AppearUnownColors[i];
            }
        }
    }
    tTimer++;
}

//------------------------------------- scene: silhouette, then fade to white

static void Task_CrystalScene_Silhouette(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (gTasks[taskId].tState)
    {
    case 0:
        // Suicune turns to a silhouette as it leaps away
        SetGpuReg(REG_OFFSET_BG0CNT, CI_BGCNT_ALT);
        gTasks[taskId].tState++;
        break;
    case 1:
        if (++tTimer > 16)
        {
            BeginNormalPaletteFade(PALETTES_ALL, 1, 0, 16, RGB_WHITEALPHA);
            gTasks[taskId].tState++;
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            tTimer = 0;
            gTasks[taskId].tState++;
        }
        break;
    case 3:
        // Hold the white screen for a moment
        if (++tTimer > 0x40)
        {
            gTasks[taskId].tState = 0;
            gTasks[taskId].func = Task_CrystalScene_CrystalUnowns_Load;
        }
        break;
    }
}

//------------------------------------------- scene: "CRYSTAL" in Unowns

// Grayscale ramps for the letters darkening into view
static u16 CrystalIntro_LetterFastFade(u8 i)
{
    u8 v = 31 - 3 * (i / 2) - (i & 1);
    return RGB(v, v, v);
}

static u16 CrystalIntro_LetterSlowFade(u8 i)
{
    u8 v = 31 - i;
    return RGB(v, v, v);
}

static void Task_CrystalScene_CrystalUnowns_Load(u8 taskId)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    CrystalIntro_LoadBg(sCI_CrystalUnownsTiles, sCI_CrystalUnownsMap);
    LoadPalette(sCI_CrystalUnownsPal, BG_PLTT_ID(0), 8 * PLTT_SIZE_4BPP);
    // White backdrop to match the white scene
    gPlttBufferUnfaded[0] = RGB_WHITE;
    gPlttBufferFaded[0] = RGB_WHITE;
    CrystalIntro_InitBg(CI_BGCNT_256);
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].func = Task_CrystalScene_CrystalUnowns;
}

static void Task_CrystalScene_CrystalUnowns(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (tTimer < 0x80)
    {
        // Each letter's Unown darkens into view, one palette per 16 frames
        u8 palNum = tTimer >> 4;
        u8 step = tTimer & 0xF;
        gPlttBufferUnfaded[BG_PLTT_ID(palNum) + 3] = CrystalIntro_LetterFastFade(step);
        gPlttBufferFaded[BG_PLTT_ID(palNum) + 3] = CrystalIntro_LetterFastFade(step);
        gPlttBufferUnfaded[BG_PLTT_ID(palNum) + 4] = CrystalIntro_LetterSlowFade(step);
        gPlttBufferFaded[BG_PLTT_ID(palNum) + 4] = CrystalIntro_LetterSlowFade(step);
    }
    else if (tTimer == 0x100)
    {
        // Off to the title screen
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
        DestroyTask(taskId);
        SetMainCallback2(MainCB2_EndIntro);
        return;
    }
    tTimer++;
}

#undef sTimer
#undef sMatrix
#undef sRadius
#undef sDelay
#undef tTimer
#undef tTreeX
#undef tGrassX
#undef tSpriteId
#undef tScroll
#undef tMapFrame

static void IntroResetGpuRegs(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

void PanFadeAndZoomScreen(u16 screenX, u16 screenY, u16 zoom, u16 alpha)
{
    struct BgAffineSrcData src;
    struct BgAffineDstData dest;

    src.texX = 0x8000;
    src.texY = 0x8000;
    src.scrX = screenX;
    src.scrY = screenY;
    src.sx = zoom;
    src.sy = zoom;
    src.alpha = alpha;
    BgAffineSet(&src, &dest, 1);
    SetGpuReg(REG_OFFSET_BG2PA, dest.pa);
    SetGpuReg(REG_OFFSET_BG2PB, dest.pb);
    SetGpuReg(REG_OFFSET_BG2PC, dest.pc);
    SetGpuReg(REG_OFFSET_BG2PD, dest.pd);
    SetGpuReg(REG_OFFSET_BG2X_L, dest.dx);
    SetGpuReg(REG_OFFSET_BG2X_H, dest.dx >> 16);
    SetGpuReg(REG_OFFSET_BG2Y_L, dest.dy);
    SetGpuReg(REG_OFFSET_BG2Y_H, dest.dy >> 16);
}

