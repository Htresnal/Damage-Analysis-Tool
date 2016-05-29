/***************************************************************
 * Name:      DamageAnalysisMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2016-02-05
 * Copyright:  ()
 * License:
 **************************************************************/
//(*InternalHeaders(DamageAnalysisFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include "DamageAnalysisMain.h"

wxString BaseAttackDamageMinInputWas;
wxString BaseAttackDamageMaxInputWas;

std::string gameRulePath="DamageAnalysis_settings.txt";

extern int gamerule_HPPerStr, gamerule_MPPerInt, gamerule_StartHP, gamerule_StartMP, gamerule_StartIAS;
extern double gamerule_ArmorPerAgi, gamerule_HPRegenPerStr, gamerule_MPRegenPerInt;

extern std::vector<double> magicResistanceBuffer;

extern heroUnit *heroTemp;
extern heroUnit *heroAttTemp;
hero_Defender Defender;
hero_Attacker Attacker;
extern std::vector<heroUnit> heroVector;

extern std::map<std::string,basic_effect *> effectMapAttack;
extern std::map<std::string,basic_effect *> effectMapDefense;

extern std::vector<basic_effect *> attackEffects;
extern std::vector<basic_effect *> defenceEffects;
extern std::vector<effect_critical_damage> critEffects;
extern std::vector<effect_block_damage> shieldBlockEffects;

extern double InDamageBase, InDamage, InDamageRaw, InDamageMagic, InDamageNoReduct, aps, attackTimePart, InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle;
extern int DoDoubleHit;

AnalysisLogs *Frame1;
effectsProperties *Frame2;
GameSettings *Frame3;

extern void GetGameRules();

double Withstanded;

