OldaleTown_House1_MapScripts::
	.byte 0

OldaleTown_House1_EventScript_Woman::
	msgbox OldaleTown_House1_Text_LeftPokemonGoesOutFirst, MSGBOX_NPC
	end


@ =========================
@ Old Man: Random Starter
@ =========================
OldaleTown_House1_EventScript_OldManRandomStarter::
	lock
	faceplayer

	checkflag FLAG_GOT_OLDALE_STARTER
	goto_if TRUE, OldaleTown_House1_EventScript_OldMan_Already

	checkflag FLAG_DEFEATED_RIVAL_ROUTE103
	goto_if FALSE, OldaleTown_House1_EventScript_OldMan_Route103NotCleared

	msgbox OldaleTown_House1_Text_OldManIntro, MSGBOX_NPC

	special Special_PickOldaleRandomStarter

	@ Setup: show pic + buffer name + set transfer species
	call OldaleTown_House1_EventScript_SetupGiftStarter

	@ Give mon (Level 5, no held item)
	givemon VAR_OLDALE_STARTER_SPECIES, 5, ITEM_NONE

	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, OldaleTown_House1_EventScript_StarterToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC,    OldaleTown_House1_EventScript_StarterToPC

	@ No room at all
	hidemonpic
	release
	goto Common_EventScript_NoMoreRoomForPokemon
	end

OldaleTown_House1_EventScript_OldMan_Route103NotCleared::
	msgbox OldaleTown_House1_Text_OldMan_Route103NotCleared, MSGBOX_NPC
	release
	end

@ =========================
@ Party branch
@ =========================
OldaleTown_House1_EventScript_StarterToParty::
	playfanfare MUS_OBTAIN_ITEM
	msgbox OldaleTown_House1_Text_ReceivedMon, MSGBOX_DEFAULT
	waitfanfare

	hidemonpic

	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OldaleTown_House1_EventScript_AfterGive

	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto OldaleTown_House1_EventScript_AfterGive
	end


@ =========================
@ PC branch
@ =========================
OldaleTown_House1_EventScript_StarterToPC::
	playfanfare MUS_OBTAIN_ITEM
	msgbox OldaleTown_House1_Text_ReceivedMon, MSGBOX_DEFAULT
	waitfanfare

	hidemonpic

	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OldaleTown_House1_EventScript_StarterTransferredToPC

	call Common_EventScript_NameReceivedBoxMon
	goto OldaleTown_House1_EventScript_StarterTransferredToPC
	end

OldaleTown_House1_EventScript_StarterTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto OldaleTown_House1_EventScript_AfterGive
	end


@ =========================
@ After / Already
@ =========================
OldaleTown_House1_EventScript_AfterGive::
	setflag FLAG_GOT_OLDALE_STARTER
	msgbox OldaleTown_House1_Text_OldManAfter, MSGBOX_NPC
	release
	end

OldaleTown_House1_EventScript_OldMan_Already::
	msgbox OldaleTown_House1_Text_OldManAlready, MSGBOX_NPC
	release
	end


@ =========================
@ SetupGiftStarter
@ - Shows pic
@ - bufferspeciesname STR_VAR_1 for received text
@ - sets VAR_TEMP_TRANSFERRED_SPECIES for nickname/PC scripts
@ =========================
OldaleTown_House1_EventScript_SetupGiftStarter::
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_TURTWIG
	goto_if_eq OldaleTown_House1_EventScript_Setup_Turtwig
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_CHIMCHAR
	goto_if_eq OldaleTown_House1_EventScript_Setup_Chimchar
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_PIPLUP
	goto_if_eq OldaleTown_House1_EventScript_Setup_Piplup

	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_SNIVY
	goto_if_eq OldaleTown_House1_EventScript_Setup_Snivy
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_TEPIG
	goto_if_eq OldaleTown_House1_EventScript_Setup_Tepig
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_OSHAWOTT
	goto_if_eq OldaleTown_House1_EventScript_Setup_Oshawott

	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_CHESPIN
	goto_if_eq OldaleTown_House1_EventScript_Setup_Chespin
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_FENNEKIN
	goto_if_eq OldaleTown_House1_EventScript_Setup_Fennekin
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_FROAKIE
	goto_if_eq OldaleTown_House1_EventScript_Setup_Froakie

	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_ROWLET
	goto_if_eq OldaleTown_House1_EventScript_Setup_Rowlet
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_LITTEN
	goto_if_eq OldaleTown_House1_EventScript_Setup_Litten
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_POPPLIO
	goto_if_eq OldaleTown_House1_EventScript_Setup_Popplio

	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_GROOKEY
	goto_if_eq OldaleTown_House1_EventScript_Setup_Grookey
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_SCORBUNNY
	goto_if_eq OldaleTown_House1_EventScript_Setup_Scorbunny
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_SOBBLE
	goto_if_eq OldaleTown_House1_EventScript_Setup_Sobble

	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_SPRIGATITO
	goto_if_eq OldaleTown_House1_EventScript_Setup_Sprigatito
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_FUECOCO
	goto_if_eq OldaleTown_House1_EventScript_Setup_Fuecoco
	compare VAR_OLDALE_STARTER_SPECIES, SPECIES_QUAXLY
	goto_if_eq OldaleTown_House1_EventScript_Setup_Quaxly

	@ failsafe
	goto OldaleTown_House1_EventScript_Setup_Turtwig

