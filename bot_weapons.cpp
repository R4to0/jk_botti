//
// JK_Botti - be more human!
//
// bot_weapons.cpp
//

#include <string.h>

#include <extdll.h>
#include <dllapi.h>
#include <h_export.h>
#include <meta_api.h>

#include "bot.h"
#include "bot_func.h"
#include "bot_weapons.h"
#include "bot_skill.h"
#include "bot_weapon_select.h"

extern bot_weapon_t weapon_defs[MAX_WEAPONS];
extern int submod_id;

// weapons are stored in priority order, most desired weapon should be at
// the start of the array and least desired should be at the end

bot_weapon_select_t valve_weapon_select[13] = 
{
   {VALVE_WEAPON_CROWBAR, "weapon_crowbar", WEAPON_MELEE, 1.0,
    SKILL4, NOSKILL, FALSE, FALSE,
    0.0, 64.0, 0, 0, 1.0,
    20, TRUE, 100, 0, 0, TRUE, FALSE, FALSE, FALSE, 0.0, 0.0, FALSE, -1, -1,
    W_IFL_CROWBAR, 0, 0 },

   {VALVE_WEAPON_HANDGRENADE, "weapon_handgrenade", WEAPON_THROW, 1.0,
    SKILL4, NOSKILL, TRUE, FALSE,
    300.0, 800.0, 0.0, 0.0, 300.0,
    10, TRUE, 100, 1, 0, FALSE, FALSE, FALSE, FALSE, 0.0, 0.0, TRUE, -1, -1,
    W_IFL_HANDGRENADE, 0, 0 },

   {VALVE_WEAPON_SNARK, "weapon_snark", WEAPON_THROW, 1.0,
    SKILL3, NOSKILL, FALSE, FALSE,
    200.0, 800.0, 0, 0, 300.0,
    20, FALSE, 100, 1, 0, FALSE, FALSE, FALSE, FALSE, 0.0, 0.0, FALSE, -1, -1,
    W_IFL_SNARK, 0, 0 },

   {VALVE_WEAPON_EGON, "weapon_egon", WEAPON_FIRE, 1.0,
    SKILL3, NOSKILL, FALSE, FALSE,
    200.0, 2000.0, 0, 0, 350.0,
    50, FALSE, 100, 1, 0, TRUE, FALSE, FALSE, FALSE, 0.0, 0.0, FALSE, 20, -1,
    W_IFL_EGON, W_IFL_AMMO_GAUSS, 0 },

   {VALVE_WEAPON_GAUSS, "weapon_gauss", WEAPON_FIRE, 1.0,
    SKILL4, SKILL2, FALSE, TRUE,
    100.0, 500.0, 50.0, 3000.0, 500.0,
    20, FALSE, 80, 1, 10, TRUE, FALSE, FALSE, TRUE, 0.0, 0.8, TRUE, 30, 30,
    W_IFL_GAUSS, W_IFL_AMMO_GAUSS, 0 },

   {VALVE_WEAPON_SHOTGUN, "weapon_shotgun", WEAPON_FIRE, 1.0,
    SKILL5, SKILL3, FALSE, TRUE,
    400.0, 1500.0, 50.0, 800.0, 400.0,
    55, FALSE, 70, 1, 2, TRUE, FALSE, FALSE, FALSE, 0.0, 0.0, TRUE, 12, 12,
    W_IFL_SHOTGUN, W_IFL_AMMO_BUCKSHOT, 0 },

   {VALVE_WEAPON_PYTHON, "weapon_357", WEAPON_FIRE, 1.0,
    SKILL3, NOSKILL, FALSE, FALSE,
    50.0, 4000, 0, 0, 750.0,
    15, FALSE, 100, 1, 0, FALSE, FALSE, FALSE, FALSE, 0.0, 0.0, TRUE, 12, 12,
    W_IFL_PYTHON, W_IFL_AMMO_357, 0 },

   {VALVE_WEAPON_HORNETGUN, "weapon_hornetgun", WEAPON_FIRE, 1.0,
    SKILL4, SKILL3, FALSE, FALSE,
    200.0, 1500.0, 50.0, 250.0, 300.0,
    10, TRUE, 50, 1, 4, TRUE, TRUE, FALSE, FALSE, 0.0, 0.0, TRUE, -1, -1,
    W_IFL_HORNETGUN, 0, 0 },

   {VALVE_WEAPON_MP5, "weapon_9mmAR", WEAPON_FIRE, 0.8,
    SKILL5, SKILL3, FALSE, FALSE,
    50.0, 2000.0, 300.0, 700.0, 600.0,
    45, FALSE, 70, 1, 1, TRUE, FALSE, FALSE, FALSE, 0.0, 0.0, FALSE, 50, 2,
    W_IFL_MP5, W_IFL_AMMO_9MM, 0 },

   {VALVE_WEAPON_CROSSBOW, "weapon_crossbow", WEAPON_FIRE_ZOOM, 1.0,
    SKILL2, NOSKILL, FALSE, FALSE,
    800.0, 4000.0, 0, 0, 1000.0,
    55, TRUE, 100, 1, 0, FALSE, FALSE, FALSE, FALSE, 0.0, 0.0, TRUE, 5, -1,
    W_IFL_CROSSBOW, W_IFL_AMMO_CROSSBOW, 0 },
   
   {VALVE_WEAPON_RPG, "weapon_rpg", WEAPON_FIRE, 1.0,
    SKILL3, NOSKILL, FALSE, FALSE,
    400.0, 5000.0, 0.0, 0.0, 700.0,
    60, TRUE, 100, 1, 0, FALSE, FALSE, FALSE, FALSE, 0.0, 0.0, FALSE, 2, -1,
    W_IFL_RPG, W_IFL_AMMO_RPG, 0 },
    
   {VALVE_WEAPON_GLOCK, "weapon_9mmhandgun", WEAPON_FIRE, 1.0,
    SKILL5, SKILL3, TRUE, TRUE,
    250.0, 1500.0, 50.0, 300.0, 300.0,
    20, TRUE, 70, 1, 1, TRUE, TRUE, FALSE, FALSE, 0.0, 0.0, TRUE, 30, -1,
    W_IFL_GLOCK, W_IFL_AMMO_9MM, 0 },
    
   /* terminator */   
   {0, "", 0, 0.0,
    NOSKILL, NOSKILL, FALSE, FALSE, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0, FALSE, 0, 1, 1, FALSE, FALSE, FALSE, FALSE, 0.0, 0.0, FALSE, 0, 0, 
    0, 0, 0 },
};

