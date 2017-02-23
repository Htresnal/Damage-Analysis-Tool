/*
В Init() должны помещаться функции, которые включаются один раз -
- перед инициализацией цикла Continue(), влияющие на базовые
параметры(например, добавление количества брони, статов,
,скорости атаки, глобальные ауры и т.д.). В этом разделе НЕ должно быть
ничего, что не соответствует прямому таймлайну эмуляции, т.к. instance
Continue() будет включен сразу после Init().
Повреждения рассчитываются, добавляя цифру повреждения к переменным:
InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle.
Изменять здоровье напрямую не стоит.
В Init() лучше помещать обновление необходимых в работе переменных.
В цикле Continue() должны работать эффекты, имеющие продолжительное
динамическое поведение, например: minus armor per hit, или minus to
stats per hit.
Если эффект использует параметры, меняемые с каждым проходом Continue(),
такие как скорость атаки, максимальное здоровье и т.д., то необходимо
обязательно перерассчитать внутриклассовые переменные, основанные на них.
Ранги эффектов:
maxRanks=12; // ___ Максимальный уровень ранков.
minRanks=-5; // ___ Минимальный уровень ранков. Эффекты с ранком -5
будут применены первее, максимальный ранк будет применён позднее.
Например, критический удар или щит маны должны срабатывать раньше, чем
будут рассчитаны иные повреждения, и сопротивления.
Все повреждающие и защищающие эффекты с ранком ниже 0 могут взаимовлиять,
т.к. используют общую переменную для рассчётов повреждения, усиляя
следующий предыдущим.
Список ранков:
-5 - -1 - Critical hit, Mana shield, Stat steal
0 - Damage block.
10 - 12 - Damage amplify, Damage reduction and Heartstopper aura.
*/

//Статы не имеют силы. Необходимо иметь дело со статами через конечные, подчиненные им
//переменные.

#include "effects.h"
#include "AnalysisLogs.h"
#include "heroData.h"

// ___ Global Vectors
std::vector<basic_effect *> attackEffects;
std::vector<basic_effect *> defenceEffects;
std::vector<effect_critical_damage *> critEffects;
std::vector<effect_block_damage *> shieldBlockEffects;
std::vector<double> magicResistanceBuffer;

extern double ARReduct, InDamageBase, InDamagePerCycleCrit, InDamage, InDamageRaw, InDamageMagic, InDamageNoReduct, aps, singleAttackTime, currAps, currSingleAttackTime, InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle;
extern int DoDoubleHit, DefendercurrMaxHP;
extern unsigned WhiteDmg;
extern void recalculateAttackSpeed();

extern AnalysisLogs *Frame1;

extern hero_Defender Defender;
extern hero_Attacker Attacker;

// EFFECT MAP EFFECT MAP EFFECT MAP EFFECT MAP EFFECT MAP EFFECT MAP
// This map contains all the accessible effects.
// If you wish to add your own effect to the UI - just add them here.
// Maps are split by two purposes - to be used by the Attacker, and by the Defender.
	std::map<std::string,basic_effect *> effectMapAttack=
	{
    {"effect_stats_bonus_attacker", new effect_stats_bonus_attacker},
    {"effect_damage", new effect_damage},
    {"effect_damage_proc", new effect_damage_proc},
    {"effect_manaburn", new effect_manaburn},
    {"effect_bonus_IAS", new effect_bonus_IAS},
    {"effect_increase_IAS", new effect_increase_IAS},
    {"effect_increase_damage", new effect_increase_damage},
    {"effect_critical_damage", new effect_critical_damage},
    {"effect_critical_damage_stackable", new effect_critical_damage_stackable},
    {"effect_stats_as_damage", new effect_stats_as_damage},
    {"effect_stat_crit", new effect_stat_crit},
    {"effect_stat_steal_master", new effect_stat_steal_master},
    {"effect_fury_swipes", new effect_fury_swipes},
    {"effect_poison", new effect_poison},
    {"effect_poison_stackable_master", new effect_poison_stackable_master},
    {"effect_poison_hppercent", new effect_poison_hppercent},
    {"effect_double_attack", new effect_double_attack},
    {"effect_feast", new effect_feast},
    {"effect_heartstopper_aura", new effect_heartstopper_aura},
    {"effect_nethertoxin", new effect_nethertoxin}
    };

	std::map<std::string,basic_effect *> effectMapDefense=
	{
    {"effect_stats_bonus_defender", new effect_stats_bonus_defender},
    {"effect_bonus_hpregen", new effect_bonus_hpregen},
    {"effect_bonus_hpregen_heart", new effect_bonus_hpregen_heart},
    {"effect_bonus_mpregen", new effect_bonus_mpregen},
    {"effect_bonus_armor", new effect_bonus_armor},
    {"effect_armor_per_sec", new effect_armor_per_sec},
    {"effect_block_damage", new effect_block_damage},
    {"effect_reduce_damage", new effect_reduce_damage},
    {"effect_stat_steal_target_master", new effect_stat_steal_target_master},
    {"effect_mana_shield", new effect_mana_shield},
    {"effect_bonus_hpregen_armor_ph_master", new effect_bonus_hpregen_armor_ph_master},
    {"effect_magic_resistance", new effect_magic_resistance}
    };

basic_effect::basic_effect()
{
ID="basic_effect";
Name="Basic effect";
disabled=0;
temporary=0;
}

basic_effect::~basic_effect()
{

}

void basic_effect::Init()
{
return;
}

void basic_effect::Continue()
{
return;
}

void basic_effect::DoDoubleAttack()
{
return;
}

double *basic_effect::checkDamageType()
{
// Here, the damage type is being set. This function is only used by the damage dealing effects.
    if (damageType==Physical)
    {
	return &InDamagePerCycle;
    }
    else if (damageType==Magic)
    {
	return &InDamageMagicPerCycle;
    }
    else if (damageType==NoReduction)
    {
	return &InDamageNoReductPerCycle;
    }
return 0;
}

void basic_effect::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    //wxMessageBox(_("Hello!"), _("I want you to see this ;)"));
return;
}

