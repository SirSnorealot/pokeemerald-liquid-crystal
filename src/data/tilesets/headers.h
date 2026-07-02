#include "fieldmap.h"

// Whether a palette has a night version, located at ((x + 9) % 16).pal
#define SWAP_PAL(x) ((x) < NUM_PALS_IN_PRIMARY ? 1 << (x) : 1 << ((x) - NUM_PALS_IN_PRIMARY))



#if !IS_FRLG

const struct Tileset gTileset__building_lc =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_building_lc,
    .palettes = gTilesetPalettes_building_lc,
    .metatiles = gMetatiles_building_lc,
    .metatileAttributes = gMetatileAttributes_building_lc,
    .callback = InitTilesetAnim_Building_lc,
};

const struct Tileset gTileset__players_house_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_players_house_lc,
    .palettes = gTilesetPalettes_players_house_lc,
    .metatiles = gMetatiles_players_house_lc,
    .metatileAttributes = gMetatileAttributes_players_house_lc,
    .callback = NULL,
};

const struct Tileset gTileset__general_lc =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_general_lc,
    .palettes = gTilesetPalettes_general_lc,
    .metatiles = gMetatiles_general_lc,
    .metatileAttributes = gMetatileAttributes_general_lc,
    .callback = InitTilesetAnim_General_lc,
};

const struct Tileset gTileset__new_bark_town_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_new_bark_town_lc,
    .palettes = gTilesetPalettes_new_bark_town_lc,
    .metatiles = gMetatiles_new_bark_town_lc,
    .metatileAttributes = gMetatileAttributes_new_bark_town_lc,
    .callback = NULL,
};

const struct Tileset gTileset__elms_lab_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_elms_lab_lc,
    .palettes = gTilesetPalettes_elms_lab_lc,
    .metatiles = gMetatiles_elms_lab_lc,
    .metatileAttributes = gMetatileAttributes_elms_lab_lc,
    .callback = NULL,
};

const struct Tileset gTileset__interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_interior_lc,
    .palettes = gTilesetPalettes_interior_lc,
    .metatiles = gMetatiles_interior_lc,
    .metatileAttributes = gMetatileAttributes_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__goldenrod_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_goldenrod_city_lc,
    .palettes = gTilesetPalettes_goldenrod_city_lc,
    .metatiles = gMetatiles_goldenrod_city_lc,
    .metatileAttributes = gMetatileAttributes_goldenrod_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__cherrygrove_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_cherrygrove_city_lc,
    .palettes = gTilesetPalettes_cherrygrove_city_lc,
    .metatiles = gMetatiles_cherrygrove_city_lc,
    .metatileAttributes = gMetatileAttributes_cherrygrove_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__route_31_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_31_lc,
    .palettes = gTilesetPalettes_route_31_lc,
    .metatiles = gMetatiles_route_31_lc,
    .metatileAttributes = gMetatileAttributes_route_31_lc,
    .callback = NULL,
};

const struct Tileset gTileset__violet_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_violet_city_lc,
    .palettes = gTilesetPalettes_violet_city_lc,
    .metatiles = gMetatiles_violet_city_lc,
    .metatileAttributes = gMetatileAttributes_violet_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__route_32_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_32_lc,
    .palettes = gTilesetPalettes_route_32_lc,
    .metatiles = gMetatiles_route_32_lc,
    .metatileAttributes = gMetatileAttributes_route_32_lc,
    .callback = NULL,
};

const struct Tileset gTileset__route_35_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_35_lc,
    .palettes = gTilesetPalettes_route_35_lc,
    .metatiles = gMetatiles_route_35_lc,
    .metatileAttributes = gMetatileAttributes_route_35_lc,
    .callback = NULL,
};

const struct Tileset gTileset__olivine_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_olivine_city_lc,
    .palettes = gTilesetPalettes_olivine_city_lc,
    .metatiles = gMetatiles_olivine_city_lc,
    .metatileAttributes = gMetatileAttributes_olivine_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__olivine_port_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_olivine_port_lc,
    .palettes = gTilesetPalettes_olivine_port_lc,
    .metatiles = gMetatiles_olivine_port_lc,
    .metatileAttributes = gMetatileAttributes_olivine_port_lc,
    .callback = NULL,
};

