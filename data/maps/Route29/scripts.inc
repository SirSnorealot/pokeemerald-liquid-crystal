Route29_MapScripts::
	.byte 0

Route29_EventScript_RouteSign::
	msgbox Route29_Text_RouteSign, MSGBOX_SIGN
	end

Route29_EventScript_SaveProgressReminderNpc::
	msgbox Route29_Text_SaveProgressReminder, MSGBOX_NPC
	end

Route29_EventScript_LedgeTutorialNpc::
	msgbox Route29_Text_LedgeTutorial, MSGBOX_NPC
	end

Route29_EventScript_TallGrassWarningNpc::
	msgbox Route29_Text_TallGrassWarning, MSGBOX_NPC
	end

Route29_Script_Tuscany_AlreadyMet::
	msgbox Route29_Text_TuscanyAlreadyMet, MSGBOX_NPC
	end

Route29_Script_Tuscany_BagFull::
	msgbox Route29_Text_TuscanyBagFull, MSGBOX_NPC
	end

Route29_EventScript_TimeOfDayPokemonWatcherNpc::
	goto_if_set 0x1766, Route29_Script_TimeOfDayPokemonWatcherNpc_NightText
	goto_if_set 0x1765, Route29_Script_TimeOfDayPokemonWatcherNpc_MorningText
	release
	end

Route29_Script_TimeOfDayPokemonWatcherNpc_NightText::
	lock
	faceplayer
	msgbox Route29_Text_PokemonWatcherNight, MSGBOX_AUTOCLOSE
	release
	end

Route29_Script_TimeOfDayPokemonWatcherNpc_MorningText::
	lock
	faceplayer
	msgbox Route29_Text_PokemonWatcherMorning, MSGBOX_AUTOCLOSE
	release
	end


Route29_EventScript_CatchingTutorialTriggerWest::
	goto_if_set 0x1020, Route29_Script_CatchingTutorialWest_Start
	release
	end

Route29_EventScript_CatchingTutorialTriggerEast::
	goto_if_set 0x1020, Route29_Script_CatchingTutorialEast_Start
	release
	end

Route29_EventScript_TuscanyOfSnowflakes::
	lockall
	faceplayer
	goto_if_set 0x15CB, Route29_Script_Tuscany_AlreadyMet
	msgbox Route29_Text_TuscanyIntroduction, MSGBOX_NPC
	lockall
	setorcopyvar 0x8000, 0xD9
	setorcopyvar 0x8001, 0x1
	callstd STD_OBTAIN_ITEM
	goto_if_eq 0x800D, 0x0, Route29_Script_Tuscany_BagFull
	msgbox Route29_Text_TuscanyExplainSilkScarf, MSGBOX_NPC
	setflag 0x15CB
	release
	end

Route29_EventScript_CatchingTutorialNpc::
	lock
	faceplayer
	goto_if_set 0x1781, Route29_Script_CatchingTutorialNpc_AfterTutorial
	goto_if_set 0x1780, Route29_Script_CatchingTutorialNpc_OfferRepeatTutorial
	msgbox Route29_Text_PokemonHideInGrass, MSGBOX_AUTOCLOSE
	release
	end

Route29_Script_CatchingTutorialNpc_AfterTutorial::
	msgbox Route29_Text_PokemonHideInGrass, MSGBOX_AUTOCLOSE
	release
	end

Route29_Script_CatchingTutorialNpc_OfferRepeatTutorial::
	msgbox Route29_Text_CatchingTutorialOfferRepeat, MSGBOX_YESNO
	goto_if_eq 0x800D, 0x1, Route29_Script_CatchingTutorialNpc_RepeatDemonstration
	release
	end

Route29_Script_CatchingTutorialWest_Start::
	goto_if_set 0x1780, Route29_Script_CatchingTutorialWest_AlreadyCompleted
	goto_if_set 0x1781, Route29_Script_CatchingTutorialWest_AlreadyCompleted
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcApproachWest
	waitmovement 0x0
	msgbox Route29_Text_CatchingTutorialOfferWest, MSGBOX_YESNO
	goto_if_eq 0x800D, 0x1, Route29_Script_CatchingTutorialWest_Demonstrate
	msgbox Route29_Text_CatchingTutorialDeclinedWest, MSGBOX_NPC
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcLeaveWest
	waitmovement 0x0
	setflag 0x1780
	release
	end

Route29_Script_CatchingTutorialWest_Demonstrate::
	release
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcLeaveWest
	applymovement 0xFF, Route29_Movement_CatchingTutorialPlayerMoveToDemoWest
	delay 0x80
	@ special 0x188
	@ special 0x9D
	waitstate
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcFaceUp
	waitmovement 0x0
	msgbox Route29_Text_CatchingTutorialCompleteWest, MSGBOX_NPC
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcFaceDownFast
	waitmovement 0x0
	setflag 0x1781
	release
	end

Route29_Script_CatchingTutorialWest_AlreadyCompleted::
	release
	end

Route29_Script_CatchingTutorialEast_Start::
	goto_if_set 0x1780, Route29_Script_CatchingTutorialEast_AlreadyCompleted
	goto_if_set 0x1781, Route29_Script_CatchingTutorialEast_AlreadyCompleted
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcApproachEast
	waitmovement 0x0
	msgbox Route29_Text_CatchingTutorialOfferEast, MSGBOX_YESNO
	goto_if_eq 0x800D, 0x1, Route29_Script_CatchingTutorialEast_Demonstrate
	msgbox Route29_Text_CatchingTutorialDeclinedEast, MSGBOX_NPC
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcLeaveEast
	waitmovement 0x0
	setflag 0x1780
	release
	end

