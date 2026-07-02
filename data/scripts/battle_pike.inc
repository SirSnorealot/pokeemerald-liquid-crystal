BattleFrontier_BattlePikeRoom_MapScripts:
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePikeRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeRoom_OnWarp

BattleFrontier_BattlePikeRoom_OnTransition:
	pike_setroomobjects
	pike_getroomtype
	switch VAR_RESULT
	case PIKE_ROOM_SINGLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos
	case PIKE_ROOM_HEAL_FULL, BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos
	case PIKE_ROOM_NPC, BattleFrontier_BattlePikeRoomNormal_EventScript_SetNPCRoomObjPos
	case PIKE_ROOM_STATUS, BattleFrontier_BattlePikeRoomNormal_EventScript_SetTwoObjectRoomPos
	case PIKE_ROOM_HEAL_PART, BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos
	case PIKE_ROOM_DOUBLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_SetDoubleBattleObjPos
	case PIKE_ROOM_HARD_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_SetTwoObjectRoomPos
	case PIKE_ROOM_BRAIN, BattleFrontier_BattlePikeRoomNormal_EventScript_SetBrainRoomObjPos
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetDoubleBattleObjPos::
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_1, 2, 5
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_2, 6, 5
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetTwoObjectRoomPos::
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_1, 4, 4
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_2, 3, 4
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetOneObjectRoomPos::
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_1, 4, 4
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_2, 0, 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetNPCRoomObjPos::
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_1, 5, 5
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_2, 0, 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetBrainRoomObjPos::
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_1, 4, 3
	@ TODO(LC): removed with Hoenn maps — setobjectxyperm LOCALID_PIKE_ROOM_NPC_2, 4, 4
	end

BattleFrontier_BattlePikeRoom_OnWarp:
	map_script_2 VAR_TEMP_4, 0, BattleFrontier_BattlePikeRoomNormal_EventScript_InitRoomObjects
	.2byte 0

BattleFrontier_BattlePikeRoomNormal_EventScript_InitRoomObjects::
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_LINK_RECEPTIONIST
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_LINK_RECEPTIONIST
	pike_getroomtype
	goto_if_eq VAR_RESULT, PIKE_ROOM_STATUS, BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom
	goto_if_eq VAR_RESULT, PIKE_ROOM_HARD_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom
	goto_if_eq VAR_RESULT, PIKE_ROOM_DOUBLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom
	goto_if_eq VAR_RESULT, PIKE_ROOM_BRAIN, BattleFrontier_BattlePikeRoomNormal_EventScript_InitBrainRoomObjects
	@ TODO(LC): removed with Hoenn maps — hideobjectat LOCALID_PIKE_ROOM_NPC_2, MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL
	setvar VAR_TEMP_4, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_InitTwoObjectRoom::
	setvar VAR_TEMP_4, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_InitBrainRoomObjects::
	setvar VAR_TEMP_4, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	@ TODO(LC): removed with Hoenn maps — hideobjectat LOCALID_PIKE_ROOM_NPC_1, MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL  @ Pike Queen hidden initially
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_LeftRoomWarp::
	setvar VAR_0x8007, PIKE_ROOM_LEFT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_CenterRoomWarp::
	setvar VAR_0x8007, PIKE_ROOM_CENTER
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_RightRoomWarp::
	setvar VAR_0x8007, PIKE_ROOM_RIGHT
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_RoomWarp::
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	pike_get PIKE_DATA_WIN_STREAK
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_WIN_STREAK, VAR_RESULT
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	pike_setnextroom
	pike_getroomtype
	switch VAR_RESULT
	case PIKE_ROOM_SINGLE_BATTLE, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_HEAL_FULL, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_NPC, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_STATUS, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_HEAL_PART, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_WILD_MONS, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpWildMonRoom
	case PIKE_ROOM_HARD_BATTLE, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_DOUBLE_BATTLE, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	case PIKE_ROOM_BRAIN, BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpNPCRoom::
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	@ TODO(LC): removed with Hoenn maps — call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_DYNAMIC, 4, 7 @ TODO(LC): was MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL (removed with Hoenn maps)
	waitstate
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_WarpWildMonRoom::
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	@ TODO(LC): removed with Hoenn maps — call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_DYNAMIC, 4, 19 @ TODO(LC): was MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS (removed with Hoenn maps)
	waitstate
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_SetEnteredRoom::
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_2, 1
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_NoTurningBack::
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_2, 0
	lockall
	@ TODO(LC): removed with Hoenn maps — msgbox BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetEnteredRoom::
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_2, 1
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_NoTurningBack::
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_2, 0
	lockall
	@ TODO(LC): removed with Hoenn maps — msgbox BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_Exit::
	pike_ispartyfullhealth
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoom_EventScript_DisableHealing
	call_if_ne VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoom_EventScript_EnableHealing
	pike_get PIKE_DATA_WIN_STREAK
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_WIN_STREAK, VAR_RESULT
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	pike_isfinalroom
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom
	call_if_eq VAR_RESULT, FALSE, BattleFrontier_BattlePikeRoom_EventScript_WarpToThreePathRoom
	waitstate
	end

