RustboroCity_DevonCorp_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition:
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls::
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav::
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

@ ============================================================
@ Devon Corp 2F - Fossil Scientist (Dynamic Fossil Selector)
@ Shows ONLY fossils you actually have
@ ============================================================

RustboroCity_DevonCorp_2F_EventScript_FossilScientist::
    lock
    faceplayer

    call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_StillRegenerating

    @ If ready, give the revived Pokémon
    goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RustboroCity_DevonCorp_2F_EventScript_GiveRevivedFossilMon

    @ Check if the player has any fossils we can work with
    call RustboroCity_DevonCorp_2F_EventScript_BuildFossilDynList
    goto_if_eq VAR_RESULT, 0, RustboroCity_DevonCorp_2F_EventScript_NoFossilsInBag

    @ Confirm
    msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineFossil

    @ Rebuild list (fresh) and open selector
    goto_if_eq VAR_RESULT, 0, RustboroCity_DevonCorp_2F_EventScript_NoFossilsInBag

    goto RustboroCity_DevonCorp_2F_EventScript_OpenDynamicFossilSelector

RustboroCity_DevonCorp_2F_EventScript_NoFossilsInBag::
    msgbox RustboroCity_DevonCorp_2F_Text_DontHaveThatFossil, MSGBOX_DEFAULT
    release
    end

RustboroCity_DevonCorp_2F_EventScript_DeclineFossil::
    msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
    release
    end



@ ============================================================
@ Open the dynamic selector that contains ONLY fossils you have
@ Selected fossil itemId is stored in VAR_TEMP_0
@ ============================================================

