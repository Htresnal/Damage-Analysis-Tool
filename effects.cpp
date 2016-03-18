/*
В Init() должны помещаться функции, которые включаются один раз -
- перед инициализацией цикла Continue(), влияющие на базовые
параметры(например, добавление количества брони, статов,
,скорости атаки, глобальные ауры и т.д.). В этом разделе НЕ должно быть
ничего, что не соответствует прямому таймлайну эмуляции, т.к. instance
Continue() будет включен сразу после Init().
В Init() лучше помещать обновление необходимых в работе переменных.
В цикле Continue() должны работать эффекты, имеющие продолжительное
динамическое поведение, например: minus armor per hit, или minus to
stats per hit.
Если скилл использует параметры, которые могут меняться с каждым
проходом Continue(), такие как скорость атаки, максимальное здоровье
и т.д., то необходимо обязательно переинициализировать внутриклассовые
переменные, основанные на них.
Ранги эффектов:
maxRanks=12; // ___ Максимальный уровень ранков.
minRanks=-5; // ___ Минимальный уровень ранков. Эффекты с ранком -5
будут применены первее, максимальный ранк будет применён позднее.
Например, критический удар или щит маны должны срабатывать раньше, чем
будут рассчитаны иные повреждения, и сопротивления.
Все повреждающие и защищающие эффекты с ранком ниже 0 могут взаимовлиять,
т.к. используют общую переменную для рассчётов повреждения, усиляя
следующий предыдущим.
*/

#include "effects.h"

// ___ Global Vectors
std::vector<basic_effect *> attackEffects;
std::vector<basic_effect *> defenceEffects;
std::vector<effect_critical_damage> critEffects;
std::vector<effect_block_damage> shieldBlockEffects;

extern double  ARReduct, InDamageBase, InDamage, InDamageRaw, InDamageMagic, InDamageNoReduct, aps, attackPerSecondPart, magicResist, InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle;
extern double addWhiteDmg;
extern int statstr, statint, statagi, HP, MP, DoDoubleHit, armor;

// EFFECT MAP EFFECT MAP EFFECT MAP EFFECT MAP EFFECT MAP EFFECT MAP

	std::map<std::string,basic_effect *> effectMapAttack=
	{
    {"effect_critical_damage", new effect_critical_damage},
    {"effect_poison", new effect_poison},
    {"effect_double_attack", new effect_double_attack}
    };

	std::map<std::string,basic_effect *> effectMapDefense=
	{
    {"effect_block_damage", new effect_block_damage}
    };
	//(*unitDataMapD[lineoutAttr])=tempDouble;

/*
    attackEffectsCtrl->InsertColumn(0, L"Effect", wxLIST_FORMAT_LEFT, 215);

    effect_double_attack doubleAttackTmp(1,2.0);
    //effectTmp=&attackEffects[0];
    attackEffects.push_back(doubleAttackTmp);
    //attackEffectsChoice->Append("Double attack",effectTmp);
    attackEffectsChoice->Append("Double attack");

        attackEffectsCtrl->InsertItem(wxNewId(), L"SomeEffect", -1);
    wxListItem myEffect;
    myEffect.SetText(_("Double attack"));
    myEffect.SetId(wxNewId());
    myEffect.SetImage(0);
    myEffect.SetColumn(1);
    attackEffectsCtrl->SetItem(myEffect);
*/
    //effectTmp=(basic_effect *)attackEffectsChoice->GetClientData(attackEffectsChoice->GetSelection());
