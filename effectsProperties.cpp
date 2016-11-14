#include "effectsProperties.h"

#include <wx/grid.h>
#define wxUSE_GRID

extern DamageAnalysisFrame *Frame;

int selectPosRow,selectPosCol;

extern std::vector<basic_effect *> attackEffects;
extern std::vector<basic_effect *> defenceEffects;
extern std::vector<effect_critical_damage> critEffects;
extern std::vector<effect_block_damage> shieldBlockEffects;

class cellDataObject
{
public:
    unsigned *U;
    int *I;
    double *D;
    wxString type;
    cellDataObject(unsigned &data) : U(&data), type(_("U")) {}  //Unsigned ints(for enums)
    cellDataObject(int &data) : I(&data), type(_("I")) {}       //Ints
    cellDataObject(double &data) : D(&data), type(_("D")) {}    //Doubles
};

//(*InternalHeaders(effectsProperties)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(effectsProperties)
const long effectsProperties::ID_GRID1 = wxNewId();
const long effectsProperties::ID_BUTTON2 = wxNewId();
const long effectsProperties::ID_BUTTON1 = wxNewId();
const long effectsProperties::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(effectsProperties,wxFrame)
	//(*EventTable(effectsProperties)
	//*)
END_EVENT_TABLE()

effectsProperties::effectsProperties(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(effectsProperties)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, _("Effect properties"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFRAME_TOOL_WINDOW|wxNO_BORDER, _T("wxID_ANY"));
	SetClientSize(wxSize(390,300));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(240,280), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Grid1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxSize(390,85), 0, _T("ID_GRID1"));
	Grid1->CreateGrid(0,2);
	Grid1->EnableEditing(true);
	Grid1->EnableGridLines(true);
	Grid1->SetColLabelSize(25);
	Grid1->SetRowLabelSize(120);
	Grid1->SetDefaultColSize(135, true);
	Grid1->SetColLabelValue(0, _("Value, min"));
	Grid1->SetColLabelValue(1, _("max"));
	Grid1->SetDefaultCellFont( Grid1->GetFont() );
	Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
	BoxSizer1->Add(Grid1, 50, wxEXPAND, 0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2->Add(-1,-1,2, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(Panel1, ID_BUTTON2, _("Delete"), wxDefaultPosition, wxSize(15,25), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button2->SetMinSize(wxSize(30,25));
	Button2->SetMaxSize(wxSize(140,45));
	BoxSizer2->Add(Button2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(-1,-1,2, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(Panel1, ID_BUTTON1, _("Close"), wxDefaultPosition, wxSize(15,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button1->SetMinSize(wxSize(30,25));
	Button1->SetMaxSize(wxSize(140,45));
	BoxSizer2->Add(Button1, 1, wxALIGN_CENTER_VERTICAL, 9);
	BoxSizer1->Add(BoxSizer2, 1, wxEXPAND, 5);
	Panel1->SetSizer(BoxSizer1);
	BoxSizer1->Fit(Panel1);
	BoxSizer1->SetSizeHints(Panel1);

	Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGED,(wxObjectEventFunction)&effectsProperties::OnGrid1CellChange);
	Connect(ID_GRID1,wxEVT_GRID_SELECT_CELL,(wxObjectEventFunction)&effectsProperties::OnGrid1CellSelect);
	Grid1->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&effectsProperties::OnGrid1KeyDown1,0,this);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&effectsProperties::OnButton2Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&effectsProperties::OnButton1Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&effectsProperties::OnClose);
	//*)
	cellColumn=0;
	Grid1->AppendRows(20,true);
	Button1->SetFocus();
}

effectsProperties::~effectsProperties()
{
	//(*Destroy(effectsProperties)
	//*)
}

void effectsProperties::OnClose(wxCloseEvent& event)
{
    Hide();
}

void effectsProperties::AppendCell(double &val)
{
    wxGridCellEditor *tmpEditor=new wxGridCellFloatEditor;
    tmpEditor->SetClientData(new cellDataObject(val));
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,cellColumn,&(*tmpEditor));
    Grid1->SetCellValue(Grid1->GetNumberRows()-1,cellColumn,wxString::FromDouble(val,2));
    ++cellColumn;
}

void effectsProperties::AppendCell(int &val)
{
    wxGridCellEditor *tmpEditor=new wxGridCellNumberEditor;
    tmpEditor->SetClientData(new cellDataObject(val));
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,cellColumn,&(*tmpEditor));
    Grid1->SetCellValue(Grid1->GetNumberRows()-1,cellColumn,wxString::Format(wxT("%i"),val));
    ++cellColumn;
}

void effectsProperties::AppendRow(const wxString &headerText)
{
    cellColumn=0;
    Grid1->AppendRows(1,true);
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,headerText);
}

void effectsProperties::AppendChoiceCell(unsigned arrayCount, const wxString myChoices[], unsigned &val)
{
    wxGridCellChoiceEditor *tmpEditor=new wxGridCellChoiceEditor(arrayCount ,myChoices);
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,cellColumn,&(*tmpEditor));
    tmpEditor->SetClientData(new cellDataObject(val));
    Grid1->SetCellValue(Grid1->GetNumberRows()-1,cellColumn,myChoices[val]);
    ++cellColumn;
    return;
}

