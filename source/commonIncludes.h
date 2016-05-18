#ifndef COMMONINCLUDES_H
#define COMMONINCLUDES_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <map>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <locale.h>
#include <sstream>
#include <cstring>
#include <wctype.h>
#include <cstdio>
#include <ios>

#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <cstdlib>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/app.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/snglinst.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/utils.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/textentry.h>
#include <wx/valnum.h>
#include "wx/grid.h"
#include "wx/laywin.h"
#include <wx/config.h>

#include <wx/msgdlg.h>
#include <wx/textctrl.h>
#include <wx/event.h>
#include <wx/kbdstate.h>
#include <wx/valtext.h>
#include <wx/gdicmn.h>
#include <math.h>
#include <list>

enum DamageEnum
{
    Physical,Magic,NoReduction
};

enum StatTypes
{
    Strenght,Agility,Intelligence,AllStats
};

#endif
