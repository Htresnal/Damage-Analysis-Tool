#include "Vectors.h"

extern int gamerule_HPPerStr, gamerule_MPPerInt, gamerule_StartHP, gamerule_StartMP, gamerule_StartIAS;
extern double gamerule_ArmorPerAgi, gamerule_HPRegenPerStr, gamerule_MPRegenPerInt;

extern std::string &ltrim(std::string &s);

baseUnit::baseUnit()
{
	ArmorPhysical=-1;
	MagicalResistance=25;
	AttackDamageMin=1;
	AttackDamageMax=1;
	AttackRate=1.700000;
	StatusHealth=gamerule_StartHP;
	StatusHealthRegen=gamerule_HPRegenPerStr;
	StatusMana=gamerule_StartMP;
	StatusManaRegen=gamerule_MPRegenPerInt;
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
    AttributePrimary="DOTA_ATTRIBUTE_STRENGTH";
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
	std::map<std::string,int *>::iterator itUnitDataMapI;
	std::map<std::string,std::string *>::iterator itUnitDataMapS;
	std::map<std::string,double *>::iterator itUnitDataMapD;
	unsigned spos, epos;
	int tmpI;
	std::string lineoutValue;
	double tempDouble;
	int nextHeroPos;
    while (!myfile.fail())
    {
        if (lineoutAttr.find_first_of('"')!=std::string::npos)
        {
            lineoutValue=lineoutAttr;
            spos=lineoutAttr.find_first_not_of('"');
            epos=lineoutAttr.find('"',spos);
            lineoutAttr=lineoutAttr.substr(spos,epos-(spos));
            itUnitDataMapI=unitDataMapI.begin();
            itUnitDataMapS=unitDataMapS.begin();
            itUnitDataMapD=unitDataMapD.begin();
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
                        tmpI=atoi(lineoutValue.c_str());
                        (*unitDataMapI[lineoutAttr])=tmpI;
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
        nextHeroPos=lineoutAttr.find("npc_dota_hero_");
        if (lineoutAttr.find("npc_dota_hero_")!=std::wstring::npos && nextHeroPos<=2)
        {
		break;
        }
    }
return;
}
