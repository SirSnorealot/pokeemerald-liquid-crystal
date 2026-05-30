# Procedure: Add a New LC Map

> **AI Instructions:** This document is written to be followed precisely by an AI coding agent (GitHub Copilot). When invoking this procedure, the user will supply the required field values listed below. Substitute every `<placeholder>` with the supplied value before making any edits. Follow each step in order. The user will also specify which mode applies: **Replace** (repurpose an existing Hoenn map slot) or **Append** (add an entirely new map entry).

This procedure wires a new LC map into the project's map data, group tables, event scripts, wild encounters, and any relevant source files.

---

## Information Required

| Field | Example |
|---|---|
| `map_name` | `Route46` |
| `map_id` | `MAP_ROUTE46` |
| `layout_id` | `LAYOUT_ROUTE46` |
| `map_group` | `gMapGroup_TownsAndRoutes` |
| **Replace mode only:** `hoenn_map_name` | `Route118` |
| **Replace mode only:** `hoenn_map_id` | `MAP_ROUTE118` |
| **Append mode only:** `map_group_neighbor` | the existing map name to insert after |

> **Naming conventions**
> - Map folders use no leading underscore: `data/maps/Route46/`
> - `map_id` is all caps with underscores: `MAP_ROUTE46`
> - `layout_id` is all caps: `LAYOUT_ROUTE46`
> - `map_name` is PascalCase with no spaces: `Route46`

---

## Step 1 — Rename (or Create) the Map Folder

### Replace mode
Rename the existing Hoenn map folder:
```
data/maps/<hoenn_map_name>/  →  data/maps/<map_name>/
```

### Append mode
Create a new folder `data/maps/<map_name>/` and place the exported `map.json` and `scripts.inc` files from PokeMapExport inside it.

---

## Step 2 — Update `map.json`

Open `data/maps/<map_name>/map.json` and make the following changes:

- `"id"` → `"<map_id>"`
- `"name"` → `"<map_name>"`
- `"layout"` → `"<layout_id>"`
- `"connections"` → `[]` *(leave empty; neighboring maps will add connections when they are added later)*

> **Do not change** `music`, `region_map_section`, `weather`, `map_type`, `allow_cycling`, `allow_escaping`, `allow_running`, `show_map_name`, `battle_scene`, `object_events`, `warp_events`, `coord_events`, or `bg_events`. These are carried over from the source and are updated later as LC content is built out.

> **Exception:** If any already-added LC neighbor maps border this map, add their connections to `"connections"` now. Check existing LC maps that reference this map's area.

### Sanitize LC event data (required)

The LC export `map.json` uses old GBA formats that mapjson cannot process. Run these fixes before building:

**Remove `local_id` key from all `object_events`** — the key must not exist at all (not even `null`). If present, mapjson generates `#define 1 1` in the map event ID header, breaking the build.

```python
import json
with open('data/maps/<map_name>/map.json') as f:
    m = json.load(f)
for e in m.get('object_events', []):
    e.pop('local_id', None)
with open('data/maps/<map_name>/map.json', 'w') as f:
    json.dump(m, f, indent=4)
```

**Remove `coord_events` and `bg_events` entries missing a `type` field** — old GBA-extracted events use `trigger`/`index` fields instead of `type`/`var`/`var_value`. mapjson requires `type` and will error on entries without it. Strip them:

```python
import json
with open('data/maps/<map_name>/map.json') as f:
    m = json.load(f)
m['coord_events'] = [e for e in m.get('coord_events', []) if 'type' in e]
m['bg_events']    = [e for e in m.get('bg_events', [])    if 'type' in e]
with open('data/maps/<map_name>/map.json', 'w') as f:
    json.dump(m, f, indent=4)
```

---

## Step 3 — Handle `scripts.inc`

### Replace mode
Open `data/maps/<map_name>/scripts.inc` (the renamed Hoenn file) and rename **only** the top-level map scripts label:

