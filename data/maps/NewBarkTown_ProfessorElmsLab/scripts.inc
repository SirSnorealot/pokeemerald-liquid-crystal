NewBarkTown_ProfessorElmsLab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_ProfessorElmsLab_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, NewBarkTown_ProfessorElmsLab_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_ProfessorElmsLab_OnFrame
	.byte 0

	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE - Not assigned.
	@ 1: Beat Elite Four, Dex upgrade ready
	@ 2: Received National Dex
	@ 3: Left lab after receiving National Dex
	@ 4: Entered lab after catching all Hoenn mons
	@ 5: Birch told player to choose Johto starter
	@ 6: Chose Johto starter

	@ State descriptions for VAR_BIRCH_LAB_STATE - Not assigned.
	@ 1: Never occurs
	@ 2: Chose starter
	@ 3: Received starter in lab
	@ 4: Defeated rival on Route 103
	@ 5: Received pokedex

NewBarkTown_ProfessorElmsLab_OnTransition:
	end

NewBarkTown_ProfessorElmsLab_OnWarp:
	.2byte 0

NewBarkTown_ProfessorElmsLab_OnFrame:
	map_script_2 VAR_NEWBARK_INTRO_STATE, 2, NewBarkTown_ProfessorElmsLab_Starter_script
	.2byte 0

@NPC Scripts
NewBarkTown_ProfessorElmsLab_Elm_script::
	switch VAR_NEWBARK_INTRO_STATE
	case 3, NewBarkTown_ProfessorElmsLab_Elm_during_pick_script
	case 4, NewBarkTown_ProfessorElmsLab_Elm_after_pick_script
	end

NewBarkTown_ProfessorElmsLab_Elm_during_pick_script:
	msgbox NewBarkTown_ProfessorElmsLab_WildPoke_text, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_Elm_after_pick_script:
	msgbox NewBarkTown_ProfessorElmsLab_MRPOKEMON_text_2, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_Aide_script::
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Busy_text, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_Elm_DontLeaveDuringPick_script::
	lock
	msgbox NewBarkTown_ProfessorElmsLab_Elm_DontLeaveDuringPick_text, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement LOCALID_PLAYER
	release
	end

NewBarkTown_ProfessorElmsLab_Aide_Potion_Script_1::
	lockall
	applymovement LOCALID_ELMS_LAB_AIDE, NewBarkTown_ProfessorElmsLab_Aide_Move_To_Player_1
	waitmovement LOCALID_ELMS_LAB_AIDE
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Potion_text, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION, 1
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Busy_text, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELMS_LAB_AIDE, NewBarkTown_ProfessorElmsLab_Aide_Return_1
	waitmovement LOCALID_ELMS_LAB_AIDE
	setvar VAR_NEWBARK_INTRO_STATE, 5
	releaseall
	end

NewBarkTown_ProfessorElmsLab_Aide_Potion_Script_2::
	lockall
	applymovement LOCALID_ELMS_LAB_AIDE, NewBarkTown_ProfessorElmsLab_Aide_Move_To_Player_2
	waitmovement LOCALID_ELMS_LAB_AIDE
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Potion_text, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION, 1
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Busy_text, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELMS_LAB_AIDE, NewBarkTown_ProfessorElmsLab_Aide_Return_2
	waitmovement LOCALID_ELMS_LAB_AIDE
	setvar VAR_NEWBARK_INTRO_STATE, 5
	releaseall
	end

NewBarkTown_ProfessorElmsLab_Aide_Potion_Script_3::
	lockall
	applymovement LOCALID_ELMS_LAB_AIDE, NewBarkTown_ProfessorElmsLab_Aide_Move_To_Player_3
	waitmovement LOCALID_ELMS_LAB_AIDE
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Potion_text, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION, 1
	msgbox NewBarkTown_ProfessorElmsLab_Aide_Busy_text, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELMS_LAB_AIDE, NewBarkTown_ProfessorElmsLab_Aide_Return_3
	waitmovement LOCALID_ELMS_LAB_AIDE
	setvar VAR_NEWBARK_INTRO_STATE, 5
	releaseall
	end

