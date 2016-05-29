#include "GameSettings.h"

extern std::string gameRulePath;

int gamerule_HPPerStr, gamerule_MPPerInt, gamerule_StartHP, gamerule_StartMP, gamerule_StartIAS;
double gamerule_ArmorPerAgi, gamerule_HPRegenPerStr, gamerule_MPRegenPerInt;

extern std::string &ltrim(std::string &s);
bool exists_test3 (const std::string& name);

//(*InternalHeaders(GameSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GameSettings)
const long GameSettings::ID_GRID1 = wxNewId();
//*)

class cellDataObject
{
public:
    unsigned *U;
    int *I;
    double *D;
    wxString type;
    cellDataObject(unsigned &data) : U(&data), type(_("U")) {}  //Unsigned ints
    cellDataObject(int &data) : I(&data), type(_("I")) {}       //Ints
    cellDataObject(double &data) : D(&data), type(_("D")) {}    //Doubles
};

BEGIN_EVENT_TABLE(GameSettings,wxFrame)
	//(*EventTable(GameSettings)
	//*)
END_EVENT_TABLE()

GameSettings::GameSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(GameSettings)
	Create(parent, id, _("Game engine settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(390,248));
	Move(wxDefaultPosition);
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	Grid1 = new wxGrid(this, ID_GRID1, wxPoint(144,272), wxSize(232,450), 0, _T("ID_GRID1"));
	Grid1->CreateGrid(0,1);
	Grid1->EnableEditing(true);
	Grid1->EnableGridLines(true);
	Grid1->SetRowLabelSize(130);
	Grid1->SetDefaultColSize(289, true);
	Grid1->SetColLabelValue(0, _("Value"));
	Grid1->SetDefaultCellFont( Grid1->GetFont() );
	Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );

	Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&GameSettings::OnSettingsGrid1CellChange);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&GameSettings::OnClose);
	//*)

	wxGridCellEditor *tmpEditor;
	cellDataObject *tmpDataObj;
    Grid1->AppendRows(1,true);

	tmpEditor=new wxGridCellNumberEditor;
    tmpDataObj=new cellDataObject(gamerule_StartHP);
    tmpDataObj->type=_("I");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Starting health");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::Format(wxT("%i"),gamerule_StartHP),Grid1->GetNumberRows()-1,0);

    Grid1->AppendRows(1,true);

	tmpEditor=new wxGridCellNumberEditor;
    tmpDataObj=new cellDataObject(gamerule_StartMP);
    tmpDataObj->type=_("I");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Starting mana");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::Format(wxT("%i"),gamerule_StartMP),Grid1->GetNumberRows()-1,0);

	Grid1->AppendRows(1,true);

	tmpEditor=new wxGridCellNumberEditor;
    tmpDataObj=new cellDataObject(gamerule_StartIAS);
    tmpDataObj->type=_("I");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Starting IAS");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::Format(wxT("%i"),gamerule_StartIAS),Grid1->GetNumberRows()-1,0);

	Grid1->AppendRows(1,true);

	Grid1->SetReadOnly(Grid1->GetNumberRows()-1,0,true);
	Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1," ");

    Grid1->AppendRows(1,true);

    tmpEditor=new wxGridCellNumberEditor;
    tmpDataObj=new cellDataObject(gamerule_HPPerStr);
    tmpDataObj->type=_("I");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Health per STR");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::Format(wxT("%i"),gamerule_HPPerStr),Grid1->GetNumberRows()-1,0);

    Grid1->AppendRows(1,true);

    tmpEditor=new wxGridCellFloatEditor;
    tmpDataObj=new cellDataObject(gamerule_HPRegenPerStr);
    tmpDataObj->type=_("D");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Health regen per STR");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::FromDouble(gamerule_HPRegenPerStr,2),Grid1->GetNumberRows()-1,0);

    Grid1->AppendRows(1,true);

    tmpEditor=new wxGridCellFloatEditor;
    tmpDataObj=new cellDataObject(gamerule_ArmorPerAgi);
    tmpDataObj->type=_("D");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Armor per AGI");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::FromDouble(gamerule_ArmorPerAgi,2),Grid1->GetNumberRows()-1,0);

    Grid1->AppendRows(1,true);

    tmpEditor=new wxGridCellNumberEditor;
    tmpDataObj=new cellDataObject(gamerule_MPPerInt);
    tmpDataObj->type=_("I");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Mana per INT");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::Format(wxT("%i"),gamerule_MPPerInt),Grid1->GetNumberRows()-1,0);

    Grid1->AppendRows(1,true);

    tmpEditor=new wxGridCellFloatEditor;
    tmpDataObj=new cellDataObject(gamerule_MPRegenPerInt);
    tmpDataObj->type=_("D");
    tmpEditor->SetClientData(&(*tmpDataObj));
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,"Mana regen per INT");
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,0,&(*tmpEditor));
    Grid1->SetCellValue(wxString::FromDouble(gamerule_MPRegenPerInt,2),Grid1->GetNumberRows()-1,0);
}

GameSettings::~GameSettings()
{
	//(*Destroy(GameSettings)
	//*)
}