OldaleTown_House1_EventScript_Setup_Turtwig::
	bufferspeciesname STR_VAR_1, SPECIES_TURTWIG
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TURTWIG
	showmonpic SPECIES_TURTWIG, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Chimchar::
	bufferspeciesname STR_VAR_1, SPECIES_CHIMCHAR
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIMCHAR
	showmonpic SPECIES_CHIMCHAR, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Piplup::
	bufferspeciesname STR_VAR_1, SPECIES_PIPLUP
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_PIPLUP
	showmonpic SPECIES_PIPLUP, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Snivy::
	bufferspeciesname STR_VAR_1, SPECIES_SNIVY
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SNIVY
	showmonpic SPECIES_SNIVY, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Tepig::
	bufferspeciesname STR_VAR_1, SPECIES_TEPIG
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TEPIG
	showmonpic SPECIES_TEPIG, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Oshawott::
	bufferspeciesname STR_VAR_1, SPECIES_OSHAWOTT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_OSHAWOTT
	showmonpic SPECIES_OSHAWOTT, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Chespin::
	bufferspeciesname STR_VAR_1, SPECIES_CHESPIN
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHESPIN
	showmonpic SPECIES_CHESPIN, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Fennekin::
	bufferspeciesname STR_VAR_1, SPECIES_FENNEKIN
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_FENNEKIN
	showmonpic SPECIES_FENNEKIN, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Froakie::
	bufferspeciesname STR_VAR_1, SPECIES_FROAKIE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_FROAKIE
	showmonpic SPECIES_FROAKIE, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Rowlet::
	bufferspeciesname STR_VAR_1, SPECIES_ROWLET
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ROWLET
	showmonpic SPECIES_ROWLET, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Litten::
	bufferspeciesname STR_VAR_1, SPECIES_LITTEN
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LITTEN
	showmonpic SPECIES_LITTEN, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Popplio::
	bufferspeciesname STR_VAR_1, SPECIES_POPPLIO
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_POPPLIO
	showmonpic SPECIES_POPPLIO, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Grookey::
	bufferspeciesname STR_VAR_1, SPECIES_GROOKEY
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_GROOKEY
	showmonpic SPECIES_GROOKEY, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Scorbunny::
	bufferspeciesname STR_VAR_1, SPECIES_SCORBUNNY
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SCORBUNNY
	showmonpic SPECIES_SCORBUNNY, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Sobble::
	bufferspeciesname STR_VAR_1, SPECIES_SOBBLE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SOBBLE
	showmonpic SPECIES_SOBBLE, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Sprigatito::
	bufferspeciesname STR_VAR_1, SPECIES_SPRIGATITO
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SPRIGATITO
	showmonpic SPECIES_SPRIGATITO, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Fuecoco::
	bufferspeciesname STR_VAR_1, SPECIES_FUECOCO
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_FUECOCO
	showmonpic SPECIES_FUECOCO, 10, 3
	return

OldaleTown_House1_EventScript_Setup_Quaxly::
	bufferspeciesname STR_VAR_1, SPECIES_QUAXLY
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_QUAXLY
	showmonpic SPECIES_QUAXLY, 10, 3
	return


@ =========================
@ Text
@ =========================
OldaleTown_House1_Text_OldManIntro:
	.string "Heh… looking for a partner, are ya?\p"
	.string "You don’t choose.\nFATE chooses!$"

OldaleTown_House1_Text_OldManAfter:
	.string "There you go!\p"
	.string "Treat it well, and it’ll\n"
	.string "take you far.$"

OldaleTown_House1_Text_OldManAlready:
	.string "I already gave you a POKéMON.\p"
	.string "Now go make a legend.$"

OldaleTown_House1_Text_LeftPokemonGoesOutFirst:
	.string "When a POKéMON battle starts, the one\n"
	.string "at the left of the list goes out first.\p"
	.string "So, when you get more POKéMON in your\n"
	.string "party, try switching around the order\l"
	.string "of your POKéMON.\p"
	.string "It could give you an advantage.$"

OldaleTown_House1_Text_ReceivedMon:
	.string "{PLAYER} received {STR_VAR_1}!$"

OldaleTown_House1_Text_OldMan_Route103NotCleared:
	.string "No… the time isn’t right yet.\p"
	.string "There’s a battle you haven’t fought\n"
	.string "and a bond you haven’t forged.\p"
	.string "Come back after that.$"