// List of different ammo we are looking for
bot_ammo_names_t ammo_names[] = {
   { W_IFL_AMMO_GAUSS     , "ammo_gaussclip" },
   { W_IFL_AMMO_BUCKSHOT  , "ammo_buckshot" },
   { W_IFL_AMMO_357       , "ammo_357" },
   { W_IFL_AMMO_9MM       , "ammo_9mmclip" },
   { W_IFL_AMMO_9MM       , "ammo_9mmAR" },
   { W_IFL_AMMO_ARGRENADES, "ammo_ARgrenades" },
   { W_IFL_AMMO_CROSSBOW  , "ammo_crossbow" },
   { W_IFL_AMMO_RPG       , "ammo_rpgclip" },
   { 0, "" },
};

// weapon firing delay based on skill (min and max delay for each weapon)
// THESE MUST MATCH THE SAME ORDER AS THE WEAPON SELECT ARRAY!!!

bot_fire_delay_t valve_fire_delay[13] = {
   {VALVE_WEAPON_CROWBAR,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_HANDGRENADE,
    0.5, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_SNARK,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_EGON,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_GAUSS,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_SHOTGUN,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_PYTHON,
    0.8, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_HORNETGUN,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_MP5,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    1.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
  {VALVE_WEAPON_CROSSBOW,
    0.05, {0.05, 0.1, 0.2, 0.0, 0.0}, {0.05, 0.1, 0.2, 0.0, 0.0},
    0.1, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_RPG,
    1.5, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.5, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   {VALVE_WEAPON_GLOCK,
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
    0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}},
   /* terminator */
   {0, 0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0},
       0.0, {0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0}}
};