basic_effect* basic_effect::getnewCopy()
{
return new basic_effect(*this);
// How to use: basic_effect *tmpEff = &(baseEff->getnewCopy());
}
//////////////////////////////PREPARATION LINE///////////////////////////////
// effect_stats_bonus_defender
effect_stats_bonus_defender::effect_stats_bonus_defender()
{
ID="effect_stats_bonus_defender";
Name="Attribute Bonus"; // UI Choice List representation.
initRank=-5; // Rank of emulation order. Less is prior.
disabled=0; // Skills with 1 will disappear out of the emulation order.
temporary=0; // Skills with 1 would be deleted out of the effect vector(list of active effects).
statbonus=2; // Default stat value.
statbonusString="Bonus to stats"; // Effect description string in the properties UI.
mainStat=AllStats; // Selected stat. Default is all 3 stats.
statStrings[0] = "Strength";
statStrings[1] = "Agility";
statStrings[2] = "Intelligence";
statStrings[3] = "All stats";// Text array(Numbers correlate with the effect actions).
rowName="Stat type"; // Effect description string in the properties UI.
}

effect_stats_bonus_defender* effect_stats_bonus_defender::getnewCopy()
{
return new effect_stats_bonus_defender(*this);
// This part is essential for the main UI, to be hook up with the effects.
// How to use: effect_stats_bonus_defender *tmpEff = &(baseEff->getnewCopy());
}

void effect_stats_bonus_defender::Init()
{
    // Init() is run once, before the emulation begins, but there is are rare occasions, when effects can,
    // make their own child copies. They could be Init()'ed at any time, during the emulation time.
    if (mainStat==Strength)
    {
        Defender.changeSTR(statbonus);
    }
    else if (mainStat==Agility)
    {
        Defender.changeAGI(statbonus);
    }
    else if (mainStat==Intelligence)
    {
        Defender.changeINT(statbonus);
    }
    else if (mainStat==AllStats)
    {
        Defender.changeSTR(statbonus);
        Defender.changeAGI(statbonus);
        Defender.changeINT(statbonus);
    }
return;
}

void effect_stats_bonus_defender::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    // That part is responsible of the Properties menu. Here, variables are being loaded in, and UI
    // communicate with them using references. System of "type adaptation" is used, receiving only 2 types:
    // double and int.
    callBackEffBase->Clear();
    callBackEffBase->AppendCustomSelector(mainStat,4,rowName,statStrings);
    callBackEffBase->AppendFullRow(statbonusString,statbonus);
    callBackEffBase->ptrtoItem=this;
    // Append types can be found at effectsProperties.cpp file.
}

// effect_reduce_damage
effect_reduce_damage::effect_reduce_damage()
{
percentageString="Reduction %";
Name="Reduce damage";
ID="effect_reduce_damage";
disabled=0;
temporary=0;
percentage=60;
initRank=-4;
}

effect_reduce_damage* effect_reduce_damage::getnewCopy()
{
return new effect_reduce_damage(*this);
// How to use: effect_reduce_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_reduce_damage::Continue()
{
    InDamagePerCycle=InDamagePerCycle/100*(100-percentage);
    InDamageMagicPerCycle=InDamageMagicPerCycle/100*(100-percentage);
    InDamageNoReductPerCycle=InDamageNoReductPerCycle/100*(100-percentage);
}

void effect_reduce_damage::DoDoubleAttack()
{
    // Some effects act differently during proc of the "second hit", for example - poisons,
    // or effects, that require time to do their work.
    Continue();
return;
}

void effect_reduce_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(percentageString,percentage);
    callBackEffBase->ptrtoItem=&(*this);
}

// effect_bonus_armor
effect_bonus_armor::effect_bonus_armor()
{
ID="effect_bonus_armor";
Name="Bonus armor";
disabled=0;
temporary=0;
initRank=0;
armor=10;
armorString="Armor";
}

effect_bonus_armor* effect_bonus_armor::getnewCopy()
{
return new effect_bonus_armor(*this);
// How to use: effect_bonus_armor *tmpEff = &(baseEff->getnewCopy());
}

void effect_bonus_armor::Init()
{
    Defender.armor=Defender.armor+armor;
return;
}

void effect_bonus_armor::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(armorString,armor);
    callBackEffBase->ptrtoItem=this;
}

// effect_armor_per_sec
effect_armor_per_sec::effect_armor_per_sec()
{
ID="effect_armor_per_sec";
Name="Weave";
initRank=1;
disabled=0;
temporary=0;
armor=1.75;
armorString="Armor per sec.";
duration=24;
durationString="Duration, sec.";
interval=1;
intervalString="Change interval";
}

effect_armor_per_sec* effect_armor_per_sec::getnewCopy()
{
return new effect_armor_per_sec(*this);
// How to use: effect_armor_per_sec *tmpEff = &(baseEff->getnewCopy());
}

void effect_armor_per_sec::Init()
{
    //Effect starts at the Init() part, then, with Continue(), it tries to reach the end of the duration.
    durationTimer=duration;
    armorBuffer=0;
    armorMultiplier=0;
    changedTimes=0;
    firstHit=1;
return;
}

void effect_armor_per_sec::Continue()
{
    if (firstHit!=0)
    {
        firstHit=0;
	return;
    }
    if (durationTimer!=0)
    {
        speedRatio=currSingleAttackTime/interval;
        if (currSingleAttackTime>=durationTimer)
        {
            Defender.armor=Defender.armor+armor*changedTimes*-1;
            durationTimer=0;
        return;
        }
        durationTimer=durationTimer-currSingleAttackTime;
        asynchronousAttacks=speedRatio+armorBuffer;
        armorBuffer=modf (asynchronousAttacks,&armorMultiplier);
        if (armorMultiplier!=0)
        {
            Defender.armor=Defender.armor+armor*armorMultiplier;
            changedTimes=changedTimes+armorMultiplier;
        }
    }
return;
}

void effect_armor_per_sec::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(armorString,armor);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->AppendFullRow(intervalString,interval);
    callBackEffBase->ptrtoItem=this;
}

// effect_bonus_hpregen
effect_bonus_hpregen::effect_bonus_hpregen()
{
ID="effect_bonus_hpregen";
Name="Bonus HP regeneration";
disabled=0;
temporary=0;
initRank=0;
hpregen=6;
hpregenString="Health regeneration";
}

effect_bonus_hpregen* effect_bonus_hpregen::getnewCopy()
{
return new effect_bonus_hpregen(*this);
// How to use: effect_bonus_hpregen *tmpEff = &(baseEff->getnewCopy());
}

void effect_bonus_hpregen::Init()
{
    // Original values are saved before the emulation start, and then restored afterwards.
    Defender.HPRegen=Defender.HPRegen+hpregen;
return;
}

void effect_bonus_hpregen::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(hpregenString,hpregen);
    callBackEffBase->ptrtoItem=this;
}

// effect_bonus_hpregen_heart
effect_bonus_hpregen_heart::effect_bonus_hpregen_heart()
{
ID="effect_bonus_hpregen_heart";
Name="Bonus HP regeneration(%)";
disabled=0;
temporary=0;
initRank=0;
hpregen=4.75;
hpregenString="Health regeneration(%)";
}

