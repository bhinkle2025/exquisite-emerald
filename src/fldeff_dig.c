#include "global.h"
#include "braille_puzzles.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fldeff.h"
#include "item_use.h"
#include "overworld.h"
#include "party_menu.h"
#include "script.h"
#include "sprite.h"
#include "constants/field_effects.h"
#include "item.h"

// static functions
static void FieldCallback_Dig(void);
static void StartDigFieldEffect(void);

// text
bool32 SetUpFieldMove_Dig(void)
{
    struct Pokemon* mon = &gPlayerParty[GetCursorSelectionMonId()];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    bool32 knowsDig = MonKnowsMove(mon, MOVE_DIG);

    // Safety (cheap, correct, future-proof)
    if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
        return FALSE;

    // 1) Map restriction (DO NOT REMOVE)
    if (!CanUseDigOrEscapeRopeOnCurMap())
        return FALSE;

    // 2) Eligible if knows OR can learn
    if (!knowsDig && !CanLearnTeachableMove(species, MOVE_DIG))
        return FALSE;

    // 3) TM required only if not already known
    if (!knowsDig && !CheckBagHasItem(ITEM_TM_DIG, 1))
        return FALSE;

    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = FieldCallback_Dig;
    return TRUE;
}



static void FieldCallback_Dig(void)
{
    Overworld_ResetStateAfterDigEscRope();
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext_SetupScript(EventScript_UseDig);
}

bool8 FldEff_UseDig(void)
{
    u8 taskId = CreateFieldMoveTask();

    gTasks[taskId].data[8] = (u32)StartDigFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartDigFieldEffect;
    if (!ShouldDoBrailleDigEffect())
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
    return FALSE;
}

static void StartDigFieldEffect(void)
{
    u8 taskId;

    FieldEffectActiveListRemove(FLDEFF_USE_DIG);
    if (ShouldDoBrailleDigEffect())
    {
        // EventScript_DigSealedChamber handles DoBrailleDigEffect call
        ScriptContext_Enable();
    }
    else
    {
        taskId = CreateTask(Task_UseDigEscapeRopeOnField, 8);
        gTasks[taskId].data[0] = 0;
    }
}