Route29_Script_CatchingTutorialEast_Demonstrate::
	release
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcLeaveEast
	applymovement 0xFF, Route29_Movement_CatchingTutorialPlayerMoveToDemoEast
	delay 0x80
	@ special 0x188
	@ special 0x9D
	waitstate
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcFaceUpAlternate
	waitmovement 0x0
	msgbox Route29_Text_CatchingTutorialCompleteEast, MSGBOX_NPC
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcFaceDown
	waitmovement 0x0
	setflag 0x1781
	release
	end

Route29_Script_CatchingTutorialEast_AlreadyCompleted::
	release
	end

Route29_Script_CatchingTutorialNpc_RepeatDemonstration::
	release
	@ special 0x188
	@ special 0x9D
	waitstate
	msgbox Route29_Text_CatchingTutorialCompleteWest, MSGBOX_NPC
	applymovement 0x5, Route29_Movement_CatchingTutorialNpcFaceDownFast
	setflag 0x1781
	release
	end

Route29_Movement_CatchingTutorialPlayerMoveToDemoWest::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

Route29_Movement_CatchingTutorialNpcLeaveWest::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route29_Movement_CatchingTutorialNpcApproachWest::
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route29_Movement_CatchingTutorialNpcFaceUp::
	face_up
	step_end

Route29_Movement_CatchingTutorialNpcFaceDownFast::
	face_down
	step_end

Route29_Movement_CatchingTutorialNpcFaceUpAlternate::
	face_up
	step_end

Route29_Movement_CatchingTutorialNpcFaceDown::
	face_down
	step_end

Route29_Movement_CatchingTutorialPlayerMoveToDemoEast::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route29_Movement_CatchingTutorialNpcLeaveEast::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

Route29_Movement_CatchingTutorialNpcApproachEast::
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route29_Text_RouteSign:
	.string "ROUTE 29\p"
	.string "{LEFT_ARROW} CHERRYGROVE CITY\n"
	.string "{RIGHT_ARROW} NEW BARK TOWN$"

Route29_Text_SaveProgressReminder:
	.string "I wanted to take a break, so I\n"
	.string "saved to record my progress.$"

Route29_Text_LedgeTutorial:
	.string "See those ledges? It's scary to jump\n"
	.string "off them.\p"
	.string "But you can go to NEW BARK TOWN\n"
	.string "without walking through the grass.$"

Route29_Text_PokemonWatcherNight:
	.string "I'm waiting for POKéMON that\n"
	.string "only appear in the NIGHT.$"

Route29_Text_TallGrassWarning:
	.string "Yo. How are your POKéMON?\n"
	.string "If they're weak and not ready for\l"
	.string "battle, keep out of the grass.$"

Route29_Text_PokemonHideInGrass:
	.string "POKéMON hide in the grass.\n"
	.string "Who knows when they'll pop out...$"

Route29_Text_TuscanyExplainSilkScarf:
	.string "Wouldn't you agree that it is\n"
	.string "most adorable?\p"
	.string "It strengthens normal-type moves.\n"
	.string "I am certain it will be of use.$"

Route29_Text_TuscanyAlreadyMet:
	.string "Have you met MONICA, my older\n"
	.string "sister?\p"
	.string "Or my younger brother, WESLEY?\n"
	.string "I am the second of seven children.$"

Route29_Text_TuscanyBagFull:
	.string "It appears that your BAG is\n"
	.string "full.\n"
	.string "Please make space for this.$"

Route29_Text_TuscanyIntroduction:
	.string "I do believe that this is the\n"
	.string "first time we've met?\p"
	.string "Please allow me to introduce\n"
	.string "myself.\p"
	.string "I am TUSCANY of Snowflakes.\p"
	.string "By way of introduction, please\n"
	.string "accept this gift, SILK SCARF.$"

Route29_Text_PokemonWatcherMorning:
	.string "I'm waiting for POKéMON that\n"
	.string "only appear in the MORNING.$"

Route29_Text_CatchingTutorialCompleteWest:
	.string "That's how you do it.\p"
	.string "If you weaken them first, POKéMON\n"
	.string "are easier to catch.$"

Route29_Text_CatchingTutorialDeclinedWest:
	.string "Oh. Fine, then.\p"
	.string "Anyway, if you want to catch\n"
	.string "POKéMON, you have to walk a lot.$"

Route29_Text_CatchingTutorialOfferWest:
	.string "I've seen you a couple times.\p"
	.string "How many POKéMON have you caught?\p"
	.string "Would you like me to show you how\n"
	.string "to catch POKéMON?$"

Route29_Text_CatchingTutorialCompleteEast:
	.string "That's how you do it.\p"
	.string "If you weaken them first, POKéMON\n"
	.string "are easier to catch.$"

Route29_Text_CatchingTutorialDeclinedEast:
	.string "Oh. Fine, then.\p"
	.string "Anyway, if you want to catch\n"
	.string "POKéMON, you have to walk a lot.$"

Route29_Text_CatchingTutorialOfferEast:
	.string "I've seen you a couple times.\p"
	.string "How many POKéMON have you caught?\p"
	.string "Would you like me to show you how\n"
	.string "to catch POKéMON?$"

Route29_Text_CatchingTutorialOfferRepeat:
	.string "Huh? You want me to show you how\n"
	.string "to catch POKéMON?$"