void effectsProperties::Clear()
{
    int tmpCols=Grid1->GetNumberCols();
    int j=tmpCols;
    for(int i=Grid1->GetNumberRows();i!=0;i--)
    {
        for (;j!=0;j--)
        {
            if(!Grid1->IsReadOnly(i-1,j-1))
            {
                wxGridCellEditor *tmpEditor=Grid1->GetCellEditor(i-1,j-1);
                delete (cellDataObject *)tmpEditor->GetClientData();
                tmpEditor->DecRef();
            }
        }
        j=tmpCols;
    }
    cellColumn=0;
    Grid1->ClearGrid();
    Grid1->DeleteRows(0,Grid1->GetNumberRows(),true);
}

template <typename Tstring, typename Tval1, typename Tval2> void effectsProperties::AppendFullRow (const Tstring headerText, Tval1 &val1, Tval2 &val2)
{
    AppendRow(headerText);
    AppendCell(val1);
    AppendCell(val2);
}

void effectsProperties::AppendFullRow(const wxString headerText,double &val1)
{
    AppendRow(headerText);
    AppendCell(val1);
    AppendReadOnly();
}

void effectsProperties::AppendFullRow(const wxString headerText,int &val1)
{
    AppendRow(headerText);
    AppendCell(val1);
    AppendReadOnly();
}

void effectsProperties::AppendReadOnly()
{
    Grid1->SetReadOnly(Grid1->GetNumberRows()-1,cellColumn,true);
    cellColumn++;
}

void effectsProperties::AppendDamageTypeSelector(unsigned &damageType)
{
    wxString damageTypeString[3];
    damageTypeString[0] = "Physical";
    damageTypeString[1] = "Magic";
    damageTypeString[2] = "Pure";
    AppendRow(_("Damage type"));
    AppendChoiceCell(3 ,damageTypeString, damageType);
    AppendReadOnly();
}

void effectsProperties::AppendCustomSelector(unsigned &selection, int choiceSize,wxString const rowName, wxString const customArray[])
{
    AppendRow(rowName);
    AppendChoiceCell(choiceSize ,customArray, selection);
    AppendReadOnly();
}

void effectsProperties::OnGrid1CellChange(wxGridEvent& event)
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
    wxChoice *tmpChoice=reinterpret_cast<wxChoice *>(tmpEditor->GetControl());//Causes crashes when used. Be careful.
    (*tmpDataObject->U)=tmpChoice->GetSelection();
}
((basic_effect *)currEditObject)->FillPropertiesGrid(this);
// ___ Refreshing the screen to get actual data(in case if any effect wants to show dynamic information).
}

void effectsProperties::OnButton1Click(wxCommandEvent& event)
{
    Hide();
}

void effectsProperties::OnButton2Click(wxCommandEvent& event)
{
    int answer = wxMessageBox("Are you sure you want to delete this effect?", "Deleting effect", wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_WARNING, this);
    if (answer == wxOK)
    {
        std::vector<basic_effect *>::iterator tempVecIt=attackEffects.end()-1;
        int i=Frame->attackEffectsCtrl->FindItem(-1,(wxUIntPtr)ptrtoItem);
        if (i!=-1)
        {
            int vectSize=attackEffects.size()-1;
            for (int j=attackEffects.size()-1;vectSize==attackEffects.size()-1;j--,tempVecIt--)
            {
                if (Frame->isSameRefAddress((*(basic_effect *)Frame->attackEffectsCtrl->GetItemData(i)),**tempVecIt)==true)
                {
                    basic_effect *myPtr=&(*(basic_effect *)Frame->attackEffectsCtrl->GetItemData(i));
                    delete (basic_effect *)Frame->attackEffectsCtrl->GetItemData(i);
                    attackEffects.erase(tempVecIt);
                    Frame->attackEffectsCtrl->DeleteItem(i);
                }
            }
        }
        std::vector<basic_effect *>::iterator tempVecIt2=defenceEffects.end()-1;
        i=Frame->defenseEffectsCtrl->FindItem(-1,(wxUIntPtr)ptrtoItem);
        if (i!=-1)
        {
            int vectSize2=defenceEffects.size()-1;
            for (int j=defenceEffects.size()-1;vectSize2==defenceEffects.size()-1;j--,tempVecIt2--)
            {
                if (Frame->isSameRefAddress((*(basic_effect *)Frame->defenseEffectsCtrl->GetItemData(i)),**tempVecIt2)==true)
                {
                    basic_effect *myPtr=&(*(basic_effect *)Frame->defenseEffectsCtrl->GetItemData(i));
                    delete (basic_effect *)Frame->defenseEffectsCtrl->GetItemData(i);
                    defenceEffects.erase(tempVecIt2);
                    Frame->defenseEffectsCtrl->DeleteItem(i);
                }
            }
        }
        this->GetParent()->SetFocus();
        Hide();
    }
}

void effectsProperties::OnGrid1KeyDown1(wxKeyEvent& event)
{
    switch ( event.GetKeyCode() )
    {
        case WXK_RETURN:
        case WXK_NUMPAD_ENTER:
            Grid1->GoToCell(selectPosRow,selectPosCol);
    }
    event.Skip();
}

void effectsProperties::OnGrid1CellSelect(wxGridEvent& event)
{
    selectPosRow=event.GetRow();
    selectPosCol=event.GetCol();
    if (selectPosRow==1)
    {
         selectPosRow=0;
    }
    else
    {
         selectPosRow=event.GetRow()-1;
    }
    if (selectPosCol==0)
    {
        selectPosCol=0;
    }
    else
    {
         selectPosCol=event.GetCol();
    }
}
