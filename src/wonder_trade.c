#include "global.h"
#include "script.h"
#include "pokemon.h"
#include "random.h"
#include "string_util.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "event_data.h"

extern u16 gSpecialVar_0x8004;
extern u16 gSpecialVar_Result;

#define WONDER_OT_ID 0x57544F4EU
#define NAME_EOS 0xFF

static const u8 sWonderOtName[] = _("WONDER");

// 0 = success
// 1 = generic fail
// 2 = egg blocked

static bool8 IsValidLZ77Data(const void* ptr)
{
    const u8* p = (const u8*)ptr;
    return (p != NULL && p[0] == 0x10);
}

static bool8 IsAlreadyWonderTraded(struct Pokemon* mon)
{
    u32 otId = GetMonData(mon, MON_DATA_OT_ID);
    u8 otName[PLAYER_NAME_LENGTH + 1];

    if (otId == WONDER_OT_ID)
        return TRUE;

    GetMonData(mon, MON_DATA_OT_NAME, otName);
    // Compare in game encoding (since sWonderOtName is encoded)
    if (StringCompare(otName, sWonderOtName) == 0)
        return TRUE;

    return FALSE;
}

static bool8 IsBannedWonderTradeSpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_MEW:
    case SPECIES_KYOGRE:
    case SPECIES_GROUDON:
    case SPECIES_RAYQUAZA:
    case SPECIES_LATIAS:
    case SPECIES_LATIOS:
    case SPECIES_REGIROCK:
    case SPECIES_REGICE:
    case SPECIES_REGISTEEL:
    case SPECIES_JIRACHI:
    case SPECIES_DEOXYS:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool8 IsBannedMegaEvolutions(u16 species)
{
    switch (species)
    {
    case SPECIES_VENUSAUR_MEGA:
    case SPECIES_BLASTOISE_MEGA:
    case SPECIES_CHARIZARD_MEGA_X:
    case SPECIES_CHARIZARD_MEGA_Y:
    case SPECIES_BEEDRILL_MEGA:
    case SPECIES_PIDGEOT_MEGA:
    case SPECIES_SLOWBRO_MEGA:
    case SPECIES_ALAKAZAM_MEGA:
    case SPECIES_GENGAR_MEGA:
    case SPECIES_KANGASKHAN_MEGA:
    case SPECIES_PINSIR_MEGA:
    case SPECIES_GYARADOS_MEGA:
    case SPECIES_AERODACTYL_MEGA:
    case SPECIES_MEWTWO_MEGA_X:
    case SPECIES_MEWTWO_MEGA_Y:
    case SPECIES_AMPHAROS_MEGA:
    case SPECIES_STEELIX_MEGA:
    case SPECIES_SCIZOR_MEGA:
    case SPECIES_HERACROSS_MEGA:
    case SPECIES_HOUNDOOM_MEGA:
    case SPECIES_TYRANITAR_MEGA:
    case SPECIES_BLAZIKEN_MEGA:
    case SPECIES_SCEPTILE_MEGA:
    case SPECIES_SWAMPERT_MEGA:
    case SPECIES_MAWILE_MEGA:
    case SPECIES_AGGRON_MEGA:
    case SPECIES_MEDICHAM_MEGA:
    case SPECIES_MANECTRIC_MEGA:
    case SPECIES_BANETTE_MEGA:
    case SPECIES_ABSOL_MEGA:
    case SPECIES_SABLEYE_MEGA:
    case SPECIES_SHARPEDO_MEGA:
    case SPECIES_CAMERUPT_MEGA:
    case SPECIES_ALTARIA_MEGA:
    case SPECIES_GLALIE_MEGA:
    case SPECIES_SALAMENCE_MEGA:
    case SPECIES_METAGROSS_MEGA:
    case SPECIES_RAYQUAZA_MEGA:
    case SPECIES_LATIAS_MEGA:
    case SPECIES_LATIOS_MEGA:
    case SPECIES_GARCHOMP_MEGA:
    case SPECIES_LUCARIO_MEGA:
    case SPECIES_ABOMASNOW_MEGA:
    case SPECIES_LOPUNNY_MEGA:
    case SPECIES_GALLADE_MEGA:
    case SPECIES_AUDINO_MEGA:
    case SPECIES_DIANCIE_MEGA:
            return TRUE;
        default:
            return FALSE;
    }
}