bot_fire_delay_t fire_delay[13];
bot_weapon_select_t weapon_select[13];


//
void InitWeaponSelect(int submod_id)
{
   memcpy(fire_delay, valve_fire_delay, sizeof(fire_delay));
   memcpy(weapon_select, valve_weapon_select, sizeof(weapon_select));
   
   if(SUBMOD_SEVS == submod_id)
   {
      bot_weapon_select_t * shotgun = GetWeaponSelect(VALVE_WEAPON_SHOTGUN);
      
      if(!shotgun)
         return;
      
      shotgun->primary_fire_percent = 25;
   }
   else if(SUBMOD_BUBBLEMOD == submod_id)
   {
      // bubblemod specialities (?)
   }
   else if(SUBMOD_XDM == submod_id)
   {
      // xdm specialities (?)
   }
}


//
bot_weapon_select_t * GetWeaponSelect(int id)
{
   bot_weapon_select_t * pSelect = weapon_select;
   
   do {
      if(pSelect->iId == id)
         return(pSelect);
   } while((++pSelect)->iId);
   
   return(NULL);
}


// find weapon item flag
int GetWeaponItemFlag(const char * classname)
{
   bot_weapon_select_t *pSelect = &weapon_select[0];
   int itemflag = 0;
      
   while(pSelect->iId)
   {
      if(strcmp(classname, pSelect->weapon_name) == 0)
      {
         itemflag = pSelect->waypoint_flag;
         break;
      }
         
      pSelect++;
   }
   
   return(itemflag);
}

// find ammo itemflag
int GetAmmoItemFlag(const char * classname)
{
   bot_ammo_names_t *pAmmo = &ammo_names[0];
   int itemflag = 0;
   
   while(pAmmo->waypoint_flag)
   {
      if(strcmp(classname, pAmmo->ammoName) == 0)
      {
         itemflag = pAmmo->waypoint_flag;
         break;
      }
      pAmmo++;
   }
   
   return(itemflag);
}

//
qboolean BotCanUseWeapon(bot_t &pBot, const bot_weapon_select_t &select)
{
   return((pBot.bot_skill + 1) <= select.primary_skill_level || (pBot.bot_skill + 1) <= select.secondary_skill_level);
}

//
void BotSelectAttack(bot_t &pBot, const bot_weapon_select_t &select, qboolean &use_primary, qboolean &use_secondary) 
{
   use_secondary = FALSE;
   use_primary = FALSE;
   
   // if better attack is preferred
   // and bot_skill is equal or lesser than attack skill on both attacks
   if(select.prefer_higher_skill_attack && 
      (pBot.bot_skill + 1) <= select.secondary_skill_level && 
      (pBot.bot_skill + 1) <= select.primary_skill_level)
   {
      // check which one is prefered
      if(select.secondary_skill_level < select.primary_skill_level)
         use_secondary = TRUE;
      else
         use_primary = TRUE;
   }
   else
   {
      // use old method last
      if(RANDOM_LONG2(1, 100) <= select.primary_fire_percent) 
         use_primary = TRUE;
      else
         use_secondary = TRUE;
   }
}

// 
qboolean IsValidToFireAtTheMoment(bot_t &pBot, const bot_weapon_select_t &select) 
{
   // is the bot NOT carrying this weapon?
   if (!(pBot.pEdict->v.weapons & (1<<select.iId)))
      return(FALSE);

   // underwater and cannot use underwater
   if (pBot.pEdict->v.waterlevel == 3 && !select.can_use_underwater)
      return(FALSE);
   
   return(TRUE);
}

//
qboolean IsValidWeaponChoose(bot_t &pBot, const bot_weapon_select_t &select) 
{
   // iId == 0 is null terminator, don't allow
   if(select.iId == 0 || select.weapon_name[0] == 0)
      return(FALSE);
   
   // Severians and Bubblemod checks, skip egon (bubblemod-egon is total conversion and severians-egon is selfkilling after time)
   if (select.iId == VALVE_WEAPON_EGON)
   {
      if(submod_id == SUBMOD_SEVS)
         return(FALSE);
      
      if(submod_id == SUBMOD_BUBBLEMOD && CVAR_GET_FLOAT("bm_gluon_mod") > 0)
         return(FALSE);
   }
      
   return(TRUE);
}

