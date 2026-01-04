// gym_leader_rematch.c
#include "global.h"
#include "random.h"
#include "event_data.h"
#include "battle_setup.h"
#include "gym_leader_rematch.h"
#include "constants/flags.h"
#include "constants/vars.h"

#if FREE_MATCH_CALL == FALSE
static bool8 UpdateGymLeaderRematchFromUnlockedMask(u16 unlockedMask, u32 maxRematch);
static s32 GetRematchIndex(u32 trainerIdx);
#endif

// Bit positions for each leader in VAR_GYM_REMATCH_UNLOCK_MASK
enum
{
    UNLOCK_ROXANNE = 0,
    UNLOCK_BRAWLY,
    UNLOCK_WATTSON,
    UNLOCK_FLANNERY,
    UNLOCK_NORMAN,
    UNLOCK_WINONA,
    UNLOCK_TATE_LIZA,
    UNLOCK_JUAN,
};

#define UNLOCK_BIT(x) (1 << (x))

// Map unlock-bit -> REMATCH_* id
static const u16 sUnlockBitToRematchId[] =
{
    [UNLOCK_ROXANNE] = REMATCH_ROXANNE,
    [UNLOCK_BRAWLY] = REMATCH_BRAWLY,
    [UNLOCK_WATTSON] = REMATCH_WATTSON,
    [UNLOCK_FLANNERY] = REMATCH_FLANNERY,
    [UNLOCK_NORMAN] = REMATCH_NORMAN,
    [UNLOCK_WINONA] = REMATCH_WINONA,
    [UNLOCK_TATE_LIZA] = REMATCH_TATE_AND_LIZA,
    [UNLOCK_JUAN] = REMATCH_JUAN,
};

static u8 GetBadgeCount(void)
{
    u8 count = 0;
    if (FlagGet(FLAG_BADGE01_GET)) count++;
    if (FlagGet(FLAG_BADGE02_GET)) count++;
    if (FlagGet(FLAG_BADGE03_GET)) count++;
    if (FlagGet(FLAG_BADGE04_GET)) count++;
    if (FlagGet(FLAG_BADGE05_GET)) count++;
    if (FlagGet(FLAG_BADGE06_GET)) count++;
    if (FlagGet(FLAG_BADGE07_GET)) count++;
    if (FlagGet(FLAG_BADGE08_GET)) count++;
    return count;
}

// Called inside UpdateGymLeaderRematch().
// When badges increase, unlock previous gym leader rematch.
// Juan unlocks immediately when badge 8 is obtained.
static u16 UpdateUnlockedRematchesFromBadges(void)
{
    u8 badgeCount = GetBadgeCount();
    u16 lastBadges = VarGet(VAR_GYM_REMATCH_LAST_BADGES);
    u16 mask = VarGet(VAR_GYM_REMATCH_UNLOCK_MASK);

    if (lastBadges == 0 && mask == 0 && badgeCount >= 2)
    {
        // Backfill unlocks based on current badge count (first-time init)
        u8 b;
        for (b = 2; b <= badgeCount; b++)
        {
            switch (b)
            {
            case 2: mask |= UNLOCK_BIT(UNLOCK_ROXANNE); break;
            case 3: mask |= UNLOCK_BIT(UNLOCK_BRAWLY); break;
            case 4: mask |= UNLOCK_BIT(UNLOCK_WATTSON); break;
            case 5: mask |= UNLOCK_BIT(UNLOCK_FLANNERY); break;
            case 6: mask |= UNLOCK_BIT(UNLOCK_NORMAN); break;
            case 7: mask |= UNLOCK_BIT(UNLOCK_WINONA); break;
            case 8: mask |= UNLOCK_BIT(UNLOCK_TATE_LIZA) | UNLOCK_BIT(UNLOCK_JUAN); break;
            }
        }
        VarSet(VAR_GYM_REMATCH_LAST_BADGES, badgeCount);
        VarSet(VAR_GYM_REMATCH_UNLOCK_MASK, mask);
        return mask;
    }

    if (badgeCount <= lastBadges)
        return mask;

    // Process each newly gained badge count one-by-one
    while (lastBadges < badgeCount)
    {
        lastBadges++;

        // "Beat next gym unlocks previous gym leader"
        // When lastBadges becomes 2..8, unlock leader for badge (lastBadges - 1)
        switch (lastBadges)
        {
        case 2: mask |= UNLOCK_BIT(UNLOCK_ROXANNE);   break; // after Brawly
        case 3: mask |= UNLOCK_BIT(UNLOCK_BRAWLY);    break; // after Wattson
        case 4: mask |= UNLOCK_BIT(UNLOCK_WATTSON);   break; // after Flannery
        case 5: mask |= UNLOCK_BIT(UNLOCK_FLANNERY);  break; // after Norman
        case 6: mask |= UNLOCK_BIT(UNLOCK_NORMAN);    break; // after Winona
        case 7: mask |= UNLOCK_BIT(UNLOCK_WINONA);    break; // after Tate & Liza
        case 8:
            mask |= UNLOCK_BIT(UNLOCK_TATE_LIZA);     // after Juan
            mask |= UNLOCK_BIT(UNLOCK_JUAN);          // Juan unlocks immediately
            break;
        default:
            break;
        }
    }

    VarSet(VAR_GYM_REMATCH_LAST_BADGES, badgeCount);
    VarSet(VAR_GYM_REMATCH_UNLOCK_MASK, mask);
    return mask;
}

