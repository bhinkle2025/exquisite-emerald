VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	lock
	faceplayer

	@ Try to give Aggronite if not received yet
	checkflag FLAG_RECEIVED_AGGRONITE_RUSTURF
	goto_if TRUE, VerdanturfTown_WandasHouse_EventScript_NormalDialogue

	checkitemspace ITEM_AGGRONITE, 1
	goto_if_eq VAR_RESULT, FALSE, VerdanturfTown_WandasHouse_EventScript_AggroniteBagFull

	msgbox VerdanturfTown_WandasHouse_Text_GiveAggronite, MSGBOX_NPC
	giveitem ITEM_AGGRONITE
	setflag FLAG_RECEIVED_AGGRONITE_RUSTURF
	release
	end

VerdanturfTown_WandasHouse_EventScript_AggroniteBagFull:
	msgbox VerdanturfTown_WandasHouse_Text_AggroniteBagFull, MSGBOX_NPC
	release
	end

VerdanturfTown_WandasHouse_EventScript_NormalDialogue:
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	release
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer

	@ One-time gift check
	goto_if_set FLAG_RECEIVED_GARDEVOIRITE, VerdanturfTown_WandasHouse_EventScript_WandaAlreadyGaveStone

	@ Must beat Wally first
	goto_if_unset FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry

	@ Give the stone regardless of Lavaridge order
	goto VerdanturfTown_WandasHouse_EventScript_WandaGiveGardevoirite

VerdanturfTown_WandasHouse_EventScript_WandaGiveGardevoirite::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaGiveAfterLavaridge

	msgbox VerdanturfTown_WandasHouse_Text_GaveGardevoirite, MSGBOX_DEFAULT
	goto VerdanturfTown_WandasHouse_EventScript_WandaFinishGive

VerdanturfTown_WandasHouse_EventScript_WandaGiveAfterLavaridge::
	msgbox VerdanturfTown_WandasHouse_Text_GaveGardevoirite_PostLavaridge, MSGBOX_DEFAULT

VerdanturfTown_WandasHouse_EventScript_WandaFinishGive::
	giveitem ITEM_GARDEVOIRITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_GARDEVOIRITE
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaAlreadyGaveStone::
	msgbox VerdanturfTown_WandasHouse_Text_AlreadyGaveGardevoirite, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "WALLY: I lost to you, {PLAYER}, but I'm\n"
	.string "not feeling down anymore.\p"
	.string "Because I have a new purpose in life.\n"
	.string "Together with my KIRLIA, I'm going\l"
	.string "to challenge POKéMON GYMS and become\l"
	.string "a great TRAINER.\p"
	.string "Please watch me, {PLAYER}.\n"
	.string "I'm going to be stronger than you.\p"
	.string "When I do, I'm going to challenge you\n"
	.string "to another battle.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "WALLY: Please watch me, {PLAYER}.\n"
	.string "I'm going to get stronger than you.\p"
	.string "When I do, I'm going to challenge you\n"
	.string "to another battle.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "UNCLE: Oh! {PLAYER}{KUN}!\n"
	.string "WALLY's next door.\p"
	.string "But, boy, there's something I have to\n"
	.string "tell you.\p"
	.string "This natural environment is doing\n"
	.string "wonders for WALLY's health.\p"
	.string "Maybe it's not just the environment.\n"
	.string "It could be POKéMON that are giving\l"
	.string "the boy hope.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY's gone away…\n"
	.string "He slipped off on his own…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "UNCLE: Is that right?\n"
	.string "WALLY's gone away that far all by\l"
	.string "himself…\p"
	.string "Well, I have to give him credit--he is\n"
	.string "my little brother's son.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "WANDA: You are?\n"
	.string "Oh, right, I get it!\p"
	.string "You're the {PLAYER} who WALLY was\n"
	.string "telling me about.\p"
	.string "I'm WALLY's cousin.\n"
	.string "Glad to meet you!\p"
	.string "I think WALLY's become a lot more lively\n"
	.string "and healthy since he came here.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WANDA: Don't worry about WALLY.\n"
	.string "He'll be just fine.\p"
	.string "I know my little cousin, and he has\n"
	.string "POKéMON with him, too.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Thanks to you, I can see my girlfriend\n"
	.string "every day.\l"
	.string "Happy? You bet I am!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "My daughter's boyfriend is a very\n"
	.string "driven and passionate sort of person.\p"
	.string "He's been digging a tunnel nonstop\n"
	.string "just so he can see my daughter.\p"
	.string "My daughter's a little concerned,\n"
	.string "so she goes out to the tunnel a lot.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "It's amazing. My daughter's boyfriend\n"
	.string "was digging the tunnel by hand!\p"
	.string "It's so incredible!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "If anything were to happen to WALLY,\n"
	.string "I would never be able to look his\l"
	.string "parents in PETALBURG in the eye…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "WALLY was in EVER GRANDE?\p"
	.string "His parents in PETALBURG would be\n"
	.string "astonished to hear that!$"

VerdanturfTown_WandasHouse_Text_GiveAggronite:
	.string "Oh, hey!\p"
	.string "I meant to give you this earlier.\n"
	.string "It's an AGGRONITE.\p"
	.string "Thanks again for everything you did.$"

VerdanturfTown_WandasHouse_Text_AggroniteBagFull:
	.string "Oh, hey!\p"
	.string "I want to give you an AGGRONITE,\n"
	.string "but your BAG is full.\p"
	.string "Make some space and talk to me again.$"

VerdanturfTown_WandasHouse_Text_GaveGardevoirite::
	.string "WANDA: Oh! You're the TRAINER who\n"
	.string "helped WALLY, aren't you?\p"
	.string "His confidence is coming back,\n"
	.string "little by little.\p"
	.string "I want you to have this.\n"
	.string "It's special to our family.\p"
	.string "If you have a GARDEVOIR,\n"
	.string "it will respond to it.$"

VerdanturfTown_WandasHouse_Text_AlreadyGaveGardevoirite::
	.string "WANDA: How is it?\n"
	.string "That stone suits you.\p"
	.string "Take good care of your POKeMON,\n"
	.string "and they'll take good care of you.$"

VerdanturfTown_WandasHouse_Text_GaveGardevoirite_PostLavaridge::
	.string "WANDA: Ah, {PLAYER}{KUN}…\n"
	.string "WALLY told me you kept going.\p"
	.string "Please take this.\n"
	.string "It’s a special stone.\p"
	.string "It resonates with GARDEVOIR.$"