const struct Tileset gTileset__cianwood_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_cianwood_city_lc,
    .palettes = gTilesetPalettes_cianwood_city_lc,
    .metatiles = gMetatiles_cianwood_city_lc,
    .metatileAttributes = gMetatileAttributes_cianwood_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__celadon_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_celadon_city_lc,
    .palettes = gTilesetPalettes_celadon_city_lc,
    .metatiles = gMetatiles_celadon_city_lc,
    .metatileAttributes = gMetatileAttributes_celadon_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__fuchsia_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_fuchsia_city_lc,
    .palettes = gTilesetPalettes_fuchsia_city_lc,
    .metatiles = gMetatiles_fuchsia_city_lc,
    .metatileAttributes = gMetatileAttributes_fuchsia_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__route_100_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_100_lc,
    .palettes = gTilesetPalettes_route_100_lc,
    .metatiles = gMetatiles_route_100_lc,
    .metatileAttributes = gMetatileAttributes_route_100_lc,
    .callback = NULL,
};

const struct Tileset gTileset__pewter_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_pewter_city_lc,
    .palettes = gTilesetPalettes_pewter_city_lc,
    .metatiles = gMetatiles_pewter_city_lc,
    .metatileAttributes = gMetatileAttributes_pewter_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__viridian_city_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_viridian_city_lc,
    .palettes = gTilesetPalettes_viridian_city_lc,
    .metatiles = gMetatiles_viridian_city_lc,
    .metatileAttributes = gMetatileAttributes_viridian_city_lc,
    .callback = NULL,
};

const struct Tileset gTileset__route_gate_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_gate_lc,
    .palettes = gTilesetPalettes_route_gate_lc,
    .metatiles = gMetatiles_route_gate_lc,
    .metatileAttributes = gMetatileAttributes_route_gate_lc,
    .callback = NULL,
};

const struct Tileset gTileset__house1_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_house1_lc,
    .palettes = gTilesetPalettes_house1_lc,
    .metatiles = gMetatiles_house1_lc,
    .metatileAttributes = gMetatileAttributes_house1_lc,
    .callback = NULL,
};

const struct Tileset gTileset__pokemon_center_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_pokemon_center_lc,
    .palettes = gTilesetPalettes_pokemon_center_lc,
    .metatiles = gMetatiles_pokemon_center_lc,
    .metatileAttributes = gMetatileAttributes_pokemon_center_lc,
    .callback = NULL,
};

const struct Tileset gTileset__dark_cave_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_dark_cave_lc,
    .palettes = gTilesetPalettes_dark_cave_lc,
    .metatiles = gMetatiles_dark_cave_lc,
    .metatileAttributes = gMetatileAttributes_dark_cave_lc,
    .callback = NULL,
};

const struct Tileset gTileset__violet_academy_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_violet_academy_lc,
    .palettes = gTilesetPalettes_violet_academy_lc,
    .metatiles = gMetatiles_violet_academy_lc,
    .metatileAttributes = gMetatileAttributes_violet_academy_lc,
    .callback = NULL,
};

const struct Tileset gTileset__violet_gym_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_violet_gym_lc,
    .palettes = gTilesetPalettes_violet_gym_lc,
    .metatiles = gMetatiles_violet_gym_lc,
    .metatileAttributes = gMetatileAttributes_violet_gym_lc,
    .callback = NULL,
};

const struct Tileset gTileset__house2_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_house2_lc,
    .palettes = gTilesetPalettes_house2_lc,
    .metatiles = gMetatiles_house2_lc,
    .metatileAttributes = gMetatileAttributes_house2_lc,
    .callback = NULL,
};

const struct Tileset gTileset__sprout_tower_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_sprout_tower_lc,
    .palettes = gTilesetPalettes_sprout_tower_lc,
    .metatiles = gMetatiles_sprout_tower_lc,
    .metatileAttributes = gMetatileAttributes_sprout_tower_lc,
    .callback = NULL,
};

const struct Tileset gTileset__azalea_gym_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_azalea_gym_lc,
    .palettes = gTilesetPalettes_azalea_gym_lc,
    .metatiles = gMetatiles_azalea_gym_lc,
    .metatileAttributes = gMetatileAttributes_azalea_gym_lc,
    .callback = NULL,
};

const struct Tileset gTileset__slowpoke_well_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_slowpoke_well_lc,
    .palettes = gTilesetPalettes_slowpoke_well_lc,
    .metatiles = gMetatiles_slowpoke_well_lc,
    .metatileAttributes = gMetatileAttributes_slowpoke_well_lc,
    .callback = NULL,
};

