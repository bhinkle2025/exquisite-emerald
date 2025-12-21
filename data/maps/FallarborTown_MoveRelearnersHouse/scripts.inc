FallarborTown_MoveRelearnersHouse_MapScripts::
	.byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, FallarborTown_MoveRelearnersHouse_EventScript_AskPerfectIV
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskPerfectIV
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskPerfectIV::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseStat
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseStat::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_IV_STAT, 0
	switch VAR_RESULT
	case 0, FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV
	case 1, FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV
	case 2, FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV
	case 3, FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV
	case 4, FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV
	case 5, FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV
	case MULTI_B_PRESSED, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_PerfectIV::
	// At this point:
	// - ChooseMonForMoveRelearner stored the chosen mon in the usual vars (your existing system)
	// - VAR_RESULT (0-5) is the stat index from MULTI_IV_STAT
	//
	// You’ll implement this special in C to set the chosen IV to 31 based on VAR_RESULT.
	specialvar VAR_0x8006, PerfectSelectedMonIV
	goto_if_eq VAR_0x8006, 0, FallarborTown_MoveRelearnersHouse_EventScript_AlreadyPerfect
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

FallarborTown_MoveRelearnersHouse_EventScript_AlreadyPerfect::
	msgbox FallarborTown_MoveRelearnersHouse_Text_AlreadyPerfect, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseStat
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor:
	.string "I'm a POKéMON SPECIALIST.\p"
	.string "Moves aren't the only thing that\n"
	.string "can be refined in a POKéMON.\l"
	.string "With the right focus, its true\l"
	.string "potential can be brought out.\p"
	.string "I can perfect one of a POKéMON's\n"
	.string "natural strengths for you.\p"
	.string "All it takes is a HEART SCALE.\n"
	.string "I'm collecting those now.$"


FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh! Is that a HEART SCALE?\p"
	.string "That'll do nicely.\p"
	.string "So, which POKéMON's potential\n"
	.string "do you want me to refine?$"


FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon:
	.string "Which POKéMON should I work on?$"


FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove:
	.string "Which stat should I perfect?$"


FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon:
	.string "Hmm…\p"
	.string "That POKéMON's potential can't be\n"
	.string "refined any further right now.$"


FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale:
	.string "{PLAYER} handed over one HEART SCALE.\p"
	.string "The POKéMON's potential was perfected!$"


FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale:
	.string "If you want a POKéMON to reach its\n"
	.string "true potential, bring me a HEART SCALE.$"


FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg:
	.string "Hmm? An EGG?\p"
	.string "Potential can't be refined until\n"
	.string "it's hatched.$"

FallarborTown_MoveRelearnersHouse_Text_AlreadyPerfect:
    .string "Ah! That stat is already perfect.\p"
    .string "I won't take your HEART SCALE.$"