void UpdateGymLeaderRematch(void)
{
#if FREE_MATCH_CALL == FALSE
    u16 unlockedMask;
    u32 maxRematch;

    // Update unlocks based on badge progression
    unlockedMask = UpdateUnlockedRematchesFromBadges();

    // ===== DEBUG: FORCE UNLOCKS =====
    unlockedMask = UNLOCK_BIT(UNLOCK_ROXANNE) | UNLOCK_BIT(UNLOCK_BRAWLY);
    // ===== END DEBUG =====

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
        maxRematch = 5;
    else
        maxRematch = 1;

    UpdateGymLeaderRematchFromUnlockedMask(unlockedMask, maxRematch);
#endif
}


#if FREE_MATCH_CALL == FALSE
static bool8 UpdateGymLeaderRematchFromUnlockedMask(u16 unlockedMask, u32 maxRematch)
{
    s32 whichLeader = 0;
    s32 lowestRematchIndex = 5;
    s32 rematchIndex;
    u32 bit;

    // Find the lowest rematch tier among unlocked leaders that aren't already queued
    for (bit = 0; bit < ARRAY_COUNT(sUnlockBitToRematchId); bit++)
    {
        u16 rematchId;

        if (!(unlockedMask & UNLOCK_BIT(bit)))
            continue;

        rematchId = sUnlockBitToRematchId[bit];

        if (gSaveBlock1Ptr->trainerRematches[rematchId])
            continue;

        rematchIndex = GetRematchIndex(rematchId);
        if (lowestRematchIndex > rematchIndex)
            lowestRematchIndex = rematchIndex;

        whichLeader++;
    }

    if (whichLeader == 0 || lowestRematchIndex > (s32)maxRematch)
        return FALSE;

    // Count leaders that share that lowest tier (so we choose uniformly among them)
    whichLeader = 0;
    for (bit = 0; bit < ARRAY_COUNT(sUnlockBitToRematchId); bit++)
    {
        u16 rematchId;

        if (!(unlockedMask & UNLOCK_BIT(bit)))
            continue;

        rematchId = sUnlockBitToRematchId[bit];

        if (gSaveBlock1Ptr->trainerRematches[rematchId])
            continue;

        rematchIndex = GetRematchIndex(rematchId);
        if (rematchIndex == lowestRematchIndex)
            whichLeader++;
    }

    if (whichLeader == 0)
        return FALSE;

    whichLeader = Random() % whichLeader;

    // Queue the chosen leader
    for (bit = 0; bit < ARRAY_COUNT(sUnlockBitToRematchId); bit++)
    {
        u16 rematchId;

        if (!(unlockedMask & UNLOCK_BIT(bit)))
            continue;

        rematchId = sUnlockBitToRematchId[bit];

        if (gSaveBlock1Ptr->trainerRematches[rematchId])
            continue;

        rematchIndex = GetRematchIndex(rematchId);
        if (rematchIndex == lowestRematchIndex)
        {
            if (whichLeader == 0)
            {
                gSaveBlock1Ptr->trainerRematches[rematchId] = lowestRematchIndex;
                return TRUE;
            }
            whichLeader--;
        }
    }

    return FALSE;
}

static s32 GetRematchIndex(u32 trainerIdx)
{
    s32 i;
    for (i = 0; i < 5; i++)
    {
        if (!HasTrainerBeenFought(gRematchTable[trainerIdx].trainerIds[i]))
            return i;
    }
    return 5;
}
#endif // FREE_MATCH_CALL
