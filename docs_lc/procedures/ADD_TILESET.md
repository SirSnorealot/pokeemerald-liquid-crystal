# Procedure: Add a New LC Tileset

> **AI Instructions:** This document is written to be followed precisely by an AI coding agent (GitHub Copilot). When invoking this procedure, the user will supply the required field values listed below. Substitute every `<placeholder>` with the supplied value before making any edits. Follow each step in order. Do not touch any files not explicitly listed.

This procedure registers a new tileset (exported from the GBA game via PokeMapExport) into the pokeemerald-liquid-crystal project source code.

---

## Information Required

When invoking this procedure, provide the following. Most values come from
the PokeMapExport output; the **amap number** is the only value you supply
manually.

| Field | Example |
|---|---|
| `tileset_name` | `route_33_lc` |
| `tileset_type` | `secondary` |
| `num_tiles` | `498` |

> **Naming conventions (important)**
> - Tileset folders always have a leading underscore: `data/tilesets/secondary/_route_33_lc/`
> - The `gTileset` struct uses a **double** underscore: `gTileset__route_33_lc`
>   (the folder's leading `_` plus the `gTileset_` prefix = two underscores)
> - All other variable names use a single underscore suffix: `gTilesetTiles_route_33_lc`, `gTilesetPalettes_route_33_lc`, etc.

---

## Step 1 — Place Tileset Files

Copy the exported tileset folder from PokeMapExport into the project under
the correct tileset type directory.

**For a secondary tileset** (most LC area tilesets):
```
data/tilesets/secondary/_<tileset_name>/
    palettes/
        00.pal  01.pal  02.pal  03.pal
        04.pal  05.pal  06.pal  07.pal
        08.pal  09.pal  10.pal  11.pal
        12.pal  13.pal  14.pal  15.pal
    tiles.png
    metatiles.bin
    metatile_attributes.bin
```

**For a primary tileset** (used when a new primary is needed, e.g. `_building_lc`, `_general_lc`):
```
data/tilesets/primary/_<tileset_name>/
    palettes/ ... (same as above)
    tiles.png
    metatiles.bin
    metatile_attributes.bin
```

---

## Step 2 — Run the Triple Layer Converter

After placing the tileset files, run the converter so the metatile format is
upgraded to the triple-layer system used by this project. The script
auto-detects all tilesets and skips any already converted.

```bash
python3 dev_scripts/triple_layer_converter/triple_layer_converter.py --tsroot /home/sirsnorealot/pokeemerald-liquid-crystal/data/tilesets/
```

Verify the output line for the new tileset says it was converted and not
skipped.

---

## Step 3 — Register in `src/data/tilesets/metatiles.h`

Add two lines immediately **before** the `#else` guard (before the FRLG block).

```c
const u16 gMetatiles_<tileset_name>[] = INCBIN_U16("data/tilesets/<tileset_type>/_<tileset_name>/metatiles.bin");
const u16 gMetatileAttributes_<tileset_name>[] = INCBIN_U16("data/tilesets/<tileset_type>/_<tileset_name>/metatile_attributes.bin");
```

**Example** (`route_33_lc`, secondary):
```c
const u16 gMetatiles_route_33_lc[] = INCBIN_U16("data/tilesets/secondary/_route_33_lc/metatiles.bin");
const u16 gMetatileAttributes_route_33_lc[] = INCBIN_U16("data/tilesets/secondary/_route_33_lc/metatile_attributes.bin");
```

Insert immediately before the existing `#else` line in that file.

---

## Step 4 — Register in `src/data/tilesets/graphics.h`

Add a palette array and a tiles line immediately **before** the `#if IS_FRLG`
guard (line ~1946 at time of writing). 

```c
const u16 gTilesetPalettes_<tileset_name>[][16] =
{
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/00.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/01.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/02.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/03.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/04.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/05.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/06.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/07.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/08.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/09.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/10.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/11.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/12.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/13.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/14.pal", ".gbapal"),
	INCGFX_U16("data/tilesets/<tileset_type>/_<tileset_name>/palettes/15.pal", ".gbapal"),
};

const u32 gTilesetTiles_<tileset_name>[] = INCGFX_U32("data/tilesets/<tileset_type>/_<tileset_name>/tiles.png", ".4bpp.fastSmol", "-num_tiles <num_tiles> -Wnum_tiles");
```

For a **primary** tileset the num_tiles value is typically `512`. For secondary
tilesets use the exact value from your tracking notes.

---

## Step 5 — Register in `src/data/tilesets/headers.h`

Add the `Tileset` struct immediately **before** the `#else` guard (before the FRLG block).

```c
const struct Tileset gTileset__<tileset_name> =
{
    .isCompressed = TRUE,
    .isSecondary = <TRUE|FALSE>,
    .tiles = gTilesetTiles_<tileset_name>,
    .palettes = gTilesetPalettes_<tileset_name>,
    .metatiles = gMetatiles_<tileset_name>,
    .metatileAttributes = gMetatileAttributes_<tileset_name>,
    .callback = NULL,
};
```

Set `.isSecondary = TRUE` for secondary tilesets, `FALSE` for primary.

**Example** (`route_33_lc`, secondary):
```c
const struct Tileset gTileset__route_33_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_33_lc,
    .palettes = gTilesetPalettes_route_33_lc,
    .metatiles = gMetatiles_route_33_lc,
    .metatileAttributes = gMetatileAttributes_route_33_lc,
    .callback = NULL,
};
```

---

## Step 6 — Update the Tileset Registry

Add a new row to `docs_lc/tileset_registry.md`. Leave **AMAP #** as `?` — the developer will fill it in.

| Exported Name | AMAP # | LC Name |
|---|---|---|
| `gTileset_XXXXXXXX` | ? | `gTileset__<tileset_name>` |

---

## Step 7 — Verify the Build

Always run `make clean` before building to avoid stale generated files:

```bash
make clean && make debug -j$(nproc) > /tmp/build_output.txt 2>&1; echo "EXIT:$?"
grep -E "error:" /tmp/build_output.txt | grep -v "^make" | sort -u
```

> **Build hang note:** Parallel builds may appear idle while still working. Wait for `EXIT:N` to appear before checking results.

Check for errors about unknown tilesets, missing files, or tile count warnings.

---

## Summary Checklist

- [ ] Tileset files placed in `data/tilesets/<tileset_type>/_<tileset_name>/`
- [ ] `triple_layer_converter.py` run — new tileset was converted (not skipped)
- [ ] `src/data/tilesets/metatiles.h` — two INCBIN lines added before `#else`
- [ ] `src/data/tilesets/graphics.h` — palette array + tiles line added before `#if IS_FRLG`
- [ ] `src/data/tilesets/headers.h` — `gTileset__<tileset_name>` struct added before `#else`
- [ ] `docs_lc/tileset_registry.md` — new row added
- [ ] Build succeeds (`EXIT:0`)