//
qboolean IsValidPrimaryAttack(bot_t &pBot, const bot_weapon_select_t &select, const float distance, const float height, const qboolean always_in_range)
{
   int weapon_index = select.iId;
   qboolean primary_in_range;
      
   primary_in_range = (always_in_range) || (distance >= select.primary_min_distance && distance <= select.primary_max_distance);

   // no ammo required for this weapon OR
   // enough ammo available to fire AND
   // the bot is far enough away to use primary fire AND
   // the bot is close enough to the enemy to use primary fire
   return (primary_in_range && (weapon_defs[weapon_index].iAmmo1 == -1 || pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo1] >= select.min_primary_ammo));
}

//
qboolean IsValidSecondaryAttack(bot_t &pBot, const bot_weapon_select_t &select, const float distance, const float height, const qboolean always_in_range)
{
   int weapon_index = select.iId;
   qboolean secondary_valid = FALSE;
   qboolean secondary_in_range;
   
   // target is close enough
   secondary_in_range = (always_in_range) || (distance >= select.secondary_min_distance && distance <= select.secondary_max_distance);

   // see if there is enough secondary ammo AND
   // the bot is far enough away to use secondary fire AND
   // the bot is close enough to the enemy to use secondary fire
   if (secondary_in_range && 
       ((weapon_defs[weapon_index].iAmmo2 == -1 && !select.secondary_use_primary_ammo) ||
         (pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo2] >= select.min_secondary_ammo) ||
         (select.secondary_use_primary_ammo && 
          (weapon_defs[weapon_index].iAmmo1 == -1 || pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo1] >= select.min_primary_ammo))))
   {
      secondary_valid = TRUE;
      
      // MP5 cannot use secondary if primary is empty
      if(weapon_index == VALVE_WEAPON_MP5 &&
         (pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo1] <
          select.min_primary_ammo))
      {
         secondary_valid = FALSE;
      }
      else if(weapon_index == VALVE_WEAPON_MP5 && distance != 0.0 && height != 0.0)
      {
         // check if can get valid launch angle for mp2 grenade
         float angle = ValveWeaponMP5_GetBestLaunchAngleByDistanceAndHeight(distance, height);
         
         if(angle > 89.0 || angle < -89.0)
            secondary_valid = FALSE;
      }
   }
   
   return(secondary_valid);
}

//
qboolean BotGetGoodWeaponCount(bot_t &pBot, const int stop_count)
{
   bot_weapon_select_t * pSelect = &weapon_select[0];
   int select_index;
   int good_count = 0;
   
   // loop through all the weapons until terminator is found...
   select_index = -1;
   while (pSelect[++select_index].iId) {
      if(!IsValidWeaponChoose(pBot, pSelect[select_index]))
         continue;
      
      if(pSelect[select_index].avoid_this_gun || pSelect[select_index].type != WEAPON_FIRE)
         continue;
      
      // don't do distance check, check if enough ammo
      if(!IsValidSecondaryAttack(pBot, pSelect[select_index], 0.0, 0.0, TRUE) &&
         !IsValidPrimaryAttack(pBot, pSelect[select_index], 0.0, 0.0, TRUE))
         continue;
      
      // not bad gun
      if(++good_count == stop_count)
         return(good_count);
   }
   
   return(good_count);
}

//
ammo_low_t BotPrimaryAmmoLow(bot_t &pBot, const bot_weapon_select_t &select)
{
   int weapon_index = select.iId;
   
   // this weapon doesn't use ammo
   if(weapon_defs[weapon_index].iAmmo1 == -1 || select.low_ammo_primary == -1)
      return(AMMO_NO);
   
   if(pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo1] <= select.low_ammo_primary)
      return(AMMO_LOW);
   
   return(AMMO_OK);      
}

