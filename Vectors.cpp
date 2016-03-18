#include "Vectors.h"

heroUnit *heroTemp;
extern std::string &ltrim(std::string &s);

baseUnit::baseUnit()
{
	ArmorPhysical=-1;
	MagicalResistance=25;
	AttackDamageMin=1;
	AttackDamageMax=1;
	AttackRate=1.700000;
	StatusHealth=180;
	StatusHealthRegen=0.250000;
	StatusMana=0;
	StatusManaRegen=0.010000;
	unitDataMapS["unitID"]=&unitID;
	unitDataMapS["unitName"]=&unitName;
	unitDataMapD["AttackRate"]=&AttackRate;
	unitDataMapD["StatusHealthRegen"]=&StatusHealthRegen;
	unitDataMapD["StatusManaRegen"]=&StatusManaRegen;
	unitDataMapI["ArmorPhysical"]=&ArmorPhysical;
	unitDataMapI["MagicalResistance"]=&MagicalResistance;
	unitDataMapI["AttackDamageMin"]=&AttackDamageMin;
	unitDataMapI["AttackDamageMax"]=&AttackDamageMax;
	unitDataMapI["StatusHealth"]=&StatusHealth;
	unitDataMapI["StatusMana"]=&StatusMana;
}

heroUnit::heroUnit()
{

    MagicalResistance=25;
    AttributePrimary="DOTA_ATTRIBUTE_STRENGHT";
	AttributeBaseStrength=0;
	AttributeStrengthGain=0.0;
	AttributeBaseIntelligence=0;
	AttributeIntelligenceGain=0.0;
	AttributeBaseAgility=0;
	AttributeAgilityGain=0.0;
	unitDataMapS["AttributePrimary"]=&AttributePrimary;
	unitDataMapD["AttributeStrengthGain"]=&AttributeStrengthGain;
	unitDataMapD["AttributeIntelligenceGain"]=&AttributeIntelligenceGain;
	unitDataMapD["AttributeAgilityGain"]=&AttributeAgilityGain;
	unitDataMapI["AttributeBaseStrength"]=&AttributeBaseStrength;
	unitDataMapI["AttributeBaseIntelligence"]=&AttributeBaseIntelligence;
	unitDataMapI["AttributeBaseAgility"]=&AttributeBaseAgility;
}

void baseUnit::loadUnitFromStream(std::fstream &myfile, std::string &lineoutAttr)
{
while (!myfile.fail())
{
    if (lineoutAttr.find_first_of('"')!=std::string::npos)
    {
        unsigned spos, epos;
        int tempInt;
        std::string lineoutValue, tempString;
        lineoutValue=lineoutAttr;
        double tempDouble;
        spos=lineoutAttr.find_first_not_of('"');
        epos=lineoutAttr.find('"',spos);
        lineoutAttr=lineoutAttr.substr(spos,epos-(spos));
        std::map<std::string,int*>::iterator itUnitDataMapI=unitDataMapI.begin();;
        std::map<std::string,std::string*>::iterator itUnitDataMapS=unitDataMapS.begin();;
        std::map<std::string,double*>::iterator itUnitDataMapD=unitDataMapD.begin();;
        if (lineoutValue.find('"',epos+1)!=std::string::npos)
        {
            spos=lineoutValue.find('"');
            spos=lineoutValue.find('"',spos+1);
            if (lineoutValue.find('"',spos+1)!=std::string::npos)
            {
                spos=lineoutValue.find('"',spos+1);
                epos=lineoutValue.find('"',spos+1);
                lineoutValue=lineoutValue.substr(spos+1,epos-(spos+1));
                itUnitDataMapI=unitDataMapI.find(lineoutAttr);
                if (itUnitDataMapI!=unitDataMapI.end())
                {
                    tempInt=atoi(lineoutValue.c_str());
                    (*unitDataMapI[lineoutAttr])=tempInt;
                }
                itUnitDataMapS=unitDataMapS.find(lineoutAttr);
                if (itUnitDataMapS!=unitDataMapS.end())
                {
                    (*unitDataMapS[lineoutAttr])=lineoutValue;
                }
                itUnitDataMapD=unitDataMapD.find(lineoutAttr);
                if (itUnitDataMapD!=unitDataMapD.end())
                {
                    tempDouble=atof(lineoutValue.c_str());
                    (*unitDataMapD[lineoutAttr])=tempDouble;
                }
            }
        }

    }
std::getline(myfile,lineoutAttr);
ltrim(lineoutAttr);
int nextHeroPos=lineoutAttr.find("npc_dota_hero_");
if (lineoutAttr.find("npc_dota_hero_")!=std::wstring::npos && nextHeroPos<=2)
{
    return;
}
}
return;
}
