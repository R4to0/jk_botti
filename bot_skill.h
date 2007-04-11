//
// JK_Botti - be more human!
//
// bot_skill.h
//

typedef struct
{
   int pause_frequency; // how often (out of 1000 times) the bot will pause, based on bot skill
   float pause_time[2]; // how long bot pauses (min, max)
   
   float normal_strafe; // how much bot straifes when walking around
   float battle_strafe; // how much bot straifes when attacking enemy
   
   int keep_optimal_distance; // how often bot (out of 1000 times) the bot try to keep at optimum distance of weapon when attacking
   
   float react_delay_min[3]; // reaction delay settings (first is for bot_reaction 1, second for 2, etc)
   float react_delay_max[3]; 
   
   float weaponchange_rate[2]; // how fast changing weapons (min, max)
   
   float shootcone_diameter; // bot tries to fire when aim line is less than [diameter / 2] apart from target 
   float shootcone_minangle; // OR angle between bot aim line and line to target is less than angle set here
      
   // Bot doesn't use real origin of target player but instead use data from earlier
   // and does latency prediction based on this data to get player origin. These settings
   // specify ammount of latency used at this skill level.
   float prediction_latency;
   float turn_skill; // BotAim turn_skill, how good bot is at aiming on enemy origin.
   float prediction_velocity_varitation;
   
   float hearing_sensitivity; // how well bot hears sounds
   
   qboolean can_longjump; // and can longjump.
   
   int random_jump_frequency; // how often (out of 100 times) the bot will do random jump
   int random_jump_duck_frequency; // how often (out of 100 times) the bot will do random duck when random jumping
   int random_duck_frequency; // how often (out of 100 times) the bot will do random duck jumping in combat mode
   int random_longjump_frequency; // how often (out of 100 times) the bot will do random longjump instead of random jump
   
   qboolean can_taujump; // can tau jump? (waypoint taujump, attack/flee taujump)
   
   int attack_taujump_frequency; // how often (out of 100 times) the bot will do tau jump at far away enemy
   int flee_taujump_frequency; // how often (out of 100 times) the bot will taujump away from enemy
   
   float attack_taujump_distance; // how far enemy have to be to bot to use tau jump
   float flee_taujump_distance; // max distance to flee enemy from
   float flee_taujump_health; // how much bot has health left when tries to escape
   float flee_taujump_escape_distance; // how long way bot tries to move away
   
   qboolean can_shoot_through_walls; // can shoot through walls by sound
   int wallshoot_frequency; // how often (out of 100 times) the bot will try attack enemy behind wall
   
} bot_skill_settings_t;

#ifdef BOTSKILL
bot_skill_settings_t default_skill_settings[5] = {
   // best skill (lvl1)
   { 5, {0.10, 0.25}, 10.0, 50.0, 999, 
     {0.01, 0.07, 0.10}, {0.04, 0.11, 0.15}, 
     {0.1, 0.3},
     150.0, 10.0, 0.100, 5.0, 0.025,
     4.0, TRUE, 50, 75, 50, 100,
     TRUE, 100, 100, 1000.0, 400.0, 20.0, 1000.0,
     TRUE, 99 },
   // lvl2
   { 15, {0.25, 0.5}, 8.0, 30.0, 800,
     {0.02, 0.09, 0.12}, {0.06, 0.14, 0.18},
     {0.2, 0.5},
     175.0, 20.0, 0.200, 3.0, 0.05,
     3.0, TRUE, 35, 60, 35, 90,
     TRUE, 50, 50, 1000.0, 400.0, 10.0, 1000.0,
     TRUE, 66 },
   // lvl3
   { 50, {0.50, 0.75}, 6.0, 15.0, 600,
     {0.03, 0.12, 0.15}, {0.08, 0.18, 0.22},
     {0.3, 0.7},
     200.0, 25.0, 0.300, 2.0, 0.075,
     2.0, TRUE, 20, 40, 20, 70,
     TRUE, 20, 20, 1000.0, 400.0, 10.0, 1000.0,
     TRUE, 33 },
   // lvl4
   { 100, {1.0, 1.5}, 4.0, 5.0, 400,
     {0.04, 0.14, 0.18}, {0.10, 0.21, 0.25},
     {0.6, 1.4},
     250.0, 30.0, 0.400, 1.5, 0.1,
     1.0, TRUE, 10, 25, 10, 40,
     TRUE, 0, 0, 0.0, 0.0, 0.0, 0.0,
     FALSE, 0 },
   // worst skill (lvl5)
   { 200, {1.5, 2.5}, 0.5, 1.0, 200,
     {0.05, 0.17, 0.21}, {0.12, 0.25, 0.30},
     {1.2, 2.8},
     300.0, 35.0, 0.500, 1.0, 0.15,
     0.5, FALSE, 5, 15, 5, 0,
     FALSE, 0, 0, 0.0, 0.0, 0.0, 0.0,
     FALSE, 0 },
};

bot_skill_settings_t skill_settings[5];

#else
extern bot_skill_settings_t skill_settings[5];

void ResetSkillsToDefault(void);
#endif