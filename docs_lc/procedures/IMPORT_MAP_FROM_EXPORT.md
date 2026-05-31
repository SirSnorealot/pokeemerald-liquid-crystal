# Procedure: Import a Map from LC Export

> **AI Instructions:** This procedure is the entry point when the user says something like "import Cherrygrove City" or "import Route 29 and all connected maps." Instructions arrive in plain English. You must discover the correct `lc_maps` folder yourself using Phase 0. Follow every phase in order. Do not skip a phase even if you believe something is already present; verify with the commands given. Substitute every `<placeholder>` with actual values before executing.
>
> **Multi-map mode:** The user may ask you to import adjacent/connected maps indefinitely, or to follow warps into interior maps. See Phase 4 for chaining rules.

---

## User Supplies (Plain English)

The user will say something like:
- *"Import Cherrygrove City, replace OldaleTown"*
- *"Import Route 29 and all connected maps"*
- *"Import Cherrygrove City and follow all warps too"*

From this you must determine:

| Field | How to determine |
|---|---|
| English map name | Stated by user |
| `map_name` | PascalCase form, e.g. `CherrygroveCity` — derive from English name |
| Mode | **Replace** or **Append** — user states it |
| *(Replace only)* `hoenn_map_name` | User states it, e.g. `OldaleTown` |
| *(Replace only)* `hoenn_map_id` | Derive: `MAP_` + SCREAMING_SNAKE_CASE of hoenn_map_name |
| *(Append only)* `map_group` + `map_group_neighbor` | User states it |
| Multi-map scope | Stated by user: single / connected / connected+warps / indefinite |

> All other identifiers (folder names, layout IDs, tileset names) are discovered in the phases below.

---

## Phase 0 — Locate and Read the Export

### 0-A: Check the map registry

Before doing anything else, check [docs_lc/map_registry.md](../map_registry.md). If the map is already listed there, it has been fully imported — skip all phases and report to the user.

### 0-B: Derive standard identifiers

```
map_id     = "MAP_" + SCREAMING_SNAKE_CASE(<map_name>)
             e.g. CherrygroveCity → MAP_CHERRYGROVE_CITY
hoenn_map_id = "MAP_" + SCREAMING_SNAKE_CASE(<hoenn_map_name>)   [Replace mode only]
```

### 0-C: Find the lc_maps folder

Convert the English map name to a SCREAMING_SNAKE_CASE search token (e.g. "Cherrygrove City" → `CHERRYGROVE_CITY`), then list candidates:

```bash
ls lc_maps/data/maps/ | grep "<SEARCH_TOKEN>"
```

Multiple folders will often appear (e.g. `CHERRYGROVE_CITY_3_65`, `CHERRYGROVE_CITY_6_3`, etc.). Each folder's `map.json` contains a `"map_type"` field:

- Outdoor towns/routes use `MAP_TYPE_TOWN`, `MAP_TYPE_CITY`, or `MAP_TYPE_ROUTE`
- Indoor maps use `MAP_TYPE_INDOOR`
- The outdoor main map typically also has a non-empty `"connections"` array

Select the folder whose `map_type` matches the expected type for the location (outdoor for towns/routes/cities; indoor for buildings). If ambiguous, inspect each candidate's `map_type` and `connections` to pick the right one. Call the chosen folder `lc_map_folder`.

```bash
python3 -c "
import json, os
maps_dir = 'lc_maps/data/maps'
for d in sorted(os.listdir(maps_dir)):
    if not d.startswith('<SEARCH_TOKEN>'): continue
    with open(f'{maps_dir}/{d}/map.json') as f:
        m = json.load(f)
    print(f'{d:40s}  type={m[\"map_type\"]:20s}  connections={len(m.get(\"connections\",[]))}  warps={len(m.get(\"warp_events\",[]))}')
"
```

### 0-D: Load the source map.json

```bash
cat lc_maps/data/maps/<lc_map_folder>/map.json
```

Record the value of `"layout"` — call it `lc_layout_id` (e.g. `LAYOUT_2D5064`).

### 0-E: Load the layout record

```bash
python3 -c "
import json
with open('lc_maps/data/layouts/layouts.json') as f:
    d = json.load(f)
target = next(e for e in d['layouts'] if e['id'] == '<lc_layout_id>')
print(json.dumps(target, indent=2))
"
```

Record from output:
- `lc_primary_tileset` — e.g. `gTileset_2D4A94`
- `lc_secondary_tileset` — e.g. `gTileset_2D4AAC`
- `lc_layout_width`, `lc_layout_height`

---

## Phase 1 — Tileset Import Check

For **each** of `lc_primary_tileset` and `lc_secondary_tileset`:

### 1-A: Check the tileset registry

```bash
grep "<lc_primary_tileset>" docs_lc/tileset_registry.md
grep "<lc_secondary_tileset>" docs_lc/tileset_registry.md
```

- **If found** → the tileset is already imported. Record its LC name (e.g. `gTileset__general_lc`) from the registry. Skip to the next tileset.
- **If not found** → the tileset must be imported. Continue to step 1-B.

### 1-B: Gather tileset info from lc_maps headers

Determine whether the tileset is primary or secondary:

```bash
# primary or secondary?
ls lc_maps/data/tilesets/primary/<ADDR>/    2>/dev/null && echo PRIMARY
ls lc_maps/data/tilesets/secondary/<ADDR>/  2>/dev/null && echo SECONDARY
```

where `<ADDR>` is the hex address suffix of the tileset name (e.g. `2D4AAC` from `gTileset_2D4AAC`).

Get `isSecondary` and `num_tiles` from the lc_maps headers:

```bash
grep "<lc_tileset_name>" lc_maps/src/data/tilesets/headers.h
grep "<lc_tileset_name>" lc_maps/src/data/tilesets/graphics.h
```

### 1-C: Choose an LC name

Ask the user to supply the LC name for the new tileset (e.g. `new_bark_town_lc`). The full name will be `gTileset__<name>`.

### 1-D: Run ADD_TILESET procedure

Follow [ADD_TILESET.md](ADD_TILESET.md) with:

| ADD_TILESET field | Value |
|---|---|
| `tileset_name` | `<name>` chosen in 1-C |
| `tileset_type` | `primary` or `secondary` |
| `num_tiles` | from 1-B |
| Source files | `lc_maps/data/tilesets/<primary\|secondary>/<ADDR>/` |

After the tileset is imported, record its LC name in the registry table as `gTileset__<name>`.

---

## Phase 2 — Layout Import Check

### 2-A: Check the layout registry

Before hashing, check [docs_lc/layout_registry.md](../layout_registry.md). If `lc_layout_id`'s hex folder appears in the `lc_maps Folder` column, the layout is already imported — record the matching `Project Layout ID` as `layout_id` and skip to Phase 3.

### 2-B: Compute the layout binary hashes (fallback)

```bash
md5sum lc_maps/data/layouts/<lc_layout_folder>/map.bin
md5sum lc_maps/data/layouts/<lc_layout_folder>/border.bin
```

where `<lc_layout_folder>` is the hex address part of `lc_layout_id` (e.g. `2D5064` from `LAYOUT_2D5064`).

### 2-C: Search the project for matching binaries

```bash
find data/layouts -name "map.bin" | xargs md5sum | grep "<map_bin_hash>"
find data/layouts -name "border.bin" | xargs md5sum | grep "<border_bin_hash>"
```

- **Both match the same folder** → the layout is already imported. Record the project `layout_id` from `data/layouts/layouts.json` by searching for that folder's `blockdata_filepath`. Skip to Phase 3.
- **No match** → the layout must be imported. Continue to step 2-C.

### 2-D: Choose an LC layout identity

The user supplies (or you derive from `map_name`):
- `layout_id` — e.g. `LAYOUT_CHERRYGROVE_CITY`
- `layout_folder` — e.g. `_CherrygroveCity`
- `layout_name` — e.g. `CherrygroveCity_Layout`

Translate the lc_maps tileset names to LC names (already resolved in Phase 1):
- `primary_tileset_ref` — the `gTileset__<name>` LC form
- `secondary_tileset_ref` — the `gTileset__<name>` LC form

### 2-E: Run ADD_LAYOUT procedure

> **`layout_version` warning:** `mapjson` skips any layout whose `layout_version` does not match the current build target. For a debug/release emerald build the value must be `"emerald"`. If you set (or inherit) `"frlg"`, the layout will be silently omitted from `layouts.inc`, causing `undefined reference to '<Name>_Layout'` linker errors. After ADD_LAYOUT completes, verify:
> ```bash
> python3 -c "import json; d=json.load(open('data/layouts/layouts.json')); print(next(l['layout_version'] for l in d['layouts'] if l['id']=='<layout_id>'))"
> ```
> The output must be `emerald`.

Follow [ADD_LAYOUT.md](ADD_LAYOUT.md) with:

| ADD_LAYOUT field | Value |
|---|---|
| `layout_folder` | from 2-C |
| `layout_id` | from 2-C |
| `layout_name` | from 2-C |
| `map_width` | `lc_layout_width` from Phase 0 |
| `map_height` | `lc_layout_height` from Phase 0 |
| `primary_tileset_ref` | from 2-C |
| `secondary_tileset_ref` | from 2-C |
| Source `.bin` files | `lc_maps/data/layouts/<lc_layout_folder>/map.bin` and `border.bin` |