//
ammo_low_t BotSecondaryAmmoLow(bot_t &pBot, const bot_weapon_select_t &select)
{
   int weapon_index = select.iId;
   
   if(select.low_ammo_secondary == -1)
      return(AMMO_NO);
   
   if(select.secondary_use_primary_ammo)
   {
      // this weapon doesn't use ammo
      if(weapon_defs[weapon_index].iAmmo2 == -1)
         return(AMMO_NO);
   
      if(pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo2] <= select.low_ammo_secondary)
         return(AMMO_LOW);
   }
   else
   {
      // this weapon doesn't use ammo
      if(weapon_defs[weapon_index].iAmmo1 == -1)
         return(AMMO_NO);
   
      if(pBot.m_rgAmmo[weapon_defs[weapon_index].iAmmo1] <= select.low_ammo_secondary)
         return(AMMO_LOW);
   }
   
   return(AMMO_OK);
}

//
int BotGetLowAmmoFlags(bot_t &pBot)
{
   bot_weapon_select_t * pSelect = &weapon_select[0];
   int select_index;
   int ammoflags = 0;
   
   // loop through all the weapons until terminator is found...
   select_index = -1;
   while (pSelect[++select_index].iId) {
      if(!IsValidWeaponChoose(pBot, pSelect[select_index]))
         continue;
      
      // low primary ammo?
      if(BotPrimaryAmmoLow(pBot, pSelect[select_index]) == AMMO_LOW)
      {
         ammoflags |= pSelect[select_index].ammo1_waypoint_flag;
      }
      
      // low secondary ammo?
      if(BotSecondaryAmmoLow(pBot, pSelect[select_index]) == AMMO_LOW)
      {
         ammoflags |= pSelect[select_index].ammo2_waypoint_flag;
      }
   }
   
   return(ammoflags);
}

//
qboolean BotAllWeaponsRunningOutOfAmmo(bot_t &pBot)
{
   bot_weapon_select_t * pSelect = &weapon_select[0];
   int select_index;
   
   // loop through all the weapons until terminator is found...
   select_index = -1;
   while (pSelect[++select_index].iId) {
      if(!IsValidWeaponChoose(pBot, pSelect[select_index]))
         continue;
      
      // don't do distance check, not enough ammo --> running out of ammo
      if(!IsValidSecondaryAttack(pBot, pSelect[select_index], 0.0, 0.0, TRUE) &&
         !IsValidPrimaryAttack(pBot, pSelect[select_index], 0.0, 0.0, TRUE))
         continue;
      
      // low primary ammo? continue
      if(BotPrimaryAmmoLow(pBot, pSelect[select_index]) != AMMO_OK)
         continue;
      
      // low secondary ammo? continue
      if(BotSecondaryAmmoLow(pBot, pSelect[select_index]) != AMMO_OK)
         continue;
      
      // this gun had enough ammo
      return(FALSE);
   }
   
   return(TRUE);
}

// Check if want to change to better weapon
int BotGetBetterWeaponChoice(bot_t &pBot, const bot_weapon_select_t &current, const bot_weapon_select_t *pSelect, const float distance, const float height, qboolean *use_primary, qboolean *use_secondary) {
   int select_index;
   *use_primary = FALSE;
   *use_secondary = FALSE;
   
   // check if we don't like current weapon.
   if(!current.avoid_this_gun)
      return -1;
        
   // loop through all the weapons until terminator is found...
   select_index = -1;
   while (pSelect[++select_index].iId) 
   {
      if(!IsValidToFireAtTheMoment(pBot, pSelect[select_index]))
         continue;

      if(!IsValidWeaponChoose(pBot, pSelect[select_index]))
         continue;
      
      if(pSelect[select_index].avoid_this_gun)
         continue;

      *use_primary = IsValidPrimaryAttack(pBot, pSelect[select_index], distance, height, FALSE);
      *use_secondary = IsValidSecondaryAttack(pBot, pSelect[select_index], distance, height, FALSE);
      
      if(*use_primary || *use_secondary)
         return select_index;
   }
   
   return -1;
}

typedef struct {
   float angles[7]; //angles for distances: 300, 400, 500, 700, 1000, 1400, 2000 (2000 is all -99)
} mp5_grenade_angles_distance_t;

typedef struct {
   float height;
   mp5_grenade_angles_distance_t distance;
} mp5_grenades_angles_t;