RustboroCity_DevonCorp_2F_EventScript_OpenDynamicFossilSelector::
    message RustboroCity_DevonCorp_2F_Text_WhichFossilWouldYouRegenerate
    waitmessage

    @ Use CB_NONE first. Once confirmed stable, you can try SHOW_ITEM.
    dynmultistack 17, 6, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE

    copyvar VAR_TEMP_0, VAR_RESULT

    @ Do NOT treat 0 as cancel (0 can be the first option's id/index in some configs)
    goto_if_eq VAR_TEMP_0, 255, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect

    goto RustboroCity_DevonCorp_2F_EventScript_SetWhichFossilFromItem


RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect::
    closemessage
    release
    end


@ ============================================================
@ Map itemId in VAR_TEMP_0 to VAR_WHICH_FOSSIL_REVIVED
@ Then jump to shared accept/remove logic
@ ============================================================

RustboroCity_DevonCorp_2F_EventScript_SetWhichFossilFromItem::
    switch VAR_TEMP_0
    case ITEM_CLAW_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_SetClaw
    case ITEM_ROOT_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_SetRoot
    case ITEM_HELIX_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_SetHelix
    case ITEM_DOME_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_SetDome
    case ITEM_OLD_AMBER,    RustboroCity_DevonCorp_2F_EventScript_SetOldAmber
    case ITEM_SKULL_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_SetSkull
    case ITEM_ARMOR_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_SetArmor
    case ITEM_COVER_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_SetCover
    case ITEM_PLUME_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_SetPlume
    case ITEM_JAW_FOSSIL,   RustboroCity_DevonCorp_2F_EventScript_SetJaw
    case ITEM_SAIL_FOSSIL,  RustboroCity_DevonCorp_2F_EventScript_SetSail

    @ Safety fallback (shouldn’t happen if list is correct)
    goto RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
    end



@ ============================================================
@ Shared accept/remove logic (your same pattern)
@ Uses VAR_TEMP_0 = selected fossil ITEM id
@ ============================================================

RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil::
    checkitem VAR_TEMP_0
    goto_if_eq VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_NoFossilsInBag

    bufferitemname STR_VAR_1, VAR_TEMP_0
    msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
    removeitem VAR_TEMP_0

    setvar VAR_FOSSIL_RESURRECTION_STATE, 1
    release
    end

@ ============================================================
@ Build dynamic fossil list based on what the player has in bag
@ - Pushes entries via dynmultipush
@ - Sets VAR_RESULT = number of entries pushed
@ ============================================================

RustboroCity_DevonCorp_2F_EventScript_BuildFossilDynList::
    setvar VAR_TEMP_1, 0  @ count
    goto RustboroCity_DevonCorp_2F_EventScript_CheckClaw

RustboroCity_DevonCorp_2F_EventScript_CheckClaw::
    checkitem ITEM_CLAW_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushClaw
    goto RustboroCity_DevonCorp_2F_EventScript_CheckRoot

RustboroCity_DevonCorp_2F_EventScript_CheckRoot::
    checkitem ITEM_ROOT_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushRoot
    goto RustboroCity_DevonCorp_2F_EventScript_CheckHelix

RustboroCity_DevonCorp_2F_EventScript_CheckHelix::
    checkitem ITEM_HELIX_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushHelix
    goto RustboroCity_DevonCorp_2F_EventScript_CheckDome

RustboroCity_DevonCorp_2F_EventScript_CheckDome::
    checkitem ITEM_DOME_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushDome
    goto RustboroCity_DevonCorp_2F_EventScript_CheckOldAmber

RustboroCity_DevonCorp_2F_EventScript_CheckOldAmber::
    checkitem ITEM_OLD_AMBER
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushOldAmber
    goto RustboroCity_DevonCorp_2F_EventScript_CheckSkull

RustboroCity_DevonCorp_2F_EventScript_CheckSkull::
    checkitem ITEM_SKULL_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushSkull
    goto RustboroCity_DevonCorp_2F_EventScript_CheckArmor

RustboroCity_DevonCorp_2F_EventScript_CheckArmor::
    checkitem ITEM_ARMOR_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushArmor
    goto RustboroCity_DevonCorp_2F_EventScript_CheckCover

RustboroCity_DevonCorp_2F_EventScript_CheckCover::
    checkitem ITEM_COVER_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushCover
    goto RustboroCity_DevonCorp_2F_EventScript_CheckPlume

RustboroCity_DevonCorp_2F_EventScript_CheckPlume::
    checkitem ITEM_PLUME_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushPlume
    goto RustboroCity_DevonCorp_2F_EventScript_CheckJaw

RustboroCity_DevonCorp_2F_EventScript_CheckJaw::
    checkitem ITEM_JAW_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushJaw
    goto RustboroCity_DevonCorp_2F_EventScript_CheckSail

RustboroCity_DevonCorp_2F_EventScript_CheckSail::
    checkitem ITEM_SAIL_FOSSIL
    goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_PushSail
    goto RustboroCity_DevonCorp_2F_EventScript_BuildFossilDynList_Done

RustboroCity_DevonCorp_2F_EventScript_BuildFossilDynList_Done::
    copyvar VAR_RESULT, VAR_TEMP_1
    return


RustboroCity_DevonCorp_2F_EventScript_SetClaw::
    setvar VAR_WHICH_FOSSIL_REVIVED, 1
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetRoot::
    setvar VAR_WHICH_FOSSIL_REVIVED, 2
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetHelix::
    setvar VAR_WHICH_FOSSIL_REVIVED, 3
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetDome::
    setvar VAR_WHICH_FOSSIL_REVIVED, 4
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetOldAmber::
    setvar VAR_WHICH_FOSSIL_REVIVED, 5
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetSkull::
    setvar VAR_WHICH_FOSSIL_REVIVED, 6
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetArmor::
    setvar VAR_WHICH_FOSSIL_REVIVED, 7
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetCover::
    setvar VAR_WHICH_FOSSIL_REVIVED, 8
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetPlume::
    setvar VAR_WHICH_FOSSIL_REVIVED, 9
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetJaw::
    setvar VAR_WHICH_FOSSIL_REVIVED, 10
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

RustboroCity_DevonCorp_2F_EventScript_SetSail::
    setvar VAR_WHICH_FOSSIL_REVIVED, 11
    goto RustboroCity_DevonCorp_2F_EventScript_TryAcceptSelectedFossil

@ -------------------------
@ Push entries (NULL name; id = item constant)
@ -------------------------

RustboroCity_DevonCorp_2F_EventScript_PushClaw::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptClawFossil, ITEM_CLAW_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckRoot

RustboroCity_DevonCorp_2F_EventScript_PushRoot::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptRootFossil, ITEM_ROOT_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckHelix

RustboroCity_DevonCorp_2F_EventScript_PushHelix::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptHelixFossil, ITEM_HELIX_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckDome

RustboroCity_DevonCorp_2F_EventScript_PushDome::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptDomeFossil, ITEM_DOME_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckOldAmber

RustboroCity_DevonCorp_2F_EventScript_PushOldAmber::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptOldAmber, ITEM_OLD_AMBER
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckSkull

RustboroCity_DevonCorp_2F_EventScript_PushSkull::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptSkullFossil, ITEM_SKULL_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckArmor

RustboroCity_DevonCorp_2F_EventScript_PushArmor::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptArmorFossil, ITEM_ARMOR_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckCover

RustboroCity_DevonCorp_2F_EventScript_PushCover::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptCoverFossil, ITEM_COVER_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckPlume

RustboroCity_DevonCorp_2F_EventScript_PushPlume::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptPlumeFossil, ITEM_PLUME_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckJaw

RustboroCity_DevonCorp_2F_EventScript_PushJaw::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptJawFossil, ITEM_JAW_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_CheckSail

RustboroCity_DevonCorp_2F_EventScript_PushSail::
    dynmultipush RustboroCity_DevonCorp_2F_Text_OptSailFossil, ITEM_SAIL_FOSSIL
    addvar VAR_TEMP_1, 1
    goto RustboroCity_DevonCorp_2F_EventScript_BuildFossilDynList_Done


RustboroCity_DevonCorp_2F_Text_OptClawFossil::  
	.string "Claw Fossil$"
RustboroCity_DevonCorp_2F_Text_OptRootFossil::  
	.string "Root Fossil$"
RustboroCity_DevonCorp_2F_Text_OptHelixFossil:: 
	.string "Helix Fossil$"
RustboroCity_DevonCorp_2F_Text_OptDomeFossil::  
	.string "Dome Fossil$"
RustboroCity_DevonCorp_2F_Text_OptOldAmber::    
	.string "Old Amber$"
RustboroCity_DevonCorp_2F_Text_OptSkullFossil:: 
	.string "Skull Fossil$"
RustboroCity_DevonCorp_2F_Text_OptArmorFossil:: 
	.string "Armor Fossil$"
RustboroCity_DevonCorp_2F_Text_OptCoverFossil:: 
	.string "Cover Fossil$"
RustboroCity_DevonCorp_2F_Text_OptPlumeFossil:: 
	.string "Plume Fossil$"
RustboroCity_DevonCorp_2F_Text_OptJawFossil::   
	.string "Jaw Fossil$"
RustboroCity_DevonCorp_2F_Text_OptSailFossil::  
	.string "Sail Fossil$"


RustboroCity_DevonCorp_2F_EventScript_GiveRevivedFossilMon::
    @ safety: must have party space
    getpartysize

    @ Map which fossil -> species, then give
    switch VAR_WHICH_FOSSIL_REVIVED
    case 1, RustboroCity_DevonCorp_2F_EventScript_GiveAnorith
    case 2, RustboroCity_DevonCorp_2F_EventScript_GiveLileep
    case 3, RustboroCity_DevonCorp_2F_EventScript_GiveOmanyte
    case 4, RustboroCity_DevonCorp_2F_EventScript_GiveKabuto
    case 5, RustboroCity_DevonCorp_2F_EventScript_GiveAerodactyl
    case 6, RustboroCity_DevonCorp_2F_EventScript_GiveCranidos
    case 7, RustboroCity_DevonCorp_2F_EventScript_GiveShieldon
    case 8, RustboroCity_DevonCorp_2F_EventScript_GiveTirtouga
    case 9, RustboroCity_DevonCorp_2F_EventScript_GiveArchen
    case 10, RustboroCity_DevonCorp_2F_EventScript_GiveTyrunt
    case 11, RustboroCity_DevonCorp_2F_EventScript_GiveAmaura

    @ fallback if var got corrupted
    setvar VAR_FOSSIL_RESURRECTION_STATE, 0
    setvar VAR_WHICH_FOSSIL_REVIVED, 0
    release
    end

@ ----- Give scripts -----
@ Pick any level you want. I'm using 20 as a sane default.

RustboroCity_DevonCorp_2F_EventScript_GiveAnorith::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
    givemon SPECIES_ANORITH, 20, ITEM_NONE, 0, 0, 0
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveLileep::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LILEEP
    givemon SPECIES_LILEEP, 20, ITEM_NONE, 0, 0, 0
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveOmanyte::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_OMANYTE
    givemon SPECIES_OMANYTE, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanyteParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanytePC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveKabuto::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KABUTO
    givemon SPECIES_KABUTO, 20, ITEM_NONE, 0, 0, 0
   	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveKabutoParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveKabutoPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveAerodactyl::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_AERODACTYL
    givemon SPECIES_AERODACTYL, 20, ITEM_NONE, 0, 0, 0
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveAerodactylParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveAerodactylPC
	goto Common_EventScript_NoMoreRoomForPokemon
   

RustboroCity_DevonCorp_2F_EventScript_GiveCranidos::
	bufferspeciesname STR_VAR_2, SPECIES_CRANIDOS
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CRANIDOS
    givemon SPECIES_CRANIDOS, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveCranidosParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveCranidosPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveShieldon::
	bufferspeciesname STR_VAR_2, SPECIES_SHIELDON
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SHIELDON
    givemon SPECIES_SHIELDON, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveShieldonParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveShieldonPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveTirtouga::
	bufferspeciesname STR_VAR_2, SPECIES_TIRTOUGA
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TIRTOUGA
    givemon SPECIES_TIRTOUGA, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveTirtougaParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveTirtougaPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveArchen::
	bufferspeciesname STR_VAR_2, SPECIES_ARCHEN
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ARCHEN
    givemon SPECIES_ARCHEN, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveArchenParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveArchenPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveTyrunt::
	bufferspeciesname STR_VAR_2, SPECIES_TYRUNT
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYRUNT
    givemon SPECIES_TYRUNT, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveTyruntParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveTyruntPC
	goto Common_EventScript_NoMoreRoomForPokemon

RustboroCity_DevonCorp_2F_EventScript_GiveAmaura::
	bufferspeciesname STR_VAR_2, SPECIES_AMAURA
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_AMAURA
    givemon SPECIES_AMAURA, 20, ITEM_NONE, 0, 0, 0
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveAmauraParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveAmauraPC
	goto Common_EventScript_NoMoreRoomForPokemon


RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil::
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ROOT_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 1
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil::
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 2
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveHelixFossil::
	bufferitemname STR_VAR_1, ITEM_HELIX_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_HELIX_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 3
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveDomeFossil::
	bufferitemname STR_VAR_1, ITEM_DOME_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_DOME_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 4
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveOldAmber::
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_OLD_AMBER
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 5
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveSkullFossil::
	bufferitemname STR_VAR_1, ITEM_SKULL_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_SKULL_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 6
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveArmorFossil::
	bufferitemname STR_VAR_1, ITEM_ARMOR_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ARMOR_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 7
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveCoverFossil::
	bufferitemname STR_VAR_1, ITEM_COVER_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_COVER_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 8
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GivePlumeFossil::
	bufferitemname STR_VAR_1, ITEM_PLUME_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_PLUME_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 9
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveJawFossil::
	bufferitemname STR_VAR_1, ITEM_JAW_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_JAW_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 10
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveSailFossil::
	bufferitemname STR_VAR_1, ITEM_SAIL_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_SAIL_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 11
	release
	end
RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_StillRegenerating::
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_LILEEP
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
	givemon SPECIES_ANORITH, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_ANORITH
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanyte::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_OMANYTE
	givemon SPECIES_OMANYTE, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanyteParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanytePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanyteParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedOmanyteFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingOmanyte
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingOmanyte
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanytePC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedOmanyteFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferOmanyteToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferOmanyteToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferOmanyteToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingOmanyte
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedOmanyteFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingOmanyte::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveKabuto::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KABUTO
	givemon SPECIES_KABUTO, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveKabutoParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveKabutoPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveKabutoParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedKabutoFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKabuto
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKabuto
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveKabutoPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedKabutoFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferKabutoToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferKabutoToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferKabutoToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKabuto
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedKabutoFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_KABUTO
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKabuto::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAerodactylParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAerodactylFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAerodactyl
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAerodactyl
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAerodactylPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAerodactylFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferAerodactylToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferAerodactylToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferAerodactylToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAerodactyl
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedAerodactylFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAerodactyl::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveCranidosParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedCranidosFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingCranidos
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingCranidos
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveCranidosPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedCranidosFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferCranidosToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferCranidosToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferCranidosToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingCranidos
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedCranidosFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_CRANIDOS
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_CRANIDOS
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingCranidos::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveShieldonParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedShieldonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingShieldon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingShieldon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveShieldonPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedShieldonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferShieldonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferShieldonToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferShieldonToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingShieldon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedShieldonFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_SHIELDON
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_SHIELDON
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingShieldon::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveTirtougaParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedTirtougaFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTirtouga
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTirtouga
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveTirtougaPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedTirtougaFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferTirtougaToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferTirtougaToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferTirtougaToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTirtouga
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedTirtougaFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_TIRTOUGA
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_TIRTOUGA
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTirtouga::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveArchenParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedArchenFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingArchen
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingArchen
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveArchenPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedArchenFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferArchenToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferArchenToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferArchenToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingArchen
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedArchenFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_ARCHEN
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_ARCHEN
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingArchen::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveTyruntParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedTyruntFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTyrunt
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTyrunt
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveTyruntPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedTyruntFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferTyruntToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferTyruntToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferTyruntToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTyrunt
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedTyruntFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_TYRUNT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_TYRUNT
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingTyrunt::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAmauraParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAmauraFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAmaura
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAmaura
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAmauraPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAmauraFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferAmauraToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferAmauraToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferAmauraToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAmaura
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedAmauraFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_AMAURA
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_AMAURA
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAmaura::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseHelixFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveHelixFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseDomeFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveDomeFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseOldAmber::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveOldAmber
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseSkullFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveSkullFossil
	end
RustboroCity_DevonCorp_2F_EventScript_ChooseArmorFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveArmorFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseCoverFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveCoverFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChoosePlumeFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GivePlumeFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseJawFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveJawFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseSailFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveSailFossil
	end


RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_ge VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext::
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon:
	.string "We're developing a device for talking\n"
	.string "with POKéMON.\p"
	.string "But we haven't had much success…$"

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls:
	.string "I'm developing new kinds of\n"
	.string "POKé BALLS…\p"
	.string "But I haven't made much headway…$"

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls:
	.string "We finally made new kinds of\n"
	.string "POKé BALLS!\p"
	.string "The REPEAT BALL makes it easier to\n"
	.string "catch POKéMON you've caught before.\p"
	.string "The TIMER BALL gets better at catching\n"
	.string "POKéMON the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the DEVON CORPORATION.\p"
	.string "Please give them a try!$"

RustboroCity_DevonCorp_2F_Text_IMadePokenav:
	.string "I made the POKéNAV!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav:
	.string "Oh, wow!\n"
	.string "That's a POKéNAV!\p"
	.string "It came about as a result of our\n"
	.string "PRESIDENT's desire to learn about\l"
	.string "the feelings of POKéMON.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the POKéNAV out.$"

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams:
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "POKéMON…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils:
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife:
	.string "Wait! That thing you have there…\n"
	.string "Is that a POKéMON fossil?\p"
	.string "Would you like to bring that POKéMON\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "FOSSIL REGENERATOR.$"

RustboroCity_DevonCorp_2F_Text_OhIsThatSo:
	.string "Oh, is that so?\p"
	.string "DEVON's technological expertise\n"
	.string "is outstanding, I tell you.$"

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher:
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the DEVON RESEARCHER.$"

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime:
	.string "The FOSSIL REGENERATOR, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife:
	.string "Thanks for waiting!\p"
	.string "Your fossilized POKéMON has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient POKéMON.\n"
	.string "{STR_VAR_2}, it was!$"

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the DEVON RESEARCHER.$"

@ Unused
RustboroCity_DevonCorp_2F_Text_TooManyPokemon:
	.string "Uh-oh, you've got too many POKéMON.\n"
	.string "You have no room for this one.$"

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature:
	.string "I'm trying to develop a new feature\n"
	.string "for the POKéNAV…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext:
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"

RustboroCity_DevonCorp_2F_Text_DontHaveThatFossil::
    .string "Hm... You don't seem to have any fossils.\n"
    .string "Come back if you find one.$"

RustboroCity_DevonCorp_2F_Text_WhichFossilWouldYouRegenerate::
    .string "Which fossil would you like me to\n"
    .string "regenerate?$"

RustboroCity_DevonCorp_2F_Text_PartyFull::
    .string "Your party is full.\nMake room and come back.$"

RustboroCity_DevonCorp_2F_Text_HeresYourPokemon::
    .string "All done!\nIt was successfully regenerated.$"
