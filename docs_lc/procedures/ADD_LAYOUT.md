# Procedure: Add a New LC Layout

> **AI Instructions:** This document is written to be followed precisely by an AI coding agent (GitHub Copilot). When invoking this procedure, the user will supply the required field values listed below. Substitute every `<placeholder>` with the supplied value before making any edits. Follow each step in order. Do not touch any files not explicitly listed. The user will also specify which mode applies: **Replace** or **Append**.

This procedure places layout binary files and registers the layout entry in `data/layouts/layouts.json`.

---

## Information Required

| Field | Example |
|---|---|
| `layout_folder` | `_CherrygroveCity` |
| `layout_id` | `LAYOUT_CHERRYGROVE_CITY` |
| `layout_name` | `CherrygroveCity_Layout` |
| `map_width` | `56` |
| `map_height` | `92` |
| `primary_tileset_ref` | `gTileset__general_lc` |
| `secondary_tileset_ref` | `gTileset__cherrygrove_city_lc` |
| **Replace mode only:** `hoenn_layout_id` | `LAYOUT_OLDALE_TOWN` |

> **Naming conventions (important)**
> - Layout folders use a leading underscore: `data/layouts/_CherrygroveCity/`
> - `layout_id` is all caps with underscores: `LAYOUT_CHERRYGROVE_CITY`
> - `layout_name` is PascalCase with a `_Layout` suffix: `CherrygroveCity_Layout`

---

## Step 1 — Place Layout Binary Files

Create the layout folder and place the exported binary files from PokeMapExport:

```
data/layouts/<layout_folder>/
    border.bin
    map.bin
```

---

## Step 2 — Update `data/layouts/layouts.json`

There are two modes depending on whether a Hoenn slot is being repurposed or an entirely new entry is needed.

### Mode A — Replace an existing Hoenn entry

Find the entry whose `"id"` matches `<hoenn_layout_id>` and replace the entire block:

```json
{
  "id": "<layout_id>",
  "name": "<layout_name>",
  "width": <map_width>,
  "height": <map_height>,
  "primary_tileset": "<primary_tileset_ref>",
  "secondary_tileset": "<secondary_tileset_ref>",
  "border_filepath": "data/layouts/<layout_folder>/border.bin",
  "blockdata_filepath": "data/layouts/<layout_folder>/map.bin",
  "layout_version": "emerald"
},
```

> The old Hoenn layout folder is now unused. Delete its `border.bin` and `map.bin` files.

### Mode B — Append a new entry

Add the following block as a new element inside the `"layouts"` array, placed after the last existing LC layout entry and before the FRLG entries at the end of the array:

```json
{
  "id": "<layout_id>",
  "name": "<layout_name>",
  "width": <map_width>,
  "height": <map_height>,
  "primary_tileset": "<primary_tileset_ref>",
  "secondary_tileset": "<secondary_tileset_ref>",
  "border_filepath": "data/layouts/<layout_folder>/border.bin",
  "blockdata_filepath": "data/layouts/<layout_folder>/map.bin",
  "layout_version": "emerald"
},
```

---

## Step 3 — Verify the Build

Always run `make clean` before building to avoid stale generated files:

```bash
make clean && make debug -j$(nproc) > /tmp/build_output.txt 2>&1; echo "EXIT:$?"
grep -E "error:" /tmp/build_output.txt | grep -v "^make" | sort -u
```

> **Build hang note:** Parallel builds may appear idle while still working. Wait for `EXIT:N` to appear before checking results.

Check for errors about unknown layouts, missing files, or tileset references.

---

## Summary Checklist

- [ ] `data/layouts/<layout_folder>/border.bin` and `map.bin` placed
- [ ] `data/layouts/layouts.json` — entry added or replaced
- [ ] *(Replace mode only)* Old Hoenn layout folder's `.bin` files deleted
- [ ] Build succeeds (`EXIT:0`)
