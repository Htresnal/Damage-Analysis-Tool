/**
Stats can't be less than 0. To avoid that, I save all stats that go lower than 0 to statReal. Any changes should be
done with "set", "change" and "get":
set - overrides stats, and is only supposed to be used by the start phase of analysis. Will not take numbers less than 0;
change - Allows user to manipulate stats, increase or decrease it, by passing positive or negative values.
get - Reads stat value(will return 0 if statReal is less than 0).

How to use:
setSTR(8); - now we have 8 str stat.
changeSTR(-20); - now we have 0 at str stat, and -12 at the statReal.
changeSTR(40); - now we have 28 str stat, and 0 at the statReal.

Hero class is basically just a variable wearing dummy, thus should not cause any problems with calls
to the "outside world". The only dependence is the existence of heroUnit class objects, since it needs
basic stat data and stat growth data.
*/

#include "heroData.h"

extern int gamerule_HPPerStr, gamerule_MPPerInt, gamerule_StartHP, gamerule_StartMP, gamerule_StartIAS;
extern double gamerule_ArmorPerAgi, gamerule_HPRegenPerStr, gamerule_MPRegenPerInt;

extern DamageAnalysisFrame *Frame;

heroUnit *heroTemp;
heroUnit *heroAttTemp;

unsigned hero::getSTR()
{
return statstr;
}
unsigned hero::getAGI()
{
return statagi;
}
unsigned hero::getINT()
{
return statint;
}

void hero::setSTR(unsigned newStat)
{
    statstr=newStat;
    statstrReal=0;
return;
}

void hero::setAGI(unsigned newStat)
{
    statagi=newStat;
    statagiReal=0;
return;
}

void hero::setINT(unsigned newStat)
{
    statint=newStat;
    statintReal=0;
return;
}

void hero::changeSTR(double bonusStat)
{
    recalcStat(Strength, (double)changeStat(statstr, statstrReal, bonusStat));
return;
}
void hero::changeAGI(double bonusStat)
{
    recalcStat(Agility, (double)changeStat(statagi, statagiReal, bonusStat));
return;
}
void hero::changeINT(double bonusStat)
{
    recalcStat(Intelligence, (double)changeStat(statint, statintReal, bonusStat));
return;
}

int hero::changeStat(double &Stat, int &StatReal, double newStat)
{
    int tmpStat=Stat;
    Stat=Stat+newStat;
    if (Stat<0)
    {
        StatReal=StatReal+Stat;
        Stat=0;
    }
    else if (StatReal<0 && Stat>0)
    {
        Stat=Stat+StatReal;
        if (Stat<0)
        {
            StatReal=Stat;
            Stat=0;
        }
        else
        {
            StatReal=0;
        }
    }
    if (newStat<0)
    {
	return (Stat==0?(tmpStat*-1):newStat);
    }
    else
    {
	return (Stat-tmpStat);
    }
}

void hero::recalcStat(StatTypes checkStat, double bonusStat)
{
return;
}

void hero::fillFromUI()
{
return;
}

//////////////////////////////////////////////DEFENDER/////////////////////////////////////////////
hero_Defender::hero_Defender()
{

}

void hero_Defender::recalcStat(StatTypes checkStat, double bonusStat)
{
    if (checkStat==Strength)
    {
        int myTMPHP=maxHP;
        maxHP=maxHP+gamerule_HPPerStr*bonusStat;
        HP=(double)HP/myTMPHP*maxHP;
        HPRegen=HPRegen+gamerule_HPRegenPerStr*bonusStat;
    }
    else if (checkStat==Agility)
    {
        armor=armor+gamerule_ArmorPerAgi*bonusStat;
    }
    else if (checkStat==Intelligence && bonusStat!=0)
    {
        int myTMPMP=maxMP;
        maxMP=maxMP+gamerule_MPPerInt*bonusStat;
        MP=(double)MP/myTMPMP*maxMP;
        MPRegen=MPRegen+gamerule_MPRegenPerInt*bonusStat;
    }
return;
}

void hero_Defender::fillFromUI()
{
    Level=wxAtoi(Frame->LevelInput->GetValue());
    setSTR(wxAtoi(Frame->StatStrInput->GetValue()));
    maxHP=HP=wxAtoi(Frame->StatHPInput->GetValue());
    HPRegen=wxAtof(Frame->StatHPRegenInput->GetValue());
    setAGI(wxAtoi(Frame->StatAgiInput->GetValue()));
    armor=wxAtof(Frame->ArmorInput->GetValue());
    setINT(wxAtoi(Frame->StatIntInput->GetValue()));
    maxMP=MP=wxAtoi(Frame->StatMPInput->GetValue());
    MPRegen=wxAtof(Frame->StatMPRegenInput->GetValue());
    magicResist=wxAtoi(Frame->MagicResistanceInput->GetValue());
return;
}

//////////////////////////////////////////////ATTACKER/////////////////////////////////////////////
hero_Attacker::hero_Attacker()
{

}

void hero_Attacker::recalcStat(StatTypes checkStat, double bonusStat)
{
    if (checkStat==Strength)
    {
        HP=HP+gamerule_HPPerStr*bonusStat;
    }
    else if (checkStat==Agility)
    {
        IAS=IAS+bonusStat; // ___ 1 AGI = 1 IAS
    }
    else if (checkStat==Intelligence)
    {
        MP=MP+gamerule_MPPerInt*bonusStat;
    }
return;
}

void hero_Attacker::fillFromUI()
{
    Level=wxAtoi(Frame->LevelInput2->GetValue());
    if (heroAttTemp->AttributePrimary=="DOTA_ATTRIBUTE_STRENGTH")
    {
        mainStat=Strength;
    }
    else if (heroAttTemp->AttributePrimary=="DOTA_ATTRIBUTE_AGILITY")
    {
        mainStat=Agility;
    }
    else
    {
        mainStat=Intelligence;
    }
    setSTR(wxAtoi(Frame->StatStrInput2->GetValue()));
    HP=wxAtoi(Frame->StatHPInput2->GetValue());
    setAGI(wxAtoi(Frame->StatAgiInput2->GetValue()));
    IAS=wxAtoi(Frame->AttackSpeedInput->GetValue());
    setINT(wxAtoi(Frame->StatIntInput2->GetValue()));
    MP=wxAtoi(Frame->StatMPInput2->GetValue());
    BATD=wxAtof(Frame->BATInput->GetValue());
return;
}