// basic_effect
basic_effect::basic_effect()
{
ID="basic_effect";
Name="Basic effect";
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

// effect_critical_damage
effect_critical_damage::effect_critical_damage()
{
chanceString="Chance";
damageString="Damage";
Name="Critical hit";
ID="effect_critical_damage";
initRank=1;
chance=30;
damage=220;
}

effect_critical_damage* effect_critical_damage::getnewCopy()
{
return new effect_critical_damage(*this);
// How to use: effect_critical_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_critical_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(chanceString,chance);
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->ptrtoItem=&(*this);
}

void effect_critical_damage::Continue()
{
    InDamagePerCycle=InDamagePerCycle+(((InDamageBase/100*damage)-InDamageBase)/100*chance);
    InDamageRaw=InDamageRaw+(((InDamageBase/100*damage)-InDamageBase)/100*chance);
}

void effect_critical_damage::DoDoubleAttack()
{
    Continue();
    return;
}

// effect_block_damage
effect_block_damage::effect_block_damage()
{
chanceString="Chance";
blockString="Block damage";
Name="Block damage";
ID="effect_block_damage";
chance=53;
block=20;
initRank=1;
}

effect_block_damage* effect_block_damage::getnewCopy()
{
return new effect_block_damage(*this);
// How to use: effect_block_damage *tmpEff = &(baseEff->getnewCopy());
}

void effect_block_damage::Continue()
{

}

void effect_block_damage::DoDoubleAttack()
{
    Continue();
    return;
}

void effect_block_damage::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(chanceString,chance);
    callBackEffBase->AppendFullRow(blockString,block);
    callBackEffBase->ptrtoItem=&(*this);
}

// effect_poison
effect_poison::effect_poison()
{
ID="effect_poison";
Name="Poison";
initRank=1;
damageMultiplier=0;
asynchronousAttacks=0;
damageBuffer=0;
damage=24;
damageString="Damage";
duration=15;
durationString="Duration";
iterspeed=1;
iterspeedString="Damage ratio";
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
    asynchronousAttacks=0;
    speedRatio=attackPerSecondPart/iterspeed;
    nozzle=(double)damage/iterspeed;
    damagepool=(double)damage*duration/iterspeed;
    return;
}

void effect_poison::Continue()
{
    if (attackPerSecondPart>=duration)
    {
        InDamageNoReductPerCycle=InDamageNoReductPerCycle+damagepool;
        InDamageRaw=InDamageRaw+damagepool;
    return;
    }
    if (attackPerSecondPart==iterspeed)
    {
        InDamageNoReductPerCycle=InDamageNoReductPerCycle+nozzle;
        InDamageRaw=InDamageRaw+nozzle;
    return;
    }
    asynchronousAttacks=speedRatio+damageBuffer;
    damageBuffer=modf (asynchronousAttacks,&damageMultiplier);
    if (damageMultiplier==0)
    {
        InDamageNoReductPerCycle=InDamageNoReductPerCycle+damage;
        InDamageRaw=InDamageRaw+damage;
    }
    else
    {
        InDamageNoReductPerCycle=InDamageNoReductPerCycle+(damage*(1+damageMultiplier));
        InDamageRaw=InDamageRaw+(damage*(1+damageMultiplier));
    }
return;
}

void effect_poison::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(damageString,damage);
    callBackEffBase->AppendFullRow(durationString,duration);
    callBackEffBase->AppendFullRow(iterspeedString,iterspeed);
    callBackEffBase->ptrtoItem=&(*this);
}

// effect_double_attack
effect_double_attack::effect_double_attack()
{
ID="effect_double_attack";
Name="Double attack";
cooldownString="Cooldown";
cooldown=3.0;
initRank=1;
asynchronousAttacks=0;
}

effect_double_attack* effect_double_attack::getnewCopy()
{
return new effect_double_attack(*this);
// How to use: effect_double_attack *tmpEff = &(baseEff->getnewCopy());
}

void effect_double_attack::Init()
{
    asynchronousAttacks=0;
}

void effect_double_attack::Continue()
{
if (cooldown<=attackPerSecondPart)
{
    return;
}
asynchronousAttacks=asynchronousAttacks+attackPerSecondPart;
if (asynchronousAttacks<cooldown)
{
    return;
}
else
{
    asynchronousAttacks=asynchronousAttacks-cooldown;
    DoDoubleHit=1;
    return;
}
}

void effect_double_attack::DoDoubleAttack()
{
DoDoubleHit=0;
return;
}

void effect_double_attack::FillPropertiesGrid(effectsProperties *callBackEffBase)
{
    callBackEffBase->Clear();
    callBackEffBase->AppendFullRow(cooldownString,cooldown);
    callBackEffBase->ptrtoItem=&(*this);
}

/*
    for (unsigned i;i<attackEffects.size();i++)
    {
        if (attackEffects[i]->index==index)
        {
            attackEffects.erase(attackEffects.begin()+i);
            break;
        }
    }
    delete this;
*/
