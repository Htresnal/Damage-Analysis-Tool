#include "heroDataLoad.h"

std::vector<heroUnit> heroVector;

char heroPath[]="npc_heroes.txt";
char namesPath[]="dota_english.txt";
std::string &ltrim(std::string &s)
{
s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
return s;
}

bool exists_test3 (const std::string& name)
{
struct stat buffer;
return (stat (name.c_str(), &buffer) == 0);
}

int heroDataLoad()
{
if (!exists_test3(heroPath))
{
    return 1;
}
heroVector.resize(0);
heroLoadFile(heroVector);
return 0;
}

void heroLoadFile(std::vector<heroUnit> &heroVector)
{
std::string lineout, lineout2, lineout3;
std::fstream myfile(heroPath);
std::getline(myfile,lineout);
if (!myfile.good())
{
    return;
}
while (lineout.find("npc_dota_hero_")==std::string::npos && !myfile.fail())
{
    std::getline(myfile,lineout);
    ltrim(lineout);
}
unsigned spos,epos;
while (!myfile.fail())
{
if (lineout.find("npc_dota_hero_")!=std::string::npos)
{
    heroUnit newheroUnit;
    spos=lineout.find("npc_dota_hero_");
    epos=lineout.find('"',spos);
    newheroUnit.unitID=lineout.substr(spos,epos-(spos));
    newheroUnit.loadUnitFromStream(myfile,lineout);
    heroVector.push_back(newheroUnit);
}
}
std::fstream myfile2;
myfile2.open(namesPath);
while (std::getline(myfile2,lineout,'\n') && !myfile2.fail())
{
    for (int i=0;i<lineout.length();i++)
    {
        if (lineout[i]!=0x00)
        {
            lineout2.push_back(lineout[i]);
        }
    }
    if (lineout2.find("\"npc_dota_hero_")!=std::string::npos)
    {
        for (int i=0;i<heroVector.size();i++)
        {
            lineout3='"'+heroVector[i].unitID+'"';
            if (lineout2.find(lineout3)!=std::string::npos)
            {
                spos=lineout2.find(lineout3);
                spos=spos+lineout3.size();
                spos=lineout2.find_first_of('"',spos);
                ++spos;
                epos=lineout2.find_first_of('"',spos);
                lineout3=lineout2.substr(spos,epos-spos);
                heroVector[i].unitName=lineout3;
            }
        }
    }
lineout2="";
}
}