const struct Tileset gTileset__ruins_of_alph_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ruins_of_alph_lc,
    .palettes = gTilesetPalettes_ruins_of_alph_lc,
    .metatiles = gMetatiles_ruins_of_alph_lc,
    .metatileAttributes = gMetatileAttributes_ruins_of_alph_lc,
    .callback = NULL,
};

const struct Tileset gTileset__ruins_of_alph_puzzle_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ruins_of_alph_puzzle_lc,
    .palettes = gTilesetPalettes_ruins_of_alph_puzzle_lc,
    .metatiles = gMetatiles_ruins_of_alph_puzzle_lc,
    .metatileAttributes = gMetatileAttributes_ruins_of_alph_puzzle_lc,
    .callback = NULL,
};

const struct Tileset gTileset__indigo_plateau_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_indigo_plateau_lc,
    .palettes = gTilesetPalettes_indigo_plateau_lc,
    .metatiles = gMetatiles_indigo_plateau_lc,
    .metatileAttributes = gMetatileAttributes_indigo_plateau_lc,
    .callback = NULL,
};

const struct Tileset gTileset__sandway_town_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_sandway_town_lc,
    .palettes = gTilesetPalettes_sandway_town_lc,
    .metatiles = gMetatiles_sandway_town_lc,
    .metatileAttributes = gMetatileAttributes_sandway_town_lc,
    .callback = NULL,
};

const struct Tileset gTileset__goldenrod_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_goldenrod_interior_lc,
    .palettes = gTilesetPalettes_goldenrod_interior_lc,
    .metatiles = gMetatiles_goldenrod_interior_lc,
    .metatileAttributes = gMetatileAttributes_goldenrod_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__fuchsia_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_fuchsia_interior_lc,
    .palettes = gTilesetPalettes_fuchsia_interior_lc,
    .metatiles = gMetatiles_fuchsia_interior_lc,
    .metatileAttributes = gMetatileAttributes_fuchsia_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__viridian_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_viridian_interior_lc,
    .palettes = gTilesetPalettes_viridian_interior_lc,
    .metatiles = gMetatiles_viridian_interior_lc,
    .metatileAttributes = gMetatileAttributes_viridian_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__city_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_city_interior_lc,
    .palettes = gTilesetPalettes_city_interior_lc,
    .metatiles = gMetatiles_city_interior_lc,
    .metatileAttributes = gMetatileAttributes_city_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__museum_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_museum_interior_lc,
    .palettes = gTilesetPalettes_museum_interior_lc,
    .metatiles = gMetatiles_museum_interior_lc,
    .metatileAttributes = gMetatileAttributes_museum_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__cerulean_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_cerulean_interior_lc,
    .palettes = gTilesetPalettes_cerulean_interior_lc,
    .metatiles = gMetatiles_cerulean_interior_lc,
    .metatileAttributes = gMetatileAttributes_cerulean_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__vermilion_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_vermilion_interior_lc,
    .palettes = gTilesetPalettes_vermilion_interior_lc,
    .metatiles = gMetatiles_vermilion_interior_lc,
    .metatileAttributes = gMetatileAttributes_vermilion_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__celadon_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_celadon_interior_lc,
    .palettes = gTilesetPalettes_celadon_interior_lc,
    .metatiles = gMetatiles_celadon_interior_lc,
    .metatileAttributes = gMetatileAttributes_celadon_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__saffron_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_saffron_interior_lc,
    .palettes = gTilesetPalettes_saffron_interior_lc,
    .metatiles = gMetatiles_saffron_interior_lc,
    .metatileAttributes = gMetatileAttributes_saffron_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__ss_aqua_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ss_aqua_lc,
    .palettes = gTilesetPalettes_ss_aqua_lc,
    .metatiles = gMetatiles_ss_aqua_lc,
    .metatileAttributes = gMetatileAttributes_ss_aqua_lc,
    .callback = NULL,
};

const struct Tileset gTileset__digletts_cave_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_digletts_cave_lc,
    .palettes = gTilesetPalettes_digletts_cave_lc,
    .metatiles = gMetatiles_digletts_cave_lc,
    .metatileAttributes = gMetatileAttributes_digletts_cave_lc,
    .callback = NULL,
};

const struct Tileset gTileset__ice_path_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ice_path_lc,
    .palettes = gTilesetPalettes_ice_path_lc,
    .metatiles = gMetatiles_ice_path_lc,
    .metatileAttributes = gMetatileAttributes_ice_path_lc,
    .callback = NULL,
};