---

## Phase 3 — Map Import

Follow [ADD_MAP.md](ADD_MAP.md) with:

| ADD_MAP field | Value |
|---|---|
| `map_name` | user-supplied |
| `map_id` | derived in Phase 0 |
| `layout_id` | resolved in Phase 2 |
| `lc_map_folder` | identified in Phase 0-C |
| Mode | user-supplied |
| `hoenn_map_name` | user-supplied *(Replace only)* |
| `hoenn_map_id` | user-supplied *(Replace only)* |

> Even in single-map mode, the build must succeed before this procedure is considered complete. Do not stop at the first error — fix it and rebuild until `EXIT:0`.

---

## Phase 4 — Multi-Map Chaining (only when requested)

This phase applies when the user asks to also import connected maps, adjacent maps, follow warps, or continue indefinitely. It uses the `lc_maps` source data — **not** the already-imported project data — as the source of truth for what is connected.

### Deriving folders from map references

Every map reference in `lc_maps` uses the format `MAP_<FOLDER_NAME>`. Strip the `MAP_` prefix to get the `lc_maps` folder name:

```
MAP_ROUTE_29_3_45  →  ROUTE_29_3_45
MAP_CHERRYGROVE_CITY_6_3  →  CHERRYGROVE_CITY_6_3
```

Verify the folder exists before attempting import:
```bash
ls lc_maps/data/maps/<derived_folder>/
```

### 4-A: Follow map connections (outdoor neighbors)

Read the `"connections"` array from `lc_maps/data/maps/<lc_map_folder>/map.json`. Each entry has a `"map"` field. Derive a candidate folder for each, then check whether it is already imported by:

1. Checking [docs_lc/map_registry.md](../map_registry.md) — if the project map name appears there, it is already imported.
2. If not in the registry, also verify against the project: `grep '"<DERIVED_MAP_ID>"' data/maps/map_groups.json`

- **Found (either check)** → already imported, skip.
- **Not found** → queue it for import.

For each queued connection, run this entire procedure (Phases 0–3) for that map. The user must supply a `map_name` and mode for each; ask if not obvious from context.

### 4-B: Follow warps into interior maps (only when explicitly asked)

Read the `"warp_events"` array from `lc_maps/data/maps/<lc_map_folder>/map.json`. Each entry has a `"dest_map"` field. Derive the folder and check if already imported (same grep as above).

Only follow warps whose `dest_map` refers to a map that belongs to the same location (i.e., the folder name starts with the same location prefix). Do not follow warps to unrelated maps (e.g. a warp to a distant city or `MAP_NOT_USED`).

Skip entries where `dest_map` is `MAP_NOT_USED_0_0` or does not exist in `lc_maps/data/maps/`.

### 4-C: Infinite / chain mode

When the user says "import all connected maps" or "keep going":

1. Maintain a queue of folders to import and a set of already-imported folders (check against `data/maps/map_groups.json`).
2. After importing each map, enqueue its unimported connections (and warps if requested).
3. Continue until the queue is empty.
4. Always run `make clean` before the batch build to avoid stale generated `.inc` files:
   ```bash
   make clean && make debug -j$(nproc) > /tmp/build_output.txt 2>&1; echo "EXIT:$?"
   grep -E "error:" /tmp/build_output.txt | grep -v "^make" | sort -u
   ```
5. If the build fails, fix all errors and rebuild until `EXIT:0` before reporting completion.

> **Build hang note:** Parallel builds may appear idle while still working. Do not interrupt. Wait for the completion notification before checking output.

---

## Summary Checklist

- [ ] Map registry checked — not already imported
- [ ] English name resolved to `lc_map_folder` via `map_type` / connections inspection
- [ ] `lc_layout_id`, `lc_primary_tileset`, `lc_secondary_tileset` recorded from export
- [ ] Primary tileset — checked in registry; imported via ADD_TILESET if missing
- [ ] Secondary tileset — checked in registry; imported via ADD_TILESET if missing
- [ ] Layout — checked in layout registry (and md5 hash fallback); imported via ADD_LAYOUT if not already present
- [ ] ADD_MAP procedure completed in full per [ADD_MAP.md](ADD_MAP.md)
- [ ] *(Multi-map)* All queued connections/warps processed
- [ ] **`layout_version` is `"emerald"`** in `data/layouts/layouts.json` for every new layout
- [ ] **Build passes with zero errors** — piped build `EXIT:0`, all errors fixed and rebuilt until clean
- [ ] Map added to [docs_lc/map_registry.md](../map_registry.md)
