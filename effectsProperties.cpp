#include "effectsProperties.h"

extern DamageAnalysisFrame *DamageInputWindow;

extern void *itemID;

extern std::vector<basic_effect *> attackEffects;
extern std::vector<basic_effect *> defenceEffects;
extern std::vector<effect_critical_damage> critEffects;
extern std::vector<effect_block_damage> shieldBlockEffects;

class cellDataObject
{
public:
    int *I;
    double *D;
    wxString type;
    cellDataObject(int &data) : I(&data), type(_("I")) {}
    cellDataObject(double &data) : D(&data), type(_("D")) {}
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

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
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
	BoxSizer1->Add(Grid1, 50, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
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
	BoxSizer2->Add(Button1, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 9);
	BoxSizer1->Add(BoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(BoxSizer1);
	BoxSizer1->Fit(Panel1);
	BoxSizer1->SetSizeHints(Panel1);

	Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&effectsProperties::OnGrid1CellChange);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&effectsProperties::OnButton2Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&effectsProperties::OnButton1Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&effectsProperties::OnClose);
	//*)
	cellColumn=0;
	Grid1->AppendRows(20,true);
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
    Grid1->SetCellValue(wxString::FromDouble(val,2),Grid1->GetNumberRows()-1,cellColumn);
    ++cellColumn;
}

void effectsProperties::AppendCell(int &val)
{
    wxGridCellEditor *tmpEditor=new wxGridCellNumberEditor;
    tmpEditor->SetClientData(new cellDataObject(val));
    Grid1->SetCellEditor(Grid1->GetNumberRows()-1,cellColumn,&(*tmpEditor));
    Grid1->SetCellValue(wxString::Format(wxT("%i"),val),Grid1->GetNumberRows()-1,cellColumn);
    ++cellColumn;
}

void effectsProperties::AppendRow(const wxString &headerText)
{
    cellColumn=0;
    Grid1->AppendRows(1,true);
    Grid1->SetRowLabelValue(Grid1->GetNumberRows()-1,headerText);
}

void effectsProperties::Clear()
{
    int tmpCols=Grid1->GetCols();
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
}

void effectsProperties::OnButton1Click(wxCommandEvent& event)
{
    Hide();
}

void effectsProperties::OnButton2Click(wxCommandEvent& event)
{
    std::vector<basic_effect *>::iterator tempVecIt=attackEffects.end()-1;
    int i=DamageInputWindow->attackEffectsCtrl->FindItem(-1,(wxUIntPtr)ptrtoItem);
    if (i!=-1)
    {
        for (int j=attackEffects.size()-1;j--;)
        {
            DamageInputWindow->isSameRefAddress(attackEffects.at(j),*tempVecIt);
            if (true)
            {
                event.Skip();
            }
            tempVecIt--;
        }
        DamageInputWindow->attackEffectsCtrl->DeleteItem(itemID);
    }

    //index
    /*
    if (isSameRefAddress(var1, val2))
    {

    }

    if ((foundIndex=defenseEffectsCtrl->GetNextItem(0, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
{
    if (defenseEffectsCtrl->GetItemData(foundIndex)!=NULL)
    {
        ((basic_effect *)event.GetItem().GetData())->FillPropertiesGrid();
        Show();
        Restore();
        Raise();
    }
}
    attackEffects.push_back(((basic_effect *)attackEffectsChoice2->GetClientData(event.GetSelection()))->getnewCopy());
    wxListItem tmpListItem;
    tmpListItem.SetId(wxNewId());
    std::vector<basic_effect *>::iterator tempVecIt=attackEffects.end()-1;
    tmpListItem.SetText((*tempVecIt)->Name);
    tmpListItem.SetData(&(**tempVecIt));
    //wxMessageBox(((basic_effect *)tmpListItem.GetData())->Name, _("I want you to see this ;)"));
    attackEffectsCtrl->InsertItem(tmpListItem);
    */
    this->GetParent()->SetFocus();
    Hide();
}
