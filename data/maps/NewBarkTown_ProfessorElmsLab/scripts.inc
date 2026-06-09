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
	msgbox NewBarkTown_ProfessorElmsLab_Starter_Greeting_text, MSGBOX_DEFAULT
	msgbox NewBarkTown_ProfessorElmsLab_Starter_Research_Request_text, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_ProfessorElmsLab_Starter_Request_Declined_script
	goto NewBarkTown_ProfessorElmsLab_Starter_Request_Accepted_script

NewBarkTown_ProfessorElmsLab_Starter_Request_Declined_script:
	msgbox NewBarkTown_ProfessorElmsLab_Starter_Please_Help_text, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_ProfessorElmsLab_Starter_Request_Declined_script
	goto NewBarkTown_ProfessorElmsLab_Starter_Request_Accepted_script

NewBarkTown_ProfessorElmsLab_Starter_Request_Accepted_script:
	msgbox NewBarkTown_ProfessorElmsLab_Starter_Thanks_text, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ELMS_LAB_ELM, NewBarkTown_ProfessorElmsLab_Elm_Move_To_Computer
	waitmovement LOCALID_ELMS_LAB_ELM
	delay 0x50
	msgbox NewBarkTown_ProfessorElmsLab_Starter_Email_text, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELMS_LAB_ELM, NewBarkTown_ProfessorElmsLab_Elm_Return_From_Computer
	waitmovement LOCALID_ELMS_LAB_ELM
	msgbox NewBarkTown_ProfessorElmsLab_Starter_MrPokemon_Request_text, MSGBOX_DEFAULT
	closemessage
	msgbox NewBarkTown_ProfessorElmsLab_Starter_Pick_One_text, MSGBOX_DEFAULT
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
	msgbox NewBarkTown_ProfessorElmsLab_Watcher_text, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ELMS_LAB_ELM, NewBarkTown_ProfessorElmsLab_Elm_React_To_Watcher
	waitmovement LOCALID_ELMS_LAB_ELM
	msgbox NewBarkTown_ProfessorElmsLab_Who_Was_That_text, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELMS_LAB_ELM, NewBarkTown_ProfessorElmsLab_Elm_Face_Right_After_Watcher
	waitmovement LOCALID_ELMS_LAB_ELM
	msgbox NewBarkTown_ProfessorElmsLab_MRPOKEMON_text, MSGBOX_DEFAULT
	setvar VAR_NEWBARK_INTRO_STATE, 4
	releaseall
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
	msgbox NewBarkTown_ProfessorElmsLab_Complicated_Device_text, MSGBOX_NPC
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

NewBarkTown_ProfessorElmsLab_EventScript_ElmEmail::
    msgbox NewBarkTown_ProfessorElmsLab_Text_ElmEmail, MSGBOX_SIGN
    end

NewBarkTown_ProfessorElmsLab_EventScript_PokemonEvolutionScreen::
    msgbox NewBarkTown_ProfessorElmsLab_Text_PokemonEvolutionScreen, MSGBOX_NPC
    end

@Movement
NewBarkTown_ProfessorElmsLab_Elm_Move_To_Computer:
	emote_exclamation_mark
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end

NewBarkTown_ProfessorElmsLab_Elm_Return_From_Computer:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end

NewBarkTown_ProfessorElmsLab_Elm_React_To_Watcher:
	emote_exclamation_mark
	face_left
	step_end

NewBarkTown_ProfessorElmsLab_Elm_Face_Right_After_Watcher:
	face_down
	step_end

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
NewBarkTown_ProfessorElmsLab_Starter_Greeting_text:
	.string "ELM: {PLAYER}!\n"
	.string "There you are!$"

NewBarkTown_ProfessorElmsLab_Starter_Research_Request_text:
	.string "ELM: I needed to ask you a favor.\p"
	.string "I'm conducting new POKéMON research\n"
	.string "right now.\p"
	.string "I was wondering if you could help me\n"
	.string "with it, {PLAYER}.\p"
	.string "You see...\p"
	.string "I'm writing a paper that I want to\n"
	.string "present at a conference.\p"
	.string "But there are some things I don't\n"
	.string "quite understand yet.\p"
	.string "So!\p"
	.string "I'd like you to raise a POKéMON that\n"
	.string "I recently caught.$"

NewBarkTown_ProfessorElmsLab_Starter_Please_Help_text:
	.string "ELM: But...\n"
	.string "Please, I need your help!$"

NewBarkTown_ProfessorElmsLab_Starter_Thanks_text:
	.string "ELM: Thanks, {PLAYER}!\n"
	.string "You're a great help!\p"
	.string "When I announce my findings, I'm\n"
	.string "sure we'll delve a bit deeper into\l"
	.string "the many mysteries of POKéMON.\p"
	.string "You can count on it!$"

NewBarkTown_ProfessorElmsLab_Starter_Email_text:
	.string "ELM: Oh, hey!\n"
	.string "I got an e-mail!\p"
	.string "..................\n"
	.string "Hm...\l"
	.string "Uh-huh...\p"
	.string "Okay...$"

NewBarkTown_ProfessorElmsLab_Starter_MrPokemon_Request_text:
	.string "ELM: Hey, listen.\p"
	.string "I have an acquaintance called\n"
	.string "MR.POKéMON.\p"
	.string "He keeps finding weird things and\n"
	.string "raving about his discoveries.\p"
	.string "Anyway, I just got an e-mail from him\n"
	.string "saying that this time it's real.\p"
	.string "It is intriguing, but we're busy\n"
	.string "with our POKéMON research...\p"
	.string "Wait!\p"
	.string "I know!\p"
	.string "{PLAYER}, can you go in our place?$"

