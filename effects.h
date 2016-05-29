#ifndef EFFECTS_H
#define EFFECTS_H

#include "commonIncludes.h"
#include "effectsProperties.h"
#include "AnalysisLogs.h"

class effectsProperties;

class basic_effect
{
public:
basic_effect();
virtual ~basic_effect();
wxString ID;
wxString Name;
bool disabled;
bool temporary;
bool externalContinueCycle;
unsigned damageType;
unsigned initRank;
virtual void Init();
virtual void Continue();
virtual void DoDoubleAttack();
virtual void FillPropertiesGrid(effectsProperties *);
virtual double *checkDamageType(); //Function that returns address for a pointer;
virtual basic_effect *getnewCopy(); //Make new object of this class and return its address.
};

// ___ Defense effects
class effect_stats_bonus_defender : public basic_effect
{
public:
    int statbonus;
    wxString statbonusString;
    effect_stats_bonus_defender();
    unsigned mainStat;
    wxString statStrings[4];
    wxString rowName;
    void Init();
    void FillPropertiesGrid(effectsProperties *);
    effect_stats_bonus_defender *getnewCopy();
};

class effect_block_damage : public basic_effect
{
public:
    int chance;
    wxString chanceString;
    int block;
    wxString blockString;
    effect_block_damage();
    void Init();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_block_damage *getnewCopy();
};

class effect_reduce_damage : public basic_effect
{
public:
    int percentage;
    wxString percentageString;
    effect_reduce_damage();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_reduce_damage *getnewCopy();
};

class effect_bonus_armor : public basic_effect
{
public:
    int armor;
    wxString armorString;
    effect_bonus_armor();
    void Init();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_bonus_armor *getnewCopy();
};

class effect_bonus_hpregen : public basic_effect
{
public:
    double hpregen;
    wxString hpregenString;
    effect_bonus_hpregen();
    void Init();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_bonus_hpregen *getnewCopy();
};

class effect_bonus_hpregen_heart : public basic_effect
{
public:
    double hpregen;
    wxString hpregenString;
    effect_bonus_hpregen_heart();
    void Continue();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_bonus_hpregen_heart *getnewCopy();
};

class effect_bonus_mpregen : public basic_effect
{
public:
    double mpregen;
    wxString mpregenString;
    int mpregenmult;
    wxString mpregenmultString;
    effect_bonus_mpregen();
    void Init();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_bonus_mpregen *getnewCopy();
};

class effect_magic_resistance : public basic_effect
{
public:
    int percentage;
    wxString percentageString;
    effect_magic_resistance();
    void Init();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_magic_resistance *getnewCopy();
};

class effect_bonus_hpregen_armor_ph_dummy;

class effect_bonus_hpregen_armor_ph_master : public basic_effect
{
public:
    int duration;
    wxString durationString;
    double armor;
    wxString armorString;
    double hpregen;
    wxString hpregenString;
    int maxStacks, oldStacks, realStacks;
    wxString maxStacksString;
    std::vector<effect_bonus_hpregen_armor_ph_dummy> dummyVector;
    effect_bonus_hpregen_armor_ph_master();
    void Init();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_bonus_hpregen_armor_ph_master *getnewCopy();
};

class effect_bonus_hpregen_armor_ph_dummy : public basic_effect
{
public:
    int duration;
    effect_bonus_hpregen_armor_ph_dummy();
    void Continue();
};

class effect_mana_shield : public basic_effect
{
public:
    int percentage;
    double dpm;
    wxString percentageString;
    wxString dpmString;
    effect_mana_shield();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_mana_shield *getnewCopy();
};

// ___ Attack effects
class effect_stats_bonus_attacker : public basic_effect
{
public:
    int statbonus;
    wxString statbonusString;
    effect_stats_bonus_attacker();
    unsigned mainStat;
    wxString statStrings[4];
    wxString rowName;
    void Init();
    void FillPropertiesGrid(effectsProperties *);
    effect_stats_bonus_attacker *getnewCopy();
};

class effect_damage : public basic_effect
{
public:
    int damage;
    wxString damageString;
    effect_damage();
    void Continue();
    void DoDoubleHit();
    void FillPropertiesGrid(effectsProperties *);
    effect_damage *getnewCopy();
};

class effect_damage_proc : public basic_effect
{
public:
    int damage;
    wxString damageString;
    int chance;
    wxString chanceString;
    effect_damage_proc();
    void Continue();
    void DoDoubleHit();
    void FillPropertiesGrid(effectsProperties *);
    effect_damage_proc *getnewCopy();
};

class effect_stats_as_damage : public basic_effect
{
public:
    int percentage;
    wxString percentageString;
    effect_stats_as_damage();
    unsigned mainStat;
    wxString statStrings[5];
    wxString rowName;
    void Continue();
    void DoDoubleHit();
    void FillPropertiesGrid(effectsProperties *);
    effect_stats_as_damage *getnewCopy();
};

class effect_stat_crit : public basic_effect
{
public:
    int percentage;
    wxString percentageString;
    effect_stat_crit();
    unsigned mainStat;
    wxString statStrings[3];
    wxString rowName;
    void Continue();
    void DoDoubleHit();
    void FillPropertiesGrid(effectsProperties *);
    effect_stat_crit *getnewCopy();
};

class effect_critical_damage : public basic_effect
{
public:
    int chance;
    int damage;
    wxString damageString;
    wxString chanceString;
    effect_critical_damage();
    void Init();
    void FillPropertiesGrid(effectsProperties *);
    effect_critical_damage *getnewCopy();
};

