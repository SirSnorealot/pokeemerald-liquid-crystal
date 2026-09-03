#include "config/general.h"
#include "config/battle.h"
#include "config/item.h"
#include "constants/global.h"
#include "constants/apprentice.h"
#include "constants/apricorn_tree.h"
#include "constants/battle.h"
#include "constants/battle_arena.h"
#include "constants/battle_dome.h"
#include "constants/battle_factory.h"
#include "constants/battle_frontier.h"
#include "constants/battle_palace.h"
#include "constants/battle_pike.h"
#include "constants/battle_pyramid.h"
#include "constants/battle_special.h"
#include "constants/battle_tent.h"
#include "constants/battle_tower.h"
#include "constants/berry.h"
#include "constants/cable_club.h"
#include "constants/coins.h"
#include "constants/comparison_operators.h"
#include "constants/contest.h"
#include "constants/daycare.h"
#include "constants/decorations.h"
#include "constants/difficulty.h"
#include "constants/easy_chat.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/fame_checker.h"
#include "constants/field_effects.h"
#include "constants/field_move.h"
#include "constants/field_poison.h"
#include "constants/field_specials.h"
#include "constants/field_tasks.h"
#include "constants/field_weather.h"
#include "constants/flags.h"
#include "constants/follower_npc.h"
#include "constants/frontier_util.h"
#include "constants/game_stat.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"
#include "constants/lilycove_lady.h"
#include "constants/map_scripts.h"
#include "constants/maps.h"
#include "constants/mass_outbreak.h"
#include "constants/mauville_old_man.h"
#include "constants/metatile_labels.h"
#include "constants/move_relearner.h"
#include "constants/moves.h"
#include "constants/mystery_gift.h"
#include "constants/party_menu.h"
#include "constants/pokeball.h"
#include "constants/pokedex.h"
#include "constants/pokemon.h"
#include "constants/pokemon_size_record.h"
#include "constants/random_mon_generation.h"
#include "constants/rtc.h"
#include "constants/roulette.h"
#include "constants/script_menu.h"
#include "constants/seagallop.h"
#include "constants/secret_bases.h"
#include "constants/siirtc.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "constants/trainer_hill.h"
#include "constants/trainer_tower.h"
#include "constants/trainers.h"
#include "constants/trainer_card.h"
#include "constants/tv.h"
#include "constants/union_room.h"
#include "constants/vars.h"
#include "constants/weather.h"
#include "constants/speaker_names.h"
	.include "asm/macros.inc"
	.include "asm/macros/event.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

	.set ALLOCATE_SCRIPT_CMD_TABLE, 1
	.include "data/script_cmd_table.inc"

.align 2
gSpecialVars::
	.4byte gSpecialVar_0x8000
	.4byte gSpecialVar_0x8001
	.4byte gSpecialVar_0x8002
	.4byte gSpecialVar_0x8003
	.4byte gSpecialVar_0x8004
	.4byte gSpecialVar_0x8005
	.4byte gSpecialVar_0x8006
	.4byte gSpecialVar_0x8007
	.4byte gSpecialVar_0x8008
	.4byte gSpecialVar_0x8009
	.4byte gSpecialVar_0x800A
	.4byte gSpecialVar_0x800B
	.4byte gSpecialVar_Facing
	.4byte gSpecialVar_Result
	.4byte gSpecialVar_ItemId
	.4byte gSpecialVar_LastTalked
	.4byte gSpecialVar_ContestRank
	.4byte gSpecialVar_ContestCategory
	.4byte gSpecialVar_MonBoxId
	.4byte gSpecialVar_MonBoxPos
	.4byte gSpecialVar_Unused_0x8014
	.4byte gTrainerBattleParameter + 2 // gTrainerBattleParameter.params.opponentA

	.purgem def_special
	.set ALLOCATE_SPECIAL_TABLE, 1
	.include "data/specials.inc"

gStdScripts::
	.4byte Std_ObtainItem              @ STD_OBTAIN_ITEM
	.4byte Std_FindItem                @ STD_FIND_ITEM
	.4byte Std_MsgboxNPC               @ MSGBOX_NPC
	.4byte Std_MsgboxSign              @ MSGBOX_SIGN
	.4byte Std_MsgboxDefault           @ MSGBOX_DEFAULT
	.4byte Std_MsgboxYesNo             @ MSGBOX_YESNO
	.4byte Std_MsgboxAutoclose         @ MSGBOX_AUTOCLOSE
	.4byte Std_ObtainDecoration        @ STD_OBTAIN_DECORATION
	.4byte Std_RegisteredInMatchCall   @ STD_REGISTER_MATCH_CALL
	.4byte Std_MsgboxGetPoints         @ MSGBOX_GETPOINTS
	.4byte Std_MsgboxPokenav           @ MSGBOX_POKENAV
	.4byte Std_PutItemAway             @ STD_PUT_ITEM_AWAY
	.4byte Std_ReceivedItem            @ STD_RECEIVED_ITEM
