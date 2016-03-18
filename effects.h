#ifndef EFFECTS_H
#define EFFECTS_H

#include "commonIncludes.h"
#include "effectsProperties.h"

class effectsProperties;

class basic_effect
{
public:
basic_effect();
virtual ~basic_effect();
wxString ID;
wxString Name;
unsigned index;
bool disabled;
unsigned initRank;
virtual void Init();
virtual void Continue();
virtual void DoDoubleAttack();
virtual void FillPropertiesGrid(effectsProperties *);
virtual basic_effect *getnewCopy(); //Make new object of this class and return its address.
};

class effect_critical_damage : public basic_effect
{
public:
    int chance;
    int damage;
    wxString damageString;
    wxString chanceString;
    effect_critical_damage();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_critical_damage *getnewCopy();
};

class effect_block_damage : public basic_effect
{
public:
    int chance;
    wxString chanceString;
    int block;
    wxString blockString;
    effect_block_damage();
    void Continue();
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *callBackEffBase);
    effect_block_damage *getnewCopy();
};

class effect_poison : public basic_effect
{
public:
    double iterspeed;
    wxString iterspeedString;
    double damagepool, nozzle;
    int duration;
    wxString durationString;
    int damage;
    wxString damageString;
    double damageMultiplier;
    double asynchronousAttacks, speedRatio, damageBuffer;
    effect_poison();
    void Init();
    void Continue();
    void FillPropertiesGrid(effectsProperties *);
    effect_poison *getnewCopy();
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
    void DoDoubleAttack();
    void FillPropertiesGrid(effectsProperties *);
    effect_double_attack *getnewCopy();
};

const int maxRanks=12;
const int minRanks=-5;

inline isLessThanChance(const effect_critical_damage& crit1, const effect_critical_damage& crit2)
{
    return (crit1.chance < crit2.chance);
}
#endif
