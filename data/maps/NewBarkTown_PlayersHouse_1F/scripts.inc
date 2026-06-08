NewBarkTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_PlayersHouse_1F_Scripts
	.byte 0

NewBarkTown_PlayersHouse_1F_Scripts:
	map_script_2 VAR_NEWBARK_INTRO_STATE, 1, NewBarkTown_PlayersHouse_Obtain_PokeGear
	.2byte 0

NewBarkTown_PlayersHouse_Obtain_PokeGear::
	lockall
	playse SE_PIN
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, NewBarkTown_PlayersHouse_Mom_Move_Up
	waitmovement LOCALID_PLAYERS_HOUSE_1F_MOM
	applymovement LOCALID_PLAYER, NewBarkTown_PlayersHouse_Player_Face_Down
	waitmovement LOCALID_PLAYER
	msgbox NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_1, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_2
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	msgbox NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_3, MSGBOX_DEFAULT
	msgbox NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_4, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq NewBarkTown_PlayersHouse_Obtain_PokeGear_AnsweredNo
	msgbox NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_5_Yes, MSGBOX_DEFAULT
	goto NewBarkTown_PlayersHouse_Obtain_PokeGear_End


NewBarkTown_PlayersHouse_Obtain_PokeGear_AnsweredNo::
	msgbox NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_5_No, MSGBOX_DEFAULT

NewBarkTown_PlayersHouse_Obtain_PokeGear_End::
	msgbox NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_6, MSGBOX_DEFAULT
	setvar VAR_NEWBARK_INTRO_STATE, 2
	closemessage
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, NewBarkTown_PlayersHouse_Mom_Move_Down
	waitmovement LOCALID_PLAYERS_HOUSE_1F_MOM
	releaseall
	end

NewBarkTown_PlayersHouse_Mom_Script::
	msgbox NewBarkTown_PlayersHouse_Mom_Script_Text_1, MSGBOX_NPC
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, NewBarkTown_PlayersHouse_Mom_Face_Left
	waitmovement LOCALID_PLAYERS_HOUSE_1F_MOM
	end

NewBarkTown_PlayersHouse_1F_EventScript_Visitor::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_Script_Visitor_Text, MSGBOX_NPC
	applymovement LOCALID_PLAYERS_HOUSE_1F_VISITOR, NewBarkTown_PlayersHouse_Visitor_Face_Right
	waitmovement LOCALID_PLAYERS_HOUSE_1F_VISITOR
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Sink::
	msgbox NewBarkTown_PlayersHouse_Script_Sink_Text, MSGBOX_NPC
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Fridge::
	msgbox NewBarkTown_PlayersHouse_Script_Fridge_Text, MSGBOX_NPC
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_TV::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, NewBarkTown_PlayersHouse_1F_EventScript_TV_Male
	goto_if_eq VAR_RESULT, FEMALE, NewBarkTown_PlayersHouse_1F_EventScript_TV_Female
	releaseall
	end

NewBarkTown_PlayersHouse_1F_EventScript_TV_Male::
	msgbox NewBarkTown_PlayersHouse_Script_TV_Text_Male, MSGBOX_NPC
	return

NewBarkTown_PlayersHouse_1F_EventScript_TV_Female::
	msgbox NewBarkTown_PlayersHouse_Script_TV_Text_Female, MSGBOX_NPC
	return

@Movement
NewBarkTown_PlayersHouse_Mom_Move_Up:
	emote_exclamation_mark
	delay_4
	walk_right
	walk_right
	walk_up
	step_end

NewBarkTown_PlayersHouse_Mom_Move_Down:
	walk_down
	face_left
	walk_left
	walk_left
	step_end

NewBarkTown_PlayersHouse_Player_Face_Down:
	face_down
	step_end

NewBarkTown_PlayersHouse_Visitor_Face_Right:
	face_right
	step_end

NewBarkTown_PlayersHouse_Mom_Face_Left:
	face_left
	step_end

@Text
NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_1:
	.string "Oh, {PLAYER}! Our neighbor, PROF. ELM,\n"
	.string "was looking for you.\p"
	.string "He said he wanted you to do something\n"
	.string "for him.\p"
	.string "Oh! I almost forgot! Your POKéMON GEAR\n"
	.string "is back from the repair shop.\p"
	.string "Here you go!$"

NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_2:
	.string "{PLAYER} received a POKéGEAR.$"

NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_3:
	.string "POKéMON GEAR or just POKéGEAR.\n"
	.string "It's essential if you want\p"
	.string "to be a good trainer.$"

NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_4:
	.string "By the way, do you know how\n"
	.string "to use the PHONE?$"

NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_5_Yes:
	.string "Don't you just turn the POKéGEAR\n"
	.string "on and select the PHONE icon?$"

NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_5_No:
	.string "I'll read the instructions.\p"
	.string "Turn the POKéGEAR on and\n"
	.string "select the PHONE icon.$"

NewBarkTown_PlayersHouse_Obtain_PokeGear_Text_6:
	.string "Phone numbers are stored in memory.\n"
	.string "Just choose a name you want to call.\p"
	.string "Gee, isn't that convenient?$"

NewBarkTown_PlayersHouse_Mom_Script_Text_1:
	.string "PROF. ELM is waiting for you.\n"
	.string "Hurry up, baby!$"

NewBarkTown_PlayersHouse_Script_Visitor_Text:
	.string "Good morning, {PLAYER},\n"
	.string "I'm visiting!\p"
	.string "Have you heard?\p"
	.string "My daughter is adamant about \n"
	.string "becoming PROF.ELM's assistant. \p"
	.string "She really loves POKéMON!$"

NewBarkTown_PlayersHouse_Script_Sink_Text:
	.string "The sink is spotless.\n"
	.string "Mom likes it clean.$"

NewBarkTown_PlayersHouse_Script_Fridge_Text:
	.string "Let's see what's in the fridge...\n"
	.string "FRESH WATER and tasty LEMONADE!$"

NewBarkTown_PlayersHouse_Script_TV_Text_Male:
	.string "There's a movie on TV:\n"
	.string "Stars dot the sky as two boys ride\l"
	.string "on a train...\p"
	.string "I'd better get rolling too!$"

NewBarkTown_PlayersHouse_Script_TV_Text_Female:
	.string "There's a movie on TV.\n"
	.string "A girl with her hair in pigtails is\l"
	.string "walking up a brick road.\p"
	.string "I better go, too.$"
