#ifndef HERODATALOAD_H
#define HERODATALOAD_H

#include "Vectors.h"

std::string &ltrim(std::string &);
void heroLoadFile(std::array<heroUnit, HERO_COUNT> &);
bool exists_test3 (const std::string&);
int heroDataLoad();
void heroLoadFile(std::array<heroUnit, HERO_COUNT> &);

#endif