gStdScripts_End::


	.include "data/maps/NewBarkTown/scripts.inc"
	.include "data/maps/CherrygroveCity/scripts.inc"
	.include "data/maps/VioletCity/scripts.inc"
	.include "data/maps/AzaleaTown/scripts.inc"
	.include "data/maps/GoldenrodCity/scripts.inc"
	.include "data/maps/EcruteakCity/scripts.inc"
	.include "data/maps/OlivineCity/scripts.inc"
	.include "data/maps/CianwoodCity/scripts.inc"
	.include "data/maps/MahoganyTown/scripts.inc"
	.include "data/maps/BlackthornCity/scripts.inc"
	.include "data/maps/CeladonCity/scripts.inc"
	.include "data/maps/SaffronCity/scripts.inc"
	.include "data/maps/CeruleanCity/scripts.inc"
	.include "data/maps/CinnabarIsland/scripts.inc"
	.include "data/maps/PalletTown/scripts.inc"
	.include "data/maps/ViridianCity/scripts.inc"
	.include "data/maps/LavenderTown/scripts.inc"
	.include "data/maps/VermilionCity/scripts.inc"
	.include "data/maps/FuchsiaCity/scripts.inc"
	.include "data/maps/PewterCity/scripts.inc"
	.include "data/maps/Route29/scripts.inc"
	.include "data/maps/Route30/scripts.inc"
	.include "data/maps/Route31/scripts.inc"
	.include "data/maps/Route32/scripts.inc"
	.include "data/maps/Route33/scripts.inc"
	.include "data/maps/Route34/scripts.inc"
	.include "data/maps/Route35/scripts.inc"
	.include "data/maps/Route36/scripts.inc"
	.include "data/maps/Route37/scripts.inc"
	.include "data/maps/Route38/scripts.inc"
	.include "data/maps/Route39/scripts.inc"
	.include "data/maps/Route40/scripts.inc"
	.include "data/maps/Route41/scripts.inc"
	.include "data/maps/Route42/scripts.inc"
	.include "data/maps/Route43/scripts.inc"
	.include "data/maps/Route44/scripts.inc"
	.include "data/maps/Route45/scripts.inc"
	.include "data/maps/Route46/scripts.inc"
	.include "data/maps/Route1/scripts.inc"
	.include "data/maps/Route2/scripts.inc"
	.include "data/maps/Route3/scripts.inc"
	.include "data/maps/Route4/scripts.inc"
	.include "data/maps/Route5/scripts.inc"
	.include "data/maps/Route6/scripts.inc"
	.include "data/maps/Route7/scripts.inc"
	.include "data/maps/Route8/scripts.inc"
	.include "data/maps/Route9/scripts.inc"
	.include "data/maps/Route10/scripts.inc"
	.include "data/maps/Route11/scripts.inc"
	.include "data/maps/Route12/scripts.inc"
	.include "data/maps/Route13/scripts.inc"
	.include "data/maps/Route14/scripts.inc"
	.include "data/maps/Route15/scripts.inc"
	.include "data/maps/Route16/scripts.inc"
	.include "data/maps/Route17/scripts.inc"
	.include "data/maps/Route18/scripts.inc"
	.include "data/maps/Route19/scripts.inc"
	.include "data/maps/Route20/scripts.inc"
	.include "data/maps/Route21/scripts.inc"
	.include "data/maps/Route22/scripts.inc"
	.include "data/maps/Route24/scripts.inc"
	.include "data/maps/Route25/scripts.inc"
	.include "data/maps/Route26/scripts.inc"
	.include "data/maps/Route27/scripts.inc"
	.include "data/maps/Route32_2/scripts.inc"
	.include "data/maps/Route34_2/scripts.inc"
	.include "data/maps/Route39_2/scripts.inc"
	.include "data/maps/Route42_2/scripts.inc"
	.include "data/maps/Route100/scripts.inc"
	.include "data/maps/Route100_2/scripts.inc"
	.include "data/maps/NationalPark/scripts.inc"
	.include "data/maps/RuinsOfAlph/scripts.inc"
	.include "data/maps/NewBarkTown_PlayersHouse_1F/scripts.inc"
	.include "data/maps/NewBarkTown_PlayersHouse_2F/scripts.inc"
	.include "data/maps/NewBarkTown_House1/scripts.inc"
	.include "data/maps/NewBarkTown_House2/scripts.inc"
	.include "data/maps/NewBarkTown_ProfessorElmsLab/scripts.inc"
	.include "data/maps/CherrygroveCity_PokemonCenter/scripts.inc"
	.include "data/maps/CherrygroveCity_GuidesHouse/scripts.inc"
	.include "data/maps/CherrygroveCity_Mart/scripts.inc"
	.include "data/maps/CherrygroveCity_House1/scripts.inc"
	.include "data/maps/CherrygroveCity_House2/scripts.inc"
	.include "data/maps/VioletCity_EarlsPokemonAcademy/scripts.inc"
	.include "data/maps/VioletCity_Gym/scripts.inc"
	.include "data/maps/VioletCity_House1/scripts.inc"
	.include "data/maps/VioletCity_House2/scripts.inc"
	.include "data/maps/VioletCity_PokemonCenter/scripts.inc"
	.include "data/maps/VioletCity_Mart/scripts.inc"
	.include "data/maps/Route31_GateHouse/scripts.inc"
	.include "data/maps/Route32_PokemonCenter/scripts.inc"
	.include "data/maps/Route32_RuinsOfAlphGate/scripts.inc"
	.include "data/maps/Route36_RuinsOfAlphGate/scripts.inc"
	.include "data/maps/Route34_IlexForestGate/scripts.inc"
	.include "data/maps/AzaleaTown_PokemonCenter/scripts.inc"
	.include "data/maps/AzaleaTown_House1/scripts.inc"
	.include "data/maps/AzaleaTown_Mart/scripts.inc"
	.include "data/maps/AzaleaTown_KurtsHouse/scripts.inc"
	.include "data/maps/AzaleaTown_IlexForestGate/scripts.inc"
	.include "data/maps/AzaleaTown_Gym/scripts.inc"
	.include "data/maps/Route34_PokemonDayCare/scripts.inc"
	.include "data/maps/DarkCave_VioletCitySide/scripts.inc"
	.include "data/maps/DarkCave_BlackthornCitySide/scripts.inc"
	.include "data/maps/DarkCave_DeepSection/scripts.inc"
	.include "data/maps/DarkCave_InnerSection/scripts.inc"
	.include "data/maps/SproutTower_1F/scripts.inc"
	.include "data/maps/SproutTower_2F/scripts.inc"
	.include "data/maps/SproutTower_3F/scripts.inc"
	.include "data/maps/IlexForest/scripts.inc"
	.include "data/maps/UnionCave_1F/scripts.inc"
	.include "data/maps/UnionCave_B1F/scripts.inc"
	.include "data/maps/UnionCave_B2F/scripts.inc"
	.include "data/maps/SlowpokeWell_1F/scripts.inc"
	.include "data/maps/SlowpokeWell_B1F/scripts.inc"
	.include "data/maps/RuinsOfAlph_ChamberA/scripts.inc"
	.include "data/maps/RuinsOfAlph_ResearchCenter/scripts.inc"
	.include "data/maps/RuinsOfAlph_PuzzleRoomA/scripts.inc"
	.include "data/maps/RuinsOfAlph_ChamberB/scripts.inc"
	.include "data/maps/RuinsOfAlph_ChamberC/scripts.inc"
	.include "data/maps/RuinsOfAlph_ChamberD/scripts.inc"
	.include "data/maps/RuinsOfAlph_InnerChamber/scripts.inc"
	.include "data/maps/RuinsOfAlph_PuzzleRoomB/scripts.inc"
	.include "data/scripts/shared_secret_base.inc"
	.include "data/maps/OutskirtIsland/scripts.inc"
	.include "data/maps/LakeOfRage/scripts.inc"
	.include "data/maps/Route40_2/scripts.inc"
	.include "data/maps/Route30_House1/scripts.inc"
	.include "data/maps/Route30_House2/scripts.inc"
	.include "data/maps/Route29_GateHouse/scripts.inc"
	.include "data/maps/AzaleaTown_House2/scripts.inc"
	.include "data/maps/BattleTower/scripts.inc"
	.include "data/maps/BattleTower_Room1/scripts.inc"
	.include "data/maps/BattleTower_Room2/scripts.inc"
	.include "data/maps/BlackthornCity_House1/scripts.inc"
	.include "data/maps/BlackthornCity_House2/scripts.inc"
	.include "data/maps/BlackthornCity_House3/scripts.inc"
	.include "data/maps/BlackthornCity_PokemonCenter/scripts.inc"
	.include "data/maps/BlackthornCity_Mart/scripts.inc"
	.include "data/maps/BlackthornCity_House4/scripts.inc"
	.include "data/maps/BlackthornCity_House5/scripts.inc"
	.include "data/maps/BurntTower_Room1/scripts.inc"
	.include "data/maps/BurntTower_Room2/scripts.inc"
	.include "data/maps/CaveOfWisdom/scripts.inc"
	.include "data/maps/CeladonCity_House6/scripts.inc"
	.include "data/maps/CeladonCity_House7/scripts.inc"
	.include "data/maps/CeladonCity_PokemonCenter/scripts.inc"
	.include "data/maps/CeladonCity_House8/scripts.inc"
	.include "data/maps/CeladonCity_House9/scripts.inc"
	.include "data/maps/CeladonCity_House10/scripts.inc"
	.include "data/maps/CeladonCity_House2/scripts.inc"
	.include "data/maps/CeladonCity_House3/scripts.inc"
	.include "data/maps/CeladonCity_House4/scripts.inc"
	.include "data/maps/CeladonCity_House5/scripts.inc"
	.include "data/maps/CeladonCity_House1/scripts.inc"
	.include "data/maps/CeladonCity_DepartmentStore_Room1/scripts.inc"
	.include "data/maps/CeladonCity_DepartmentStore_Room2/scripts.inc"
	.include "data/maps/CeladonCity_DepartmentStore_Room3/scripts.inc"
	.include "data/maps/CeladonCity_DepartmentStore_Room4/scripts.inc"
	.include "data/maps/CeladonCity_DepartmentStore_Room5/scripts.inc"
	.include "data/maps/CeladonCity_DepartmentStore_Room6/scripts.inc"
	.include "data/maps/CeruleanCave_Room1/scripts.inc"
	.include "data/maps/CeruleanCave_Room2/scripts.inc"
	.include "data/maps/CeruleanCave_Room3/scripts.inc"
	.include "data/maps/CeruleanCity_House1/scripts.inc"
	.include "data/maps/CeruleanCity_Mart/scripts.inc"
	.include "data/maps/CeruleanCity_House2/scripts.inc"
	.include "data/maps/CeruleanCity_House3/scripts.inc"
	.include "data/maps/CeruleanCity_House4/scripts.inc"
	.include "data/maps/CeruleanCity_PokemonCenter/scripts.inc"
	.include "data/maps/CeruleanCity_House5/scripts.inc"
	.include "data/maps/CherrygroveCity_House3/scripts.inc"
	.include "data/maps/CianwoodCity_PokemonCenter/scripts.inc"
	.include "data/maps/CianwoodCity_House7/scripts.inc"
	.include "data/maps/CianwoodCity_House1/scripts.inc"
	.include "data/maps/CianwoodCity_House2/scripts.inc"
	.include "data/maps/CianwoodCity_House3/scripts.inc"
	.include "data/maps/CianwoodCity_House4/scripts.inc"
	.include "data/maps/CianwoodCity_House5/scripts.inc"
	.include "data/maps/CianwoodCity_House6/scripts.inc"
	.include "data/maps/CinnabarIsland_PokemonCenter/scripts.inc"
	.include "data/maps/CinnabarIsland_House1/scripts.inc"
	.include "data/maps/CinnabarIsland_Room1/scripts.inc"
	.include "data/maps/CinnabarVolcano_Room1/scripts.inc"
	.include "data/maps/CinnabarVolcano_Room2/scripts.inc"
	.include "data/maps/CorsolaCave/scripts.inc"
	.include "data/maps/CrystalCaves_Room7/scripts.inc"
	.include "data/maps/CrystalCaves_Room8/scripts.inc"
	.include "data/maps/CrystalCaves_Room1/scripts.inc"
	.include "data/maps/CrystalCaves_Room2/scripts.inc"
	.include "data/maps/CrystalCaves_Room3/scripts.inc"
	.include "data/maps/CrystalCaves_Room4/scripts.inc"
	.include "data/maps/CrystalCaves_Room5/scripts.inc"
	.include "data/maps/CrystalCaves_Room6/scripts.inc"
	.include "data/maps/DiglettsCave_Room1/scripts.inc"
	.include "data/maps/DiglettsCave_Room2/scripts.inc"
	.include "data/maps/DiglettsCave_Room3/scripts.inc"
	.include "data/maps/DragonsDen_Room1/scripts.inc"
	.include "data/maps/DragonsDen_Room2/scripts.inc"
	.include "data/maps/DragonsDen_Room3/scripts.inc"
	.include "data/maps/DragonsDen_Room4/scripts.inc"
	.include "data/maps/DragonsDen_Room5/scripts.inc"
	.include "data/maps/DragonsDen_Room6/scripts.inc"
	.include "data/maps/DragonsDen_Room7/scripts.inc"
	.include "data/maps/DragonsDen_Room8/scripts.inc"
	.include "data/maps/DragonsDen_Room9/scripts.inc"
	.include "data/maps/DragonsDen_Room10/scripts.inc"
	.include "data/maps/DragonsDen_Room11/scripts.inc"
	.include "data/maps/DragonsDen_Room13/scripts.inc"
	.include "data/maps/DragonsDen_Room14/scripts.inc"
	.include "data/maps/DragonsDen_Room15/scripts.inc"
	.include "data/maps/DragonsDen_Room16/scripts.inc"
	.include "data/maps/DragonsDen_Room17/scripts.inc"
	.include "data/maps/DragonsDen_Room18/scripts.inc"
	.include "data/maps/DragonsDen_Room12/scripts.inc"
	.include "data/maps/EcruteakCity_House5/scripts.inc"
	.include "data/maps/EcruteakCity_House1/scripts.inc"
	.include "data/maps/EcruteakCity_House2/scripts.inc"
	.include "data/maps/EcruteakCity_House3/scripts.inc"
	.include "data/maps/EcruteakCity_House4/scripts.inc"
	.include "data/maps/EcruteakCity_Mart/scripts.inc"
	.include "data/maps/EcruteakCity_PokemonCenter/scripts.inc"
	.include "data/maps/EcruteakCity_House8/scripts.inc"
	.include "data/maps/EcruteakCity_House6/scripts.inc"
	.include "data/maps/EcruteakCity_House7/scripts.inc"
	.include "data/maps/EssenceTown/scripts.inc"
	.include "data/maps/EssenceTown_House1/scripts.inc"
	.include "data/maps/EssenceTown_House2/scripts.inc"
	.include "data/maps/EssenceTown_House3/scripts.inc"
	.include "data/maps/EssenceTown_PokemonCenter/scripts.inc"
	.include "data/maps/ForestOfMyth/scripts.inc"
	.include "data/maps/FuchsiaCity_House6/scripts.inc"
	.include "data/maps/FuchsiaCity_House5/scripts.inc"
	.include "data/maps/FuchsiaCity_House1/scripts.inc"
	.include "data/maps/FuchsiaCity_Mart/scripts.inc"
	.include "data/maps/FuchsiaCity_House2/scripts.inc"
	.include "data/maps/FuchsiaCity_PokemonCenter/scripts.inc"
	.include "data/maps/FuchsiaCity_House4/scripts.inc"
	.include "data/maps/FuchsiaCity_House3/scripts.inc"
	.include "data/maps/GoldenrodCity_House15/scripts.inc"
	.include "data/maps/GoldenrodCity_House16/scripts.inc"
	.include "data/maps/GoldenrodCity_House17/scripts.inc"
	.include "data/maps/GoldenrodCity_House18/scripts.inc"
	.include "data/maps/GoldenrodCity_House19/scripts.inc"
	.include "data/maps/GoldenrodCity_House1/scripts.inc"
	.include "data/maps/GoldenrodCity_House10/scripts.inc"
	.include "data/maps/GoldenrodCity_House2/scripts.inc"
	.include "data/maps/GoldenrodCity_House3/scripts.inc"
	.include "data/maps/GoldenrodCity_House4/scripts.inc"
	.include "data/maps/GoldenrodCity_House5/scripts.inc"
	.include "data/maps/GoldenrodCity_House6/scripts.inc"
	.include "data/maps/GoldenrodCity_House7/scripts.inc"
	.include "data/maps/GoldenrodCity_House8/scripts.inc"
	.include "data/maps/GoldenrodCity_House9/scripts.inc"
	.include "data/maps/GoldenrodCity_House20/scripts.inc"
	.include "data/maps/GoldenrodCity_House21/scripts.inc"
	.include "data/maps/GoldenrodCity_House22/scripts.inc"
	.include "data/maps/GoldenrodCity_House23/scripts.inc"
	.include "data/maps/GoldenrodCity_House11/scripts.inc"
	.include "data/maps/GoldenrodCity_House12/scripts.inc"
	.include "data/maps/GoldenrodCity_House13/scripts.inc"
	.include "data/maps/GoldenrodCity_House14/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room1/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room2/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room3/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room4/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room5/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room6/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room7/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room8/scripts.inc"
	.include "data/maps/GoldenrodCity_DepartmentStore_Room9/scripts.inc"
	.include "data/maps/HollowCave_Room1/scripts.inc"
	.include "data/maps/HollowCave_Room2/scripts.inc"
	.include "data/maps/HollowCave_Room3/scripts.inc"
	.include "data/maps/IcePath_Room1/scripts.inc"
	.include "data/maps/IcePath_Room2/scripts.inc"
	.include "data/maps/IcePath_Room3/scripts.inc"
	.include "data/maps/IcePath_Room4/scripts.inc"
	.include "data/maps/IcePath_Room5/scripts.inc"
	.include "data/maps/IcePath_Room6/scripts.inc"
	.include "data/maps/IcePath_Room7/scripts.inc"
	.include "data/maps/IcePath_Room8/scripts.inc"
	.include "data/maps/IndigoPlateau_Room1/scripts.inc"
	.include "data/maps/IndigoPlateau_Room2/scripts.inc"
	.include "data/maps/IndigoPlateau/scripts.inc"
	.include "data/maps/KantoOffice_Room1/scripts.inc"
	.include "data/maps/KantoOffice_Room2/scripts.inc"
	.include "data/maps/KantoOffice_Room3/scripts.inc"
	.include "data/maps/LakeOfRage_House1/scripts.inc"
	.include "data/maps/LakeOfRage_House2/scripts.inc"
	.include "data/maps/LakeOfRage_House3/scripts.inc"
	.include "data/maps/LavenderTown_House1/scripts.inc"
	.include "data/maps/LavenderTown_House2/scripts.inc"
	.include "data/maps/LavenderTown_House3/scripts.inc"
	.include "data/maps/LavenderTown_PokemonCenter/scripts.inc"
	.include "data/maps/LavenderTown_House4/scripts.inc"
	.include "data/maps/LavenderTown_House5/scripts.inc"
	.include "data/maps/LavenderTown_Mart/scripts.inc"
	.include "data/maps/LavenderTown_House6/scripts.inc"
	.include "data/maps/LeafBayCity_House1/scripts.inc"
	.include "data/maps/LeafBayCity/scripts.inc"
	.include "data/maps/LeafBayCity_House2/scripts.inc"
	.include "data/maps/LeafBayCity_House3/scripts.inc"
	.include "data/maps/LeafBayCity_House4/scripts.inc"
	.include "data/maps/LeafBayCity_House5/scripts.inc"
	.include "data/maps/LeafBayCity_DepartmentStore_Room1/scripts.inc"
	.include "data/maps/LeafBayCity_DepartmentStore_Room2/scripts.inc"
	.include "data/maps/LeafBayCity_DepartmentStore_Room3/scripts.inc"
	.include "data/maps/Lighthouse_Room1/scripts.inc"
	.include "data/maps/LostWoods/scripts.inc"
	.include "data/maps/MahoganyTown_House1/scripts.inc"
	.include "data/maps/MahoganyTown_House2/scripts.inc"
	.include "data/maps/MahoganyTown_House3/scripts.inc"
	.include "data/maps/MahoganyTown_PokemonCenter/scripts.inc"
	.include "data/maps/MahoganyTown_House4/scripts.inc"
	.include "data/maps/MandarinCity/scripts.inc"
	.include "data/maps/MandarinCity_House1/scripts.inc"
	.include "data/maps/MandarinCity_House2/scripts.inc"
	.include "data/maps/MandarinCity_House3/scripts.inc"
	.include "data/maps/MandarinCity_House4/scripts.inc"
	.include "data/maps/MandarinCity_House5/scripts.inc"
	.include "data/maps/MandarinCity_House6/scripts.inc"
	.include "data/maps/MandarinCity_House7/scripts.inc"
	.include "data/maps/MandarinCity_House8/scripts.inc"
	.include "data/maps/MandarinCity_House9/scripts.inc"
	.include "data/maps/MandarinCity_House10/scripts.inc"
	.include "data/maps/MandarinCity_House11/scripts.inc"
	.include "data/maps/MandarinCity_House12/scripts.inc"
	.include "data/maps/MandarinCity_House13/scripts.inc"
	.include "data/maps/MandarinCity_House14/scripts.inc"
	.include "data/maps/MandarinCity_House15/scripts.inc"
	.include "data/maps/MandarinCity_House16/scripts.inc"
	.include "data/maps/MandarinCity_House17/scripts.inc"
	.include "data/maps/MandarinCity_House18/scripts.inc"
	.include "data/maps/MeadowTown/scripts.inc"
	.include "data/maps/MeadowTown_PokemonCenter/scripts.inc"
	.include "data/maps/MeadowTown_House1/scripts.inc"
	.include "data/maps/MeadowTown_House2/scripts.inc"
	.include "data/maps/MeadowTown_House3/scripts.inc"
	.include "data/maps/MeadowTown_Mart/scripts.inc"
	.include "data/maps/MtMoon_Room1/scripts.inc"
	.include "data/maps/MtMoon_Room2/scripts.inc"
	.include "data/maps/MtMoon_Room3/scripts.inc"
	.include "data/maps/MtMoon/scripts.inc"
	.include "data/maps/MtMortar_Room1/scripts.inc"
	.include "data/maps/MtMortar_Room2/scripts.inc"
	.include "data/maps/MtMortar_Room3/scripts.inc"
	.include "data/maps/MtMortar_Room4/scripts.inc"
	.include "data/maps/MtMortar_Room5/scripts.inc"
	.include "data/maps/NationalPark_House1/scripts.inc"
	.include "data/maps/NationalPark_House2/scripts.inc"
	.include "data/maps/NexusLaboratory_Room3/scripts.inc"
	.include "data/maps/NexusLaboratory_Room4/scripts.inc"
	.include "data/maps/NexusLaboratory_Room5/scripts.inc"
	.include "data/maps/NexusLaboratory_Room1/scripts.inc"
	.include "data/maps/NexusLaboratory_Room2/scripts.inc"
	.include "data/maps/OldMansion_Room1/scripts.inc"
	.include "data/maps/OldMansion_Room2/scripts.inc"
	.include "data/maps/OldMansion_Room3/scripts.inc"
	.include "data/maps/OlivineCity_House4/scripts.inc"
	.include "data/maps/OlivineCity_House5/scripts.inc"
	.include "data/maps/OlivineCity_Mart/scripts.inc"
	.include "data/maps/OlivineCity_House1/scripts.inc"
	.include "data/maps/OlivineCity_House2/scripts.inc"
	.include "data/maps/OlivineCity_House3/scripts.inc"
	.include "data/maps/OlivineCity_House6/scripts.inc"
	.include "data/maps/PalletTown_House1/scripts.inc"
	.include "data/maps/PalletTown_House2/scripts.inc"
	.include "data/maps/PalletTown_House3/scripts.inc"
	.include "data/maps/PalletTown_House4/scripts.inc"
	.include "data/maps/PewterCity_Mart/scripts.inc"
	.include "data/maps/PewterCity_House1/scripts.inc"
	.include "data/maps/PewterCity_House2/scripts.inc"
	.include "data/maps/PewterCity_PokemonCenter/scripts.inc"
	.include "data/maps/PewterCity_House3/scripts.inc"
	.include "data/maps/PewterCity_House4/scripts.inc"
	.include "data/maps/PokemonLeague_Room6/scripts.inc"
	.include "data/maps/PokemonLeague_Room1/scripts.inc"
	.include "data/maps/PokemonLeague_Room2/scripts.inc"
	.include "data/maps/PokemonLeague_Room3/scripts.inc"
	.include "data/maps/PokemonLeague_Room4/scripts.inc"
	.include "data/maps/PokemonLeague_Room5/scripts.inc"
	.include "data/maps/PokemonLeague_Room7/scripts.inc"
	.include "data/maps/PowerPlant_Room1/scripts.inc"
	.include "data/maps/PowerPlant_Room3/scripts.inc"
	.include "data/maps/PowerPlant_Room2/scripts.inc"
	.include "data/maps/RadioTower_Room1/scripts.inc"
	.include "data/maps/RadioTower_Room2/scripts.inc"
	.include "data/maps/RadioTower_Room3/scripts.inc"
	.include "data/maps/RadioTower_Room4/scripts.inc"
	.include "data/maps/RadioTower_Room5/scripts.inc"
	.include "data/maps/RadioTower_Room6/scripts.inc"
	.include "data/maps/RadioTower_Room7/scripts.inc"
	.include "data/maps/RadioTower_Room8/scripts.inc"
	.include "data/maps/RadioTower_Room9/scripts.inc"
	.include "data/maps/RocketHideout_Room1/scripts.inc"
	.include "data/maps/RocketHideout_Room2/scripts.inc"
	.include "data/maps/RocketHideout_Room3/scripts.inc"
	.include "data/maps/RocketHideout_Room4/scripts.inc"
	.include "data/maps/RockTunnel_Room1/scripts.inc"
	.include "data/maps/RockTunnel_Room2/scripts.inc"
	.include "data/maps/Route100_House1/scripts.inc"
	.include "data/maps/Route100_House2/scripts.inc"
	.include "data/maps/Route100_House3/scripts.inc"
	.include "data/maps/Route100_House4/scripts.inc"
	.include "data/maps/Route100_House5/scripts.inc"
	.include "data/maps/Route100_House6/scripts.inc"
	.include "data/maps/Route100_House7/scripts.inc"
	.include "data/maps/Route10_PokemonCenter/scripts.inc"
	.include "data/maps/Route12_House1/scripts.inc"
	.include "data/maps/Route15_House1/scripts.inc"
	.include "data/maps/Route16_House1/scripts.inc"
	.include "data/maps/Route16_House2/scripts.inc"
	.include "data/maps/Route18_House1/scripts.inc"
	.include "data/maps/Route19_Room1/scripts.inc"
	.include "data/maps/Route19_House1/scripts.inc"
	.include "data/maps/Route202/scripts.inc"
	.include "data/maps/Route22_House1/scripts.inc"
	.include "data/maps/Route23/scripts.inc"
	.include "data/maps/Route23_House1/scripts.inc"
	.include "data/maps/Route25_House1/scripts.inc"
	.include "data/maps/Route26_House1/scripts.inc"
	.include "data/maps/Route26_House2/scripts.inc"
	.include "data/maps/Route27_House1/scripts.inc"
	.include "data/maps/Route28/scripts.inc"
	.include "data/maps/Route28_House1/scripts.inc"
	.include "data/maps/Route2_House3/scripts.inc"
	.include "data/maps/Route2_House4/scripts.inc"
	.include "data/maps/Route2_House1/scripts.inc"
	.include "data/maps/Route2_House2/scripts.inc"
	.include "data/maps/Route35_House1/scripts.inc"
	.include "data/maps/Route35_House2/scripts.inc"
	.include "data/maps/Route39_House1/scripts.inc"
	.include "data/maps/Route39_House2/scripts.inc"
	.include "data/maps/Route40_House1/scripts.inc"
	.include "data/maps/Route42_House1/scripts.inc"
	.include "data/maps/Route42_House2/scripts.inc"
	.include "data/maps/Route42_House3/scripts.inc"
	.include "data/maps/Route43_House1/scripts.inc"
	.include "data/maps/Route43_House2/scripts.inc"
	.include "data/maps/Route47/scripts.inc"
	.include "data/maps/Route48/scripts.inc"
	.include "data/maps/Route49/scripts.inc"
	.include "data/maps/Route49_House1/scripts.inc"
	.include "data/maps/Route50/scripts.inc"
	.include "data/maps/Route50_2/scripts.inc"
	.include "data/maps/Route50_House1/scripts.inc"
	.include "data/maps/Route50_Room1/scripts.inc"
	.include "data/maps/Route51/scripts.inc"
	.include "data/maps/Route52/scripts.inc"
	.include "data/maps/Route53/scripts.inc"
	.include "data/maps/Route54/scripts.inc"
	.include "data/maps/Route54_House1/scripts.inc"
	.include "data/maps/Route55/scripts.inc"
	.include "data/maps/Route55_2/scripts.inc"
	.include "data/maps/Route56/scripts.inc"
	.include "data/maps/Route56_House1/scripts.inc"
	.include "data/maps/Route57/scripts.inc"
	.include "data/maps/Route57_Room1/scripts.inc"
	.include "data/maps/Route57_Room2/scripts.inc"
	.include "data/maps/Route58/scripts.inc"
	.include "data/maps/Route58_House1/scripts.inc"
	.include "data/maps/Route59/scripts.inc"
	.include "data/maps/Route59_House1/scripts.inc"
	.include "data/maps/Route59_House2/scripts.inc"
	.include "data/maps/Route59_Room1/scripts.inc"
	.include "data/maps/Route59_House3/scripts.inc"
	.include "data/maps/Route5_House2/scripts.inc"
	.include "data/maps/Route5_House3/scripts.inc"
	.include "data/maps/Route5_House1/scripts.inc"
	.include "data/maps/Route6_House1/scripts.inc"
	.include "data/maps/Route6_House2/scripts.inc"
	.include "data/maps/Route7_House1/scripts.inc"
	.include "data/maps/Route8_House1/scripts.inc"
	.include "data/maps/Route92/scripts.inc"
	.include "data/maps/RuinsOfAlph2/scripts.inc"
	.include "data/maps/SSAqua_Room3/scripts.inc"
	.include "data/maps/SSAqua_Room1/scripts.inc"
	.include "data/maps/SSAqua_Room2/scripts.inc"
	.include "data/maps/SSAqua_Room4/scripts.inc"
	.include "data/maps/SSAqua_Room5/scripts.inc"
	.include "data/maps/SSAqua_Room6/scripts.inc"
	.include "data/maps/SSAqua_Room7/scripts.inc"
	.include "data/maps/SSAqua_Room8/scripts.inc"
	.include "data/maps/SSAqua_Room9/scripts.inc"
	.include "data/maps/SSAqua_Room10/scripts.inc"
	.include "data/maps/SSAqua_Room11/scripts.inc"
	.include "data/maps/SafariTown/scripts.inc"
	.include "data/maps/SafariTown_House1/scripts.inc"
	.include "data/maps/SafariTown_Mart/scripts.inc"
	.include "data/maps/SafariTown_House2/scripts.inc"
	.include "data/maps/SafariTown_House3/scripts.inc"
	.include "data/maps/SafariTown_House4/scripts.inc"
	.include "data/maps/SafariTown_House5/scripts.inc"
	.include "data/maps/SafariTown_House6/scripts.inc"
	.include "data/maps/SafariTown_2/scripts.inc"
	.include "data/maps/SafariTown_3/scripts.inc"
	.include "data/maps/SafariTown_4/scripts.inc"
	.include "data/maps/SafariZone/scripts.inc"
	.include "data/maps/SafariZone_2/scripts.inc"
	.include "data/maps/SafariZone_3/scripts.inc"
	.include "data/maps/SafariZone_4/scripts.inc"
	.include "data/maps/SaffronCity_House2/scripts.inc"
	.include "data/maps/SaffronCity_House3/scripts.inc"
	.include "data/maps/SaffronCity_House9/scripts.inc"
	.include "data/maps/SaffronCity_House10/scripts.inc"
	.include "data/maps/SaffronCity_House4/scripts.inc"
	.include "data/maps/SaffronCity_House5/scripts.inc"
	.include "data/maps/SaffronCity_Mart/scripts.inc"
	.include "data/maps/SaffronCity_PokemonCenter/scripts.inc"
	.include "data/maps/SaffronCity_House6/scripts.inc"
	.include "data/maps/SaffronCity_House7/scripts.inc"
	.include "data/maps/SaffronCity_House8/scripts.inc"
	.include "data/maps/SaffronCity_House1/scripts.inc"
	.include "data/maps/SandwayTown/scripts.inc"
	.include "data/maps/SandwayTown_House1/scripts.inc"
	.include "data/maps/SandwayTown_House2/scripts.inc"
	.include "data/maps/SandwayTown_House3/scripts.inc"
	.include "data/maps/SandwayTown_House4/scripts.inc"
	.include "data/maps/SandwayTown_House5/scripts.inc"
	.include "data/maps/SeafoamIslands_Room1/scripts.inc"
	.include "data/maps/SeafoamIslands_Room2/scripts.inc"
	.include "data/maps/SeafoamIslands_Room3/scripts.inc"
	.include "data/maps/SeafoamIslands_Room4/scripts.inc"
	.include "data/maps/SeafoamIslands_Room5/scripts.inc"
	.include "data/maps/SeafoamIslands_Room6/scripts.inc"
	.include "data/maps/SilphCo_Room2/scripts.inc"
	.include "data/maps/SilphCo_Room3/scripts.inc"
	.include "data/maps/SilphCo_Room4/scripts.inc"
	.include "data/maps/SilphCo_Room1/scripts.inc"
	.include "data/maps/SilverCave/scripts.inc"
	.include "data/maps/SilverCave_Room1/scripts.inc"
	.include "data/maps/SilverCave_Room2/scripts.inc"
	.include "data/maps/SilverCave_Room3/scripts.inc"
	.include "data/maps/SilverCave_Room4/scripts.inc"
	.include "data/maps/SpecialHq_Room1/scripts.inc"
	.include "data/maps/TempleOfRock/scripts.inc"
	.include "data/maps/TinTower_Room1/scripts.inc"
	.include "data/maps/TinTower_Room2/scripts.inc"
	.include "data/maps/TinTower_Room12/scripts.inc"
	.include "data/maps/TinTower_Room3/scripts.inc"
	.include "data/maps/TinTower_Room4/scripts.inc"
	.include "data/maps/TinTower_Room5/scripts.inc"
	.include "data/maps/TinTower_Room6/scripts.inc"
	.include "data/maps/TinTower_Room7/scripts.inc"
	.include "data/maps/TinTower_Room8/scripts.inc"
	.include "data/maps/TinTower_Room9/scripts.inc"
	.include "data/maps/TinTower_Room10/scripts.inc"
	.include "data/maps/TinTower_Room11/scripts.inc"
	.include "data/maps/TohjoFalls/scripts.inc"
	.include "data/maps/UndergroundPath/scripts.inc"
	.include "data/maps/UnderseaCavern_Room7/scripts.inc"
	.include "data/maps/UnderseaCavern_Room8/scripts.inc"
	.include "data/maps/UnderseaCavern_Room9/scripts.inc"
	.include "data/maps/UnderseaCavern_Room2/scripts.inc"
	.include "data/maps/UnderseaCavern_Room3/scripts.inc"
	.include "data/maps/UnderseaCavern_Room4/scripts.inc"
	.include "data/maps/UnderseaCavern_Room1/scripts.inc"
	.include "data/maps/UnderseaCavern_Room5/scripts.inc"
	.include "data/maps/UnderseaCavern_Room6/scripts.inc"
	.include "data/maps/ValenciaIsland_House1/scripts.inc"
	.include "data/maps/ValenciaPort/scripts.inc"
	.include "data/maps/ValenciaPort_2/scripts.inc"
	.include "data/maps/ValenciaPort_House1/scripts.inc"
	.include "data/maps/VermilionCity_House1/scripts.inc"
	.include "data/maps/VermilionCity_PokemonCenter/scripts.inc"
	.include "data/maps/VermilionCity_House2/scripts.inc"
	.include "data/maps/VermilionCity_House3/scripts.inc"
	.include "data/maps/VermilionCity_Mart/scripts.inc"
	.include "data/maps/VermilionCity_House4/scripts.inc"
	.include "data/maps/VermilionCity_House5/scripts.inc"
	.include "data/maps/VictoryRoad_Room1/scripts.inc"
	.include "data/maps/VictoryRoad_Room2/scripts.inc"
	.include "data/maps/VictoryRoad_Room3/scripts.inc"
	.include "data/maps/VioletCity_House3/scripts.inc"
	.include "data/maps/ViridianCity_House1/scripts.inc"
	.include "data/maps/ViridianCity_House2/scripts.inc"
	.include "data/maps/ViridianCity_House3/scripts.inc"
	.include "data/maps/ViridianCity_PokemonCenter/scripts.inc"
	.include "data/maps/ViridianCity_House4/scripts.inc"
	.include "data/maps/ViridianCity_Mart/scripts.inc"
	.include "data/maps/ViridianForest/scripts.inc"
	.include "data/maps/WestValePort/scripts.inc"
	.include "data/maps/WestValePort_House1/scripts.inc"
	.include "data/maps/WestValePort_House2/scripts.inc"
	.include "data/maps/WestValePort_House3/scripts.inc"
	.include "data/maps/WestValePort_House4/scripts.inc"
	.include "data/maps/WestValePort_Mart/scripts.inc"
	.include "data/maps/WestValePort_House5/scripts.inc"
	.include "data/maps/WhirlIslands_Room1/scripts.inc"
	.include "data/maps/WhirlIslands_Room2/scripts.inc"
	.include "data/maps/WhirlIslands_Room3/scripts.inc"

