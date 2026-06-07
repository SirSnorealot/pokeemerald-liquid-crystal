NewBarkTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_PlayersHouse_2F_OnTransition
	@map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_BrendansHouse_2F_OnWarp
	.byte 0

NewBarkTown_PlayersHouse_2F_OnTransition:
	call_if_unset FLAG_SYS_B_DASH, NewBarkTown_PlayersHouse_2F_SetUpNewGame_Script
	@call_if_lt VAR_LITTLEROOT_RIVAL_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_CheckSetReadyToMeetBrendan
	@call_if_ge VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_BrendansHouse_2F_EventScript_CheckShouldUpdateBrendanPos
	@call_if_eq VAR_NEWBARK_INTRO_STATE, 4, PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	@call SecretBase_EventScript_SetDecorationFlags
	@setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

@ LittlerootTown_BrendansHouse_2F_EventScript_CheckShouldUpdateBrendanPos::
@ 	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos
@ 	goto_if_ge VAR_BIRCH_LAB_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_Ret
@ 	goto LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos



@ LittlerootTown_BrendansHouse_2F_EventScript_Ret::
@ 	return

@ LittlerootTown_BrendansHouse_2F_EventScript_CheckSetReadyToMeetBrendan::
@ 	checkplayergender
@ 	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_BrendansHouse_2F_EventScript_SetReadyToMeetBrendan
@ 	return

@ LittlerootTown_BrendansHouse_2F_EventScript_SetReadyToMeetBrendan::
@ 	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
@ 	return

@ LittlerootTown_BrendansHouse_2F_OnWarp:
@ 	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_BrendansHouse_2F_EventScript_CheckInitDecor
@ 	.2byte 0

@ LittlerootTown_BrendansHouse_2F_EventScript_CheckInitDecor::
@ 	checkplayergender
@ 	goto_if_eq VAR_RESULT, MALE, SecretBase_EventScript_InitDecorations
@ 	end

NewBarkTown_PlayersHouse_2F_SetUpNewGame_Script::
	setrespawn HEAL_LOCATION_NEWBARK_TOWN_PLAYERS_HOUSE_2F
	setflag FLAG_SYS_B_DASH
	setflag FLAG_VISITED_NEWBARK_TOWN
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	setvar VAR_NEWBARK_INTRO_STATE, 1
	return

NewBarkTown_PlayersHouse_2F_EventScript_CheckPlayersPC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	releaseall
	end

NewBarkTown_PlayersHouse_2F_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

PlayersHouse_2F_EventScript_GameCube::
	msgbox PlayersHouse_2F_Text_PlayNES, MSGBOX_SIGN
	end

PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

Common_Text_LookCloserAtMap:
	.string "{PLAYER} took a closer look at the\n"
	.string "{REGION} region map.$"

PlayersHouse_2F_Text_PlayNES:
	.string "{PLAYER} played with the NES\n"
	.string "shaped Wii.\p"
	.string "Okay!\n"
	.string "It's time to go!$"
