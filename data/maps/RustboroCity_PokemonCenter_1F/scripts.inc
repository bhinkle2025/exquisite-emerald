RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_RUSTBORO_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_GameboyKid::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LINKING_CABLE, RustboroCity_PokemonCenter_1F_EventScript_GameboyKid_After

	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonThatEvolveWhenTraded_Gift, MSGBOX_DEFAULT
	giveitem ITEM_LINKING_CORD, 1
	waitmessage
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_PokemonCenter_1F_EventScript_GameboyKid_BagFull

	setflag FLAG_RECEIVED_LINKING_CABLE
	msgbox RustboroCity_PokemonCenter_1F_Text_GameboyKid_GaveLinkingCable, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_GameboyKid_BagFull:
    msgbox RustboroCity_PokemonCenter_1F_Text_GameboyKid_BagFull, MSGBOX_DEFAULT
    release
    end

RustboroCity_PokemonCenter_1F_EventScript_GameboyKid_After:
    msgbox RustboroCity_PokemonCenter_1F_Text_PokemonThatEvolveWhenTraded_After, MSGBOX_NPC
    release
    end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "My POKéMON has a NAIVE nature, and my\n"
	.string "friend's has a JOLLY nature.\p"
	.string "It's fascinating how POKéMON have\n"
	.string "personalities!$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Just like people, there are male and\n"
	.string "female POKéMON.\p"
	.string "But no one seems to have any idea how\n"
	.string "they're different.$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "The man next door gave me an HM!\p"
	.string "I used it to teach my POKéMON how to\n"
	.string "CUT down skinny trees.$"

RustboroCity_PokemonCenter_1F_Text_PokemonThatEvolveWhenTraded_Gift:
    .string "There are POKéMON that evolve when\n"
    .string "you trade them! That's what I heard!\p"
    .string "But not everyone has someone to trade\n"
    .string "with...\p"
    .string "Here, you can have this!$"

RustboroCity_PokemonCenter_1F_Text_GameboyKid_GaveLinkingCable:
    .string "I heard that using that item can\n"
    .string "help with trade evolutions.\p"
    .string "I only have one, so use it wisely!$"

RustboroCity_PokemonCenter_1F_Text_GameboyKid_BagFull:
    .string "Oh!\n"
    .string "Your BAG is full...\p"
    .string "Come back after you make some room!$"

RustboroCity_PokemonCenter_1F_Text_PokemonThatEvolveWhenTraded_After:
    .string "Some POKéMON evolve from trading...\p"
    .string "That item I gave you might help\n"
    .string "someday.$"
