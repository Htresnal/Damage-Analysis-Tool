
//(*InternalHeaders(AnalysisLogs)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "AnalysisLogs.h"

const double speedBATPart=5.72;
const double speedBATStart=-100;
extern double Withstanded, IAS, BATD;
extern double attackTimeParts;
extern double attackHits;

double  ARReduct, InDamageBase, InDamage, InDamageRaw, InDamageMagic, InDamageNoReduct, aps, attackPerSecondPart, magicResist, InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle;
double addWhiteDmg;
int statstr, statint, statagi, HP, MP, DoDoubleHit, armor;

extern std::vector<double> magicResistanceBuffer;

extern std::vector<basic_effect *> attackEffects;
extern std::vector<basic_effect *> defenceEffects;
extern std::vector<effect_critical_damage> critEffects;
extern std::vector<effect_block_damage> shieldBlockEffects;

extern DamageAnalysisFrame *DamageInputWindow;

//(*IdInit(AnalysisLogs)
const long AnalysisLogs::ID_RICHTEXTCTRL1 = wxNewId();
const long AnalysisLogs::ID_BUTTON1 = wxNewId();
const long AnalysisLogs::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AnalysisLogs,wxFrame)
	//(*EventTable(AnalysisLogs)
	//*)
END_EVENT_TABLE()