wxIntegerValidator<unsigned long>numsOnlyValidator(NULL, wxNUM_VAL_THOUSANDS_SEPARATOR);
wxIntegerValidator<long>numsOnlyValidatorSigned(NULL, wxNUM_VAL_THOUSANDS_SEPARATOR);
wxFloatingPointValidator<double>numsFloatOnlyValidator(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
wxFloatingPointValidator<double>numsFloatOnlyValidatorSigned(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);

//(*IdInit(DamageAnalysisFrame)
const long DamageAnalysisFrame::ID_CHOICE1 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL1 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT1 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT2 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT3 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL2 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL3 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL4 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL5 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL7 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT5 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT4 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT8 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT9 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL6 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL8 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT6 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL9 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL10 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT7 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL11 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT10 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT11 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL12 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT12 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL13 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL14 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT13 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT14 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL15 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT15 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL16 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT16 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT17 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT18 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL17 = wxNewId();
const long DamageAnalysisFrame::ID_LISTCTRL1 = wxNewId();
const long DamageAnalysisFrame::ID_LISTCTRL2 = wxNewId();
const long DamageAnalysisFrame::ID_BITMAPBUTTON1 = wxNewId();
const long DamageAnalysisFrame::ID_BITMAPBUTTON3 = wxNewId();
const long DamageAnalysisFrame::ID_BITMAPBUTTON4 = wxNewId();
const long DamageAnalysisFrame::ID_BITMAPBUTTON5 = wxNewId();
const long DamageAnalysisFrame::ID_CHOICE2 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT19 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL18 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT20 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL19 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT21 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL20 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT22 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL21 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT23 = wxNewId();
const long DamageAnalysisFrame::ID_STATICTEXT24 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL22 = wxNewId();
const long DamageAnalysisFrame::ID_TEXTCTRL23 = wxNewId();
const long DamageAnalysisFrame::ID_BITMAPBUTTON2 = wxNewId();
const long DamageAnalysisFrame::ID_PANEL1 = wxNewId();
const long DamageAnalysisFrame::ID_PANEL3 = wxNewId();
const long DamageAnalysisFrame::ID_NOTEBOOK1 = wxNewId();
const long DamageAnalysisFrame::idMenuQuit = wxNewId();
const long DamageAnalysisFrame::idSettings = wxNewId();
const long DamageAnalysisFrame::idMenuAbout = wxNewId();
const long DamageAnalysisFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long DamageAnalysisFrame::ID_CHOICE3 = wxNewId();
const long DamageAnalysisFrame::ID_CHOICE4 = wxNewId();

BEGIN_EVENT_TABLE(DamageAnalysisFrame,wxFrame)
    //(*EventTable(DamageAnalysisFrame)
    //*)
END_EVENT_TABLE()

DamageAnalysisFrame::DamageAnalysisFrame(wxWindow* parent,wxWindowID id)
{
    wxIntegerValidator<unsigned long>numsOnlyValidator(NULL, wxNUM_VAL_THOUSANDS_SEPARATOR);
    wxIntegerValidator<long>numsOnlyValidatorSigned(NULL, wxNUM_VAL_THOUSANDS_SEPARATOR);
    wxFloatingPointValidator<double>numsFloatOnlyValidator(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    wxFloatingPointValidator<double>numsFloatOnlyValidatorSigned(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
    //(*Initialize(DamageAnalysisFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Damage analysis Tool v0.3"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxNO_BORDER, _T("wxID_ANY"));
    SetClientSize(wxSize(700,510));
    SetMinSize(wxSize(700,510));
    SetMaxSize(wxSize(700,510));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("resources\\myIcon.png"))));
    	SetIcon(FrameIcon);
    }
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(56,56), wxDefaultSize, wxNO_BORDER, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Choice1 = new wxChoice(Panel1, ID_CHOICE1, wxPoint(16,16), wxSize(168,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    LevelInput = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("1"), wxPoint(224,16), wxSize(54,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL1"));
    LvlInputText = new wxStaticText(Panel1, ID_STATICTEXT1, _("Level"), wxPoint(192,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StatStrText = new wxStaticText(Panel1, ID_STATICTEXT2, _("STR"), wxPoint(24,48), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StatAgiText = new wxStaticText(Panel1, ID_STATICTEXT3, _("AGI"), wxPoint(96,48), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StatStrInput = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("0"), wxPoint(48,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL2"));
    StatAgiInput = new wxTextCtrl(Panel1, ID_TEXTCTRL3, _("0"), wxPoint(120,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL3"));
    StatIntInput = new wxTextCtrl(Panel1, ID_TEXTCTRL4, _("0"), wxPoint(192,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL4"));
    StatHPRegenInput = new wxTextCtrl(Panel1, ID_TEXTCTRL5, _("0"), wxPoint(176,88), wxSize(48,21), wxTE_PROCESS_ENTER, numsFloatOnlyValidatorSigned, _T("ID_TEXTCTRL5"));
    StatMPRegenInput = new wxTextCtrl(Panel1, ID_TEXTCTRL7, _("0"), wxPoint(176,112), wxSize(48,21), wxTE_PROCESS_ENTER, numsFloatOnlyValidatorSigned, _T("ID_TEXTCTRL7"));
    RegenText = new wxStaticText(Panel1, ID_STATICTEXT5, _("Regeneration"), wxPoint(166,72), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StatIntText = new wxStaticText(Panel1, ID_STATICTEXT4, _("INT"), wxPoint(168,48), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StatHealthText = new wxStaticText(Panel1, ID_STATICTEXT8, _("Health"), wxPoint(24,88), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StatManaText = new wxStaticText(Panel1, ID_STATICTEXT9, _("Mana"), wxPoint(32,112), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StatHPInput = new wxTextCtrl(Panel1, ID_TEXTCTRL6, _("0"), wxPoint(64,88), wxSize(112,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL6"));
    StatMPInput = new wxTextCtrl(Panel1, ID_TEXTCTRL8, _("0"), wxPoint(64,112), wxSize(112,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL8"));
    BaseAttackDamageText = new wxStaticText(Panel1, ID_STATICTEXT6, _("Base attack damage"), wxPoint(452,96), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BaseAttackDamageMinInput = new wxTextCtrl(Panel1, ID_TEXTCTRL9, _("0"), wxPoint(560,96), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL9"));
    BaseAttackDamageMaxInput = new wxTextCtrl(Panel1, ID_TEXTCTRL10, _("0"), wxPoint(624,96), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL10"));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT7, _("-"), wxPoint(613,96), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    WhiteDamageInput = new wxTextCtrl(Panel1, ID_TEXTCTRL11, _("0"), wxPoint(478,120), wxSize(56,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL11"));
    WhiteDamageText = new wxStaticText(Panel1, ID_STATICTEXT10, _("Damage"), wxPoint(432,120), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    GreenDamageText = new wxStaticText(Panel1, ID_STATICTEXT11, _("Bonus damage"), wxPoint(535,120), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    GreenDamageInput = new wxTextCtrl(Panel1, ID_TEXTCTRL12, _("0"), wxPoint(616,120), wxSize(56,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL12"));
    BATText = new wxStaticText(Panel1, ID_STATICTEXT12, _("Base attack time"), wxPoint(416,144), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    BATInput = new wxTextCtrl(Panel1, ID_TEXTCTRL13, _("1.0"), wxPoint(512,144), wxSize(40,21), wxTE_PROCESS_ENTER, numsFloatOnlyValidator, _T("ID_TEXTCTRL13"));
    AttackSpeedInput = new wxTextCtrl(Panel1, ID_TEXTCTRL14, _("100"), wxPoint(624,144), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL14"));
    AttackSpeedText = new wxStaticText(Panel1, ID_STATICTEXT13, _("Attack speed"), wxPoint(554,144), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    MagicalResistanceText = new wxStaticText(Panel1, ID_STATICTEXT14, _("Magical Resistance"), wxPoint(120,136), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    MagicResistanceInput = new wxTextCtrl(Panel1, ID_TEXTCTRL15, _("0"), wxPoint(225,136), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL15"));
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT15, _("%"), wxPoint(274,136), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    WithstandInput = new wxTextCtrl(Panel1, ID_TEXTCTRL16, _("10"), wxPoint(305,280), wxSize(56,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL16"));
    WithstandText = new wxStaticText(Panel1, ID_STATICTEXT16, _("Withstand"), wxPoint(308,264), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    WithstandText2 = new wxStaticText(Panel1, ID_STATICTEXT17, _("seconds"), wxPoint(312,300), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    ArmorText = new wxStaticText(Panel1, ID_STATICTEXT18, _("Armor"), wxPoint(28,136), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    ArmorInput = new wxTextCtrl(Panel1, ID_TEXTCTRL17, _("0"), wxPoint(64,136), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL17"));
    attackEffectsCtrl = new wxListCtrl(Panel1, ID_LISTCTRL1, wxPoint(424,168), wxSize(216,232), wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL1"));
    wxFont attackEffectsCtrlFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    attackEffectsCtrl->SetFont(attackEffectsCtrlFont);
    defenseEffectsCtrl = new wxListCtrl(Panel1, ID_LISTCTRL2, wxPoint(32,168), wxSize(216,232), wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL2"));
    wxFont defenseEffectsCtrlFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    defenseEffectsCtrl->SetFont(defenseEffectsCtrlFont);
    aECBButtonAdd = new wxBitmapButton(Panel1, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("resources\\plus26.png"))), wxPoint(644,168), wxSize(28,28), wxBU_AUTODRAW|wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    aECBButtonAdd->SetBitmapSelected(wxBitmap(wxImage(_T("resources\\plusd26.png"))));
    aECBButtonAdd->SetToolTip(_("Add new effect"));
    dECBButtonAdd = new wxBitmapButton(Panel1, ID_BITMAPBUTTON3, wxBitmap(wxImage(_T("resources\\plus26.png"))), wxPoint(252,168), wxSize(28,28), wxBU_AUTODRAW|wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    dECBButtonAdd->SetBitmapSelected(wxBitmap(wxImage(_T("resources\\plusd26.png"))));
    dECBButtonAdd->SetToolTip(_("Add new effect"));
    dECBButtonRemove = new wxBitmapButton(Panel1, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("resources\\cross26.png"))), wxPoint(252,200), wxSize(28,28), wxBU_AUTODRAW|wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
    dECBButtonRemove->SetBitmapSelected(wxBitmap(wxImage(_T("resources\\crossd26.png"))));
    dECBButtonRemove->SetToolTip(_("Remove selected effect"));
    BitmapButton1 = new wxBitmapButton(Panel1, ID_BITMAPBUTTON5, wxBitmap(wxImage(_T("resources\\Analyze.png"))), wxPoint(280,352), wxSize(112,45), wxBU_AUTODRAW|wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
    BitmapButton1->SetBitmapSelected(wxBitmap(wxImage(_T("resources\\Analyzed.png"))));
    BitmapButton1->SetToolTip(_("Run analyze process"));
    Choice2 = new wxChoice(Panel1, ID_CHOICE2, wxPoint(416,16), wxSize(168,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    LvlInputText2 = new wxStaticText(Panel1, ID_STATICTEXT19, _("Level"), wxPoint(592,16), wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    LevelInput2 = new wxTextCtrl(Panel1, ID_TEXTCTRL18, _("1"), wxPoint(624,16), wxSize(54,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL18"));
    StatStrText2 = new wxStaticText(Panel1, ID_STATICTEXT20, _("STR"), wxPoint(464,48), wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    StatStrInput2 = new wxTextCtrl(Panel1, ID_TEXTCTRL19, _("0"), wxPoint(488,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL19"));
    StatAgiText2 = new wxStaticText(Panel1, ID_STATICTEXT21, _("AGI"), wxPoint(536,48), wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StatAgiInput2 = new wxTextCtrl(Panel1, ID_TEXTCTRL20, _("0"), wxPoint(560,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL20"));
    StatIntText2 = new wxStaticText(Panel1, ID_STATICTEXT22, _("INT"), wxPoint(608,48), wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    StatIntInput2 = new wxTextCtrl(Panel1, ID_TEXTCTRL21, _("0"), wxPoint(632,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL21"));
    StatHealthText2 = new wxStaticText(Panel1, ID_STATICTEXT23, _("Health"), wxPoint(368,72), wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    StatManaText2 = new wxStaticText(Panel1, ID_STATICTEXT24, _("Mana"), wxPoint(528,72), wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    StatMPInput2 = new wxTextCtrl(Panel1, ID_TEXTCTRL22, _("0"), wxPoint(560,72), wxSize(112,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL22"));
    StatHPInput2 = new wxTextCtrl(Panel1, ID_TEXTCTRL23, _("0"), wxPoint(408,72), wxSize(112,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL23"));
    aECBButtonRemove = new wxBitmapButton(Panel1, ID_BITMAPBUTTON2, wxBitmap(wxImage(_T("resources\\cross26.png"))), wxPoint(644,200), wxSize(28,28), wxBU_AUTODRAW|wxNO_BORDER|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
    aECBButtonRemove->SetBitmapSelected(wxBitmap(wxImage(_T("resources\\crossd26.png"))));
    aECBButtonRemove->SetToolTip(_("Remove selected effect"));
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->Disable();
    Panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Notebook1->AddPage(Panel1, _("Damage analysis"), true);
    Notebook1->AddPage(Panel3, _("Mana cost analysis"), false);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, idSettings, _("Game engine\tF3"), _("Open game engine related settings"), wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuBar1->Append(Menu3, _("Settings"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnChoice1Select);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnLevelInputTextEnter);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatStrInputTextEnter);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatAgiInputTextEnter);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatIntInputTextEnter);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatHPRegenInputTextEnter);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatMPRegenInputTextEnter);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatHPInputTextEnter);
    Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatMPInputTextEnter);
    Connect(ID_TEXTCTRL9,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnBaseAttackDamageMinInputText);
    Connect(ID_TEXTCTRL10,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnBaseAttackDamageMaxInputText);
    Connect(ID_TEXTCTRL11,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnWhiteDamageInputText);
    Connect(ID_TEXTCTRL12,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnGreenDamageInputTextEnter);
    Connect(ID_TEXTCTRL13,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnBATInputTextEnter);
    Connect(ID_TEXTCTRL14,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnAttackSpeedInputTextEnter);
    Connect(ID_TEXTCTRL15,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnMagicResistanceInputTextEnter);
    Connect(ID_TEXTCTRL16,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnWithstandInputTextEnter);
    Connect(ID_TEXTCTRL17,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnArmorInputTextEnter);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&DamageAnalysisFrame::OnattackEffectsCtrlItemActivated);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&DamageAnalysisFrame::OndefenseEffectsCtrlItemActivated2);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DamageAnalysisFrame::OnaECBButtonAddClick);
    Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DamageAnalysisFrame::OndECBButtonAddClick);
    Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DamageAnalysisFrame::OndECBButtonRemoveClick);
    Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DamageAnalysisFrame::OnButton1Click1);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnChoice2Select1);
    Connect(ID_TEXTCTRL18,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnLevelInput2TextEnter);
    Connect(ID_TEXTCTRL19,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatStrInput2TextEnter);
    Connect(ID_TEXTCTRL20,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatAgiInput2TextEnter);
    Connect(ID_TEXTCTRL21,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatIntInput2TextEnter);
    Connect(ID_TEXTCTRL22,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatMPInput2TextEnter);
    Connect(ID_TEXTCTRL23,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&DamageAnalysisFrame::OnStatHPInput2TextEnter);
    Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DamageAnalysisFrame::OnaECBButtonRemoveClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnQuit);
    Connect(idSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnMenuSettingsSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnAbout);
    //*)
    //Initializing additional windows
    Frame1=new AnalysisLogs(this,wxNewId());
    Frame2=new effectsProperties(this,wxNewId());
    Frame3=new GameSettings(this,wxNewId());
    //Initializing Game rules
    GetGameRules();
    //Initializing main window   Initializing main window   Initializing main window   Initializing main window
    attackEffectsChoice2 = new wxChoice(attackEffectsCtrl, ID_CHOICE3, wxPoint(0,0), wxSize(176,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    defenseEffectsChoice2 = new wxChoice(defenseEffectsCtrl, ID_CHOICE4, wxPoint(0,0), wxSize(176,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    EffectChoiceFill();
    attackEffectsCtrl->InsertColumn(0, _("Effect name"));
    defenseEffectsCtrl->InsertColumn(0, _("Effect name"));
    attackEffectsCtrl->SetColumnWidth(0,215);
    defenseEffectsCtrl->SetColumnWidth(0,215);
    attackEffectsCtrl->InsertItem(0,_(" "));
    defenseEffectsCtrl->InsertItem(0,_(" "));
// ___ New event binds are placed here ___ New event binds are placed here ___ New event binds are placed here ___ New event binds are placed here
    BaseAttackDamageMinInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnBADamageMinLostFocus, this);
    BaseAttackDamageMaxInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnBADamageMaxLostFocus, this);
    WhiteDamageInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnWhiteDamageLostFocus, this);
    GreenDamageInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnGreenDamageLostFocus, this);
    BATInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnBATLostFocus, this);
    AttackSpeedInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnAttackSpeedLostFocus, this);
    LevelInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnLevelLostFocus, this);
    StatStrInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatStrLostFocus, this);
    StatAgiInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatAgiLostFocus, this);
    StatIntInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatIntLostFocus, this);
    StatHPInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatHPLostFocus, this);
    StatMPInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatMPLostFocus, this);
    StatHPRegenInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatHPRegenLostFocus, this);
    StatMPRegenInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatMPRegenLostFocus, this);
    ArmorInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnArmorLostFocus, this);
    MagicResistanceInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnMagicResistanceLostFocus, this);
    WithstandInput->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnWithstandLostFocus, this);
    LevelInput2->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnLevel2LostFocus, this);
    StatStrInput2->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatStr2LostFocus, this);
    StatAgiInput2->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatAgi2LostFocus, this);
    StatIntInput2->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatInt2LostFocus, this);
    StatHPInput2->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatHP2LostFocus, this);
    StatMPInput2->Bind(wxEVT_KILL_FOCUS, &DamageAnalysisFrame::OnStatMP2LostFocus, this);

    wxInitAllImageHandlers();
    SetClientSize(wxSize(700,510));

    heroLoadFile(heroVector);
    for (unsigned i=0;i<heroVector.size();i++)
    {
        heroUnit *heroPtr=&heroVector[i];
        Choice1->Append(heroVector[i].unitName,heroPtr);
        Choice2->Append(heroVector[i].unitName,heroPtr);
    }
    attackEffects.reserve(20);
    defenceEffects.reserve(20);
    Choice1->Select(0);
    Choice2->Select(0);
    attackEffectsChoice2->Select(0);
    defenseEffectsChoice2->Select(0);
    BaseAttackDamageMinInputWas='0';
    BaseAttackDamageMaxInputWas='0';
    heroTemp=(heroUnit *)Choice1->GetClientData(Choice1->GetSelection());
    heroAttTemp=(heroUnit *)Choice2->GetClientData(Choice2->GetSelection());
    Panel1->SetFocus();
}

DamageAnalysisFrame::~DamageAnalysisFrame()
{
    //(*Destroy(DamageAnalysisFrame)
    //*)
}

void DamageAnalysisFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DamageAnalysisFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("This program allows you to emulate the in-game fight process, involving receiver of damage - Defender, and dealer of damage - Attacker.\n\nMade by Siege. 2016"), _("Damage Analysis Tool"));
}

void DamageAnalysisFrame::OnClose(wxCloseEvent& event)
{
    Close();
}

void DamageAnalysisFrame::OnButton1Click1(wxCommandEvent& event)
{
    Frame1->RunAnalysis();
}

void DamageAnalysisFrame::OnWithstandLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(WithstandInput->GetValue()) || WithstandInput->GetValue()=="0")
    {
        WithstandInput->SetValue("1");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnWithstandInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnWithstandLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::EffectChoiceFill()
{
    for (std::map<std::string,basic_effect *>::iterator it=effectMapAttack.begin(); it!=effectMapAttack.end(); ++it)
    {
        attackEffectsChoice2->Append(it->second->Name,&(*it->second));
    }
    for (std::map<std::string,basic_effect *>::iterator it=effectMapDefense.begin(); it!=effectMapDefense.end(); ++it)
    {
        defenseEffectsChoice2->Append(it->second->Name,&(*it->second));
    }
    return;
}

/////////////////////////////////////////////////DEFENDER/////////////////////////////////////////////////////////////
void DamageAnalysisFrame::OnChoice1Select(wxCommandEvent& event)
{
    heroTemp=(heroUnit *)Choice1->GetClientData(Choice1->GetSelection());
    HeroFillForms();
    event.Skip();
}

void DamageAnalysisFrame::HeroFillForms()
{
    int Level=wxAtoi(LevelInput->GetValue());
    // ___ Processing stats:
    if (Level>1)
    {
        StatStrInput->SetValue(wxString::FromDouble(heroTemp->AttributeBaseStrength+(heroTemp->AttributeStrengthGain*(Level-1)),0));
        StatAgiInput->SetValue(wxString::FromDouble(heroTemp->AttributeBaseAgility+(heroTemp->AttributeAgilityGain*(Level-1)),0));
        StatIntInput->SetValue(wxString::FromDouble(heroTemp->AttributeBaseIntelligence+(heroTemp->AttributeIntelligenceGain*(Level-1)),0));
    }
    else
    {
        StatStrInput->SetValue(wxString::FromDouble(heroTemp->AttributeBaseStrength,0));
        StatAgiInput->SetValue(wxString::FromDouble(heroTemp->AttributeBaseAgility,0));
        StatIntInput->SetValue(wxString::FromDouble(heroTemp->AttributeBaseIntelligence,0));
    }
    // ___ Magic resist
    MagicResistanceInput->SetValue(wxString::FromDouble(heroTemp->MagicalResistance,0));
    // ___ Filling UI with fresh information:
    HeroFillForms(Strenght);
    HeroFillForms(Agility);
    HeroFillForms(Intelligence);
    return;
}

void DamageAnalysisFrame::HeroFillForms(StatTypes checkStat)
{
    if (checkStat==Strenght)
    {
        StatHPInput->SetValue(wxString::Format(wxT("%i"),heroTemp->StatusHealth+(wxAtoi(StatStrInput->GetValue())*gamerule_HPPerStr)));
        StatHPRegenInput->SetValue(wxString::FromDouble(heroTemp->StatusHealthRegen+((double)(wxAtoi(StatStrInput->GetValue()))*gamerule_HPRegenPerStr),2));
    }
    else if(checkStat==Agility)
    {
        ArmorInput->SetValue(wxString::FromDouble(heroTemp->ArmorPhysical+wxAtoi(StatAgiInput->GetValue())*gamerule_ArmorPerAgi,0));
    }
    else if (checkStat==Intelligence)
    {
        StatMPInput->SetValue(wxString::Format(wxT("%i"),heroTemp->StatusMana+(wxAtoi(StatIntInput->GetValue())*gamerule_MPPerInt)));
        StatMPRegenInput->SetValue(wxString::FromDouble(heroTemp->StatusManaRegen+((double)(wxAtoi(StatIntInput->GetValue()))*gamerule_MPRegenPerInt),2));
    }
    return;
}

void DamageAnalysisFrame::OnLevelInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnLevelLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnLevelLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(LevelInput->GetValue()))
    {
        LevelInput->SetValue("1");
    }
    HeroFillForms();
    event.Skip();
}

void DamageAnalysisFrame::OnStatStrLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatStrInput->GetValue()))
    {
        StatStrInput->SetValue("0");
    }
    HeroFillForms(Strenght);
    event.Skip();
}

void DamageAnalysisFrame::OnStatStrInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatStrLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatAgiLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatAgiInput->GetValue()))
    {
        StatAgiInput->SetValue("0");
    }
    HeroFillForms(Agility);
    event.Skip();
}

void DamageAnalysisFrame::OnStatAgiInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatAgiLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatIntLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatIntInput->GetValue()))
    {
        StatIntInput->SetValue("0");
    }
    HeroFillForms(Intelligence);
    event.Skip();
}

void DamageAnalysisFrame::OnStatIntInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatIntLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatHPLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatHPInput->GetValue()))
    {
        StatHPInput->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnStatHPInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatHPLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatMPLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatMPInput->GetValue()))
    {
        StatMPInput->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnStatMPInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatMPLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatHPRegenLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatHPRegenInput->GetValue()))
    {
        StatHPRegenInput->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnStatHPRegenInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatHPRegenLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatMPRegenLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatMPRegenInput->GetValue()))
    {
        StatMPRegenInput->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnStatMPRegenInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatMPRegenLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnArmorLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(ArmorInput->GetValue()))
    {
        ArmorInput->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnArmorInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnArmorLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnMagicResistanceInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnMagicResistanceLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnMagicResistanceLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(MagicResistanceInput->GetValue()))
    {
        MagicResistanceInput->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OndefenseEffectsCtrlItemActivated2(wxListEvent& event)
{
    int foundIndex;
    if ((foundIndex=defenseEffectsCtrl->GetNextItem(0, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        if (defenseEffectsCtrl->GetItemData(foundIndex)!=NULL)
        {
            Frame2->currEditObject=(void *)event.GetItem().GetData();
            ((basic_effect *)(Frame2->currEditObject))->FillPropertiesGrid(Frame2);
            Frame2->Show();
            Frame2->Restore();
            Frame2->Raise();
        }
    }
    event.Skip();
}

void DamageAnalysisFrame::OndECBButtonAddClick(wxCommandEvent& event)
{
    defenceEffects.push_back(((basic_effect *)defenseEffectsChoice2->GetClientData(defenseEffectsChoice2->GetSelection()))->getnewCopy());
    wxListItem tmpListItem;
    tmpListItem.SetId(wxNewId());
    std::vector<basic_effect *>::iterator tempVecIt2=defenceEffects.end()-1;
    tmpListItem.SetText((*tempVecIt2)->Name);
    tmpListItem.SetData(&(**tempVecIt2));
    defenseEffectsCtrl->InsertItem(tmpListItem);
    defenseEffectsCtrl->EnsureVisible(defenseEffectsCtrl->GetItemCount()-1);
    defenseEffectsCtrl->SetItemState(defenseEffectsCtrl->GetItemCount()-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void DamageAnalysisFrame::OndECBButtonRemoveClick(wxCommandEvent& event)
{
    std::vector<basic_effect *>::iterator tempVecIt2=defenceEffects.end()-1;
    int i=defenseEffectsCtrl->GetNextItem(-1,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (i!=-1 && i!=0)
    {
        int answer = wxMessageBox("Are you sure you want to delete this effect?", "Deleting effect", wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_WARNING, this);
        if (answer == wxOK)
        {
            int vectSize2=defenceEffects.size()-1;
            for (int j=defenceEffects.size()-1;vectSize2==defenceEffects.size()-1;j--,tempVecIt2--)
            {
                if (isSameRefAddress((*(basic_effect *)defenseEffectsCtrl->GetItemData(i)),**tempVecIt2)==true)
                {
                    delete (basic_effect *)defenseEffectsCtrl->GetItemData(i);
                    defenceEffects.erase(tempVecIt2);
                    defenseEffectsCtrl->DeleteItem(i);
                    Frame2->Hide();
                }
            }
        }
    }
}

/////////////////////////////////////////////////////ATTACKER///////////////////////////////////////////////////////
void DamageAnalysisFrame::OnChoice2Select1(wxCommandEvent& event)
{
    heroAttTemp=(heroUnit *)Choice2->GetClientData(Choice2->GetSelection());
    AttackerFillForms();
    event.Skip();
}

void DamageAnalysisFrame::AttackerFillForms()
{
    int Level=wxAtoi(LevelInput2->GetValue());
    // ___ Processing stats:
    if (Level>1)
    {
        StatStrInput2->SetValue(wxString::FromDouble(heroAttTemp->AttributeBaseStrength+(heroAttTemp->AttributeStrengthGain*(Level-1)),0));
        StatAgiInput2->SetValue(wxString::FromDouble(heroAttTemp->AttributeBaseAgility+(heroAttTemp->AttributeAgilityGain*(Level-1)),0));
        StatIntInput2->SetValue(wxString::FromDouble(heroAttTemp->AttributeBaseIntelligence+(heroAttTemp->AttributeIntelligenceGain*(Level-1)),0));
    }
    else
    {
        StatStrInput2->SetValue(wxString::FromDouble(heroAttTemp->AttributeBaseStrength,0));
        StatAgiInput2->SetValue(wxString::FromDouble(heroAttTemp->AttributeBaseAgility,0));
        StatIntInput2->SetValue(wxString::FromDouble(heroAttTemp->AttributeBaseIntelligence,0));
    }
    BATInput->SetValue(wxString::FromDouble(heroAttTemp->AttackRate,2));
    // ___ Filling UI with fresh information:
    AttackerFillForms(Strenght);
    AttackerFillForms(Agility);
    AttackerFillForms(Intelligence);
    return;
}

void DamageAnalysisFrame::AttackerFillForms(StatTypes checkStat)
{
    if (checkStat==Strenght)
    {
        StatHPInput2->SetValue(wxString::Format(wxT("%i"),heroAttTemp->StatusHealth+gamerule_HPPerStr*(wxAtoi(StatStrInput2->GetValue()))));
        if (heroAttTemp->AttributePrimary=="DOTA_ATTRIBUTE_STRENGTH")
        {
            BaseAttackDamageMinInput->SetValue(wxString::FromDouble(heroAttTemp->AttackDamageMin+wxAtoi(StatStrInput2->GetValue()),0));
            BaseAttackDamageMaxInput->SetValue(wxString::FromDouble(heroAttTemp->AttackDamageMax+wxAtoi(StatStrInput2->GetValue()),0));
            WhiteDamageCount();
        }
    }
    else if(checkStat==Agility)
    {
        AttackSpeedInput->SetValue(wxString::FromDouble(gamerule_StartIAS+wxAtoi(StatAgiInput2->GetValue()),0));
        if (heroAttTemp->AttributePrimary=="DOTA_ATTRIBUTE_AGILITY")
        {
            BaseAttackDamageMinInput->SetValue(wxString::FromDouble(heroAttTemp->AttackDamageMin+wxAtoi(StatAgiInput2->GetValue()),0));
            BaseAttackDamageMaxInput->SetValue(wxString::FromDouble(heroAttTemp->AttackDamageMax+wxAtoi(StatAgiInput2->GetValue()),0));
            WhiteDamageCount();
        }
    }
    else if (checkStat==Intelligence)
    {
        StatMPInput2->SetValue(wxString::Format(wxT("%i"),heroAttTemp->StatusMana+gamerule_MPPerInt*wxAtoi(StatIntInput2->GetValue())));
        if (heroAttTemp->AttributePrimary=="DOTA_ATTRIBUTE_INTELLECT")
        {
            BaseAttackDamageMinInput->SetValue(wxString::FromDouble(heroAttTemp->AttackDamageMin+wxAtoi(StatIntInput2->GetValue()),0));
            BaseAttackDamageMaxInput->SetValue(wxString::FromDouble(heroAttTemp->AttackDamageMax+wxAtoi(StatIntInput2->GetValue()),0));
            WhiteDamageCount();
        }
    }
    return;
}

void DamageAnalysisFrame::OnLevelInput2TextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnLevel2LostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnLevel2LostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(LevelInput2->GetValue()))
    {
        LevelInput2->SetValue("1");
    }
    AttackerFillForms();
    event.Skip();
}

void DamageAnalysisFrame::OnStatStr2LostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatStrInput2->GetValue()))
    {
        StatStrInput2->SetValue("0");
    }
    AttackerFillForms(Strenght);
    event.Skip();
}

void DamageAnalysisFrame::OnStatStrInput2TextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatStr2LostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatAgi2LostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatAgiInput2->GetValue()))
    {
        StatAgiInput2->SetValue("0");
    }
    AttackerFillForms(Agility);
    event.Skip();
}

void DamageAnalysisFrame::OnStatAgiInput2TextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatAgi2LostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatInt2LostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatIntInput2->GetValue()))
    {
        StatIntInput2->SetValue("0");
    }
    AttackerFillForms(Intelligence);
    event.Skip();
}

void DamageAnalysisFrame::OnStatIntInput2TextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatInt2LostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatHP2LostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatHPInput2->GetValue()))
    {
        StatHPInput2->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnStatHPInput2TextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatHP2LostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnStatMP2LostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(StatMPInput2->GetValue()))
    {
        StatMPInput2->SetValue("0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnStatMPInput2TextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnStatMP2LostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnBADamageMinLostFocus(wxFocusEvent& event)
{
    wxCommandEvent tmpEvt;
    DamageAnalysisFrame::OnBaseAttackDamageMinInputText(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnBADamageMaxLostFocus(wxFocusEvent& event)
{
    wxCommandEvent tmpEvt;
    DamageAnalysisFrame::OnBaseAttackDamageMaxInputText(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnWhiteDamageLostFocus(wxFocusEvent& event)
{
    wxCommandEvent tmpEvt;
    DamageAnalysisFrame::OnWhiteDamageInputText(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnBaseAttackDamageMinInputText(wxCommandEvent& event)
{
    wxString tmpDmg=BaseAttackDamageMinInput->GetValue();
    if (wxIsEmpty(tmpDmg))
    {
        BaseAttackDamageMinInput->SetValue('0');
    }
    else if (!tmpDmg.IsSameAs(BaseAttackDamageMinInputWas))
    {
        BaseAttackDamageMinInputWas=tmpDmg;
    }
    WhiteDamageCount();
    event.Skip();
}

void DamageAnalysisFrame::OnBaseAttackDamageMaxInputText(wxCommandEvent& event)
{
    wxString tmpDmg=BaseAttackDamageMaxInput->GetValue();
    if (wxIsEmpty(tmpDmg))
    {
        BaseAttackDamageMaxInput->SetValue('0');
    }
    else if (!tmpDmg.IsSameAs(BaseAttackDamageMaxInputWas))
    {
        BaseAttackDamageMaxInputWas=tmpDmg;
    }
    WhiteDamageCount();
    event.Skip();
}

void DamageAnalysisFrame::OnWhiteDamageInputText(wxCommandEvent& event)
{
    event.Skip();
}

void DamageAnalysisFrame::WhiteDamageCount()
{
    double minimal=wxAtoi(BaseAttackDamageMinInput->GetValue());
    double maximal=wxAtoi(BaseAttackDamageMaxInput->GetValue());
    if (minimal==0)
    {
        wxString DamageString=wxString::Format(wxT("%i"),(unsigned)maximal);
        WhiteDamageInput->SetValue(DamageString);
        return;
    }
    if (maximal==0)
    {
        wxString DamageString=wxString::Format(wxT("%i"),(unsigned)minimal);
        WhiteDamageInput->SetValue(DamageString);
        return;
    }
    wxString DamageString=wxString::Format(wxT("%i"),(unsigned)((minimal+maximal)/2));
    WhiteDamageInput->SetValue(DamageString);
}

void DamageAnalysisFrame::OnGreenDamageInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnGreenDamageLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnGreenDamageLostFocus(wxFocusEvent& event)
{
    wxString checkEmptyS=GreenDamageInput->GetValue();
    if (wxIsEmpty(checkEmptyS))
    {
        GreenDamageInput->SetValue('0');
    }
    event.Skip();
}

void DamageAnalysisFrame::OnBATInputTextEnter(wxCommandEvent& event)
{
    wxFocusEvent tmpEvt;
    DamageAnalysisFrame::OnBATLostFocus(tmpEvt);
    event.Skip();
}

void DamageAnalysisFrame::OnBATLostFocus(wxFocusEvent& event)
{
    double tmpData=wxAtof(BATInput->GetValue());
    if (wxIsEmpty(BATInput->GetValue()) || tmpData<=0)
    {
        BATInput->SetValue("1.0");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnAttackSpeedInputTextEnter(wxCommandEvent& event)
{
        wxFocusEvent tmpEvt;
        DamageAnalysisFrame::OnAttackSpeedLostFocus(tmpEvt);
        event.Skip();
}

void DamageAnalysisFrame::OnAttackSpeedLostFocus(wxFocusEvent& event)
{
    if (wxIsEmpty(AttackSpeedInput->GetValue()))
    {
        AttackSpeedInput->SetValue(wxString::Format(wxT("%i"),gamerule_StartIAS));
    }
    else if (AttackSpeedInput->GetValue()=="0")
    {
        AttackSpeedInput->SetValue("20");
    }
    event.Skip();
}

void DamageAnalysisFrame::OnattackEffectsCtrlItemActivated(wxListEvent& event)
{
    int foundIndex=0;
    if ((foundIndex=attackEffectsCtrl->GetNextItem(0, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        if (attackEffectsCtrl->GetItemData(foundIndex)!=NULL)
        {
            Frame2->currEditObject=(void *)event.GetItem().GetData();
            ((basic_effect *)(Frame2->currEditObject))->FillPropertiesGrid(Frame2);
            Frame2->Show();
            Frame2->Restore();
            Frame2->Raise();
        }
    }
    event.Skip();
}

void DamageAnalysisFrame::OnaECBButtonAddClick(wxCommandEvent& event)
{
    attackEffects.push_back(((basic_effect *)attackEffectsChoice2->GetClientData(attackEffectsChoice2->GetSelection()))->getnewCopy());
    wxListItem tmpListItem;
    tmpListItem.SetId(wxNewId());
    std::vector<basic_effect *>::iterator tempVecIt=attackEffects.end()-1;
    tmpListItem.SetText((*tempVecIt)->Name);
    tmpListItem.SetData(&(**tempVecIt));
    attackEffectsCtrl->InsertItem(tmpListItem);
    attackEffectsCtrl->EnsureVisible(attackEffectsCtrl->GetItemCount()-1);
    attackEffectsCtrl->SetItemState(attackEffectsCtrl->GetItemCount()-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void DamageAnalysisFrame::OnaECBButtonRemoveClick(wxCommandEvent& event)
{
    std::vector<basic_effect *>::iterator tempVecIt=attackEffects.end()-1;
    int i=attackEffectsCtrl->GetNextItem(-1,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (i!=-1 && i!=0)
    {
        int answer = wxMessageBox("Are you sure you want to delete this effect?", "Deleting effect", wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxICON_WARNING, this);
        if (answer == wxOK)
        {
            int vectSize=attackEffects.size()-1;
            for (int j=attackEffects.size()-1;vectSize==attackEffects.size()-1;j--,tempVecIt--)
            {
                if (isSameRefAddress((*(basic_effect *)attackEffectsCtrl->GetItemData(i)),**tempVecIt)==true)
                {
                    delete (basic_effect *)attackEffectsCtrl->GetItemData(i);
                    attackEffects.erase(tempVecIt);
                    attackEffectsCtrl->DeleteItem(i);
                    Frame2->Hide();
                }
            }
        }
    }
}

void DamageAnalysisFrame::OnMenuSettingsSelected(wxCommandEvent& event)
{
    Frame3->Show();
    Frame3->Restore();
    Frame3->Raise();
}
