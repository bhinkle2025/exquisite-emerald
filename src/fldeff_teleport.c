#include "global.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fldeff.h"
#include "follower_npc.h"
#include "party_menu.h"
#include "overworld.h"
#include "task.h"
#include "constants/field_effects.h"
#include "constants/moves.h"

static void FieldCallback_Teleport(void);
static void StartTeleportFieldEffect(void);

static bool32 MonIsEligibleForFieldMove(struct Pokemon* mon, u16 move)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    if (species == SPECIES_NONE)
        return FALSE;
    if (GetMonData(mon, MON_DATA_IS_EGG))
        return FALSE;

    // Eligible if it knows it OR could be taught it (teachable learnset)
    return MonKnowsMove(mon, move) || CanLearnTeachableMove(species, move);
}

bool32 SetUpFieldMove_Teleport(void)
{
    struct Pokemon* mon = &gPlayerParty[GetCursorSelectionMonId()];

    if (!CheckFollowerNPCFlag(FOLLOWER_NPC_FLAG_CAN_LEAVE_ROUTE))
        return FALSE;

    if (Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) != TRUE)
        return FALSE;

    // NEW: must know it OR be capable of learning it
    if (!MonIsEligibleForFieldMove(mon, MOVE_TELEPORT))
        return FALSE;

    gFieldCallback2 = FieldCallback_PrepareFadeInForTeleport;
    gPostMenuFieldCallback = FieldCallback_Teleport;
    return TRUE;
}


static void FieldCallback_Teleport(void)
{
    Overworld_ResetStateAfterTeleport();
    FieldEffectStart(FLDEFF_USE_TELEPORT);
    gFieldEffectArguments[0] = (u32)GetCursorSelectionMonId();
}

bool8 FldEff_UseTeleport(void)
{
    u8 taskId = CreateFieldMoveTask();
    gTasks[taskId].data[8] = (u32)StartTeleportFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartTeleportFieldEffect;
    SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
    return FALSE;
}

static void StartTeleportFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_TELEPORT);
    FldEff_TeleportWarpOut();
}