@Starter related Scripts
NewBarkTown_ProfessorElmsLab_Starter_script:
	lockall
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Walk_Up_1
	waitmovement LOCALID_PLAYER
	applymovement LOCALID_ELMS_LAB_ELM, Common_Movement_FacePlayer
	waitmovement LOCALID_ELMS_LAB_ELM
	msgbox NewBarkTown_ProfessorElmsLab_Starter_script_Text_1, MSGBOX_DEFAULT
	applymovement LOCALID_ELMS_LAB_ELM, Common_Movement_FaceDown
	waitmovement LOCALID_ELMS_LAB_ELM
	setvar VAR_NEWBARK_INTRO_STATE, 3
	closemessage
	releaseall
	end

NewBarkTown_ProfessorElmsLab_Chikorita_script::
	lockall
	faceplayer
	compare VAR_NEWBARK_INTRO_STATE, 3
	goto_if_ne NewBarkTown_ProfessorElmsLab_Left_Poke_script
	showmonpic SPECIES_CHIKORITA, 10, 3
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	waitmoncry
	msgbox NewBarkTown_ProfessorElmsLab_Chikorita_text, MSGBOX_YESNO
	hidemonpic
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_ProfessorElmsLab_PlayerAnsweredNo_script
	removeobject 5
	givemon SPECIES_CHIKORITA, 5, ITEM_ORAN_BERRY
	bufferleadmonspeciesname 0
	message NewBarkTown_ProfessorElmsLab_Received_text
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	callnative UpdateFollowingPokemon
	setflag FLAG_SYS_POKEMON_GET
	setvar VAR_STARTER_MON 0
	setflag FLAG_HIDE_ELM_LAB_Chikorita_BALL
	waitfanfare
	msgbox NewBarkTown_ProfessorElmsLab_Nickname_text, MSGBOX_YESNO
	compare VAR_RESULT, 1
	call_if_eq NewBarkTown_ProfessorElmsLab_Yes_Nickname_script
	specialvar VAR_RESULT, GetPlayerFacingDirection
	closemessage
	switch VAR_RESULT
	case 1, NewBarkTown_ProfessorElmsLab_Return_From_Chikorita_script_1
	case 2, NewBarkTown_ProfessorElmsLab_Return_From_Chikorita_script_2
	end

NewBarkTown_ProfessorElmsLab_Return_From_Chikorita_script_1:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Chikorita_1
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return


NewBarkTown_ProfessorElmsLab_Return_From_Chikorita_script_2:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Chikorita_2
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return

NewBarkTown_ProfessorElmsLab_Cyndaquil_script::
	lockall
	faceplayer
	compare VAR_NEWBARK_INTRO_STATE, 3
	goto_if_ne NewBarkTown_ProfessorElmsLab_Left_Poke_script
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_NORMAL
	waitmoncry
	msgbox NewBarkTown_ProfessorElmsLab_Cyndaquil_text, MSGBOX_YESNO
	hidemonpic
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_ProfessorElmsLab_PlayerAnsweredNo_script
	removeobject 3
	givemon SPECIES_CYNDAQUIL, 5, ITEM_ORAN_BERRY
	bufferleadmonspeciesname 0
	message NewBarkTown_ProfessorElmsLab_Received_text
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	callnative UpdateFollowingPokemon
	setflag FLAG_SYS_POKEMON_GET
	setvar VAR_STARTER_MON 1
	setflag FLAG_HIDE_ELM_LAB_Cyndaquil_BALL
	waitfanfare
	msgbox NewBarkTown_ProfessorElmsLab_Nickname_text, MSGBOX_YESNO
	compare VAR_RESULT, 1
	call_if_eq NewBarkTown_ProfessorElmsLab_Yes_Nickname_script
	specialvar VAR_RESULT, GetPlayerFacingDirection
	closemessage
	switch VAR_RESULT
	case 1, NewBarkTown_ProfessorElmsLab_Return_From_Cyndaquil_script_1
	case 2, NewBarkTown_ProfessorElmsLab_Return_From_Cyndaquil_script_2
	case 4, NewBarkTown_ProfessorElmsLab_Return_From_Cyndaquil_script_3
	end

NewBarkTown_ProfessorElmsLab_Return_From_Cyndaquil_script_1:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Cyndaquil_1
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return

NewBarkTown_ProfessorElmsLab_Return_From_Cyndaquil_script_2:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Cyndaquil_2
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return

NewBarkTown_ProfessorElmsLab_Return_From_Cyndaquil_script_3:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Cyndaquil_3
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return