effect_bonus_hpregen_heart* effect_bonus_hpregen_heart::getnewCopy()
{
return new effect_bonus_hpregen_heart(*this);
// How to use: effect_bonus_hpregen_heart *tmpEff = &(baseEff->getnewCopy());
}

void effect_bonus_hpregen_heart::Continue()
{
    if (Defender.HP<DefendercurrMaxHP && Defender.HP>0)
    {
        Defender.HP=Defender.HP+((double)DefendercurrMaxHP/100*hpregen);
    }
    if (Defender.HP>Defender.maxHP)
    {
        Defender.HP=Defender.maxHP;
    }
return;
}

void effect_bonus_hpregen_heart::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(hpregenString,hpregen);
    callBackEffBase->ptrtoItem=this;
}

// effect_bonus_mpregen
effect_bonus_mpregen::effect_bonus_mpregen()
{
ID="effect_bonus_mpregen";
Name="Bonus Mana regeneration";
disabled=0;
temporary=0;
initRank=0;
mpregen=0.8;
mpregenString="Mana regeneration";
mpregenmult=100;
mpregenmultString="Mana regeneration (%)";
}

effect_bonus_mpregen* effect_bonus_mpregen::getnewCopy()
{
return new effect_bonus_mpregen(*this);
// How to use: effect_bonus_mpregen *tmpEff = &(baseEff->getnewCopy());
}

void effect_bonus_mpregen::Init()
{
    Defender.MPRegenBonus=Defender.MPRegenBonus+mpregen;
    if (mpregenmult!=0)
    {
        Defender.MPRegenMultiplier=Defender.MPRegenMultiplier+((double)mpregenmult/100);
    }
return;
}

void effect_bonus_mpregen::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(mpregenString,mpregen);
    callBackEffBase->AppendFullRow(mpregenmultString,mpregenmult);
    callBackEffBase->ptrtoItem=this;
}

// effect_mana_shield
effect_mana_shield::effect_mana_shield()
{
percentageString="Absorbed damage %";
dpmString="Damage per mana";
Name="Mana shield";
ID="effect_mana_shield";
disabled=0;
temporary=0;
percentage=60;
dpm=2.5;
initRank=-4;
}

void effect_mana_shield::Continue()
{
    double tmpManaAsShield;
    if (InDamageNoReductPerCycle!=0 && Defender.MP!=0)
    {
        tmpManaAsShield=(InDamageNoReductPerCycle/100*percentage)/dpm;//This much mana we need to remove.
        if (Defender.MP>=tmpManaAsShield)
        {
            Defender.MP=Defender.MP-tmpManaAsShield;
            InDamageNoReductPerCycle=InDamageNoReductPerCycle/100*(100-percentage);//Restructuring the incoming damage to contain reduced damage.
        }
        else
        {
            InDamageNoReductPerCycle=InDamageNoReductPerCycle-(dpm*Defender.MP);
            Defender.MP=0;
        }
    }
    if (InDamageMagicPerCycle!=0 && Defender.MP!=0)
    {
        tmpManaAsShield=(InDamageMagicPerCycle/100*percentage)/dpm;
        if (Defender.MP>=tmpManaAsShield)
        {
            Defender.MP=Defender.MP-tmpManaAsShield;
            InDamageMagicPerCycle=InDamageMagicPerCycle/100*(100-percentage);
        }
        else
        {
            InDamageMagicPerCycle=InDamageMagicPerCycle-(dpm*Defender.MP);
            Defender.MP=0;
        }
    }
    if (InDamagePerCycle!=0 && Defender.MP!=0)
    {
        tmpManaAsShield=(InDamagePerCycle/100*percentage)/dpm;
        if (Defender.MP>=tmpManaAsShield)
        {
            Defender.MP=Defender.MP-tmpManaAsShield;
            InDamagePerCycle=InDamagePerCycle/100*(100-percentage);
        }
        else
        {
            InDamagePerCycle=InDamagePerCycle-(dpm*Defender.MP);
            Defender.MP=0;
        }
    }
}

effect_mana_shield* effect_mana_shield::getnewCopy()
{
return new effect_mana_shield(*this);
// How to use: effect_mana_shield *tmpEff = &(baseEff->getnewCopy());
}

void effect_mana_shield::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(percentageString,percentage);
    callBackEffBase->AppendFullRow(dpmString,dpm);
    callBackEffBase->ptrtoItem=&(*this);
}

void effect_mana_shield::DoDoubleAttack()
{
    Continue();
return;
}

// effect_magic_resistance
effect_magic_resistance::effect_magic_resistance()
{
percentageString="Resistance %";
Name="Magic resistance";
ID="effect_magic_resistance";
disabled=0;
temporary=0;
externalContinueCycle=true;
// Effects with externalContinueCycle are telling emulator not to consider them, because they
// contain their own running cycle, or being a part of someone else's cycle. In this example,
// effect don't need to be enabled through the Continue(), since it is hooked up with the magicResistanceBuffer,
// and a cycle, that is based on it.
percentage=15;
initRank=10;
}

void effect_magic_resistance::Init()
{
    magicResistanceBuffer.push_back(percentage);
}

effect_magic_resistance* effect_magic_resistance::getnewCopy()
{
return new effect_magic_resistance(*this);
// How to use: effect_magic_resistance *tmpEff = &(baseEff->getnewCopy());
}

void effect_magic_resistance::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(percentageString,percentage);
    callBackEffBase->ptrtoItem=&(*this);
}

// effect_bonus_hpregen_armor_ph_master
effect_bonus_hpregen_armor_ph_master::effect_bonus_hpregen_armor_ph_master()
{
ID="effect_bonus_hpregen_armor_ph_master";
Name="Reactive Armor";
disabled=0;
temporary=0;
initRank=-5;
armor=1.6;
armorString="Armor per stack";
hpregen=1.6;
hpregenString="Health regen per stack";
duration=19;
durationString="Stack Duration, sec.";
maxStacks=20;
maxStacksString="Max stacks";
dummyVector.reserve(20);
}

effect_bonus_hpregen_armor_ph_master* effect_bonus_hpregen_armor_ph_master::getnewCopy()
{
return new effect_bonus_hpregen_armor_ph_master(*this);
// How to use: effect_bonus_hpregen_armor_ph_master *tmpEff = &(baseEff->getnewCopy());
}

void effect_bonus_hpregen_armor_ph_master::Init()
{
    oldStacks=0;
    realStacks=0;
    dummyVector.clear();
}