void GameSettings::OnSettingsGrid1CellChange(wxGridEvent& event)
{
    wxGridCellEditor *tmpEditor=Grid1->GetCellEditor(event.GetRow(),event.GetCol());
    tmpEditor->DecRef();
    cellDataObject *tmpDataObject=reinterpret_cast<cellDataObject *>(tmpEditor->GetClientData());
    if (tmpDataObject->type.IsSameAs(_("I"),true))
    {
        (*tmpDataObject->I)=wxAtoi(tmpEditor->GetValue());
    }
    else if (tmpDataObject->type.IsSameAs(_("D"),true))
    {
        (tmpEditor->GetValue()).ToDouble(tmpDataObject->D);
    }
    else if (tmpDataObject->type.IsSameAs(_("U"),true))
    {
        (*tmpDataObject->U)=wxAtoi(tmpEditor->GetValue());
    }
    SaveChangestoFile(gameRulePath);
}

void GameSettings::OnClose(wxCloseEvent& event)
{
    Hide();
}

std::map<std::string,double*>gamerulesDataMapD=
    {
    {"gamerule_ArmorPerAgi",&gamerule_ArmorPerAgi},
    {"gamerule_HPRegenPerStr", &gamerule_HPRegenPerStr},
    {"gamerule_MPRegenPerInt", &gamerule_MPRegenPerInt}
    };

std::map<std::string,int*>gamerulesDataMapI=
    {
    {"gamerule_StartIAS", &gamerule_StartIAS},
    {"gamerule_HPPerStr", &gamerule_HPPerStr},
    {"gamerule_MPPerInt", &gamerule_MPPerInt},
    {"gamerule_StartHP", &gamerule_StartHP},
    {"gamerule_StartMP", &gamerule_StartMP}
    };

/*
gamerulesDataMapD["gamerule_ArmorPerAgi"]=&gamerule_ArmorPerAgi;
gamerulesDataMapD["gamerule_HPRegenPerStr"]=&gamerule_HPRegenPerStr;
gamerulesDataMapD["gamerule_MPRegenPerInt"]=&gamerule_MPRegenPerInt;
gamerulesDataMapI["gamerule_StartIAS"]=&gamerule_StartIAS;
gamerulesDataMapI["gamerule_HPPerStr"]=&gamerule_HPPerStr;
gamerulesDataMapI["gamerule_MPPerInt"]=&gamerule_MPPerInt;
gamerulesDataMapI["gamerule_StartHP"]=&gamerule_StartHP;
gamerulesDataMapI["gamerule_StartMP"]=&gamerule_StartMP;
*/

void GetGameRules()
{
    if (!exists_test3(gameRulePath))
    {
        wxMessageBox(_("[FILE][NOT FOUND]: DamageAnalysis_settings.txt not found. Creating new default config. Applying default settings."),_("Failed to find file"));
        ApplyDefaultRules();
        SaveChangestoFile(gameRulePath);
        return;
    }
    std::string lineout;
    std::fstream myfile(gameRulePath);
    if (!myfile.good())
    {
        wxMessageBox(_("[FILE][CORRUPT]: DamageAnalysis_settings.txt failed to load. Please, remove to acquire default config, or replace with correct one. Applying default settings."),_("Failed to load file"));
        ApplyDefaultRules();
        return;
    }
    while (!myfile.fail())
    {
        std::getline(myfile,lineout);
        if (lineout.find_first_of('"')!=std::string::npos)
        {
            std::string lineoutValue;
            lineoutValue=lineout;
            unsigned spos=lineout.find_first_not_of('"');
            unsigned epos=lineout.find('"',spos);
            lineout=lineout.substr(spos,epos-spos);
            std::map<std::string,int *>::iterator itgamerulesDataMapI=gamerulesDataMapI.begin();
            std::map<std::string,double *>::iterator itgamerulesDataMapD=gamerulesDataMapD.begin();
            spos=lineoutValue.find('"',epos+1);
            if (lineoutValue.find('"',epos+1)!=std::string::npos)
            {
                epos=lineoutValue.find('"',spos+1);
                if (lineoutValue.find('"',spos+1)!=std::string::npos)
                {
                    lineoutValue=lineoutValue.substr(spos+1,epos-(spos+1));
                    itgamerulesDataMapI=gamerulesDataMapI.find(lineout);
                    if (itgamerulesDataMapI!=gamerulesDataMapI.end())
                    {
                        (*gamerulesDataMapI[lineout])=atoi(lineoutValue.c_str());
                    }
                    itgamerulesDataMapD=gamerulesDataMapD.find(lineout);
                    if (itgamerulesDataMapD!=gamerulesDataMapD.end())
                    {
                        (*gamerulesDataMapD[lineout])=atof(lineoutValue.c_str());
                    }
                }
            }
        }
    }
}

void SaveChangestoFile(const std::string path)
{
    std::ofstream myfile(path);
    for(std::map<std::string, int *>::const_iterator it = gamerulesDataMapI.begin(); it != gamerulesDataMapI.end(); it++)
    {
        myfile<<"\""<<it->first<<"\" \""<<*(it->second)<<"\""<<std::endl;
    }
    myfile<<std::endl;
    for(std::map<std::string, double *>::const_iterator it = gamerulesDataMapD.begin(); it != gamerulesDataMapD.end(); it++)
    {
        myfile<<"\""<<it->first<<"\" \""<<*(it->second)<<"\""<<std::endl;
    }
    return;
}

void ApplyDefaultRules()
{
    gamerule_HPPerStr=20;
    gamerule_MPPerInt=12;
    gamerule_StartHP=200;
    gamerule_StartMP=50;
    gamerule_StartIAS=100;
    gamerule_ArmorPerAgi=0.14;
    gamerule_HPRegenPerStr=0.03;
    gamerule_MPRegenPerInt=0.04;
    return;
}