.if IS_FRLG

@ FRLG scripts

	.include "data/scripts/trainer_tower.inc"
	.include "data/scripts/fame_checker_frlg.inc"
	.include "data/text/fame_checker_frlg.inc"
	.include "data/scripts/item_ball_scripts_frlg.inc"
	.include "data/scripts/silphco_doors.inc"
	.include "data/scripts/move_tutors_frlg.inc"
	.include "data/scripts/cable_club_frlg.inc"
	.include "data/scripts/trainer_card_frlg.inc"
	.include "data/text/trainer_card_frlg.inc"
	.include "data/scripts/mystery_event_club.inc"
	.include "data/scripts/day_care_frlg.inc"
	.include "data/text/day_care_frlg.inc"
	.include "data/scripts/seagallop.inc"
	.include "data/scripts/static_pokemon.inc"
	.include "data/scripts/aide.inc"
	.include "data/scripts/pokemon_mansion.inc"
	.include "data/scripts/pokemon_league.inc"
	.include "data/scripts/route23.inc"
	.include "data/text/new_game_intro_frlg.inc"
	.include "data/scripts/trainers_frlg.inc"
	.include "data/text/trainers_frlg.inc"
	.include "data/text/ingame_trade_frlg.inc"
	.include "data/scripts/flavor_text.inc"
	.include "data/scripts/pkmn_center_nurse_frlg.inc"