```diff
-<OldMapName>_MapScripts::
+<map_name>_MapScripts::
```

Leave all other Hoenn script content as-is. The existing scripts are valid pokeemerald assembly and serve as placeholder logic until LC scripts are ported.

### Append mode
Create `data/maps/<map_name>/scripts.inc` with a stub containing only the required map scripts label:

```asm
<map_name>_MapScripts::
	.byte 0
```

> **Do not copy `scripts.inc` from `lc_maps` in Append mode.** The LC export scripts use old GBA macro formats that are incompatible with pokeemerald and will produce many assembler errors:
> - `trainerbattle` has a different argument signature than pokeemerald's macro
> - `checkpartymove` instruction does not exist in this codebase
> - `[.]` is not a valid charmap control code
> - `{0X??}` / `{0x??}` raw hex byte escapes are not supported
> - `{PLAY_BGM}{0x????}` uses an old argument format
> - Raw UTF-8 accented characters (e.g. `é` as bytes `0xC3 0xA9`) cause assembler errors — pokeemerald uses charmap escape codes (e.g. `{é}`) instead
>
> The lc_maps scripts are reference material only. LC script logic will be ported manually in a later pass.

---

## Step 4 — Update Sub-Maps of the Replaced Hoenn Map *(Replace mode only)*

Any sub-maps belonging to `<hoenn_map_name>` (houses, gyms, Pokémon Centers, etc.) have `warp_events` pointing back to `MAP_<HOENN_MAP_NAME>`. These warps are no longer valid. For each such sub-map, set:

```json
"warp_events": []
```

> Do not modify `object_events`, `coord_events`, `bg_events`, or `scripts.inc` of sub-maps.

---

## Step 5 — Update Adjacent Already-Added LC Maps

For any already-added LC maps that are geographically adjacent to `<map_name>`, add a connection entry to their `map.json`:

```json
{
  "map": "<map_id>",
  "offset": <offset>,
  "direction": "<direction>"
}
```

Also add the reciprocal connection on `<map_name>`'s `map.json` if it is known at this time.

---

## Step 6 — Update `data/maps/map_groups.json`

### Replace mode
Find the entry `"<hoenn_map_name>"` in the `"<map_group>"` array and replace it:

```json
"<map_name>"
```

### Append mode
Add `"<map_name>"` to the `"<map_group>"` array after `"<map_group_neighbor>"`. Also **remove** the old Hoenn map name from whichever group it currently belongs to.

---

## Step 7 — Update `data/event_scripts.s`

Find the line:

```asm
.include "data/maps/<hoenn_map_name>/scripts.inc"
```

Replace it with:

```asm
.include "data/maps/<map_name>/scripts.inc"
```

> **Note:** `data/event_scripts.s` uses **tab** indentation. When scripting this replacement (e.g. in Python), use `\t` as the line prefix, not spaces. A mismatch will silently fail to find the line.

---

## Step 8 — Update `tools/mapjson/required_map_defines.json`

Find the entry `["<hoenn_map_id>", <number>]` and replace the map ID:

```json
["<map_id>", <number>]
```

---

## Step 9 — Update Source Files

Each of the following source files may reference the old Hoenn map by its `MAP_*` constant. Search for `<hoenn_map_id>` in each file and replace all occurrences with `<map_id>`.

| File | What is stored |
|---|---|
| `src/region_map.c` | `sMapHealLocations` section map reference |
| `src/data/wild_encounters.json` | Wild encounter `"map"` and `"base_label"` entries |
| `src/battle_setup.c` | `gRematchTable` trainer map references; `BattleSetup_GetEnvironmentId` map check |
| `src/field_specials.c` | Abnormal weather map number arrays |
| `src/roamer.c` | `sRoamerLocations` map number entries |
| `src/overworld.c` | Hardcoded map group/num checks *(cities only)* |
| `src/data/heal_locations.json` | Pokémon Center heal location `"map"` field *(cities only)* |
| `src/follower_helper.c` | Hardcoded map checks for follower behavior |
| `src/tv.c` | Map ID references for in-game TV segments; also contains `LOCALID_*` NPC constants tied to specific maps — if the replaced map had named NPC IDs (e.g. `LOCALID_ROUTE120_GABBY_1`), search for those constants too and redirect them to equivalent NPCs on the new map or remove the references |
| `src/wild_encounter.c` | Hardcoded map checks for special wild encounter logic |

