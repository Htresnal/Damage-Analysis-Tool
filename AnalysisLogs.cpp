
//(*InternalHeaders(AnalysisLogs)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "AnalysisLogs.h"
extern double Withstanded;
double actualTimeline=0;

extern DamageAnalysisFrame *Frame;

extern heroUnit *heroTemp;
extern heroUnit *heroAttTemp;

extern hero_Defender Defender;
extern hero_Attacker Attacker;

double InDamageNoReductPerCycleTMP, InDamagePerCycleTMP, InDamagePerCycleCrit, InDamageMagicPerCycleTMP, InDamagePrev, InDamageBase, InDamage, InDamageRaw, InDamageMagic, InDamageNoReduct, aps, singleAttackTime, currAps, currSingleAttackTime, InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle;
double timeElapsed, timeLethalStrike;
unsigned totalHitsActual, lethalHit, WhiteDmg;
int DefendercurrMaxHP;

int DoDoubleHit, GreenDmg;

std::pair<int,int> *critTMPPair;

extern std::vector<double> magicResistanceBuffer;
extern std::vector<basic_effect *> attackEffects;
extern std::vector<basic_effect *> defenceEffects;
extern std::vector<effect_critical_damage *> critEffects;
extern std::vector<effect_block_damage *> shieldBlockEffects;

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

	Create(parent, id, _("Analysis log"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFRAME_TOOL_WINDOW|wxNO_BORDER, _T("id"));
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
unsigned hitsI;
int totalhits;
timeElapsed=0;
timeLethalStrike=0;
double hitsD;
double tmpHPRegen, tmpMPRegen, MPBuffer, HPBuffer;
MPBuffer=0;
HPBuffer=0;
/**
Before we are able to start the analyze process, we are supposed to create both hero objects, fill their
stats if present, and cause armor\IAS\Level precalculations. All effects are highly based on stats being
self-aware and in full self control. Thats why heroData.cpp contains all the methods you may need to
control the stat setting processes. Use methods instead of changing stat variables by hand, that is
vital.
*/
Defender.fillFromUI();
Attacker.fillFromUI();
hero_Attacker tmpAttacker;
tmpAttacker=Attacker;
hero_Defender tmpDefender;
tmpDefender=Defender;
critEffects.clear();
critEffects.reserve(20);
shieldBlockEffects.clear();
shieldBlockEffects.reserve(20);
magicResistanceBuffer.clear();
magicResistanceBuffer.reserve(5);
// ___ Initializing HP and MP data
magicResistanceBuffer.push_back(Defender.magicResist);
richTextPtr->AppendText("Attacker's base damage: ");
WhiteDmg=wxAtoi(Frame->WhiteDamageInput->GetValue());
richTextPtr->AppendText(Frame->WhiteDamageInput->GetValue());
richTextPtr->AppendText("\nAttacker's bonus damage: ");
GreenDmg=wxAtoi(Frame->GreenDamageInput->GetValue());
richTextPtr->AppendText(Frame->GreenDamageInput->GetValue());
recalculateAttackSpeed();
InDamage=(double)WhiteDmg+GreenDmg;
InDamageMagicPerCycle=0;
InDamageNoReductPerCycle=0;
InDamagePerCycle=0;
InDamagePerCycleCrit=0;
//Find and destroy all the temporary effects, produced by master effects.
for (int i=attackEffects.size()-1;i!=-1;i--)
{
    if (attackEffects.at(i)->temporary==true)
    {
        delete attackEffects.at(i);
        attackEffects.erase(attackEffects.begin()+i);
    }
}
for (int i=defenceEffects.size()-1;i!=-1;i--)
{
    if (defenceEffects.at(i)->temporary==true)
    {
        delete defenceEffects.at(i);
        defenceEffects.erase(defenceEffects.begin()+i);
    }
}
for (int R=minRanks;R<=maxRanks;R++)
{
    for (unsigned f=0;f<attackEffects.size();f++)
    {
        if (!attackEffects[f]->disabled && attackEffects[f]->initRank==R)
        {
            attackEffects[f]->Init();
        }
    }
}
for (int R=minRanks;R<=maxRanks;R++)
{
    for (unsigned f=0;f<defenceEffects.size();f++)
    {
        if (!defenceEffects[f]->disabled && defenceEffects[f]->initRank==R)
        {
            defenceEffects[f]->Init();
        }
    }
}
richTextPtr->AppendText("\nAttacker's base attack time: ");
richTextPtr->AppendText(wxString::FromDouble(Attacker.BATD,2));
richTextPtr->AppendText("\nAttacker's IAS: ");
richTextPtr->AppendText(wxString::FromDouble(Attacker.IAS,0));
// ___ Attack speed+BAT evaluation
richTextPtr->AppendText(" (");
richTextPtr->AppendText(wxString::FromDouble(singleAttackTime,2));
richTextPtr->AppendText(" per second)");
totalhits=(double)aps*(wxAtoi(Frame->WithstandInput->GetValue()));
richTextPtr->AppendText("\nTotal hits: ");
richTextPtr->AppendText(wxString::Format(wxT("%i"),totalhits));
richTextPtr->BeginTextColour(wxColour(255, 0, 0));
richTextPtr->WriteText("\nAll data is approximate.");
richTextPtr->EndTextColour();
richTextPtr->WriteText(" ");
richTextPtr->AppendText("\nDamage per hit: ");
richTextPtr->AppendText(wxString::FromDouble(InDamage,0));
hitsD=InDamage*aps;
hitsI=wxAtoi(Frame->WithstandInput->GetValue());
richTextPtr->AppendText("\nDamage per second: ");
richTextPtr->AppendText(wxString::FromDouble(hitsD,0));
richTextPtr->WriteText("\n");
// ___ Double attack check
// ___ Attack emulation cycle
Withstanded=wxAtof(Frame->WithstandInput->GetValue());
InDamage=0;
InDamageMagic=0;
InDamageNoReduct=0;
InDamageRaw=0;
InDamagePrev=0;
totalHitsActual=0;
actualTimeline=singleAttackTime;
lethalHit=0;
while (actualTimeline<=Withstanded)
{
    recalculateAttackSpeed();
    currAps=aps;
    DefendercurrMaxHP=Defender.maxHP;
    currSingleAttackTime=singleAttackTime;
    InDamageBase=WhiteDmg+GreenDmg;
    InDamagePerCycle=InDamageBase;
    InDamageRaw=InDamageRaw+InDamagePerCycle;
    InDamageMagicPerCycle=0;
    InDamageNoReductPerCycle=0; // ___ Necrophos aura can go there as an effect.
    DoDoubleHit=0;
    int critOnlyOnce=0;
    for (int R=minRanks;R<=maxRanks;R++)
    {
        for (unsigned f=0;f<attackEffects.size();f++)
        {
            if (R==-2 && !critEffects.empty() && critOnlyOnce!=1)
            {
                critOnlyOnce=1;
                std::sort(critEffects.begin(),critEffects.end(),isLessThanDamage);
                TMPDamageSave();
                calcCrits(critEffects);
                TMPDamageLoad();
            }
            if (!attackEffects[f]->disabled && !attackEffects[f]->externalContinueCycle && attackEffects[f]->initRank==R)
            {
                TMPDamageSave();
                attackEffects[f]->Continue();
                TMPDamageLoad();
            }
        }
    }
    int blockOnlyOnce=0;
    for (int R=minRanks;R<=maxRanks;R++)
    {
        if (R==0 && !shieldBlockEffects.empty() && blockOnlyOnce!=1)
        {
            blockOnlyOnce=1;
            std::sort(shieldBlockEffects.begin(),shieldBlockEffects.end(),isLessThanBlock);
            calcShieldBlock(shieldBlockEffects);
        }
        for (unsigned f=0;f<defenceEffects.size();f++)
        {
            if (!defenceEffects[f]->disabled && !defenceEffects[f]->externalContinueCycle && defenceEffects[f]->initRank==R)
            {
                TMPDamageSave();
                defenceEffects[f]->Continue();
                TMPDamageLoad();
            }
        }
    }
    for (;DoDoubleHit--;)
    {
        /** During double hit emulation, all the data should be "refreshed" and relaunched,
        except the time-wise ones.
        */
        ApplyResists();
        FlushDamage();
        recalculateAttackSpeed();
        InDamageBase=WhiteDmg+GreenDmg;
        InDamagePerCycle=InDamageBase;
        InDamageRaw=InDamageRaw+InDamagePerCycle;
        InDamageMagicPerCycle=0;
        InDamageNoReductPerCycle=0; // ___ Necrophos aura can go there as an effect.
        critOnlyOnce=0;
        for (int R=minRanks;R<=maxRanks;R++)
        {
            for (unsigned j=0;j<attackEffects.size();j++)
            {
                if (R==-2 && !critEffects.empty() && critOnlyOnce!=1)
                {
                    critOnlyOnce=1;
                    std::sort(critEffects.begin(),critEffects.end(),isLessThanDamage);
                    TMPDamageSave();
                    calcCrits(critEffects);
                    TMPDamageLoad();
                }
                if (!attackEffects[j]->disabled && !attackEffects[j]->externalContinueCycle && attackEffects[j]->initRank==R)
                {
                    TMPDamageSave();
                    attackEffects[j]->DoDoubleAttack();
                    TMPDamageLoad();
                }
            }
        }
        blockOnlyOnce=0;
        for (int R=minRanks;R<=maxRanks;R++)
        {
            if (R==0 && !shieldBlockEffects.empty() && blockOnlyOnce!=1)
            {
                blockOnlyOnce=1;
                std::sort(shieldBlockEffects.begin(),shieldBlockEffects.end(),isLessThanBlock);
                calcShieldBlock(shieldBlockEffects);
            }
            for (unsigned j=0;j<defenceEffects.size();j++)
            {
                if (!defenceEffects[j]->disabled && !attackEffects[j]->externalContinueCycle && defenceEffects[j]->initRank==R)
                {
                    TMPDamageSave();
                    defenceEffects[j]->DoDoubleAttack();
                    TMPDamageLoad();
                }
            }
        }
    totalHitsActual++;
    }
    actualTimeline=actualTimeline+singleAttackTime;
    ApplyResists();
    FlushDamage();
    totalHitsActual++;
    // Health regeneration between hits
    if (Defender.HPRegen)
    {
        HPBuffer=HPBuffer+currAps*Defender.HPRegen;
        if ((Defender.HP+currAps*Defender.HPRegen)>=Defender.maxHP)
        {
            Defender.HP=Defender.maxHP;
        }
        else
        {
            Defender.HP=Defender.HP+currAps*Defender.HPRegen;
        }
    }
    // Mana regeneration between hits
    if (Defender.MPRegen || Defender.MPRegenBonus)
    {
        tmpMPRegen=(((Defender.MPRegen!=0) ? Defender.MPRegen*(1+Defender.MPRegenMultiplier) : 0)+Defender.MPRegenBonus)*currAps;
        MPBuffer=MPBuffer+tmpMPRegen;
        tmpMPRegen=trunc(MPBuffer);
        MPBuffer=MPBuffer-tmpMPRegen;
        Defender.MP=Defender.MP+tmpMPRegen;
        if (Defender.MP>Defender.maxMP)
        {
            Defender.MP=Defender.maxMP;
        }
    }
    timeElapsed=timeElapsed+currSingleAttackTime;
}
if (Defender.armor!=0)
{
// Armor reduction evaluation
    richTextPtr->AppendText("Physical damage reduction: ");
    richTextPtr->AppendText(wxString::FromDouble(getArmorReduction(),0));
    richTextPtr->AppendText("%");
}
else
{
    richTextPtr->AppendText("No physical damage reduction.");
}
if (Defender.HP<=0)
{
richTextPtr->BeginTextColour(wxColour(255, 0, 0));
richTextPtr->WriteText("\nLethal hit:");
richTextPtr->EndTextColour();
richTextPtr->WriteText(" ");
    if (lethalHit)
    {
    richTextPtr->AppendText(wxString::Format(wxT("%i"),lethalHit));
    }
    else
    {
    richTextPtr->AppendText(wxString::Format(wxT("%i"),totalHitsActual));
    }
}
richTextPtr->WriteText(" (at ");
richTextPtr->AppendText(wxString::FromDouble(timeLethalStrike,2));
richTextPtr->WriteText(" seconds)");
if (totalHitsActual>=2000 || Attacker.IAS>=1000)
{
richTextPtr->BeginTextColour(wxColour(255, 0, 0));
richTextPtr->WriteText("\nAttack rate limit is reached. Expected precision level is not guaranteed.");
richTextPtr->EndTextColour();
richTextPtr->WriteText(" ");
}
richTextPtr->AppendText("\nActual hits done: ");
richTextPtr->AppendText(wxString::Format(wxT("%i"),totalHitsActual));
richTextPtr->AppendText("\nRaw damage withstanded: ");
richTextPtr->AppendText(wxString::FromDouble(InDamageRaw,0));
richTextPtr->AppendText("\nActual damage withstanded: ");
richTextPtr->AppendText(wxString::FromDouble(InDamage+InDamageMagic+InDamageNoReduct,0));
richTextPtr->AppendText(" (during ");
richTextPtr->AppendText(wxString::FromDouble(timeElapsed,2));
richTextPtr->AppendText(" seconds)");
if (Defender.HP<0)
{
richTextPtr->AppendText("\nHealth lost after lethal hit: ");
richTextPtr->AppendText(wxString::FromDouble(Defender.HP,0));
}
else
{
richTextPtr->AppendText("\nHealth left: ");
richTextPtr->AppendText(wxString::FromDouble(Defender.HP,0));
}
richTextPtr->AppendText("\nMana left: ");
richTextPtr->AppendText(wxString::FromDouble(Defender.MP,0));
//Finalization. Post-analyze processes.
//Main objects recover from temp.
Attacker=tmpAttacker;
Defender=tmpDefender;
return;
}