BattleFrontier_BattlePikeRoom_EventScript_DisableHealing::
	pike_nohealing TRUE
	return

BattleFrontier_BattlePikeRoom_EventScript_EnableHealing::
	pike_nohealing FALSE
	return

BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom::
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	@ TODO(LC): removed with Hoenn maps — call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_DYNAMIC, 2, 7 @ TODO(LC): was MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_FINAL (removed with Hoenn maps)
	return

BattleFrontier_BattlePikeRoom_EventScript_WarpToThreePathRoom::
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoom_Movement_HidePlayer
	waitmovement 0
	@ TODO(LC): removed with Hoenn maps — call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_DYNAMIC, 6, 10 @ TODO(LC): was MAP_BATTLE_FRONTIER_BATTLE_PIKE_THREE_PATH_ROOM (removed with Hoenn maps)
	return

BattleFrontier_BattlePikeRoomWildMons_EventScript_Exit::
	pike_exitwildmonroom
	pike_ispartyfullhealth
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoom_EventScript_DisableHealing
	call_if_ne VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoom_EventScript_EnableHealing
	pike_get PIKE_DATA_WIN_STREAK
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_WIN_STREAK, VAR_RESULT
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	pike_isfinalroom
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom
	call_if_eq VAR_RESULT, FALSE, BattleFrontier_BattlePikeRoom_EventScript_WarpToThreePathRoom
	waitstate
	end

BattleFrontier_BattlePikeRoomWildMons_EventScript_SetEnteredRoom::
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_2, 1
	end

BattleFrontier_BattlePikeRoomWildMons_EventScript_NoTurningBack::
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_2, 0
	lockall
	@ TODO(LC): removed with Hoenn maps — msgbox BattleFrontier_BattlePike_Text_PathBlockedNoTurningBack, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_BattlePike_EventScript_Retire::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS CHALLENGE_STATUS_LOST
	warp MAP_DYNAMIC, 5, 6 @ TODO(LC): was MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY (removed with Hoenn maps)
	waitstate
	end

BattleFrontier_BattlePikeRoom_OnResume:
	setorcopyvar VAR_0x8006, VAR_RESULT  @ Save VAR_RESULT from being overwritten
	frontier_get FRONTIER_DATA_CHALLENGE_STATUS
	goto_if_eq VAR_RESULT, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePikeThreePathRoom_EventScript_EndOnResume
	goto_if_eq VAR_RESULT, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeThreePathRoom_EventScript_EndOnResume
	call BattleFrontier_BattlePikeRoom_EventScript_ResetSketchedMoves
BattleFrontier_BattlePikeThreePathRoom_EventScript_EndOnResume::
	setorcopyvar VAR_RESULT, VAR_0x8006
	end

BattleFrontier_BattlePikeRoom_EventScript_ResetSketchedMoves::
	frontier_resetsketch
	return

BattleFrontier_BattlePikeRoom_Movement_HidePlayer:
	set_invisible
	step_end