void effect_bonus_hpregen_armor_ph_master::Continue()
{
    oldStacks=realStacks;
    realStacks=0;
    effect_bonus_hpregen_armor_ph_dummy *newDummy=new effect_bonus_hpregen_armor_ph_dummy;
    newDummy->duration=duration;
    newDummy->Init();
    dummyVector.push_back(*newDummy);
    delete newDummy;
    for (unsigned i=0;i<dummyVector.size();i++)
    {
        if (dummyVector[i].disabled!=1)
        {
            if (realStacks!=maxStacks)
            {
                realStacks=realStacks+1;
            }
        }
        else
        {
            dummyVector.erase(dummyVector.begin()+(i-1));
            i=i-1;
        }
    }
    if (realStacks<oldStacks)
    {
        Defender.armor=Defender.armor-(armor*(oldStacks-realStacks)*currSingleAttackTime);
        Defender.HPRegen=Defender.HPRegen-(hpregen*(oldStacks-realStacks)*currSingleAttackTime);
    }
    else if (oldStacks<realStacks)
    {
        Defender.armor=Defender.armor+(armor*(realStacks-oldStacks)*currSingleAttackTime);
        Defender.HPRegen=Defender.HPRegen+(hpregen*(realStacks-oldStacks)*currSingleAttackTime);
    }
return;
}

void effect_bonus_hpregen_armor_ph_master::DoDoubleAttack()
{
    effect_bonus_hpregen_armor_ph_dummy *newDummy=new effect_bonus_hpregen_armor_ph_dummy;
    newDummy->duration=duration;
    newDummy->Init();
    dummyVector.push_back(*newDummy);
    delete newDummy;
return;
}

void effect_bonus_hpregen_armor_ph_master::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(armorString,armor);
    callBackEffBase->AppendFullRow(hpregenString,hpregen);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->AppendFullRow(maxStacksString,maxStacks);
    callBackEffBase->ptrtoItem=this;
}

// effect_bonus_hpregen_armor_ph_dummy
effect_bonus_hpregen_armor_ph_dummy::effect_bonus_hpregen_armor_ph_dummy()
{
ID="effect_bonus_hpregen_armor_ph_dummy";
Name="Reactive Armor(dummy)";
disabled=0;
temporary=1;
duration=0;//Overwrited by master effect.
}

void effect_bonus_hpregen_armor_ph_dummy::Continue()
{
    duration=duration-currSingleAttackTime;
    if (duration<=0)
    {
        disabled=1;
	return;
    }
return;
}

// effect_block_damage
effect_block_damage::effect_block_damage()
{
chanceString="Chance";
blockString="Block damage";
Name="Block damage";
ID="effect_block_damage";
disabled=0;
temporary=0;
externalContinueCycle=true;
chance=53;
block=20;
initRank=0;
}

effect_block_damage* effect_block_damage::getnewCopy()
{
return new effect_block_damage(*this);
// How to use: effect_block_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_block_damage::Init()
{
    shieldBlockEffects.push_back(&(*this));
}

void effect_block_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(chanceString,chance);
    callBackEffBase->AppendFullRow(blockString,block);
    callBackEffBase->ptrtoItem=&(*this);
}
/////////////////////////////////////////////////////////////////////////////////
// effect_stats_bonus_attacker
effect_stats_bonus_attacker::effect_stats_bonus_attacker()
{
ID="effect_stats_bonus_attacker";
Name="Attribute Bonus";
initRank=-5;
disabled=0;
temporary=0;
statbonus=2;
statbonusString="Bonus to stats";
mainStat=AllStats;
statStrings[0] = "Strength";
statStrings[1] = "Agility";
statStrings[2] = "Intelligence";
statStrings[3] = "All stats";
rowName="Stat type";
}

effect_stats_bonus_attacker* effect_stats_bonus_attacker::getnewCopy()
{
return new effect_stats_bonus_attacker(*this);
// How to use: effect_stats_bonus_attacker *tmpEff = &(baseEff->getnewCopy());
}

void effect_stats_bonus_attacker::Init()
{
    if (mainStat==Strength)
    {
        Attacker.changeSTR(statbonus);
        if (Attacker.mainStat==Strength)
        {
            WhiteDmg=WhiteDmg+(statbonus);
        }
    }
    else if (mainStat==Agility)
    {
        Attacker.changeAGI(statbonus);
        Frame1->recalculateAttackSpeed();// Recalculate agi-involved speed changes.
        if (Attacker.mainStat==Agility)
        {
            WhiteDmg=WhiteDmg+(statbonus);
        }
    }
    else if (mainStat==Intelligence)
    {
        Attacker.changeINT(statbonus);
        if (Attacker.mainStat==Intelligence)
        {
            WhiteDmg=WhiteDmg+(statbonus);
        }
    }
    else if (mainStat==AllStats)
    {
        Attacker.changeSTR(statbonus);
        Attacker.changeAGI(statbonus);
        Frame1->recalculateAttackSpeed();
        Attacker.changeINT(statbonus);
        WhiteDmg=WhiteDmg+(statbonus);
    }
return;
}

void effect_stats_bonus_attacker::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendCustomSelector(mainStat,4,rowName,statStrings);
    callBackEffBase->AppendFullRow(statbonusString,statbonus);
    callBackEffBase->ptrtoItem=this;
}

// effect_damage
effect_damage::effect_damage()
{
ID="effect_damage";
Name="Bonus damage";
disabled=0;
temporary=0;
initRank=1;
damageType=Physical;
damage=60;
damageString="Damage per hit";
}

effect_damage* effect_damage::getnewCopy()
{
return new effect_damage(*this);
// How to use: effect_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_damage::Continue()
{
    double *damageOfType=checkDamageType();
    *damageOfType=*damageOfType+damage;
return;
}

void effect_damage::DoDoubleHit()
{
    Continue();
return;
}

void effect_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->ptrtoItem=this;
}

// effect_damage_proc
effect_damage_proc::effect_damage_proc()
{
ID="effect_damage_proc";
Name="Bonus damage on proc";
disabled=0;
temporary=0;
initRank=1;
damageType=Physical;
damage=90;
damageString="Damage per hit";
chance=40;
chanceString="Chance to proc";
}

effect_damage_proc* effect_damage_proc::getnewCopy()
{
return new effect_damage_proc(*this);
// How to use: effect_damage_proc *tmpEff = &(baseEff->getnewCopy());
}

void effect_damage_proc::Continue()
{
    double *damageOfType=checkDamageType();
    *damageOfType=*damageOfType+((int)((double)damage/100*chance));
return;
}