void AnalysisLogs::TMPDamageSave()
{
InDamagePerCycleTMP=InDamagePerCycle;
InDamageMagicPerCycleTMP=InDamageMagicPerCycle;
InDamageNoReductPerCycleTMP=InDamageNoReductPerCycle;
return;
}

void AnalysisLogs::TMPDamageLoad()
{
//Physical damage
if (InDamagePerCycleTMP<InDamagePerCycle)
{
    InDamageRaw=InDamageRaw+(InDamagePerCycle-InDamagePerCycleTMP);
}
else if (InDamagePerCycleTMP>InDamagePerCycle)
{
    InDamageRaw=InDamageRaw-(InDamagePerCycleTMP-InDamagePerCycle);
}
//Magical damage
if (InDamageMagicPerCycleTMP<InDamageMagicPerCycle)
{
    InDamageRaw=InDamageRaw+(InDamageMagicPerCycle-InDamageMagicPerCycleTMP);
}
else if (InDamageMagicPerCycleTMP>InDamageMagicPerCycle)
{
    InDamageRaw=InDamageRaw-(InDamagePerCycleTMP-InDamageMagicPerCycle);
}
//Pure damage
if (InDamageNoReductPerCycleTMP<InDamageNoReductPerCycle)
{
    InDamageRaw=InDamageRaw+(InDamageNoReductPerCycle-InDamageNoReductPerCycleTMP);
}
else if (InDamageNoReductPerCycleTMP>InDamageNoReductPerCycle)
{
    InDamageRaw=InDamageRaw-(InDamageNoReductPerCycleTMP-InDamageNoReductPerCycle);
}
return;
}