.endif

	.include "data/scripts/std_msgbox.inc"
	.include "data/scripts/trainer_battle.inc"
	.include "data/scripts/new_game.inc"
	.include "data/scripts/hall_of_fame.inc"
	.include "data/scripts/hall_of_fame_frlg.inc"

	.include "data/scripts/config.inc"
	.include "data/scripts/debug.inc"

EventScript_WhiteOut::
	call EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	goto EventScript_ResetMrBriney
	end

EventScript_AfterWhiteOutHeal::
	lockall
	msgbox gText_FirstShouldRestoreMonsHealth
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	call_if_unset FLAG_DEFEATED_RUSTBORO_GYM, EventScript_AfterWhiteOutHealMsgPreFirstBoss
	call_if_set FLAG_DEFEATED_RUSTBORO_GYM, EventScript_AfterWhiteOutHealMsg
	applymovement VAR_LAST_TALKED, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

EventScript_AfterWhiteOutHealMsgPreFirstBoss::
	msgbox gText_MonsHealedShouldBuyPotions
	return

EventScript_AfterWhiteOutHealMsg::
	msgbox gText_MonsHealed
	return

EventScript_AfterWhiteOutMomHeal::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox gText_HadQuiteAnExperienceTakeRest
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox gText_MomExplainHPGetPotions
	fadedefaultbgm
	releaseall
	end

