NewBarkTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, NewBarkTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE - Not assigned.
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_NEWBARK_INTRO_STATE
	@ 1: Started Game
	@ 2: Obtained PokeGear
	@ 3: Got Starter Pokemon
	@ 4: Talked to Mom after getting Starter Pokemon
	@ 5: ?
	@ 6: ?
	@ 7: ?

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN - Not assigned.
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE - Not assigned.
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


NewBarkTown_OnTransition:
	end

NewBarkTown_OnFrame:
	.2byte 0

NewBarkTown_OnWarp:
	.2byte 0


NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_TownSign, MSGBOX_SIGN
	end

NewBarkTown_EventScript_ElmsLabSign::
	msgbox NewBarkTown_Text_ProfElmsLab, MSGBOX_SIGN
	end

NewBarkTown_EventScript_PlayersHouseSign::
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_DEFAULT
	end

NewBarkTown_EventScript_ElmsHouseSign::
	msgbox NewBarkTown_Text_ProfElmsHouse, MSGBOX_DEFAULT
	end

NewBarkTown_EventScript_FatMan::
	msgbox NewBarkTown_Text_FatMan, MSGBOX_NPC
	end

NewBarkTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_INTRO_STATE, 4, NewBarkTown_EventScript_Lass2
	msgbox NewBarkTown_Text_Lass_1, MSGBOX_NPC
	release
	end

NewBarkTown_EventScript_Lass2::
	msgbox NewBarkTown_Text_Lass_2, MSGBOX_NPC
	release
	end

NewBarkTown_EventScript_Lass_Trigger_Bottom1::
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Left_from_Bottom
	waitmovement 0
	msgbox NewBarkTown_Text_Lass_Trigger1, MSGBOX_NPC
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Right_from_Bottom
	applymovement LOCALID_PLAYER NewBarkTown_movement_Lass_Right_from_Bottom
	waitmovement 0
	release
	end

NewBarkTown_EventScript_Lass_Trigger_Top1::
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Left_from_Top
	waitmovement 0
	msgbox NewBarkTown_Text_Lass_Trigger1, MSGBOX_NPC
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Right_from_Top
	applymovement LOCALID_PLAYER NewBarkTown_movement_Lass_Right_from_Top
	waitmovement 0
	release
	end

NewBarkTown_EventScript_Lass_Trigger_Bottom2::
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Left_from_Bottom
	waitmovement 0
	msgbox NewBarkTown_Text_Lass_Trigger2, MSGBOX_NPC
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Right_from_Bottom
	applymovement LOCALID_PLAYER NewBarkTown_movement_Lass_Right_from_Bottom
	waitmovement 0
	release
	end

NewBarkTown_EventScript_Lass_Trigger_Top2::
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Left_from_Top
	waitmovement 0
	msgbox NewBarkTown_Text_Lass_Trigger2, MSGBOX_NPC
	applymovement LOCALID_NEWBARK_LASS NewBarkTown_movement_Lass_Right_from_Top
	applymovement LOCALID_PLAYER NewBarkTown_movement_Lass_Right_from_Top
	waitmovement 0
	release
	end

NewBarkTown_EventScript_Rival::
	msgbox NewBarkTown_Text_Rival_1, MSGBOX_DEFAULT
	applymovement LOCALID_NEWBARK_RIVAL NewBarkTown_movement_Rival_Face_Player
	msgbox NewBarkTown_Text_Rival_2, MSGBOX_NPC
	applymovement LOCALID_NEWBARK_RIVAL NewBarkTown_movement_Rival_Shove
	applymovement LOCALID_PLAYER NewBarkTown_movement_Player_Kicked
	waitmovement LOCALID_NEWBARK_RIVAL
	waitmovement LOCALID_PLAYER
	release
	end

NewBarkTown_Text_FatMan:
	.string "Yo, {PLAYER}!\p"
	.string "I hear PROF.ELM discovered some new\n"
	.string "POKéMON.$"

NewBarkTown_Text_TownSign:
	.string "NEW BARK TOWN\p"
	.string "“The Town Where The Winds of A New\n"
	.string "Beginning Blow”$"

NewBarkTown_Text_ProfElmsLab:
	.string "PROF. ELM'S POKéMON LAB$"

NewBarkTown_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

NewBarkTown_Text_ProfElmsHouse:
	.string "PROF. ELM'S HOUSE$"

NewBarkTown_Text_Lass_1:
	.string "Wow, your POKéGEAR is impressive!\n"
	.string "Did your mom get it for you?$"

NewBarkTown_Text_Lass_2:
	.string "Call your mom on your POKéGEAR to\n"
	.string "let her know how you're doing.$"

NewBarkTown_Text_Lass_Trigger1:
	.string "Hold on {PLAYER}.\p"
	.string "PROF.ELM wants to see you.$"

@TODO: Change this text since you have the running shoes already?
NewBarkTown_Text_Lass_Trigger2:
	.string "Oh hey, {PLAYER}.\n"
	.string "Have you talked to your MOM?\p"
	.string "I think she wants to give you\n"
	.string "something before you leave.$"

NewBarkTown_Text_Rival_1:
	.string "......\p"
	.string "So this is the famous ELM\n"
	.string "POKéMON LAB...$"

NewBarkTown_Text_Rival_2:
	.string "...What are you staring at?$"

NewBarkTown_movement_Lass_Left_from_Bottom:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NewBarkTown_movement_Lass_Right_from_Bottom:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

NewBarkTown_movement_Lass_Left_from_Top:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NewBarkTown_movement_Lass_Right_from_Top:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

NewBarkTown_movement_Rival_Face_Player:
	face_left
	step_end

NewBarkTown_movement_Rival_Shove:
	walk_left
	walk_right
	step_end

NewBarkTown_movement_Player_Kicked:
	jump_2_down
	step_end
