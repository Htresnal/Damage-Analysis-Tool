#ifndef VECTORS_H
#define VECTORS_H

#include "commonIncludes.h"

class baseUnit
{
public:
    std::string unitID;
    std::string unitName;
	int ArmorPhysical;
	int MagicalResistance;
	int	AttackDamageMin;
	int	AttackDamageMax;
	double	AttackRate;
	int StatusHealth;
	double StatusHealthRegen;
	int StatusMana;
	double StatusManaRegen;
	int * tempInt;
	double * tempDouble;
	std::string * tempString;
	std::map<std::string,int *>unitDataMapI;
	std::map<std::string,double *>unitDataMapD;
	std::map<std::string,std::string *>unitDataMapS;
    virtual void loadUnitFromStream(std::fstream &, std::string &);
    baseUnit();
};

class heroUnit : public baseUnit
{
public:
    std::string AttributePrimary;
	int	AttributeBaseStrength;
	double AttributeStrengthGain;
	int AttributeBaseIntelligence;
	double AttributeIntelligenceGain;
	int AttributeBaseAgility;
	double AttributeAgilityGain;
    heroUnit();
};

#endif
