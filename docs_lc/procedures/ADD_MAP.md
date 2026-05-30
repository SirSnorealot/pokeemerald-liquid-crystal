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

---

## Step 3 — Update `scripts.inc`

Open `data/maps/<map_name>/scripts.inc` and rename only the top-level map scripts label:

```diff
-<OldMapName>_MapScripts::
+<map_name>_MapScripts::
```

Leave all other script content as-is.

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

> Not every file will have a match. Only update files where `<hoenn_map_id>` actually appears. Do not make changes if there is no occurrence.

---

## Step 10 — Verify the Build

```bash
make debug -j$(nproc)
```

Check for any errors about unknown map IDs, missing includes, or undefined references.

---

## Summary Checklist

- [ ] Map folder renamed or created at `data/maps/<map_name>/`
- [ ] `map.json` — `id`, `name`, `layout` updated; `connections` set to `[]`
- [ ] `scripts.inc` — top label renamed to `<map_name>_MapScripts::`
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
- [ ] Build succeeds