NewBarkTown_ProfessorElmsLab_Totodile_script::
	lockall
	faceplayer
	compare VAR_NEWBARK_INTRO_STATE, 3
	goto_if_ne NewBarkTown_ProfessorElmsLab_Left_Poke_script
	showmonpic SPECIES_TOTODILE, 10, 3
	playmoncry SPECIES_TOTODILE, CRY_MODE_NORMAL
	waitmoncry
	msgbox NewBarkTown_ProfessorElmsLab_Totodile_text, MSGBOX_YESNO
	hidemonpic
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_ProfessorElmsLab_PlayerAnsweredNo_script
	removeobject 4
	givemon SPECIES_TOTODILE, 5, ITEM_ORAN_BERRY
	bufferleadmonspeciesname 0
	message NewBarkTown_ProfessorElmsLab_Received_text
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	callnative UpdateFollowingPokemon
	setflag FLAG_SYS_POKEMON_GET
	setvar VAR_STARTER_MON 2
	setflag FLAG_HIDE_ELM_LAB_Totodile_BALL
	waitfanfare
	msgbox NewBarkTown_ProfessorElmsLab_Nickname_text, MSGBOX_YESNO
	compare VAR_RESULT, 1
	call_if_eq NewBarkTown_ProfessorElmsLab_Yes_Nickname_script
	specialvar VAR_RESULT, GetPlayerFacingDirection
	closemessage
	switch VAR_RESULT
	case 1, NewBarkTown_ProfessorElmsLab_Return_From_Totodile_script_1
	case 2, NewBarkTown_ProfessorElmsLab_Return_From_Totodile_script_2
	end

NewBarkTown_ProfessorElmsLab_Return_From_Totodile_script_1:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Totodile_1
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return

NewBarkTown_ProfessorElmsLab_Return_From_Totodile_script_2:
	applymovement LOCALID_PLAYER, NewBarkTown_ProfessorElmsLab_Player_Return_From_Totodile_2
	waitmovement LOCALID_PLAYER
	goto NewBarkTown_ProfessorElmsLab_Got_Poke_script
	return

NewBarkTown_ProfessorElmsLab_Got_Poke_script:
	applymovement LOCALID_ELMS_LAB_ELM, Common_Movement_FacePlayer
	waitmovement LOCALID_ELMS_LAB_ELM
	msgbox NewBarkTown_ProfessorElmsLab_MRPOKEMON_text, MSGBOX_DEFAULT
	setvar VAR_NEWBARK_INTRO_STATE, 4
	release
	end
NewBarkTown_ProfessorElmsLab_Left_Poke_script:
	msgbox NewBarkTown_ProfessorElmsLab_Left_Poke_text, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_PlayerAnsweredNo_script::
	msgbox NewBarkTown_ProfessorElmsLab_Think_Over_text, MSGBOX_DEFAULT
	releaseall
	end

NewBarkTown_ProfessorElmsLab_Yes_Nickname_script::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	return

NewBarkTown_ProfessorElmsLab_Window_Open::
	msgbox NewBarkTown_ProfessorElmsLab_Window_Open_text, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_Window_Closed::
	msgbox NewBarkTown_ProfessorElmsLab_Window_Closed_text, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_Trash_Can::
	msgbox NewBarkTown_ProfessorElmsLab_Trash_Can_text, MSGBOX_NPC
	end

NewBarkTown_ProfessorElmsLab_Machine::
	lock
	faceplayer
	checkflag FLAG_SYS_POKEMON_GET
	goto_if_unset FLAG_SYS_POKEMON_GET, NewBarkTown_ProfessorElmsLab_Complicated_Device
	msgbox NewBarkTown_ProfessorElmsLab_Heal_Mons_text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, 1, NewBarkTown_ProfessorElmsLab_Heal_Mons
	release
	end

NewBarkTown_ProfessorElmsLab_Complicated_Device::
	msgbox NewBarkTown_ProfessorElmsLab_Complicated_Device_text MSGBOX_NPC
	release
	end

NewBarkTown_ProfessorElmsLab_Heal_Mons::
	hidefollower 0
	fadescreen 0x1
	waitmessage
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen 0x0
	callnative UpdateFollowingPokemon
	release
	end