static bool8 IsRecvMonBad(struct Pokemon* mon)
{
    u16 s = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);

    if (s == SPECIES_NONE || s == SPECIES_EGG)
        return TRUE;

#ifdef MON_DATA_SANITY_IS_EGG
    if (GetMonData(mon, MON_DATA_SANITY_IS_EGG))
        return TRUE;
#endif

#ifdef MON_DATA_SANITY_IS_BAD_EGG
    if (GetMonData(mon, MON_DATA_SANITY_IS_BAD_EGG))
        return TRUE;
#endif

    return FALSE;
}


static bool8 IsValidWonderTradeSpecies(u16 species)
{
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return FALSE;

#ifdef SPECIES_BAD_EGG
    if (species == SPECIES_BAD_EGG)
        return FALSE;
#endif

    if (IsBannedWonderTradeSpecies(species))
        return FALSE;

    if (IsBannedMegaEvolutions(species))
        return FALSE;

   // if (!IsSpeciesEnabled(species))
   //     return FALSE;

   //if (gSpeciesInfo[species].frontPicSize == 0)
   //     return FALSE;

    //if (!HasValidSpeciesGfx(species))
    //    return FALSE;

    // Extra safety: reject unimplemented species entries
    if (gSpeciesInfo[species].baseHP == 0
        && gSpeciesInfo[species].baseAttack == 0
        && gSpeciesInfo[species].baseDefense == 0
        && gSpeciesInfo[species].baseSpeed == 0
        && gSpeciesInfo[species].baseSpAttack == 0
        && gSpeciesInfo[species].baseSpDefense == 0)
        return FALSE;

    return TRUE;
}

// Rolls until it finds a species that is enabled + not banned + actually creates a non-egg/non-bad mon.
static u16 GetRandomSafeWonderTradeSpecies(u8 level)
{
    u32 tries;
    u16 species;
    struct Pokemon testMon;

    for (tries = 0; tries < 10000; tries++)
    {
        species = 1 + (Random() % (NUM_SPECIES - 1));

        if (!IsValidWonderTradeSpecies(species))
            continue;

        CreateMon(&testMon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_RANDOM_NO_SHINY, 0);

        if (IsRecvMonBad(&testMon))
            continue;

        return species;
    }

    return SPECIES_MAGIKARP;
}