AnalysisLogs::AnalysisLogs(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AnalysisLogs)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(350,350));
	Move(wxDefaultPosition);
	SetMinSize(wxSize(180,180));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(256,328), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(2, 0, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	RichTextCtrl1 = new wxRichTextCtrl(Panel1, ID_RICHTEXTCTRL1, _("Initializing data..."), wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxNO_BORDER|wxVSCROLL, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	RichTextCtrl1->SetMinSize(wxSize(100,100));
	RichTextCtrl1->SetMaxSize(wxSize(0,0));
	FlexGridSizer1->Add(RichTextCtrl1, 2, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 1);
	Button1 = new wxButton(Panel1, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(Button1, 1, wxALIGN_RIGHT|wxALIGN_BOTTOM, 0);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AnalysisLogs::OnButton1Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AnalysisLogs::OnClose);
	//*)
	DamageInputWindow=(DamageAnalysisFrame *)GetParent();
}

AnalysisLogs::~AnalysisLogs()
{
	//(*Destroy(AnalysisLogs)
	//*)
}

void AnalysisLogs::RunAnalysis()
{
RichTextCtrl1->Clear();
DamageLogFill((void *)RichTextCtrl1);
Show();
Restore();
Raise();
}

void AnalysisLogs::DamageLogFill(void *myLogTable)
{
wxRichTextCtrl *richTextPtr=static_cast<wxRichTextCtrl *>(myLogTable);
unsigned WhiteDmg, hitsI;
int GreenDmg, totalhits;
double hitsD;
richTextPtr->AppendText("Attacker's base damage: ");
WhiteDmg=wxAtoi(DamageInputWindow->WhiteDamageInput->GetValue());
richTextPtr->AppendText(DamageInputWindow->WhiteDamageInput->GetValue());
richTextPtr->AppendText("\nAttacker's bonus damage: ");
GreenDmg=wxAtoi(DamageInputWindow->GreenDamageInput->GetValue());
richTextPtr->AppendText(DamageInputWindow->GreenDamageInput->GetValue());
InDamage=(double)WhiteDmg+GreenDmg;
InDamageMagicPerCycle=0;
InDamageNoReductPerCycle=0;
InDamagePerCycle=0;
for (unsigned i=0;i<attackEffects.size();i++)
{
    if (attackEffects[i]->disabled!=true)
    {
    attackEffects[i]->Init();
    }
}
for (unsigned i=0;i<defenceEffects.size();i++)
{
    if (defenceEffects[i]->disabled!=true)
    {
    defenceEffects[i]->Init();
    }
}
richTextPtr->AppendText("\nAttacker's base attack time: ");
richTextPtr->AppendText(DamageInputWindow->BATInput->GetValue());
richTextPtr->AppendText("\nAttacker's IAS: ");
richTextPtr->AppendText(DamageInputWindow->AttackSpeedInput->GetValue());
// ___ Attack speed+BAT evaluation
richTextPtr->AppendText(" (");
IAS=wxAtoi(DamageInputWindow->AttackSpeedInput->GetValue());
BATD=wxAtof(DamageInputWindow->BATInput->GetValue());
aps=(double)(IAS+(speedBATStart+(BATD*10)*speedBATPart))/(BATD*100);
attackPerSecondPart=1/aps;
richTextPtr->AppendText(wxString::FromDouble(attackPerSecondPart,2));
richTextPtr->AppendText(" per second)");
totalhits=(double)aps*(wxAtoi(DamageInputWindow->WithstandInput->GetValue()));
richTextPtr->AppendText("\nTotal hits: ");
richTextPtr->AppendText(wxString::Format(wxT("%i"),totalhits));
armor=wxAtoi(DamageInputWindow->ArmorInput->GetValue());
richTextPtr->BeginTextColour(wxColour(255, 0, 0));
richTextPtr->WriteText("\nAll data is approximate.");
richTextPtr->EndTextColour();
richTextPtr->WriteText(" ");
if (armor>0)
{
    ARReduct=((0.06*armor)/(1+0.06*armor))*100;
}
else if (armor<0)
{
    ARReduct=((0.06*armor)/(1+0.06*abs(armor)))*100;
}
richTextPtr->AppendText("\nDamage per hit: ");
richTextPtr->AppendText(wxString::FromDouble(InDamage,0));
hitsD=InDamage*aps;
hitsI=wxAtoi(DamageInputWindow->WithstandInput->GetValue());
richTextPtr->AppendText("\nDamage per second: ");
richTextPtr->AppendText(wxString::FromDouble(hitsD,0));
richTextPtr->WriteText("\n");
// ___ Double attack check
// ___ Attack emulation cycle
Withstanded=wxAtof(DamageInputWindow->WithstandInput->GetValue());
attackTimeParts=0;
attackHits=0;
InDamage=InDamage+(double)WhiteDmg+GreenDmg;
InDamageMagic=0;
InDamageNoReduct=0;
InDamageRaw=0;
unsigned totalHitsActual ,lethalHit;
totalHitsActual=0;
attackTimeParts=attackPerSecondPart;
// ___ Initializing HP data
HP=wxAtoi(DamageInputWindow->StatHPInput->GetValue());
int HPMax=HP;
while (attackTimeParts<Withstanded)
{
    aps=(IAS+(speedBATStart+(BATD*10)*speedBATPart))/(BATD*100);
    attackPerSecondPart=1/aps;
    InDamageBase=(double)WhiteDmg+GreenDmg;
    //InDamagePerCycle=InDamagePerCycle+InDamageBase;
    InDamagePerCycle=InDamageBase;
    InDamageMagicPerCycle=0;
    InDamageNoReductPerCycle=0; // ___ Necrophos aura can go there as an effect.
    for (int R=minRanks;R<maxRanks;R++)
    {
        for (unsigned f=0;f<attackEffects.size();f++)
        {
            if (R==0 && !critEffects.empty())
            {
                std::sort(critEffects.begin(),critEffects.end(),isLessThanChance);
                for (unsigned l=0;l<critEffects.size();l++)
                {
                    continue;
                }
            }
            if (!attackEffects[f]->disabled && attackEffects[f]->initRank==R)
            {
                attackEffects[f]->Continue();
            }
        }
    }
    for (int R=minRanks;R<maxRanks;R++)
    {
        for (unsigned f=0;f<defenceEffects.size();f++)
        {
            if (!defenceEffects[f]->disabled && defenceEffects[f]->initRank==R)
            {
                defenceEffects[f]->Continue();
            }
        }
    }
    if (DoDoubleHit>0)
    {
        for (int R=minRanks;R<maxRanks;R++)
        {
            for (unsigned j=0;j<attackEffects.size();j++)
            {
                if (!attackEffects[j]->disabled && attackEffects[j]->initRank==R)
                {
                    attackEffects[j]->DoDoubleAttack();
                }
            }
        }
        for (int R=minRanks;R<maxRanks;R++)
        {
            for (unsigned j=0;j<defenceEffects.size();j++)
            {
                if (!defenceEffects[j]->disabled && defenceEffects[j]->initRank==R)
                {
                    defenceEffects[j]->DoDoubleAttack();
                }
            }
        }
    totalHitsActual++;
    }
    attackTimeParts=attackTimeParts+attackPerSecondPart;
    attackHits=attackHits+1;
    InDamageNoReduct=InDamageNoReduct+InDamageNoReductPerCycle;
    InDamageRaw=InDamageRaw+InDamagePerCycle+InDamageNoReductPerCycle;
    // ___ Physical damage filter.
    if (armor>0)
    {
        ARReduct=((0.06*armor)/(1+0.06*armor))*100;
        InDamagePerCycle=(InDamagePerCycle/100)*(100-ARReduct);
    }
    else if (armor<0)
    {
        ARReduct=((0.06*armor)/(1+0.06*abs(armor)))*100;
        InDamagePerCycle=(InDamagePerCycle/100)*(100+abs(ARReduct));
    }
    InDamage=InDamage+InDamagePerCycle;
    // ___ Magical damage filter.
    double magicEffectsBuffered;
    magicEffectsBuffered=0;
    for (unsigned i=0;i<magicResistanceBuffer.size();i++)
    {
        magicEffectsBuffered=magicEffectsBuffered ? magicEffectsBuffered*magicResistanceBuffer[i] : magicResistanceBuffer[i];
    }
    magicEffectsBuffered=(1-magicEffectsBuffered);
    InDamageRaw=InDamageRaw+InDamageMagicPerCycle;
    InDamageMagicPerCycle=(InDamageMagicPerCycle/100)*magicEffectsBuffered;
    InDamageMagic=InDamageMagic+InDamageMagicPerCycle;
    //If reduction =1-(x/100) per 68%;
    //If amplifying =1+(x/100) per 68%;
    totalHitsActual++;
    if (lethalHit==0)
    {
        if ((InDamage+InDamageMagic+InDamageNoReduct)>=HP)
        {
            lethalHit=totalHitsActual;
        }
    }
}
if (armor!=0)
{
// Armor reduction evaluation
    richTextPtr->AppendText("Damage reduction: ");
    richTextPtr->AppendText(wxString::FromDouble(ARReduct,0));
    richTextPtr->AppendText("%");
}
else
{
    richTextPtr->AppendText("No damage reduction.");
}
if (lethalHit)
{
richTextPtr->AppendText("\nLethal hit: ");
richTextPtr->AppendText(wxString::Format(wxT("%i"),lethalHit));
}
richTextPtr->AppendText("\nHits done: ");
richTextPtr->AppendText(wxString::Format(wxT("%i"),totalHitsActual));
//hitsD=(double)InDamageRaw;
richTextPtr->AppendText("\nRaw damage withstanded: ");
richTextPtr->AppendText(wxString::FromDouble(((int)InDamageRaw),0));
richTextPtr->AppendText("\nActual damage withstanded: ");
richTextPtr->AppendText(wxString::FromDouble(((int)InDamage+InDamageMagic+InDamageNoReduct),0));// ___ ACTUAL DAMAGE WITHSTANDED IS NOT WORKED THROUGH
richTextPtr->AppendText("\nDEBUG INFO: ");
richTextPtr->AppendText("\n");
richTextPtr->AppendText(wxString::FromDouble(InDamage,0));
richTextPtr->AppendText("\n");
richTextPtr->AppendText(wxString::FromDouble(InDamageMagic,0));
richTextPtr->AppendText("\n");
richTextPtr->AppendText(wxString::FromDouble(InDamageNoReduct,0));
richTextPtr->AppendText("\n");
richTextPtr->AppendText(" (during ");
richTextPtr->AppendText(DamageInputWindow->WithstandInput->GetValue());
richTextPtr->AppendText(" seconds)");
// ___ Final damage calculation.
// ___ Check if lethal.
HP=InDamageNoReduct>=HP ? 0 : HP-InDamageNoReduct;
HP=InDamage>=HP ? 0 : HP-InDamage;
HP=InDamageMagic>=HP ? 0 : HP-InDamageMagic;
return;
}

void AnalysisLogs::OnClose(wxCloseEvent& event)
{
    Hide();
}

void AnalysisLogs::OnButton1Click(wxCommandEvent& event)
{
    Hide();
}

void AnalysisLogs::OnRichTextCtrl1Text(wxCommandEvent& event)
{
    event.Skip();
}