@Movement
NewBarkTown_ProfessorElmsLab_Player_Walk_Up_1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Chikorita_1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Chikorita_2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Cyndaquil_1:
	walk_left
	walk_down
	walk_left
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Cyndaquil_2:
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Cyndaquil_3:
	walk_left
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Totodile_1:
	walk_left
	walk_left
	walk_down
	walk_left
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Player_Return_From_Totodile_2:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_ProfessorElmsLab_Aide_Move_To_Player_1:
	walk_right
	walk_right
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Aide_Move_To_Player_2:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Aide_Move_To_Player_3:
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Aide_Return_1:
	walk_left
	walk_left
	step_end

NewBarkTown_ProfessorElmsLab_Aide_Return_2:
	walk_left
	walk_left
	walk_left
	step_end

NewBarkTown_ProfessorElmsLab_Aide_Return_3:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@Text
NewBarkTown_ProfessorElmsLab_Starter_script_Text_1:
	.string "ELM: {PLAYER}!\n"
	.string "There you are!\p"
	.string "I needed to ask you a favor.\p"
	.string "I have an acquaintance called\n"
	.string "MR.POKéMON.\p"
	.string "He keeps finding weird things and\n"
	.string "raving about his discoveries.\p"
	.string "Anyway, I just got an e-mail from him\n"
	.string "saying that this time it's real.\p"
	.string "It is intriguing, but we're busy with\n"
	.string "our POKéMON research.\p"
	.string "Could you look into it for us?\p"
	.string "I'll give you a POKéMON for a partner.\p"
	.string "They're all rare POKéMON that we just\n"
	.string "found.\l"
	.string "Go on. Pick one!$"

NewBarkTown_ProfessorElmsLab_Chikorita_text:
	.string "ELM: So, you like CHIKORITA, the\ngrass POKéMON?$"

NewBarkTown_ProfessorElmsLab_Cyndaquil_text:
	.string "ELM: You'll take CYNDAQUIL, the\nfire POKéMON?$"

NewBarkTown_ProfessorElmsLab_Totodile_text:
	.string "ELM: Do you want TOTODILE, the\nwater POKéMON?$"

NewBarkTown_ProfessorElmsLab_Think_Over_text:
	.string "ELM: Think it over carefully.\pYour partner is important.$"

NewBarkTown_ProfessorElmsLab_Received_text:
	.string "{PLAYER} received a {STR_VAR_1}!$"

NewBarkTown_ProfessorElmsLab_Nickname_text:
	.string "Do you want to give a nickname to\nthis {STR_VAR_1}?$"

NewBarkTown_ProfessorElmsLab_MRPOKEMON_text:
	.string "MR.POKéMON lives near CHERRYGROVE,\nthe next city.\pIt's almost a direct route to\nthere.$"

NewBarkTown_ProfessorElmsLab_WildPoke_text:
	.string "If a wild POKéMON appears, let your\nPOKéMON battle it!$"

NewBarkTown_ProfessorElmsLab_MRPOKEMON_text_2:
	.string "MR.POKéMON goes everywhere and finds\nrarities.\pToo bad they're just rare and\nnot very useful...\p{PLAYER}, I'm counting on you!$"

NewBarkTown_ProfessorElmsLab_Elm_DontLeaveDuringPick_text:
	.string "ELM: Wait! Where are you going?$"

NewBarkTown_ProfessorElmsLab_Aide_Potion_text:
	.string "{PLAYER}, I want you to have this for\nyour errand.$"

NewBarkTown_ProfessorElmsLab_Aide_Busy_text:
	.string "There are only two of us, so we're\nalways busy.$"

NewBarkTown_ProfessorElmsLab_Left_Poke_text:
	.string "It contains a POKéMON caught by\nPROF.ELM.$"

NewBarkTown_ProfessorElmsLab_Window_Open_text:
	.string "The window's open.\nA pleasant breeze is blowing in.$"

NewBarkTown_ProfessorElmsLab_Window_Closed_text:
	.string "My reflection!\nLookin' good!$"

NewBarkTown_ProfessorElmsLab_Trash_Can_text:
	.string "The wrapper from the snack PROF.ELM\nate is in there...$"

NewBarkTown_ProfessorElmsLab_Heal_Mons_text:
	.string "Would you like to heal your POKéMON?$"

NewBarkTown_ProfessorElmsLab_Complicated_Device_text:
	.string "A complicated device,\nbetter not touch it...$"
