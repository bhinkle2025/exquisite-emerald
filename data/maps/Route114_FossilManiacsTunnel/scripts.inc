Route114_FossilManiacsTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad:
	clearflag FLAG_FOSSIL_MANIAC_OFFERED_SALE
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac::
    lock
    faceplayer

    // If sale already offered this visit, just do vanilla behavior
    goto_if_set FLAG_FOSSIL_MANIAC_OFFERED_SALE, Route114_FossilManiacsTunnel_EventScript_FossilManiac_NormalOnly

    // --- VANILLA BEHAVIOR, but instead of ending, we fall through to OfferSale ---
    goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil

    checkitem ITEM_ROOT_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil_ThenOffer
    checkitem ITEM_CLAW_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil_ThenOffer

    msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
    goto Route114_FossilManiacsTunnel_EventScript_FossilManiac_OfferSaleAfter

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil_ThenOffer:
    msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
    goto Route114_FossilManiacsTunnel_EventScript_FossilManiac_OfferSaleAfter


Route114_FossilManiacsTunnel_EventScript_FossilManiac_NormalOnly:
	// This is literally your original logic, but without the sales continuation.
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil

	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil_Normal
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil_Normal

	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac_OfferSaleAfter:
	// Mark that we've offered this visit (resets on re-enter)
	setflag FLAG_FOSSIL_MANIAC_OFFERED_SALE

	// Continuation: feels bad, offers sale
	msgbox Route114_FossilManiacsTunnel_Text_FossilManiac_FeelsBadOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route114_FossilManiacsTunnel_EventScript_FossilManiac_Decline

	checkmoney 2000
	goto_if_eq VAR_RESULT, FALSE, Route114_FossilManiacsTunnel_EventScript_FossilManiac_NoMoney

	removemoney 2000
	playse SE_SHOP
	waitse

	call Route114_FossilManiacsTunnel_EventScript_GiveRandomImportedFossil
	goto_if_eq VAR_RESULT, FALSE, Route114_FossilManiacsTunnel_EventScript_FossilManiac_BagFullRefund

	msgbox Route114_FossilManiacsTunnel_Text_FossilManiac_Thanks, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac_Decline:
	msgbox Route114_FossilManiacsTunnel_Text_FossilManiac_Decline, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac_NoMoney:
	msgbox Route114_FossilManiacsTunnel_Text_FossilManiac_NoMoney, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac_BagFullRefund:
	addmoney 2000
	msgbox Route114_FossilManiacsTunnel_Text_FossilManiac_BagFull, MSGBOX_DEFAULT
	release
	end


Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil_Normal::
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end


Route114_FossilManiacsTunnel_EventScript_GiveRandomImportedFossil:
	random 9
	goto_if_eq VAR_RESULT, 0, Route114_FossilManiacsTunnel_EventScript_GiveHelix
	goto_if_eq VAR_RESULT, 1, Route114_FossilManiacsTunnel_EventScript_GiveDome
	goto_if_eq VAR_RESULT, 2, Route114_FossilManiacsTunnel_EventScript_GiveOldAmber
	goto_if_eq VAR_RESULT, 3, Route114_FossilManiacsTunnel_EventScript_GiveSkull
	goto_if_eq VAR_RESULT, 4, Route114_FossilManiacsTunnel_EventScript_GiveArmor
	goto_if_eq VAR_RESULT, 5, Route114_FossilManiacsTunnel_EventScript_GiveCover
	goto_if_eq VAR_RESULT, 6, Route114_FossilManiacsTunnel_EventScript_GivePlume
	goto_if_eq VAR_RESULT, 7, Route114_FossilManiacsTunnel_EventScript_GiveJaw
	goto Route114_FossilManiacsTunnel_EventScript_GiveSail

Route114_FossilManiacsTunnel_EventScript_GiveHelix:
	giveitem ITEM_HELIX_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveDome:
	giveitem ITEM_DOME_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveOldAmber:
	giveitem ITEM_OLD_AMBER, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveSkull:
	giveitem ITEM_SKULL_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveArmor:
	giveitem ITEM_ARMOR_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveCover:
	giveitem ITEM_COVER_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GivePlume:
	giveitem ITEM_PLUME_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveJaw:
	giveitem ITEM_JAW_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_GiveSail:
	giveitem ITEM_SAIL_FOSSIL, 1
	waitmessage
	return

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
	.string "I'm the FOSSIL MANIAC…\n"
	.string "I'm a nice guy who loves FOSSILS…\p"
	.string "Do you want a FOSSIL?\p"
	.string "But the FOSSILS around these parts all\n"
	.string "belong to me… None for you…\p"
	.string "If you can't bear to go without\n"
	.string "a FOSSIL, look in a desert where there\l"
	.string "are boulders and sand that may hide\l"
	.string "FOSSILS…$"

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
	.string "You found a FOSSIL, didn't you?\n"
	.string "That's so nice… It's so dreamy…\p"
	.string "What are you going to do with that\n"
	.string "FOSSIL?\p"
	.string "From what I've heard, DEVON is doing\n"
	.string "research on reviving POKéMON from\l"
	.string "FOSSILS…\p"
	.string "I love my FOSSILS, so I would never\n"
	.string "do anything like that…$"

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
	.string "FOSSILS are so… Wonderful…\n"
	.string "It's so dreamy…$"

Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
	.string "Oh…\n"
	.string "It's not safe that way…\p"
	.string "I was digging away, you see…\n"
	.string "When the whole wall collapsed…\p"
	.string "I think there's a giant cavern\n"
	.string "underneath now…\p"
	.string "But I've left it alone because I don't\n"
	.string "think there are any FOSSILS there…$"

Route114_FossilManiacsTunnel_Text_FossilManiac_FeelsBadOffer:
	.string "…Wait.\n"
	.string "That came out kinda harsh.\p"
	.string "Look, I really do love FOSSILS…\p"
	.string "If you want, I'll sell you a random\n"
	.string "FOSSIL for ¥2000.\p"
	.string "Want one?$"

Route114_FossilManiacsTunnel_Text_FossilManiac_Thanks:
	.string "Heh… Take good care of it.\n"
	.string "FOSSILS are… so dreamy…$"

Route114_FossilManiacsTunnel_Text_FossilManiac_Decline:
	.string "Yeah… I get it.\n"
	.string "Maybe another time…$"

Route114_FossilManiacsTunnel_Text_FossilManiac_NoMoney:
	.string "¥2000…\n"
	.string "Sorry, you don't have enough…$"

Route114_FossilManiacsTunnel_Text_FossilManiac_BagFull:
	.string "Whoa!\n"
	.string "Your BAG is full!\p"
	.string "I refunded your money.\n"
	.string "Make some room and come back.$"