EventScript_ResetMrBriney::
	goto_if_eq VAR_BRINEY_LOCATION, 1, EventScript_MoveMrBrineyToHouse
	goto_if_eq VAR_BRINEY_LOCATION, 2, EventScript_MoveMrBrineyToDewford
	goto_if_eq VAR_BRINEY_LOCATION, 3, EventScript_MoveMrBrineyToRoute109
	end

EventScript_MoveMrBrineyToHouse::
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	end

EventScript_MoveMrBrineyToDewford::
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	end

EventScript_MoveMrBrineyToRoute109::
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	end

EverGrandeCity_HallOfFame_EventScript_ResetEliteFour::
	clearflag FLAG_DEFEATED_ELITE_4_SIDNEY
	clearflag FLAG_DEFEATED_ELITE_4_PHOEBE
	clearflag FLAG_DEFEATED_ELITE_4_GLACIA
	clearflag FLAG_DEFEATED_ELITE_4_DRAKE
	setvar VAR_ELITE_4_STATE, 0
	return

Common_EventScript_UpdateBrineyLocation::
	goto_if_unset FLAG_RECEIVED_POKENAV, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, Common_EventScript_NopReturn
	goto_if_unset FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT, EventScript_SetBrineyLocation_House
	goto_if_unset FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN, EventScript_SetBrineyLocation_Dewford
	goto_if_unset FLAG_HIDE_ROUTE_109_MR_BRINEY, EventScript_SetBrineyLocation_Route109
	return