void AnalysisLogs::FlushDamage()
{
// ___ Flush damage to InDamages
InDamageNoReduct=InDamageNoReduct+InDamageNoReductPerCycle;
InDamage=InDamage+InDamagePerCycle;
InDamageMagic=InDamageMagic+InDamageMagicPerCycle;
// ___ Check if lethal.
if (lethalHit==0)
{
    if (Defender.HP<=0)
    {
        lethalHit=totalHitsActual;
        timeLethalStrike=timeElapsed;
    }
}
Defender.HP=Defender.HP-(InDamage+InDamageMagic+InDamageNoReduct-InDamagePrev);
InDamagePrev=InDamage+InDamageMagic+InDamageNoReduct;
}

void AnalysisLogs::ApplyResists()
{
    // ___ Physical damage filter.
    if (Defender.armor>0)
    {
        InDamagePerCycle=(InDamagePerCycle/100)*(100-getArmorReduction());
    }
    else if (Defender.armor<0)
    {
        InDamagePerCycle=(InDamagePerCycle/100)*(100+abs(getArmorReduction()));
    }
    // ___ Magical damage filter.
    for (unsigned i=0;i<magicResistanceBuffer.size();i++)
    {
        InDamageMagicPerCycle=InDamageMagicPerCycle/100*(100-magicResistanceBuffer.at(i));
    }
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

// ___ Critical hit calculations
void AnalysisLogs::calcCrits(std::vector<effect_critical_damage *> &myVector)
{
    std::pair<int,int> *critTMPPair;
    critTMPPair=new std::pair<int,int> [myVector.size()];   //creating the array
    // ___ Creating temporary array to restore original effects afterwards.
    for (int i=0;i<myVector.size();i++)
    {
        critTMPPair[i] = std::make_pair(myVector.at(i)->chance,myVector.at(i)->damage);
    }
    // ___ Socalculating crits with the same damage.
    for (int h=0;h<myVector.size();h++)
    {
        for (int z=0;z<myVector.size();z++)
        {
            if (z!=h)
            {
                if (myVector.at(h)->damage==myVector.at(z)->damage)
                {
                    if ((myVector.at(h)->chance+myVector.at(z)->chance)<=100)
                    {
                        myVector.at(h)->chance=myVector.at(h)->chance+myVector.at(z)->chance;
                    }
                    else
                    {
                        myVector.at(h)->chance=100;
                    }
                    myVector.at(z)->chance=0;
                }
            }
        }
    }
    InDamagePerCycleCrit=InDamagePerCycle;
    double currChanceOldAccum=0;
    double currChanceAccum=0;
    for (int critLVL=0;critLVL<myVector.size();critLVL++)
    {
        if (currChanceAccum!=100)
        {
            currChanceOldAccum=currChanceAccum;
            currChanceAccum=currChanceAccum+(100-currChanceAccum)/100*(double)myVector.at(critLVL)->chance;
            // ___ To calculate damage, we need to get it's part in main chance window:
            // ___ For effect with chance 20% being first in hierarchy, we'll have 80% left for other effects to use: 100%-20%=80%
            // ___ This way, we get the chance window left for other effects to utilize.
            // ___ Lets take 50% chance to be next in hierarchy, and thats how it's chance window would be calculated: 80%/100*50%=40%.
            // ___ Only 40% of that 50% effect could have a part in calculation.
            // ___ Next effect of 90% will have a part of 36%, leaving 4% for other effects with lower hierarchy to utilize.
            // ___ All crits with the same damage are stackable by percentage additively. So, if you had +50% and +50%, you'll have 100% as outcome.
            InDamagePerCycle=InDamagePerCycle+((InDamagePerCycleCrit/100*(double)myVector.at(critLVL)->damage-InDamagePerCycleCrit)/100*(currChanceAccum-currChanceOldAccum));
            if (InDamagePerCycle<0)
            {
                InDamagePerCycle=0;
            }
        }
    }
    // ___ Restoring original effect data.
    for (int i=0;i<myVector.size();i++)
    {
        myVector.at(i)->chance=critTMPPair[i].first;
        myVector.at(i)->damage=critTMPPair[i].second;
    }
    delete[] critTMPPair;
    return;
}

// ___ Block calculations
void AnalysisLogs::calcShieldBlock(std::vector<effect_block_damage *> &myVector)
{
    double currChanceOldAccum=0;
    double currChanceAccum=0;
    for (int blockLVL=0;blockLVL<myVector.size();blockLVL++)
    {
        if (currChanceAccum!=100)
        {
            currChanceOldAccum=currChanceAccum;
            currChanceAccum=currChanceAccum+(100-currChanceAccum)/100*(double)myVector.at(blockLVL)->chance;
            // ___ To calculate damage, we need to get it's part in the "Window of chances":
            // ___ For effect with chance 20% being first in hierarchy, we'll have 80% left for other effects to use: 100%-20%=80%
            // ___ TIP: As you may know, shield effects have a hierarchy. Effects with bigger "block" value are computed first.
            // ___ This way, we get the chance window left for other effects to utilize.
            // ___ Lets take 50% chance to be next in hierarchy, and thats how it's chance window would be calculated: 80%/100*50%=40%.
            // ___ Only 40% of that 50% effect could have a part in calculation.
            // ___ Next effect of 90% will have a part of 36%, leaving 4% for other effects with lower hierarchy to utilize.
            InDamagePerCycle=InDamagePerCycle-((double)myVector.at(blockLVL)->block/100*(currChanceAccum-currChanceOldAccum));
            if (InDamagePerCycle<0)
            {
                InDamagePerCycle=0;
            }
        }
    }
    return;
}

double AnalysisLogs::getArmorReduction()
{
    if (Defender.armor>0)
    {
        return ((0.06*Defender.armor)/(1+0.06*Defender.armor))*100;
    }
    else if (Defender.armor<0)
    {
        return ((0.06*Defender.armor)/(1+0.06*abs(Defender.armor)))*100;
    }
    else
    {
        return 0;
    }
}

inline void AnalysisLogs::recalculateAttackSpeed()
{
    singleAttackTime=(double)(Attacker.BATD/(Attacker.IAS/100));
    aps=1/singleAttackTime;
    return;
}