void effect_damage_proc::DoDoubleHit()
{
    Continue();
return;
}

void effect_damage_proc::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(chanceString,chance);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->ptrtoItem=this;
}

// effect_stats_as_damage
effect_stats_as_damage::effect_stats_as_damage()
{
ID="effect_stats_as_damage";
Name="Stats as Bonus Damage";
disabled=0;
temporary=0;
initRank=-3;
damageType=NoReduction;
percentage=80;
percentageString="% as damage";
mainStat=Intelligence;
statStrings[0] = "Strength";
statStrings[1] = "Agility";
statStrings[2] = "Intelligence";
statStrings[3] = "Health";
statStrings[4] = "Mana";
rowName="Stat type";
}

effect_stats_as_damage* effect_stats_as_damage::getnewCopy()
{
return new effect_stats_as_damage(*this);
// How to use: effect_stats_as_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_stats_as_damage::Continue()
{
    double *damageOfType=checkDamageType();
    int tmpDamage;
    if (mainStat==0 && Attacker.getSTR()!=0)
    {
        tmpDamage=Attacker.getSTR();
    }
    else if (mainStat==1 && Attacker.getAGI()!=0)
    {
        tmpDamage=Attacker.getAGI();
    }
    else if (mainStat==2 && Attacker.getINT()!=0)
    {
        tmpDamage=Attacker.getINT();
    }
    else if (mainStat==3 && Attacker.HP!=0)
    {
        tmpDamage=Attacker.HP;
    }
    else if (mainStat==4 && Attacker.MP!=0)
    {
        tmpDamage=Attacker.MP;
    }
    *damageOfType=*damageOfType+((int)((double)tmpDamage/100*percentage));
return;
}

void effect_stats_as_damage::DoDoubleHit()
{
    Continue();
return;
}

void effect_stats_as_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendCustomSelector(mainStat,5,rowName,statStrings);
    callBackEffBase->AppendFullRow(percentageString,percentage);
    callBackEffBase->ptrtoItem=this;
}

// effect_stat_crit
effect_stat_crit::effect_stat_crit()
{
ID="effect_stat_crit";
Name="Backstab";
disabled=0;
temporary=0;
initRank=0;
damageType=Physical;
percentage=125;
percentageString="% of stat as damage";
mainStat=Agility;
statStrings[0] = "Strength";
statStrings[1] = "Agility";
statStrings[2] = "Intelligence";
rowName="Stat type";
}

effect_stat_crit* effect_stat_crit::getnewCopy()
{
return new effect_stat_crit(*this);
// How to use: effect_stat_crit *tmpEff = &(baseEff->getnewCopy());
}

void effect_stat_crit::Continue()
{
    double *damageOfType=checkDamageType();
    int tmpDamage;
    if (mainStat==0 && Attacker.getSTR()!=0)
    {
        tmpDamage=Attacker.getSTR();
    }
    else if (mainStat==1 && Attacker.getAGI()!=0)
    {
        tmpDamage=Attacker.getAGI();
    }
    else if (mainStat==2 && Attacker.getINT()!=0)
    {
        tmpDamage=Attacker.getINT();
    }
    *damageOfType=*damageOfType+((int)((double)tmpDamage/100*percentage));
return;
}

void effect_stat_crit::DoDoubleHit()
{
    Continue();
return;
}

void effect_stat_crit::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendCustomSelector(mainStat,3,rowName,statStrings);
    callBackEffBase->AppendFullRow(percentageString,percentage);
    callBackEffBase->ptrtoItem=this;
}

// effect_critical_damage
effect_critical_damage::effect_critical_damage()
{
chanceString="Chance(%)";
damageString="Damage";
Name="Critical hit";
ID="effect_critical_damage";
disabled=0;
temporary=0;
externalContinueCycle=true;
initRank=-2;
chance=30;
damage=220;
}

effect_critical_damage* effect_critical_damage::getnewCopy()
{
return new effect_critical_damage(*this);
// How to use: effect_critical_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_critical_damage::Init()
{
    critEffects.push_back(&(*this));
}

void effect_critical_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(chanceString,chance);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->ptrtoItem=&(*this);
}

// effect_critical_damage_stackable
effect_critical_damage_stackable::effect_critical_damage_stackable()
{
chanceString="Chance";
damageString="Damage";
Name="Critical hit(stackable)";
ID="effect_critical_damage_stackable";
disabled=0;
temporary=0;
initRank=-1;
chance=30;
damage=220;
}

effect_critical_damage_stackable* effect_critical_damage_stackable::getnewCopy()
{
return new effect_critical_damage_stackable(*this);
// How to use: effect_critical_damage_stackable *tmpEff = &(baseEff->getnewCopy());
}

void effect_critical_damage_stackable::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(chanceString,chance);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->ptrtoItem=&(*this);
}

void effect_critical_damage_stackable::Continue()
{
    InDamagePerCycle=InDamagePerCycle+(((InDamagePerCycle/100*damage)-InDamagePerCycle)/100*chance);
}

void effect_critical_damage_stackable::DoDoubleAttack()
{
    Continue();
return;
}

// effect_feast
effect_feast::effect_feast()
{
damageString="Damage %";
Name="Feast";
ID="effect_feast";
disabled=0;
temporary=0;
initRank=-3;
damage=7.5;
}

effect_feast* effect_feast::getnewCopy()
{
return new effect_feast(*this);
// How to use: effect_feast *tmpEff = &(baseEff->getnewCopy());
}

void effect_feast::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->ptrtoItem=&(*this);
}

void effect_feast::Continue()
{
    double *damageOfType=checkDamageType();
    if (Defender.HP>=1)
    {
        *damageOfType=*damageOfType+((double)Defender.HP/100*damage);
    }
}

void effect_feast::DoDoubleAttack()
{
    Continue();
return;
}

// effect_manaburn
effect_manaburn::effect_manaburn()
{
ID="effect_manaburn";
Name="Manaburn";
disabled=0;
temporary=0;
initRank=1;
damageType=Physical;
mana=64;
manaString="Mana per hit";
manaBurn=60;
manaBurnString="Mana as damage(%)";
}

effect_manaburn* effect_manaburn::getnewCopy()
{
return new effect_manaburn(*this);
// How to use: effect_manaburn *tmpEff = &(baseEff->getnewCopy());
}

void effect_manaburn::Continue()
{
    double *damageOfType=checkDamageType();
    if (Defender.MP>=mana)
    {
        Defender.MP=Defender.MP-mana;
        *damageOfType=*damageOfType+((double)mana/100*(double)manaBurn);
    }
    else if (Defender.MP>=1)
    {
        *damageOfType=*damageOfType+((double)Defender.MP/100*(double)manaBurn);
        Defender.MP=0;
    }
return;
}