> Not every file will have a match. Only update files where `<hoenn_map_id>` actually appears. Do not make changes if there is no occurrence.

> **`src/pokedex_area_screen.c` — duplicate case value warning:** This file defines `MAP_GROUP_*` and `MAP_GROUP_*_FRLG` macros using `MAP_GROUP(MAP_<name>)`. If any replaced map causes two of these macros to expand to the same integer (because both maps now live in the same group), the compiler will emit a `duplicate case value` error in the switch statements in that file. Fix by removing the redundant `_FRLG` case labels from both switch blocks.

---

## Step 10 — Verify the Build

Always run `make clean` before building to avoid stale generated `.inc` files from previously processed maps:

```bash
make clean && make debug -j$(nproc) > /tmp/build_output.txt 2>&1; echo "EXIT:$?"
```

Check errors (ignore make infrastructure lines):

```bash
grep -E "error:" /tmp/build_output.txt | grep -v "^make" | sort -u
```

> **Build hang note:** The build runs in parallel and may appear idle in the terminal while still working. Do not interrupt it. If using an async terminal, wait for the completion notification before checking output.

Fix all errors and rebuild until `EXIT:0` is shown.

---

## Step 11 — Update the Map Registry

Add an entry for this map to [docs_lc/map_registry.md](../map_registry.md). Place it in the correct section (Outdoor or Indoor) and record the `lc_maps` source folder used.

| Column | Value |
|---|---|
| Project Map Name | `<map_name>` |
| lc_maps Folder | the `lc_map_folder` identified in Phase 0 of IMPORT_MAP_FROM_EXPORT |

---

## Summary Checklist

- [ ] Map folder renamed or created at `data/maps/<map_name>/`
- [ ] `map.json` — `id`, `name`, `layout` updated; `connections` set to `[]`
- [ ] `scripts.inc` — *(Replace)* top label renamed to `<map_name>_MapScripts::`, Hoenn content preserved; *(Append)* stub created with label and `.byte 0` only (lc_maps scripts.inc NOT used)
- [ ] *(Replace mode)* Sub-map `warp_events` pointing to old Hoenn map cleared to `[]`
- [ ] Adjacent already-added LC maps — connections updated
- [ ] `data/maps/map_groups.json` — entry replaced or appended
- [ ] `data/event_scripts.s` — `.include` path updated
- [ ] `tools/mapjson/required_map_defines.json` — map ID replaced
- [ ] `src/region_map.c` — map reference updated if present
- [ ] `src/data/wild_encounters.json` — map reference updated if present
- [ ] `src/battle_setup.c` — map references updated if present
- [ ] `src/field_specials.c` — map references updated if present
- [ ] `src/roamer.c` — map references updated if present
- [ ] `src/overworld.c` — map references updated if present *(cities)*
- [ ] `src/data/heal_locations.json` — map reference updated if present *(cities)*
- [ ] `src/follower_helper.c` — map reference updated if present
- [ ] `src/tv.c` — map reference and any `LOCALID_*` constants updated if present
- [ ] `src/wild_encounter.c` — map reference updated if present
- [ ] `src/pokedex_area_screen.c` — checked for duplicate `MAP_GROUP_*` / `MAP_GROUP_*_FRLG` case values if maps moved groups
- [ ] `map.json` — `local_id` key removed from all `object_events`
- [ ] `map.json` — `coord_events` and `bg_events` entries without `type` field removed
- [ ] Build succeeds (`EXIT:0` from piped build command)
- [ ] Map added to `docs_lc/map_registry.md`