NewBarkTown_ProfessorElmsLab_Starter_Pick_One_text:
	.string "ELM: I want you to raise one of the\n"
	.string "POKéMON contained in these BALLS.\p"
	.string "You'll be that POKéMON's first\n"
	.string "partner, {PLAYER}!\p"
	.string "Go on.\p"
	.string "Pick one!$"

NewBarkTown_ProfessorElmsLab_Chikorita_text:
	.string "ELM: I see! CHIKORITA is your choice.\n"
	.string "It's very easy to raise.\p"
	.string "So, {PLAYER}, you want to go with\n"
	.string "the GRASS POKéMON CHIKORITA?$"

NewBarkTown_ProfessorElmsLab_Cyndaquil_text:
	.string "ELM: Ah! CYNDAQUIL is your choice.\n"
	.string "You should raise it patiently.\p"
	.string "So, {PLAYER}, you're claiming the\n"
	.string "FIRE POKéMON CYNDAQUIL?$"

NewBarkTown_ProfessorElmsLab_Totodile_text:
	.string "ELM: Hm! TOTODILE is your choice.\n"
	.string "It's one worth raising.\p"
	.string "So, {PLAYER}, you've decided on the\n"
	.string "WATER POKéMON TOTODILE?$"

NewBarkTown_ProfessorElmsLab_Think_Over_text:
	.string "ELM: Think it over carefully.\p"
	.string "Your partner is important.$"

NewBarkTown_ProfessorElmsLab_Received_text:
	.string "{PLAYER} received the {STR_VAR_1}\n"
	.string "from PROF. ELM!$"

NewBarkTown_ProfessorElmsLab_Nickname_text:
	.string "Do you want to give a nickname to\n"
	.string "this {STR_VAR_1}?$"

NewBarkTown_ProfessorElmsLab_Watcher_text:
	.string "??????: I'm watching you ELM!$"

NewBarkTown_ProfessorElmsLab_Who_Was_That_text:
	.string "ELM: Who the hell was that!?$"

NewBarkTown_ProfessorElmsLab_MRPOKEMON_text:
	.string "ELM: Anyway...\p"
	.string "MR.POKéMON lives a little bit beyond\n"
	.string "CHERRYGROVE, the next city over.\p"
	.string "It's almost a direct route there so\n"
	.string "you can't miss it.\p"
	.string "If your POKéMON is hurt, you should\n"
	.string "heal it with the machine on my\l"
	.string "right.\p"
	.string "Feel free to use it anytime.$"

NewBarkTown_ProfessorElmsLab_WildPoke_text:
	.string "ELM: Now, {PLAYER}.\p"
	.string "Inside those three POKé BALLS are\n"
	.string "POKéMON.\p"
	.string "Which one will you choose for\n"
	.string "yourself?$"

NewBarkTown_ProfessorElmsLab_MRPOKEMON_text_2:
	.string "ELM: MR.POKéMON lives a little bit\n"
	.string "beyond CHERRYGROVE, the next city\l"
	.string "over.\p"
	.string "It's almost a direct route there so\n"
	.string "you can't miss it.$"

NewBarkTown_ProfessorElmsLab_Elm_DontLeaveDuringPick_text:
	.string "ELM: Hey!\n"
	.string "Don't go away yet!$"

NewBarkTown_ProfessorElmsLab_Aide_Potion_text:
	.string "{PLAYER}, I want you to have this for\n"
	.string "your errand.$"

NewBarkTown_ProfessorElmsLab_Aide_Busy_text:
	.string "There are only two of us, so we're\n"
	.string "always busy.$"

NewBarkTown_ProfessorElmsLab_Left_Poke_text:
	.string "It contains a POKéMON caught\n"
	.string "by PROF.ELM.$"

NewBarkTown_ProfessorElmsLab_Window_Open_text:
	.string "The window's open.\n"
	.string "A pleasant breeze is blowing in.$"

NewBarkTown_ProfessorElmsLab_Window_Closed_text:
	.string "My reflection!\n"
	.string "Lookin' good!$"

NewBarkTown_ProfessorElmsLab_Trash_Can_text:
	.string "The wrapper from the snack PROF.ELM\n"
	.string "ate is in there...$"

NewBarkTown_ProfessorElmsLab_Heal_Mons_text:
	.string "Would you like to heal your POKéMON?$"

NewBarkTown_ProfessorElmsLab_Complicated_Device_text:
	.string "A complicated device,\n"
	.string "better not touch it...$"

NewBarkTown_ProfessorElmsLab_Text_ElmEmail:
    .string "There's an e-mail message here.\p"
    .string "…\p"
    .string "Finally!\n"
    .string "The ultimate TRAINERS of the\l"
    .string "POKéMON LEAGUE are ready to take on\l"
    .string "all comers!\p"
    .string "Bring your best POKéMON and see\n"
    .string "how you rate as a TRAINER!\p"
    .string "POKéMON LEAGUE HQ\n"
    .string "INDIGO PLATEAU\p"
    .string "PROF. ELM, please visit us!\n"
    .string "…$"

NewBarkTown_ProfessorElmsLab_Text_PokemonEvolutionScreen:
    .string "OBSERVATIONS ON POKéMON EVOLUTION\n"
    .string "...It says on the screen...$"