void effect_manaburn::DoDoubleHit()
{
    Continue();
return;
}

void effect_manaburn::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(manaString,mana);
    callBackEffBase->AppendFullRow(manaBurnString,manaBurn);
    callBackEffBase->ptrtoItem=this;
}

// effect_bonus_IAS
effect_bonus_IAS::effect_bonus_IAS()
{
Name="Increase Attack Speed";
ID="effect_bonus_IAS";
disabled=0;
temporary=0;
bonusIAS=55;
bonusIASString="Attack speed bonus";
initRank=12;
}

effect_bonus_IAS* effect_bonus_IAS::getnewCopy()
{
return new effect_bonus_IAS(*this);
// How to use: effect_bonus_IAS *tmpEff = &(baseEff->getnewCopy());
}

void effect_bonus_IAS::Init()
{
    Attacker.IAS=Attacker.IAS+bonusIAS;
    Frame1->recalculateAttackSpeed();
}

void effect_bonus_IAS::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(bonusIASString,bonusIAS);
    callBackEffBase->ptrtoItem=this;
}

// effect_increase_IAS
effect_increase_IAS::effect_increase_IAS()
{
Name="Increase IAS per hit";
ID="effect_increase_IAS";
disabled=0;
temporary=0;
bonusIAS=30;
bonusIASString="IAS bonus per stack";
IASStacks=7;
IASStacksString="Max Stacks";
initRank=12;
}

effect_increase_IAS* effect_increase_IAS::getnewCopy()
{
return new effect_increase_IAS(*this);
// How to use: effect_increase_IAS *tmpEff = &(baseEff->getnewCopy());
}

void effect_increase_IAS::Init()
{
    tempStacks=0;
}

void effect_increase_IAS::Continue()
{
    if (tempStacks!=IASStacks)
    {
        tempStacks=tempStacks+1;
        Attacker.IAS=Attacker.IAS+bonusIAS;
        Frame1->recalculateAttackSpeed();
    }
}

void effect_increase_IAS::DoDoubleAttack()
{
    Continue();
return;
}

void effect_increase_IAS::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(bonusIASString,bonusIAS);
    callBackEffBase->AppendFullRow(IASStacksString,IASStacks);
    callBackEffBase->ptrtoItem=this;
}

// effect_increase_damage
effect_increase_damage::effect_increase_damage()
{
percentageString="Increase %";
Name="Increase damage";
ID="effect_increase_damage";
disabled=0;
temporary=0;
percentage=25;
initRank=10;
}

effect_increase_damage* effect_increase_damage::getnewCopy()
{
return new effect_increase_damage(*this);
// How to use: effect_increase_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_increase_damage::Continue()
{
    InDamagePerCycle=InDamagePerCycle/100*(100+percentage);
    InDamageMagicPerCycle=InDamageMagicPerCycle/100*(100+percentage);
    InDamageNoReductPerCycle=InDamageNoReductPerCycle/100*(100+percentage);
}

void effect_increase_damage::DoDoubleAttack()
{
    Continue();
return;
}

void effect_increase_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(percentageString,percentage);
    callBackEffBase->ptrtoItem=this;
}

// effect_stat_steal_master
effect_stat_steal_master::effect_stat_steal_master()
{
ID="effect_stat_steal_master";
Name="Stat steal(Receive)";
initRank=-5;
disabled=0;
temporary=0;
duration=15;
durationString="Duration, sec.";
statsteal=6;
statstealString="Stats per hit";
mainStat=Strength;
statStrings[0] = "Strength";
statStrings[1] = "Agility";
statStrings[2] = "Intelligence";
rowName="Stat gain";
}

effect_stat_steal_master* effect_stat_steal_master::getnewCopy()
{
return new effect_stat_steal_master(*this);
// How to use: effect_stat_steal_master *tmpEff = &(baseEff->getnewCopy());
}

void effect_stat_steal_master::Continue()
{
    effect_stat_steal *newStat_Steal=new effect_stat_steal;
    attackEffects.push_back(reinterpret_cast<basic_effect *>(newStat_Steal));
    newStat_Steal->duration=duration;
    newStat_Steal->statsteal=statsteal;
    newStat_Steal->initRank=initRank;
    newStat_Steal->mainStat=mainStat;
    newStat_Steal->Init();
return;
}

void effect_stat_steal_master::DoDoubleAttack()
{
    Continue();
return;
}

void effect_stat_steal_master::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendCustomSelector(mainStat,3,rowName,statStrings);
    callBackEffBase->AppendFullRow(statstealString,statsteal);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->ptrtoItem=this;
}

// effect_stat_steal
effect_stat_steal::effect_stat_steal()
{
ID="effect_stat_steal";
Name="Stat steal(Receive)";
initRank=0;//Overwrited by master effect.
disabled=0;
temporary=1;
duration=0;//Overwrited by master effect.
statsteal=0;//Overwrited by master effect.
mainStat=Strength;//Overwrited by master effect.
}

effect_stat_steal* effect_stat_steal::getnewCopy()
{
return new effect_stat_steal(*this);
// How to use: effect_stat_steal *tmpEff = &(baseEff->getnewCopy());
}

void effect_stat_steal::Init()
{
    if (mainStat==Strength)
    {
        Attacker.changeSTR(statsteal);
    }
    else if (mainStat==Agility)
    {
        Attacker.changeAGI(statsteal);
        Frame1->recalculateAttackSpeed();
    }
    else
    {
        Attacker.changeINT(statsteal);
    }
    WhiteDmg=WhiteDmg+(statsteal);
return;
}

void effect_stat_steal::Continue()
{
    if (duration>currSingleAttackTime)
    {
        duration=duration-currSingleAttackTime;
	return;
    }
    else
    {
        if (mainStat==Strength)
        {
            Attacker.changeSTR(statsteal*-1);
        }
        else if (mainStat==Agility)
        {
            Attacker.changeAGI(statsteal*-1);
            Frame1->recalculateAttackSpeed();
        }
        else
        {
            Attacker.changeINT(statsteal*-1);
        }
        WhiteDmg=WhiteDmg-statsteal;
        disabled=1;
    }
return;
}

// effect_stat_steal_target_master
effect_stat_steal_target_master::effect_stat_steal_target_master()
{
ID="effect_stat_steal_target_master";
Name="Stat steal(Lose)";
initRank=-5;
disabled=0;
temporary=0;
duration=15;
durationString="Duration, sec.";
statsteal=2;
statstealString="Stats per hit";
}

