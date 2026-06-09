NewBarkTown_House2_MapScripts::
	.byte 0

NewBarkTown_House2_EventScript_ElmWife::

    msgbox NewBarkTown_House2_Text_HusbandAlwaysBusy, MSGBOX_NPC
    end

NewBarkTown_House2_EventScript_ElmDaughter::
    msgbox NewBarkTown_House2_Text_ElmDaughterBecomeProfessor, MSGBOX_NPC
    end

NewBarkTown_House2_EventScript_ElmResearchPapers::
    msgbox NewBarkTown_House2_Text_ElmResearchPapers, MSGBOX_SIGN
    end

NewBarkTown_House2_Text_HusbandAlwaysBusy:
    .string "Hi, {PLAYER}!\n"
    .string "My husband's always so busy--I hope\l"
    .string "he's OK.\p"
    .string "When he's caught up in his POKéMON\n"
    .string "research, he even forgets to eat.$"

NewBarkTown_House2_Text_ElmDaughterBecomeProfessor:
    .string "When I grow up, I'm going to help my\n"
    .string "dad!\p"
    .string "I'm going to be a great POKéMON\n"
    .string "professor!$"

NewBarkTown_House2_Text_ElmResearchPapers:
    .string "POKéMON.\p"
    .string "Where do they come from?\n"
    .string "Where are they going?\p"
    .string "Why has no one ever witnessed a\n"
    .string "POKéMON's birth?\p"
    .string "I want to know!\n"
    .string "I will dedicate my life to the study\l"
    .string "of POKéMON!\p"
    .string "...\p"
    .string "It's a part of PROF. ELM's research\n"
    .string "papers.$"