EventScript_SetBrineyLocation_House::
	setvar VAR_BRINEY_LOCATION, 1
	return

EventScript_SetBrineyLocation_Dewford::
	setvar VAR_BRINEY_LOCATION, 2
	return

EventScript_SetBrineyLocation_Route109::
	setvar VAR_BRINEY_LOCATION, 3
	return

	.include "data/scripts/pkmn_center_nurse.inc"
	.include "data/scripts/obtain_item.inc"
	.include "data/scripts/record_mix.inc"
	.include "data/scripts/pc.inc"
	.include "data/scripts/move_relearner.inc"

@ scripts/notices.inc? signs.inc? See comment about text/notices.inc
Common_EventScript_ShowPokemartSign::
	msgbox gText_PokemartSign, MSGBOX_SIGN
	end

Common_EventScript_ShowPokemonCenterSign::
	msgbox gText_PokemonCenterSign, MSGBOX_SIGN
	end

Common_ShowEasyChatScreen::
	fadescreen FADE_TO_BLACK
	special ShowEasyChatScreen
	fadescreen FADE_FROM_BLACK
	return

Common_EventScript_ReadyPetalburgGymForBattle::
	clearflag FLAG_HIDE_PETALBURG_GYM_GREETER
	setflag FLAG_PETALBURG_MART_EXPANDED_ITEMS
	return