effect_stat_steal_target_master* effect_stat_steal_target_master::getnewCopy()
{
return new effect_stat_steal_target_master(*this);
// How to use: effect_stat_steal_target_master *tmpEff = &(baseEff->getnewCopy());
}

void effect_stat_steal_target_master::Continue()
{
    effect_stat_steal_target *newStat_Steal=new effect_stat_steal_target;
    attackEffects.push_back(reinterpret_cast<basic_effect *>(newStat_Steal));
    newStat_Steal->duration=duration;
    newStat_Steal->statsteal=statsteal;
    newStat_Steal->initRank=initRank;
    newStat_Steal->Init();
return;
}

void effect_stat_steal_target_master::DoDoubleAttack()
{
    Continue();
return;
}

void effect_stat_steal_target_master::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(statstealString,statsteal);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->ptrtoItem=this;
}

// effect_stat_steal_target
effect_stat_steal_target::effect_stat_steal_target()
{
ID="effect_stat_steal_target";
Name="Stat steal(Lose)";
initRank=0;//Overwrited by master effect.
disabled=0;
temporary=1;
duration=0;//Overwrited by master effect.
statsteal=0;//Overwrited by master effect.
}

effect_stat_steal_target* effect_stat_steal_target::getnewCopy()
{
return new effect_stat_steal_target(*this);
// How to use: effect_stat_steal_target *tmpEff = &(baseEff->getnewCopy());
}

void effect_stat_steal_target::Init()
{
    Defender.changeSTR(statsteal*-1);
    Defender.changeAGI(statsteal*-1);
    Defender.changeINT(statsteal*-1);
return;
}

void effect_stat_steal_target::Continue()
{
    if (duration>currSingleAttackTime)
    {
        duration=duration-currSingleAttackTime;
	return;
    }
    else
    {
        Defender.changeSTR(statsteal);
        Defender.changeAGI(statsteal);
        Defender.changeINT(statsteal);
        disabled=1;
    }
return;
}

// effect_fury_swipes
effect_fury_swipes::effect_fury_swipes()
{
ID="effect_fury_swipes";
Name="Fury Swipes";
initRank=1;
disabled=0;
temporary=0;
damageType=Physical;
damage=30;
damageString="Damage";
duration=15;
durationString="Duration, sec.";
}

effect_fury_swipes* effect_fury_swipes::getnewCopy()
{
return new effect_fury_swipes(*this);
// How to use: effect_fury_swipes *tmpEff = &(baseEff->getnewCopy());
}

void effect_fury_swipes::Init()
{
    stacks=0;
return;
}

void effect_fury_swipes::Continue()
{
    double *damageOfType=checkDamageType();
    if (currSingleAttackTime>duration)
    {
        stacks=0;
    }
    stacks=stacks+1;
    *damageOfType=*damageOfType+damage*stacks;
return;
}

void effect_fury_swipes::DoDoubleAttack()
{
    double *damageOfType=checkDamageType();
    stacks=stacks+1;
    *damageOfType=*damageOfType+damage*stacks;
return;
}

void effect_fury_swipes::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->ptrtoItem=this;
}

// effect_poison
effect_poison::effect_poison()
{
ID="effect_poison";
Name="Poison";
initRank=1;
disabled=0;
temporary=0;
damageType=NoReduction;
damage=24;
damageString="Damage";
duration=15;
durationString="Duration, sec.";
interval=1;
intervalString="Damage interval";
}

effect_poison* effect_poison::getnewCopy()
{
return new effect_poison(*this);
// How to use: effect_poison *tmpEff = &(baseEff->getnewCopy());
}

void effect_poison::Init()
{
    damageBuffer=0;
    damageMultiplier=0;
    damagepool=(double)damage*duration/interval;
return;
}

void effect_poison::Continue()
{
    double *damageOfType=checkDamageType();
    speedRatio=currSingleAttackTime/interval;
    if (currSingleAttackTime>=duration)
    {
        *damageOfType=*damageOfType+damagepool;
return;
    }
    asynchronousAttacks=speedRatio+damageBuffer;
    damageBuffer=modf (asynchronousAttacks,&damageMultiplier);
    if (damageMultiplier!=0)
    {
        *damageOfType=*damageOfType+damage*damageMultiplier;
    }
return;
}

void effect_poison::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->AppendFullRow(intervalString,interval);
    callBackEffBase->ptrtoItem=this;
}

// effect_poison_stackable_master
effect_poison_stackable_master::effect_poison_stackable_master()
{
ID="effect_poison_stackable_master";
Name="Poison(stackable)";
disabled=0;
temporary=0;
initRank=1;
damageType=NoReduction;
damage=24;
damageString="Damage";
duration=15;
durationString="Duration, sec.";
interval=1;
intervalString="Damage interval";
}

effect_poison_stackable_master* effect_poison_stackable_master::getnewCopy()
{
return new effect_poison_stackable_master(*this);
// How to use: effect_poison_stackable_master *tmpEff = &(baseEff->getnewCopy());
}

void effect_poison_stackable_master::Continue()
{
    effect_poison_stackable *newPoison=new effect_poison_stackable;
    attackEffects.push_back(reinterpret_cast<basic_effect *>(newPoison));
    newPoison->damage=damage;
    newPoison->duration=duration;
    newPoison->interval=interval;
    newPoison->damageType=damageType;
    newPoison->initRank=initRank;
    newPoison->Init();
return;
}

void effect_poison_stackable_master::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->AppendFullRow(intervalString,interval);
    callBackEffBase->ptrtoItem=this;
}

// effect_poison_stackable
effect_poison_stackable::effect_poison_stackable()
{
ID="effect_poison_stackable";
Name="Poison(stackable element)";
disabled=0;
temporary=1;
initRank=0;//Overwrited by master effect.
damageType=Physical;//Overwrited by master effect.
damageMultiplier=0;
asynchronousAttacks=0;
damageBuffer=0;
damage=0;//Overwrited by master effect.
duration=0;//Overwrited by master effect.
interval=0;//Overwrited by master effect.
}

effect_poison_stackable* effect_poison_stackable::getnewCopy()
{
return new effect_poison_stackable(*this);
// How to use: effect_poison_stackable *tmpEff = &(baseEff->getnewCopy());
}

void effect_poison_stackable::Init()
{
    damageBuffer=0;
    damageMultiplier=0;
    asynchronousAttacks=0;
return;
}

