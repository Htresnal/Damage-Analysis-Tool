#ifndef HERODATA_H
#define HERODATA_H

#include "commonIncludes.h"
#include "DamageAnalysisMain.h"
#include "Vectors.h"

class hero
{
public:
    unsigned Level;
    int HP, MP;
    double statstr, statagi, statint;
    int statstrReal, statagiReal, statintReal;
    void setSTR(unsigned );
    void setAGI(unsigned );
    void setINT(unsigned );
    void changeSTR(double );
    void changeAGI(double );
    void changeINT(double );
    int changeStat(double &,int &,double );
    void fillFromUI();
    virtual void recalcStat(StatTypes ,double );
    unsigned getSTR();
    unsigned getAGI();
    unsigned getINT();
};

class hero_Defender : public hero
{
public:
    int maxHP, maxMP;
    double HPRegen, MPRegen, MPRegenBonus, MPRegenMultiplier, armor, magicResist;
    wxString durationString;
    hero_Defender();
    void recalcStat(StatTypes ,double );
    void fillFromUI();
};

class hero_Attacker : public hero
{
public:
    double IAS, BATD;
    hero_Attacker();
    StatTypes mainStat;
    void recalcStat(StatTypes ,double );
    void fillFromUI();
};
#endif