Common_EventScript_BufferTrendyPhrase::
	dotimebasedevents
	setvar VAR_0x8004, 0
	special BufferTrendyPhraseString
	return

EventScript_BackupMrBrineyLocation::
	copyvar VAR_0x8008, VAR_BRINEY_LOCATION
	setvar VAR_BRINEY_LOCATION, 0
	return

	.include "data/scripts/surf.inc"
	.include "data/scripts/rival_graphics.inc"
	.include "data/scripts/set_gym_trainers.inc"

EventScript_CancelMessageBox::
	special UseBlankMessageToCancelPokemonPic
	release
	end

Common_EventScript_ShowBagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

Common_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	return

EventScript_BagIsFull::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox gText_TooBadBagIsFull
	release
	end

Common_EventScript_ShowNoRoomForDecor::
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	release
	end

Common_EventScript_NoRoomForDecor::
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	return

Common_EventScript_SetAbnormalWeather::
	setweather WEATHER_ABNORMAL
	return

Common_EventScript_PlayGymBadgeFanfare::
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	return

Common_EventScript_OutOfCenterPartyHeal::
	fadescreenswapbuffers FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	fadescreenswapbuffers FADE_FROM_BLACK
	return

EventScript_RegionMap::
	lockall
	msgbox Common_Text_LookCloserAtMap, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special FieldShowRegionMap
	releaseall
	end

Common_EventScript_PlayBrineysBoatMusic::
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_SAILING, FALSE
	return

Common_EventScript_StopBrineysBoatMusic::
	clearflag FLAG_DONT_TRANSITION_MUSIC
	fadedefaultbgm
	return

	.include "data/scripts/prof_birch.inc"

@ Below could be split as ferry.inc aside from the Rusturf tunnel script
Common_EventScript_FerryDepart::
	delay 60
	applymovement VAR_0x8004, Movement_FerryDepart
	waitmovement 0
	return

Movement_FerryDepart:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

EventScript_HideMrBriney::
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 0
	return

RusturfTunnel_EventScript_SetRusturfTunnelOpen::
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WANDA
	setvar VAR_RUSTURF_TUNNEL_STATE, 6
	setflag FLAG_RUSTURF_TUNNEL_OPENED
	return

EventScript_UnusedBoardFerry::
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	showplayer
	delay 30
	applymovement LOCALID_PLAYER, Movement_UnusedBoardFerry
	waitmovement 0
	delay 30
	return

Movement_UnusedBoardFerry:
	walk_up
	step_end

Common_EventScript_FerryDepartIsland::
	call_if_eq VAR_FACING, DIR_SOUTH, Ferry_EventScript_DepartIslandSouth
	call_if_eq VAR_FACING, DIR_WEST, Ferry_EventScript_DepartIslandWest
	delay 30
	hideplayer
	call Common_EventScript_FerryDepart
	return

	.include "data/scripts/cave_of_origin.inc"
	.include "data/scripts/kecleon.inc"

Common_EventScript_NameReceivedPartyMon::
	fadescreen FADE_TO_BLACK
	special ChangePokemonNickname
	return

Common_EventScript_PlayerHandedOverTheItem::
	bufferitemname STR_VAR_1, VAR_0x8004
	playfanfare MUS_OBTAIN_TMHM
	message gText_PlayerHandedOverTheItem
	waitmessage
	waitfanfare
	removeitem VAR_0x8004
	return

	.include "data/scripts/elite_four.inc"
	.include "data/scripts/movement.inc"
	.include "data/scripts/check_furniture.inc"
	.include "data/scripts/mart_clerk.inc"
	.include "data/text/record_mix.inc"
	.include "data/text/pc.inc"
	.include "data/text/pkmn_center_nurse.inc"
	.include "data/text/obtain_item.inc"
	.include "data/text/move_relearner.inc"

@ The below and surf.inc could be split into some text/notices.inc
gText_PokemartSign::
	.string "“Selected items for your convenience!”\n"
	.string "POKéMON MART$"

gText_PokemonCenterSign::
	.string "“Rejuvenate your tired partners!”\n"
	.string "POKéMON CENTER$"

gText_MomOrDadMightLikeThisProgram::
	.string "{STR_VAR_1} might like this program.\n"
	.string "… … … … … … … … … … … … … … … …\p"
	.string "Better get going!$"

gText_WhichFloorWouldYouLike::
	.string "Welcome to LILYCOVE DEPARTMENT STORE.\p"
	.string "Which floor would you like?$"

gText_SandstormIsVicious::
	.string "The sandstorm is vicious.\n"
	.string "It's impossible to keep going.$"

gText_SelectWithoutRegisteredItem::
	.string "An item in the BAG can be\n"
	.string "registered to SELECT for easy use.$"

gText_PokemonTrainerSchoolEmail::
	.string "There's an e-mail from POKéMON TRAINER\n"
	.string "SCHOOL.\p"
	.string "… … … … … …\p"
	.string "A POKéMON may learn up to four moves.\p"
	.string "A TRAINER's expertise is tested on the\n"
	.string "move sets chosen for POKéMON.\p"
	.string "… … … … … …$"

gText_PlayerHouseBootPC::
	.string "{PLAYER} booted up the PC.$"

gText_PokeblockLinkCanceled::
	.string "The link was canceled.$"

gText_UnusedNicknameReceivedPokemon::
	.string "Want to give a nickname to\n"
	.string "the {STR_VAR_2} you received?$"

gText_PlayerWhitedOut::
	.string "{PLAYER} is out of usable\n"
	.string "POKéMON!\p{PLAYER} whited out!$"

gText_FirstShouldRestoreMonsHealth::
	.string "First, you should restore your\n"
	.string "POKéMON to full health.$"

gText_MonsHealedShouldBuyPotions::
	.string "Your POKéMON have been healed\n"
	.string "to perfect health.\p"
	.string "If your POKéMON's energy, HP,\n"
	.string "is down, please come see us.\p"
	.string "If you're planning to go far in the\n"
	.string "field, you should buy some POTIONS\l"
	.string "at the POKéMON MART.\p"
	.string "We hope you excel!$"

gText_MonsHealed::
	.string "Your POKéMON have been healed\n"
	.string "to perfect health.\p"
	.string "We hope you excel!$"

gText_HadQuiteAnExperienceTakeRest::
	.string "MOM: {PLAYER}!\n"
	.string "Welcome home.\p"
	.string "It sounds like you had quite\n"
	.string "an experience.\p"
	.string "Maybe you should take a quick\n"
	.string "rest.$"

gText_MomExplainHPGetPotions::
	.string "MOM: Oh, good! You and your\n"
	.string "POKéMON are looking great.\p"
	.string "I just heard from {STR_VAR_1}.\p"
	.string "He said that POKéMON's energy is\n"
	.string "measured in HP.\p"
	.string "If your POKéMON lose their HP,\n"
	.string "you can restore them at any\l"
	.string "POKéMON CENTER.\p"
	.string "If you're going to travel far away,\n"
	.string "the smart TRAINER stocks up on\l"
	.string "POTIONS at the POKéMON MART.\p"
	.string "Make me proud, honey!\p"
	.string "Take care!$"

gText_RegisteredTrainerinPokeNav::
	.string "Registered {STR_VAR_1} {STR_VAR_2}\n"
	.string "in the POKéNAV.$"

gText_ComeBackWithSecretPower::
	.string "Do you know the TM SECRET POWER?\p"
	.string "Our group, we love the TM SECRET\n"
	.string "POWER.\p"
	.string "One of our members will give it to you.\n"
	.string "Come back and show me if you get it.\p"
	.string "We'll accept you as a member and sell\n"
	.string "you good stuff in secrecy.$"

gText_PokerusExplanation::
	.string "Your POKéMON may be infected with\n"
	.string "POKéRUS.\p"
	.string "Little is known about the POKéRUS\n"
	.string "except that they are microscopic life-\l"
	.string "forms that attach to POKéMON.\p"
	.string "While infected, POKéMON are said to\n"
	.string "grow exceptionally well.$"

	.include "data/text/surf.inc"