// -99 means not possible
mp5_grenades_angles_t mp5_grenade_angles[] = {
   { 9999.0, {300, 400, 500, 700, 1000, 1400, 2000 }}, // distances

   { 800.0, {   -99,  -99,  -99,   -99,   -99,   -99, -99 }},   
   { 600.0, {   -99,  -99,  -99, -67.4,   -59,   -99, -99 }}, // upwards
   { 400.0, {   -99,  -88,  -60,   -50,   -44,   -99, -99 }},
   { 200.0, {   -47,  -36,  -32,   -29,   -32,   -45, -99 }},
   { 100.0, { -24.9,  -22,  -21,   -22,   -26,   -37, -99 }},
   {   0.0, {    -5, -7.5, -8.5, -12.5, -19.0, -29.6, -99 }}, // same eye level
   {   -30, {   0.5, -3.1, -5.5, -10.8, -19.3,   -32, -99 }}, //ground level when ducking
   {   -64, {   7.5,  2.8, -1.2,  -7.4, -16.4, -27.7, -99 }}, //ground level when standing
   {  -150, {  24.6,   15,  7.4,   0.8,  -8.9, -23.3, -99 }},
   {  -300, {    89, 43.9, 30.6,  16.2,   1.8, -12.6, -99 }},
   {  -500, {    89,   89,  89,   38.3,  15.3,  -1.4, -99 }},
   {  -800, {    89,   89,  89,     89,  44.2,  18.9, -99 }},
   { -1000, {    89,   89,  89,     89,    89,    89, -99 }},
   { -1800, {    89,   89,  89,     89,    89,    89, -99 }},
   	
   { -9999, {   -99,  -99, -99,    -99,   -99,   -99, -99 }}, //null term(null?)
};

// neg height means downwards and positive upwards
float ValveWeaponMP5_GetBestLaunchAngleByDistanceAndHeight(float distance, float height)
{
   int i, height_idx, dis_idx;
   float * distances = &mp5_grenade_angles[0].distance.angles[0];
   
   // get index in which between out height is
   height_idx = 0;
   for(i = 1; mp5_grenade_angles[i].height > -9999.0; i++)
   {
      if(height > mp5_grenade_angles[i].height && i == 1)
         return(-99); // too much height
      
      // not first index and now we get greater height --> found our candidate (yay)
      if(height > mp5_grenade_angles[i].height)
      {
         height_idx = i;
         break;
      }
   }
   
   if(height_idx == 0)
      return(-99); // didn't find match
   
   // get index in which between out distance is
   dis_idx = -1;
   for(i = 0; i < 7; i++)
   {
      if(distance < distances[i] && i == 0)
         return(-99); // too close
      
      // not first index and now we get greater height --> found our candidate (yay)
      if(distance < distances[i])
      {
         dis_idx = i;
         break;
      }
   }
   
   if(dis_idx == -1)
      return(-99); // too far
   
   // get weighted medium of both distance, dis_idx - 1, dis_idx
   float dis1_diff = fabs(distances[dis_idx - 1] - distance);
   float dis2_diff = fabs(distances[dis_idx] - distance);
   float total_diff = dis1_diff + dis2_diff;
   
   // height_idx - 1
   float angle_1 = (dis1_diff/total_diff) * mp5_grenade_angles[height_idx - 1].distance.angles[dis_idx - 1] + 
                   (dis2_diff/total_diff) * mp5_grenade_angles[height_idx - 1].distance.angles[dis_idx];   
   // height_idx
   float angle_2 = (dis1_diff/total_diff) * mp5_grenade_angles[height_idx].distance.angles[dis_idx - 1] + 
                   (dis2_diff/total_diff) * mp5_grenade_angles[height_idx].distance.angles[dis_idx]; 
   
   // get weighted medium of both height, height_idx - 1, height_idx
   float height1_diff = fabs(mp5_grenade_angles[height_idx - 1].height - height);
   float height2_diff = fabs(mp5_grenade_angles[height_idx].height - height);
   total_diff = height1_diff + height2_diff;
   
   float launch_angle = (height1_diff/total_diff) * angle_1 + (height2_diff/total_diff) * angle_2;
   
   return(launch_angle);
}