class effect_critical_damage_stackable : public basic_effect
{
public:
    int chance;
    int damage;
    wxString damageString;
    wxString chanceString;
    effect_critical_damage_stackable();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_critical_damage_stackable *getnewCopy();
};

class effect_feast : public basic_effect
{
public:
    double damage;
    wxString damageString;
    effect_feast();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_feast *getnewCopy();
};

class effect_manaburn : public basic_effect
{
public:
    int mana;
    wxString manaString;
    int manaBurn;
    wxString manaBurnString;
    effect_manaburn();
    void Continue();
    void DoDoubleHit();
    void FillPropertiesGrid(effectsProperties *);
    effect_manaburn *getnewCopy();
};

class effect_increase_IAS : public basic_effect
{
public:
    int bonusIAS;
    wxString bonusIASString;
    int IASStacks;
    wxString IASStacksString;
    int tempStacks;
    effect_increase_IAS();
    void Init();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_increase_IAS *getnewCopy();
};

class effect_increase_damage : public basic_effect
{
public:
    int percentage;
    wxString percentageString;
    effect_increase_damage();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_increase_damage *getnewCopy();
};

class effect_stat_steal_master : public basic_effect
{
public:
    int statsteal;
    wxString statstealString;
    int duration;
    wxString durationString;
    unsigned mainStat;
    wxString statStrings[3];
    wxString rowName;
    effect_stat_steal_master();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_stat_steal_master *getnewCopy();
};

class effect_stat_steal : public basic_effect
{
public:
    int statsteal;
    int duration;
    unsigned mainStat;
    effect_stat_steal();
    void Init();
    void Continue();
    effect_stat_steal *getnewCopy();
};

class effect_stat_steal_target_master : public basic_effect
{
public:
    int statsteal;
    wxString statstealString;
    int duration;
    wxString durationString;
    effect_stat_steal_target_master();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_stat_steal_target_master *getnewCopy();
};

class effect_stat_steal_target : public basic_effect
{
public:
    int statsteal;
    int duration;
    effect_stat_steal_target();
    void Init();
    void Continue();
    effect_stat_steal_target *getnewCopy();
};

class effect_fury_swipes : public basic_effect
{
public:
    double duration;
    wxString durationString;
    int damage;
    wxString damageString;
    int stacks;
    effect_fury_swipes();
    void Init();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_fury_swipes *getnewCopy();
};

class effect_armor_per_sec : public basic_effect
{
public:
    double interval;
    wxString intervalString;
    int duration;
    wxString durationString;
    double armor;
    wxString armorString;
    double armorMultiplier;
    double asynchronousAttacks, speedRatio, armorBuffer;
    double durationTimer;
    int changedTimes;
    bool firstHit;
    effect_armor_per_sec();
    void Init();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_armor_per_sec *getnewCopy();
};

class effect_poison : public basic_effect
{
public:
    double interval;
    wxString intervalString;
    int duration;
    wxString durationString;
    int damage;
    wxString damageString;
    double damageMultiplier;
    double damagepool;
    double asynchronousAttacks, speedRatio, damageBuffer;
    effect_poison();
    void Init();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_poison *getnewCopy();
};

class effect_poison_stackable_master : public basic_effect
{
public:
    double interval;
    wxString intervalString;
    int duration;
    wxString durationString;
    int damage;
    wxString damageString;
    effect_poison_stackable_master();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_poison_stackable_master *getnewCopy();
};

class effect_poison_stackable : public basic_effect
{
public:
    double interval;
    int duration;
    int damage;
    double damageMultiplier;
    double asynchronousAttacks, speedRatio, damageBuffer;
    effect_poison_stackable();
    void Init();
    void Continue();
    effect_poison_stackable *getnewCopy();
};

class effect_poison_hppercent : public basic_effect
{
public:
    double interval;
    wxString intervalString;
    int duration;
    wxString durationString;
    double damage;
    wxString damageString;
    double damageMultiplier;
    double asynchronousAttacks, speedRatio, damageBuffer;
    effect_poison_hppercent();
    void Init();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_poison_hppercent *getnewCopy();
};

class effect_double_attack : public basic_effect
{
public:
    double cooldown;
    wxString cooldownString;
    double damageBuffer;
    double damageMultiplier;
    double asynchronousAttacks, speedRatio;
    effect_double_attack();
    void Continue();
    void Init();
    void FillPropertiesGrid(effectsProperties *);
    effect_double_attack *getnewCopy();
};

class effect_heartstopper_aura : public basic_effect
{
public:
    double interval;
    wxString intervalString;
    double damage;
    wxString damageString;
    double damageMultiplier;
    double asynchronousAttacks, speedRatio, damageBuffer;
    effect_heartstopper_aura();
    void Init();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_heartstopper_aura *getnewCopy();
};

class effect_nethertoxin : public basic_effect
{
public:
    double baseDamage;
    wxString baseDamageString;
    int maxDamage;
    effect_nethertoxin();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_nethertoxin *getnewCopy();
};

const int maxRanks=12;
const int minRanks=-5;

inline isLessThanDamage(const effect_critical_damage *crit1, const effect_critical_damage *crit2)
{
    return ((*crit1).damage > (*crit2).damage);
}

inline isLessThanBlock(const effect_block_damage *effect1, const effect_block_damage *effect2)
{
    return ((*effect1).block > (*effect2).block);
}
#endif