void WonderTrade(void)
{
    u8 slot = (u8)gSpecialVar_0x8004;
    u8 partyCount = CalculatePlayerPartyCount();
    struct Pokemon* giveMon;
    struct Pokemon recvMon;
    u8 level;
    u16 species;
    u32 i;

    if (partyCount == 0 || slot >= partyCount)
    {
        gSpecialVar_Result = 1;
        return;
    }

    giveMon = &gPlayerParty[slot];

    // Block trading eggs
    if (GetMonData(giveMon, MON_DATA_SANITY_IS_EGG)
        || GetMonData(giveMon, MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
    {
        gSpecialVar_Result = 2;
        return;
    }

    // Block re-trading Wonder Trade Pokémon
    if (IsAlreadyWonderTraded(giveMon))
    {
        gSpecialVar_Result = 3;
        return;
    }

    level = (u8)GetMonData(giveMon, MON_DATA_LEVEL);
    if (level == 0)
    {
        gSpecialVar_Result = 1;
        return;
    }

    // Create a safe received mon (reroll a few times as a final guard)
    for (i = 0; i < 50; i++)
    {
        species = GetRandomSafeWonderTradeSpecies(level);
        CreateMon(&recvMon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PRESET, WONDER_OT_ID);




        if (!IsRecvMonBad(&recvMon))
            break;
    }

    if (IsRecvMonBad(&recvMon))
    {
        gSpecialVar_Result = 1;
        return;
    }

    gPlayerParty[slot] = recvMon;

    // OT name: "WONDER"
    {
        u32 otId = WONDER_OT_ID;
        u8 otGender = MALE;
        u16 metLoc = METLOC_WONDER_TRADE;
        u8 metLevel = level;

        SetMonData(&gPlayerParty[slot], MON_DATA_OT_ID, &otId);
        SetMonData(&gPlayerParty[slot], MON_DATA_OT_NAME, sWonderOtName);
        SetMonData(&gPlayerParty[slot], MON_DATA_OT_GENDER, &otGender);

        SetMonData(&gPlayerParty[slot], MON_DATA_MET_LOCATION, &metLoc);
        SetMonData(&gPlayerParty[slot], MON_DATA_MET_LEVEL, &metLevel);

        CalculateMonStats(&gPlayerParty[slot]);
    }


    CalculatePlayerPartyCount();
    gSpecialVar_Result = 0;
}

extern u16 gSpecialVar_0x8005;   // chosen party slot (matches CreateInGameTradePokemon usage)
extern u16 gSpecialVar_Result;

#define WONDER_OT_ID 0x57544F4EU

void Special_PrepareWonderTradeScene(void)
{
    u8 slot = (u8)gSpecialVar_0x8005;
    u8 partyCount = CalculatePlayerPartyCount();
    struct Pokemon* giveMon;
    struct Pokemon* recvMon = &gEnemyParty[0]; // this is what the trade scene uses
    u8 level;
    u16 species;
    u32 tries;

    gSpecialVar_Result = 1; // default fail

    if (partyCount == 0 || slot >= partyCount)
        return;

    // Force trade scene inputs (prevents stale values)
    gSpecialVar_0x8004 = INGAME_TRADE_WONDER; // which template
    gSpecialVar_0x8005 = slot;                // which player mon slot

    giveMon = &gPlayerParty[slot];

    // Block eggs
    if (GetMonData(giveMon, MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG
#ifdef MON_DATA_SANITY_IS_EGG
        || GetMonData(giveMon, MON_DATA_SANITY_IS_EGG)
#endif
        )
    {
        gSpecialVar_Result = 2;
        return;
    }

    // Block re-trading Wonder Trade Pokémon
    if (IsAlreadyWonderTraded(giveMon))
    {
        gSpecialVar_Result = 3;
        return;
    }

    level = (u8)GetMonData(giveMon, MON_DATA_LEVEL);
    if (level == 0)
        return;

    // Generate a safe received mon into gEnemyParty[0]
    for (tries = 0; tries < 50; tries++)
    {
        species = GetRandomSafeWonderTradeSpecies(level);
        CreateMon(recvMon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PRESET, WONDER_OT_ID);

        if (!IsRecvMonBad(recvMon))
            break;
    }

    if (IsRecvMonBad(recvMon))
        return;

    // Stamp Wonder Trade identity + met data onto the received mon
    {
        u32 otId = WONDER_OT_ID;
        u8 otGender = MALE;
        metloc_u8_t metLocation =
#ifdef METLOC_WONDER_TRADE
            METLOC_WONDER_TRADE;
#else
            METLOC_IN_GAME_TRADE;
#endif
        u8 metLevel = level;

        SetMonData(recvMon, MON_DATA_OT_ID, &otId);
        SetMonData(recvMon, MON_DATA_OT_NAME, sWonderOtName);
        SetMonData(recvMon, MON_DATA_OT_GENDER, &otGender);
        SetMonData(recvMon, MON_DATA_MET_LOCATION, &metLocation);
        SetMonData(recvMon, MON_DATA_MET_LEVEL, &metLevel);

        CalculateMonStats(recvMon);
    }

    gSpecialVar_Result = 0; // success
}