void effect_poison_stackable::Continue()
{
    double *damageOfType=checkDamageType();
    speedRatio=currSingleAttackTime/interval;
    asynchronousAttacks=speedRatio+damageBuffer;
    damageBuffer=modf (asynchronousAttacks,&damageMultiplier);
    if (damageMultiplier!=0)
    {
        if (damageMultiplier>=duration)
        {
            if (duration!=0)
            {
                *damageOfType=*damageOfType+(damage*((double)duration/(double)interval));
            }
            disabled=1;
        }
        else if (damageMultiplier<duration)
        {
            *damageOfType=*damageOfType+(damage*damageMultiplier);
            duration=duration-damageMultiplier;
        }
    }
return;
}

// effect_poison_hppercent
effect_poison_hppercent::effect_poison_hppercent()
{
ID="effect_poison_hppercent";
Name="Poison(HP %)";
disabled=0;
temporary=0;
initRank=1;
damageMultiplier=0;
asynchronousAttacks=0;
damageBuffer=0;
damage=8;
damageString="Damage (HP %)";
duration=6;
durationString="Duration, sec.";
interval=1;
intervalString="Damage interval";
}

effect_poison_hppercent* effect_poison_hppercent::getnewCopy()
{
return new effect_poison_hppercent(*this);
// How to use: effect_poison_hppercent *tmpEff = &(baseEff->getnewCopy());
}

void effect_poison_hppercent::Init()
{
    damageBuffer=0;
    damageMultiplier=0;
    asynchronousAttacks=0;
return;
}

void effect_poison_hppercent::Continue()
{
    speedRatio=currSingleAttackTime/interval;
    if (currSingleAttackTime>=duration)
    {
        InDamageMagicPerCycle=InDamageMagicPerCycle+((double)Defender.HP/100*damage)*duration/interval;
    return;
    }
    if (currSingleAttackTime==interval)
    {
        InDamageMagicPerCycle=InDamageMagicPerCycle+((double)Defender.HP/100*damage);
    return;
    }
    asynchronousAttacks=speedRatio+damageBuffer;
    damageBuffer=modf (asynchronousAttacks,&damageMultiplier);
    if (damageMultiplier!=0)
    {
        InDamageMagicPerCycle=InDamageMagicPerCycle+((double)Defender.HP/100*damage)*damageMultiplier;
    }
return;
}

void effect_poison_hppercent::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->AppendFullRow(intervalString,interval);
    callBackEffBase->ptrtoItem=this;
}

// effect_double_attack
effect_double_attack::effect_double_attack()
{
ID="effect_double_attack";
Name="Double attack";
disabled=0;
temporary=0;
initRank=1;
cooldownString="Cooldown";
cooldown=3.0;
asynchronousAttacks=0;
}

effect_double_attack* effect_double_attack::getnewCopy()
{
return new effect_double_attack(*this);
// How to use: effect_double_attack *tmpEff = &(baseEff->getnewCopy());
}

void effect_double_attack::Init()
{
    asynchronousAttacks=cooldown;
}

void effect_double_attack::Continue()
{
    if (cooldown<=currSingleAttackTime)// If attacks are too long - don't bother with calculation.
    {
        DoDoubleHit=DoDoubleHit+1;
	return;
    }
    asynchronousAttacks=asynchronousAttacks+currSingleAttackTime;// Place current attack rate in the time buffer.
    if (asynchronousAttacks>=cooldown)// If any attacks are awaiting for release
    {
        asynchronousAttacks=0;
        DoDoubleHit=DoDoubleHit+1;
	return;
    }
}

void effect_double_attack::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(cooldownString,cooldown);
    callBackEffBase->ptrtoItem=this;
}

// effect_heartstopper_aura
effect_heartstopper_aura::effect_heartstopper_aura()
{
ID="effect_heartstopper_aura";
Name="Heartstopper aura(HP %)";
initRank=12; //Heartstopper aura cannot be boosted nor reduced by any other effects, so keep it 12(last) rank.
disabled=0;
temporary=0;
damageType=NoReduction;
damage=1.5;
damageString="Damage(HP %)";
interval=1;
intervalString="Damage interval";
}

effect_heartstopper_aura* effect_heartstopper_aura::getnewCopy()
{
return new effect_heartstopper_aura(*this);
// How to use: effect_heartstopper_aura *tmpEff = &(baseEff->getnewCopy());
}

void effect_heartstopper_aura::Init()
{
    damageBuffer=0;
    damageMultiplier=0;
return;
}

void effect_heartstopper_aura::Continue()
{
    double *damageOfType=checkDamageType();
    speedRatio=currSingleAttackTime/interval;
    asynchronousAttacks=speedRatio+damageBuffer;
    damageBuffer=modf (asynchronousAttacks,&damageMultiplier);
    if (damageMultiplier!=0)
    {
        *damageOfType=*damageOfType+(Defender.maxHP/100*damage)*damageMultiplier;
    }
return;
}

void effect_heartstopper_aura::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->AppendFullRow(intervalString,interval);
    callBackEffBase->ptrtoItem=this;
}

// effect_nethertoxin
effect_nethertoxin::effect_nethertoxin()
{
ID="effect_nethertoxin";
Name="Nethertoxin";
initRank=-3;
disabled=0;
temporary=0;
damageType=Physical;
baseDamage=10;
baseDamageString="Damage";
maxDamage=0;//Is changed in Continue() and FillPropertiesGrid();
}

effect_nethertoxin* effect_nethertoxin::getnewCopy()
{
return new effect_nethertoxin(*this);
// How to use: effect_nethertoxin *tmpEff = &(baseEff->getnewCopy());
}

void effect_nethertoxin::Continue()
{
    double *damageOfType=checkDamageType();
    double tmpDamage=baseDamage;
    double tmpParts=(double)Defender.HP/((double)Defender.maxHP/5); // We take the target's max health,
    //find it's 1/5th part, then divide current hp by it. This way we get, what the bonus damage will be.
    for (int i=5-tmpParts;i>0;i--)
    {
        tmpDamage=tmpDamage+tmpDamage;
    }
    *damageOfType=*damageOfType+(int)tmpDamage;
return;
}

void effect_nethertoxin::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    maxDamage=baseDamage*16;
    callBackEffBase->Clear();
    callBackEffBase->AppendDamageTypeSelector(damageType);
    callBackEffBase->AppendRow(baseDamageString);
    callBackEffBase->AppendCell(baseDamage);
    callBackEffBase->AppendCell(maxDamage);
    callBackEffBase->cellColumn--;
    callBackEffBase->AppendReadOnly();
    callBackEffBase->ptrtoItem=this;
}