gText_DoorOpenedFarAway::
	.string "It sounded as if a door opened\n"
	.string "somewhere far away.$"

gText_BigHoleInTheWall::
	.string "There is a big hole in the wall.$"

gText_SorryWirelessClubAdjustments::
	.string "I'm terribly sorry.\n"
	.string "The POKéMON WIRELESS CLUB is\l"
	.string "undergoing adjustments now.$"

gText_UndergoingAdjustments::
	.string "It appears to be undergoing\n"
	.string "adjustments…$"

@ Unused
gText_SorryTradeCenterInspections::
	.string "I'm terribly sorry. The TRADE CENTER\n"
	.string "is undergoing inspections.$"

@ Unused
gText_SorryRecordCornerPreparation::
	.string "I'm terribly sorry. The RECORD CORNER\n"
	.string "is under preparation.$"

gText_PlayerHandedOverTheItem::
	.string "{PLAYER} handed over the\n"
	.string "{STR_VAR_1}.$"

gText_ThankYouForAccessingMysteryGift::
	.string "Thank you for accessing the\n"
	.string "MYSTERY GIFT System.$"

gText_PlayerFoundOneTMHM::
	.string "{PLAYER} found one {STR_VAR_1}\n"
	.string "{STR_VAR_2}!$"

gText_PlayerFoundTMHMs::
	.string "{PLAYER} found {STR_VAR_3} {STR_VAR_1}\n"
	.string "{STR_VAR_2}!$"

gText_Sudowoodo_Attacked::
	.string "The weird tree doesn't like the\n"
	.string "WAILMER PAIL!\p"
	.string "The weird tree attacked!$"

gText_LegendaryFlewAway::
	.string "The {STR_VAR_1} flew away!$"

gText_WantWhichFloor::
	.string "Which floor do you want?$"

	.include "data/text/pc_transfer.inc"
	.include "data/text/questionnaire.inc"
	.include "data/text/abnormal_weather.inc"

EventScript_GetInGameTradeSpeciesInfo::
	copyvar VAR_0x8005, VAR_0x8008
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	return

EventScript_ChooseMonForInGameTrade::
	special ChoosePartyMon
	lock
	faceplayer
	return

EventScript_GetInGameTradeSpecies::
	specialvar VAR_RESULT, GetTradeSpecies
	return

EventScript_DoInGameTrade::
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	lock
	faceplayer
	return

EventScript_SelectWithoutRegisteredItem::
	msgbox gText_SelectWithoutRegisteredItem, MSGBOX_SIGN
	end

	.include "data/scripts/field_poison.inc"

Common_EventScript_NopReturn::
	return

EventScript_SetResultTrue::
	setvar VAR_RESULT, TRUE
	return

EventScript_SetResultFalse::
	setvar VAR_RESULT, FALSE
	return

EventScript_GetElevatorFloor::
	special GetElevatorFloor
	return

@ Unused
EventScript_CableClub_SetVarResult1::
	setvar VAR_RESULT, 1
	return

EventScript_CableClub_SetVarResult0::
	setvar VAR_RESULT, 0
	return

Common_EventScript_UnionRoomAttendant::
#if IS_FRLG
	call CableClub_EventScript_UnionRoomAttendant_Frlg
#else
	call CableClub_EventScript_UnionRoomAttendant
#endif
	end

Common_EventScript_WirelessClubAttendant::
#if IS_FRLG
	call CableClub_EventScript_WirelessClubAttendant_Frlg
#else
	call CableClub_EventScript_WirelessClubAttendant
#endif
	end

Common_EventScript_DirectCornerAttendant::
#if IS_FRLG
	call CableClub_EventScript_DirectCornerAttendant_Frlg
#else
	call CableClub_EventScript_DirectCornerAttendant
#endif
	end

Common_EventScript_RemoveStaticPokemon::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

Common_EventScript_LegendaryFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	release
	end

EventScript_VsSeekerChargingDone::
	special VsSeekerFreezeObjectsAfterChargeComplete
	waitstate
	special VsSeekerResetObjectMovementAfterChargeComplete
	releaseall
	end

@ FRLG scripts

EventScript_SetExitingCyclingRoad::
	lockall
	clearflag FLAG_SYS_ON_CYCLING_ROAD
	setvar VAR_MAP_SCENE_ROUTE16, 0
	releaseall
	end

EventScript_SetEnteringCyclingRoad::
	lockall
	setvar VAR_MAP_SCENE_ROUTE16, 1
	releaseall
	end

EventScript_TryDarkenRuins::
	goto_if_set FLAG_SYS_UNLOCKED_TANOBY_RUINS, Common_EventScript_NopReturn
	setweather WEATHER_SHADE
	doweather
	return

Text_MonFlewAway::
	.string "The {STR_VAR_1} flew away!$"

@ Call for legendary bird trio
Text_Gyaoo::
	.string "Gyaoo!$"

EventScript_BrailleCursorWaitButton::
	special BrailleCursorToggle
	waitbuttonpress
	closebraillemessage
	playse SE_SELECT
	setvar VAR_0x8006, 1
	special BrailleCursorToggle
	return

EventScript_PalletTown_PlayersHouse_2F_ShutDownPC::
	setvar VAR_0x8004, PC_LOCATION_PLAYER_HOUSE_FRLG
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

EventScript_PalletTown_PlayersHouse_2F_TurnOnPC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_PLAYER_HOUSE_FRLG
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC
	special BedroomPC
	releaseall
	end


	.include "data/scripts/pc_transfer.inc"
	.include "data/scripts/questionnaire.inc"
	.include "data/scripts/abnormal_weather.inc"
	.include "data/scripts/trainer_script.inc"
	.include "data/scripts/berry_tree.inc"
	.include "data/scripts/secret_base.inc"
	.include "data/scripts/cable_club.inc"
	.include "data/text/cable_club.inc"
	.include "data/scripts/contest_hall.inc"
	.include "data/scripts/tv.inc"
	.include "data/text/tv.inc"
	.include "data/scripts/interview.inc"
	.include "data/scripts/gabby_and_ty.inc"
	.include "data/text/pokemon_news.inc"
	.include "data/scripts/mauville_man.inc"
	.include "data/scripts/field_move_scripts.inc"
	.include "data/scripts/item_ball_scripts.inc"
	.include "data/scripts/profile_man.inc"
	.include "data/scripts/day_care.inc"
	.include "data/scripts/flash.inc"
	.include "data/scripts/players_house.inc"
	.include "data/scripts/berry_blender.inc"
	.include "data/text/mauville_man.inc"
	.include "data/text/trainers.inc"
	.include "data/scripts/repel.inc"
	.include "data/scripts/safari_zone.inc"
	.include "data/scripts/roulette.inc"
	.include "data/scripts/pokedex_rating.inc"
	.include "data/text/pokedex_rating.inc"
	.include "data/text/lottery_corner.inc"
	.include "data/text/event_ticket_1.inc"
	.include "data/text/braille.inc"
	.include "data/text/berries.inc"
	.include "data/text/shoal_cave.inc"
	.include "data/text/check_furniture.inc"
	.include "data/scripts/cave_hole.inc"
	.include "data/scripts/lilycove_lady.inc"
	.include "data/text/match_call.inc"
	.include "data/scripts/apprentice.inc"
	.include "data/text/apprentice.inc"
	.include "data/scripts/battle_pike.inc"
	.include "data/text/blend_master.inc"
	.include "data/text/battle_tent.inc"
	.include "data/text/event_ticket_2.inc"
	.include "data/text/move_tutors.inc"
	.include "data/scripts/move_tutors.inc"
	.include "data/scripts/trainer_hill.inc"
	.include "data/scripts/test_signpost.inc"
	.include "data/scripts/follower.inc"
	.include "data/text/save.inc"
	.include "data/text/birch_speech.inc"
	.include "data/scripts/dexnav.inc"
	.include "data/scripts/battle_frontier.inc"
	.include "data/scripts/apricorn_tree.inc"
	.include "data/scripts/wild_encounter.inc"
	.include "data/text/removed_maps_text.inc"
