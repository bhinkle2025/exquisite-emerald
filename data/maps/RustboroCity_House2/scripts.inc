RustboroCity_House2_MapScripts::
	.byte 0

RustboroCity_House2_EventScript_PokefanF::
	msgbox RustboroCity_House2_Text_TrainerSchoolExcellent, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_LittleGirl::
	msgbox RustboroCity_House2_Text_RoxanneKnowsALot, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_Man_1::
	checkflag FLAG_GOT_EVIOLITE_RUSTBORO
    goto_if TRUE, RustboroCity_House2_EventScript_Man_1_Already

	msgbox RustboroCity_House2_Text_EvioliteIntro, MSGBOX_NPC


	giveitem ITEM_EVIOLITE, 1
	call_if_eq VAR_RESULT, FALSE, RustboroCity_House2_EventScript_Man_1_BagFull

	setflag FLAG_GOT_EVIOLITE_RUSTBORO
	msgbox RustboroCity_House2_Text_EvioliteAfter, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_Man_1_Already::
	msgbox RustboroCity_House2_Text_EvioliteAlready, MSGBOX_NPC
	end

RustboroCity_House2_EventScript_Man_1_BagFull::
	msgbox RustboroCity_House2_Text_EvioliteBagFull, MSGBOX_NPC
	end

RustboroCity_House2_Text_TrainerSchoolExcellent:
	.string "The TRAINER'S SCHOOL is excellent.\p"
	.string "If you study there, you could even\n"
	.string "become a GYM LEADER.$"

RustboroCity_House2_Text_RoxanneKnowsALot:
	.string "ROXANNE, the GYM LEADER, really knows\n"
	.string "a lot about POKéMON.\p"
	.string "She's really strong, too!$"

RustboroCity_House2_Text_EvioliteIntro:
	.string "You look like you train with care.\p"
	.string "Take this-it's called an EVIOLITE.\p"
	.string "It boosts the defenses of POKéMON\n"
	.string "that can still evolve.$"

RustboroCity_House2_Text_EvioliteAfter:
	.string "Treat it well. Some POKéMON shine\n"
	.string "before they ever evolve.$"

RustboroCity_House2_Text_EvioliteAlready:
	.string "That EVIOLITE should serve you well.\n"
	.string "Keep training smart.$"

RustboroCity_House2_Text_EvioliteBagFull:
	.string "Your BAG is too full.\p"
	.string "Make some space and talk to me again.$"