const struct Tileset gTileset__cerulean_cave_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_cerulean_cave_lc,
    .palettes = gTilesetPalettes_cerulean_cave_lc,
    .metatiles = gMetatiles_cerulean_cave_lc,
    .metatileAttributes = gMetatileAttributes_cerulean_cave_lc,
    .callback = NULL,
};

const struct Tileset gTileset__dept_store_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_dept_store_lc,
    .palettes = gTilesetPalettes_dept_store_lc,
    .metatiles = gMetatiles_dept_store_lc,
    .metatileAttributes = gMetatileAttributes_dept_store_lc,
    .callback = NULL,
};

const struct Tileset gTileset__underground_path_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_underground_path_lc,
    .palettes = gTilesetPalettes_underground_path_lc,
    .metatiles = gMetatiles_underground_path_lc,
    .metatileAttributes = gMetatileAttributes_underground_path_lc,
    .callback = NULL,
};

const struct Tileset gTileset__lavender_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_lavender_interior_lc,
    .palettes = gTilesetPalettes_lavender_interior_lc,
    .metatiles = gMetatiles_lavender_interior_lc,
    .metatileAttributes = gMetatileAttributes_lavender_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__orange_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_orange_interior_lc,
    .palettes = gTilesetPalettes_orange_interior_lc,
    .metatiles = gMetatiles_orange_interior_lc,
    .metatileAttributes = gMetatileAttributes_orange_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__city_gym_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_city_gym_lc,
    .palettes = gTilesetPalettes_city_gym_lc,
    .metatiles = gMetatiles_city_gym_lc,
    .metatileAttributes = gMetatileAttributes_city_gym_lc,
    .callback = NULL,
};

const struct Tileset gTileset__game_corner_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_game_corner_lc,
    .palettes = gTilesetPalettes_game_corner_lc,
    .metatiles = gMetatiles_game_corner_lc,
    .metatileAttributes = gMetatileAttributes_game_corner_lc,
    .callback = NULL,
};

const struct Tileset gTileset__route_25_house_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_route_25_house_lc,
    .palettes = gTilesetPalettes_route_25_house_lc,
    .metatiles = gMetatiles_route_25_house_lc,
    .metatileAttributes = gMetatileAttributes_route_25_house_lc,
    .callback = NULL,
};

const struct Tileset gTileset__undersea_cavern_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_undersea_cavern_lc,
    .palettes = gTilesetPalettes_undersea_cavern_lc,
    .metatiles = gMetatiles_undersea_cavern_lc,
    .metatileAttributes = gMetatileAttributes_undersea_cavern_lc,
    .callback = NULL,
};

const struct Tileset gTileset__misc_interior_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_misc_interior_lc,
    .palettes = gTilesetPalettes_misc_interior_lc,
    .metatiles = gMetatiles_misc_interior_lc,
    .metatileAttributes = gMetatileAttributes_misc_interior_lc,
    .callback = NULL,
};

const struct Tileset gTileset__pokemon_league_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_pokemon_league_lc,
    .palettes = gTilesetPalettes_pokemon_league_lc,
    .metatiles = gMetatiles_pokemon_league_lc,
    .metatileAttributes = gMetatileAttributes_pokemon_league_lc,
    .callback = NULL,
};

const struct Tileset gTileset__hall_of_fame_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_hall_of_fame_lc,
    .palettes = gTilesetPalettes_hall_of_fame_lc,
    .metatiles = gMetatiles_hall_of_fame_lc,
    .metatileAttributes = gMetatileAttributes_hall_of_fame_lc,
    .callback = NULL,
};

const struct Tileset gTileset__crystal_caves_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_crystal_caves_lc,
    .palettes = gTilesetPalettes_crystal_caves_lc,
    .metatiles = gMetatiles_crystal_caves_lc,
    .metatileAttributes = gMetatileAttributes_crystal_caves_lc,
    .callback = NULL,
};

const struct Tileset gTileset__nexus_laboratory_lc =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_nexus_laboratory_lc,
    .palettes = gTilesetPalettes_nexus_laboratory_lc,
    .metatiles = gMetatiles_nexus_laboratory_lc,
    .metatileAttributes = gMetatileAttributes_nexus_laboratory_lc,
    .callback = NULL,
};

#endif // IS_FRLG
