/***************************************************************
 * Name:      DamageAnalysisMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2016-02-05
 * Copyright:  ()
 * License:
 **************************************************************/
//(*InternalHeaders(DamageAnalysisFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "DamageAnalysisMain.h"

DamageAnalysisFrame *DamageInputWindow;

const double speedBATPart=5.72;
const double speedBATStart=-100;

wxImageList* myImages=new wxImageList(14,14);

wxString BaseAttackDamageMinInputWas;
wxString BaseAttackDamageMaxInputWas;

wxKeyboardState myKeyHandler;
std::vector<double> magicResistanceBuffer;

extern heroUnit *heroTemp;
extern std::vector<heroUnit> heroVector;

extern std::map<std::string,basic_effect *> effectMapAttack;
extern std::map<std::string,basic_effect *> effectMapDefense;

extern std::vector<basic_effect *> attackEffects;
extern std::vector<basic_effect *> defenceEffects;
extern std::vector<effect_critical_damage> critEffects;
extern std::vector<effect_block_damage> shieldBlockEffects;

extern double addWhiteDmg;
extern double  ARReduct, InDamageBase, InDamage, InDamageRaw, InDamageMagic, InDamageNoReduct, aps, attackPerSecondPart, magicResist, InDamagePerCycle, InDamageMagicPerCycle, InDamageNoReductPerCycle;
extern int statstr, statint, statagi, HP, MP, DoDoubleHit, armor;

extern AnalysisLogs *Frame1;
extern effectsProperties *Frame2;

double attackTimeParts=0;
double attackHits=0;
double Withstanded, IAS, BATD;

wxIntegerValidator<unsigned long>numsOnlyValidator(NULL, wxNUM_VAL_THOUSANDS_SEPARATOR);
wxIntegerValidator<long>numsOnlyValidatorSigned(NULL, wxNUM_VAL_THOUSANDS_SEPARATOR);
wxFloatingPointValidator<double>numsFloatOnlyValidator(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);
wxFloatingPointValidator<double>numsFloatOnlyValidatorSigned(NULL, wxNUM_VAL_NO_TRAILING_ZEROES);

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(DamageAnalysisFrame)
const long DamageAnalysisFrame::ID_CHOICE1 = wxNewId();
const long DamageAnalysisFrame::ID_BUTTON1 = wxNewId();
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
const long DamageAnalysisFrame::ID_PANEL1 = wxNewId();
const long DamageAnalysisFrame::ID_BUTTON2 = wxNewId();
const long DamageAnalysisFrame::ID_PANEL2 = wxNewId();
const long DamageAnalysisFrame::ID_PANEL3 = wxNewId();
const long DamageAnalysisFrame::ID_NOTEBOOK1 = wxNewId();
const long DamageAnalysisFrame::idMenuQuit = wxNewId();
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

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(700,510));
    SetMinSize(wxSize(700,510));
    SetMaxSize(wxSize(700,510));
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(56,56), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Choice1 = new wxChoice(Panel1, ID_CHOICE1, wxPoint(16,16), wxSize(168,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Analyze"), wxPoint(560,376), wxSize(115,31), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    LevelInput = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("1"), wxPoint(224,16), wxSize(54,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL1"));
    LvlInputText = new wxStaticText(Panel1, ID_STATICTEXT1, _("Level"), wxPoint(192,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StatStrText = new wxStaticText(Panel1, ID_STATICTEXT2, _("STR"), wxPoint(24,48), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StatAgiText = new wxStaticText(Panel1, ID_STATICTEXT3, _("AGI"), wxPoint(96,48), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StatStrInput = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("0"), wxPoint(48,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL2"));
    StatAgiInput = new wxTextCtrl(Panel1, ID_TEXTCTRL3, _("0"), wxPoint(120,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL3"));
    StatIntInput = new wxTextCtrl(Panel1, ID_TEXTCTRL4, _("0"), wxPoint(192,48), wxSize(40,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL4"));
    StatHPRegenInput = new wxTextCtrl(Panel1, ID_TEXTCTRL5, _("0"), wxPoint(176,88), wxSize(48,21), wxTE_PROCESS_ENTER, numsFloatOnlyValidatorSigned, _T("ID_TEXTCTRL5"));
    StatMPRegenInput = new wxTextCtrl(Panel1, ID_TEXTCTRL7, _("0"), wxPoint(176,112), wxSize(48,21), wxTE_PROCESS_ENTER, numsFloatOnlyValidatorSigned, _T("ID_TEXTCTRL7"));
    RegenText = new wxStaticText(Panel1, ID_STATICTEXT5, _("Regeneration"), wxPoint(168,72), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StatIntText = new wxStaticText(Panel1, ID_STATICTEXT4, _("INT"), wxPoint(168,48), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StatHealthText = new wxStaticText(Panel1, ID_STATICTEXT8, _("Health"), wxPoint(24,88), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StatManaText = new wxStaticText(Panel1, ID_STATICTEXT9, _("Mana"), wxPoint(32,112), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StatHPInput = new wxTextCtrl(Panel1, ID_TEXTCTRL6, _("0"), wxPoint(64,88), wxSize(112,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL6"));
    StatMPInput = new wxTextCtrl(Panel1, ID_TEXTCTRL8, _("0"), wxPoint(64,112), wxSize(112,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL8"));
    BaseAttackDamageText = new wxStaticText(Panel1, ID_STATICTEXT6, _("Base attack damage"), wxPoint(465,50), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BaseAttackDamageMinInput = new wxTextCtrl(Panel1, ID_TEXTCTRL9, _("0"), wxPoint(566,48), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL9"));
    BaseAttackDamageMaxInput = new wxTextCtrl(Panel1, ID_TEXTCTRL10, _("0"), wxPoint(625,48), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL10"));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT7, _("-"), wxPoint(617,50), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    WhiteDamageInput = new wxTextCtrl(Panel1, ID_TEXTCTRL11, _("0"), wxPoint(592,72), wxSize(56,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL11"));
    WhiteDamageText = new wxStaticText(Panel1, ID_STATICTEXT10, _("White damage"), wxPoint(515,75), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    GreenDamageText = new wxStaticText(Panel1, ID_STATICTEXT11, _("Green[Bonus] damage"), wxPoint(477,98), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    GreenDamageInput = new wxTextCtrl(Panel1, ID_TEXTCTRL12, _("0"), wxPoint(592,96), wxSize(56,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL12"));
    BATText = new wxStaticText(Panel1, ID_STATICTEXT12, _("Base attack speed"), wxPoint(496,123), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    BATInput = new wxTextCtrl(Panel1, ID_TEXTCTRL13, _("1.0"), wxPoint(592,120), wxSize(40,21), wxTE_PROCESS_ENTER, numsFloatOnlyValidator, _T("ID_TEXTCTRL13"));
    AttackSpeedInput = new wxTextCtrl(Panel1, ID_TEXTCTRL14, _("100"), wxPoint(592,144), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL14"));
    AttackSpeedText = new wxStaticText(Panel1, ID_STATICTEXT13, _("Attack speed"), wxPoint(520,147), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    MagicalResistanceText = new wxStaticText(Panel1, ID_STATICTEXT14, _("Magical Resistance"), wxPoint(120,136), wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    MagicResistanceInput = new wxTextCtrl(Panel1, ID_TEXTCTRL15, _("0"), wxPoint(216,136), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL15"));
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT15, _("%"), wxPoint(272,136), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    WithstandInput = new wxTextCtrl(Panel1, ID_TEXTCTRL16, _("1"), wxPoint(344,96), wxSize(56,21), wxTE_PROCESS_ENTER, numsOnlyValidator, _T("ID_TEXTCTRL16"));
    WithstandText = new wxStaticText(Panel1, ID_STATICTEXT16, _("Withstand"), wxPoint(288,96), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    WithstandText2 = new wxStaticText(Panel1, ID_STATICTEXT17, _("seconds"), wxPoint(408,96), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    ArmorText = new wxStaticText(Panel1, ID_STATICTEXT18, _("Armor"), wxPoint(32,136), wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    ArmorInput = new wxTextCtrl(Panel1, ID_TEXTCTRL17, _("0"), wxPoint(64,136), wxSize(48,21), wxTE_PROCESS_ENTER, numsOnlyValidatorSigned, _T("ID_TEXTCTRL17"));
    attackEffectsCtrl = new wxListCtrl(Panel1, ID_LISTCTRL1, wxPoint(32,168), wxSize(216,232), wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL1"));
    wxFont attackEffectsCtrlFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    attackEffectsCtrl->SetFont(attackEffectsCtrlFont);
    defenseEffectsCtrl = new wxListCtrl(Panel1, ID_LISTCTRL2, wxPoint(456,168), wxSize(216,192), wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL2"));
    wxFont defenseEffectsCtrlFont(11,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    defenseEffectsCtrl->SetFont(defenseEffectsCtrlFont);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Button2 = new wxButton(Panel2, ID_BUTTON2, _("Generate"), wxPoint(560,376), wxSize(115,31), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Notebook1->AddPage(Panel1, _("Damage"), true);
    Notebook1->AddPage(Panel2, _("Statistics"), false);
    Notebook1->AddPage(Panel3, _("Mana cost"), false);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
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
    SingleInstanceChecker1.Create(wxTheApp->GetAppName() + _T("_") + wxGetUserId() + _T("_Guard"));

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnChoice1Select);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DamageAnalysisFrame::OnButton1Click1);
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
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DamageAnalysisFrame::OnAbout);
    //*)
    //Initializing main window   Initializing main window   Initializing main window   Initializing main window
    attackEffectsChoice2 = new wxChoice(attackEffectsCtrl, ID_CHOICE3, wxPoint(0,0), wxSize(176,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    defenseEffectsChoice2 = new wxChoice(defenseEffectsCtrl, ID_CHOICE4, wxPoint(0,0), wxSize(176,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    attackEffectsChoice2->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &DamageAnalysisFrame::OnChoice3Select, this);
    EffectChoiceFill();
    defenseEffectsChoice2->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &DamageAnalysisFrame::OnChoice4Select, this);
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
    Panel1->Bind(wxEVT_CHAR_HOOK, &DamageAnalysisFrame::OnKeyDown, this);
    attackEffectsChoice2->Bind(wxEVT_MOUSEWHEEL, &DamageAnalysisFrame::OnMousewheel, this);
    defenseEffectsChoice2->Bind(wxEVT_MOUSEWHEEL, &DamageAnalysisFrame::OnMousewheel, this);

    wxInitAllImageHandlers();
    SetClientSize(wxSize(700,510));

    heroLoadFile(heroVector);
    unsigned i;
    for (i=0;i<heroVector.size();i++)
    {
        heroUnit *heroPtr=&heroVector[i];
        Choice1->Append(heroVector[i].unitName,heroPtr);
    }
    Choice1->Select(0);
    BaseAttackDamageMinInputWas=BaseAttackDamageMinInput->GetValue();
    BaseAttackDamageMaxInputWas=BaseAttackDamageMaxInput->GetValue();
    heroTemp=(heroUnit *)Choice1->GetClientData(Choice1->GetSelection());
    Panel1->SetFocus();
}

DamageAnalysisFrame::~DamageAnalysisFrame()
{
    //(*Destroy(DamageAnalysisFrame)
    //*)
//    Frame1->Destroy();
//    Frame2->Destroy();
}

void DamageAnalysisFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DamageAnalysisFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void DamageAnalysisFrame::OnClose(wxCloseEvent& event)
{
    Close();
}

void DamageAnalysisFrame::OnButton1Click(wxCommandEvent& event)
{
}

void DamageAnalysisFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void DamageAnalysisFrame::OnBADamageMinLostFocus(wxFocusEvent& event)
{
wxString tmpDmg=BaseAttackDamageMinInput->GetValue();
if (tmpDmg.IsSameAs(BaseAttackDamageMinInputWas))
{
    event.Skip();
    return;
}
else
{
    addWhiteDmg=0;
    WhiteDamageInput->SetValue('0');
    wxCommandEvent tmpEvt;
    BaseAttackDamageMinInputWas=tmpDmg;
    DamageAnalysisFrame::OnWhiteDamageInputText(tmpEvt);
}
event.Skip();
}

void DamageAnalysisFrame::OnBADamageMaxLostFocus(wxFocusEvent& event)
{
wxString tmpDmg=BaseAttackDamageMaxInput->GetValue();
if (tmpDmg.IsSameAs(BaseAttackDamageMaxInputWas))
{
    event.Skip();
    return;
}
else
{
    addWhiteDmg=0;
    WhiteDamageInput->SetValue('0');
    wxCommandEvent tmpEvt;
    BaseAttackDamageMaxInputWas=tmpDmg;
    DamageAnalysisFrame::OnWhiteDamageInputText(tmpEvt);
}
event.Skip();
}

void DamageAnalysisFrame::OnWhiteDamageLostFocus(wxFocusEvent& event)
{
wxCommandEvent tmpEvt;
DamageAnalysisFrame::OnWhiteDamageInputText(tmpEvt);
event.Skip();
}

void DamageAnalysisFrame::OnButton1Click1(wxCommandEvent& event)
{
// ___ Generate hero data damage log ___ Generate hero data damage log ___ Generate hero data damage log ___ Generate hero data damage log
Frame1->RunAnalysis();
}

void DamageAnalysisFrame::OnBaseAttackDamageMinInputText(wxCommandEvent& event)
{
    wxString tmpDmg=BaseAttackDamageMinInput->GetValue();
    if (tmpDmg.IsSameAs(BaseAttackDamageMinInputWas))
    {
        event.Skip();
        return;
    }
    else
    {
    addWhiteDmg=0;
    WhiteDamageInput->SetValue('0');
    BaseAttackDamageMinInputWas=tmpDmg;
    DamageAnalysisFrame::OnWhiteDamageInputText(event);
    }
    event.Skip();
}

void DamageAnalysisFrame::OnBaseAttackDamageMaxInputText(wxCommandEvent& event)
{
    wxString tmpDmg=BaseAttackDamageMaxInput->GetValue();
    if (tmpDmg.IsSameAs(BaseAttackDamageMaxInputWas))
    {
        event.Skip();
        return;
    }
    else
    {
    addWhiteDmg=0;
    WhiteDamageInput->SetValue('0');
    BaseAttackDamageMaxInputWas=tmpDmg;
    DamageAnalysisFrame::OnWhiteDamageInputText(event);
    }
    event.Skip();
}

void DamageAnalysisFrame::OnWhiteDamageInputText(wxCommandEvent& event)
{
    double dmgTmpD,dmgTmpD2;
    unsigned tmpInt;
    wxString dmgTmp=WhiteDamageInput->GetValue();
    DamageAnalysisFrame::WhiteDamageCount();
    wxString dmgTmp2=WhiteDamageInput->GetValue();
    dmgTmpD=wxAtof(dmgTmp);
    dmgTmpD2=wxAtof(dmgTmp2);
    if (dmgTmpD2>=dmgTmpD)
    {
        addWhiteDmg=0;
        event.Skip();
        return;
    }
    else if (dmgTmpD2<dmgTmpD)
    {
        addWhiteDmg=dmgTmpD-dmgTmpD2;
        tmpInt=static_cast<unsigned int>(dmgTmpD2+addWhiteDmg);
        wxString DamageString=wxString::Format(wxT("%i"),tmpInt);
        WhiteDamageInput->SetValue(DamageString);
        tmpInt=static_cast<unsigned int>(addWhiteDmg);
        DamageString=wxString::Format(wxT("%i"),tmpInt);
    }
    event.Skip();
}

void DamageAnalysisFrame::WhiteDamageCount()
{
double minimal, maximal,tmpDmg;
unsigned dmgSum;
wxString dmgMin=BaseAttackDamageMinInput->GetValue();
wxString dmgMax=BaseAttackDamageMaxInput->GetValue();
wxString dmgWhite=WhiteDamageInput->GetValue();
if (wxIsEmpty(dmgMin))
{
    BaseAttackDamageMinInput->SetValue('0');
}
if (wxIsEmpty(dmgMax))
{
    BaseAttackDamageMaxInput->SetValue('0');
}
if (wxIsEmpty(dmgWhite))
{
    WhiteDamageInput->SetValue('0');
}
maximal=wxAtof(dmgMax);
minimal=wxAtof(dmgMin);
if (minimal<0)
{
    minimal=0;
}
if (maximal<0)
{
    maximal=0;
}
if (minimal==0 && maximal==0)
{
    return;
}
if (minimal==0)
{
    dmgSum=static_cast<unsigned int>(maximal);
    wxString DamageString=wxString::Format(wxT("%i"),dmgSum);
    WhiteDamageInput->SetValue(DamageString);
    return;
}
if (maximal==0)
{
    dmgSum=static_cast<unsigned int>(minimal);
    wxString DamageString=wxString::Format(wxT("%i"),dmgSum);
    WhiteDamageInput->SetValue(DamageString);
    return;
}
tmpDmg=(minimal+maximal)/2;
dmgSum=static_cast<unsigned int>(tmpDmg);
wxString DamageString=wxString::Format(wxT("%i"),dmgSum);
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
wxString checkEmptyS=BATInput->GetValue();
if (wxIsEmpty(checkEmptyS))
{
    BATInput->SetValue("1.0");
}
if (checkEmptyS.IsSameAs('0'))
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
wxString checkEmptyS=AttackSpeedInput->GetValue();
if (wxIsEmpty(checkEmptyS))
{
    AttackSpeedInput->SetValue("100");
}
else if (checkEmptyS=="0")
{
    AttackSpeedInput->SetValue("20");
}
event.Skip();
}

void DamageAnalysisFrame::OnChoice1Select(wxCommandEvent& event)
{
heroTemp=(heroUnit *)Choice1->GetClientData(Choice1->GetSelection());
HeroFillForms();
event.Skip();
}

void DamageAnalysisFrame::HeroFillForms()
{
int Level;
Level=wxAtoi(LevelInput->GetValue());
// ___ Processing stats:
// ___ STR
if (Level>1)
{
    statstr=(double)heroTemp->AttributeBaseStrength+(heroTemp->AttributeStrengthGain*(Level-1));
}
else
{
    statstr=heroTemp->AttributeBaseStrength;
}
StatStrInput->SetValue(wxString::Format(wxT("%i"),statstr));
HeroFillForms("str");
// ___ AGI
if (Level>1)
{
    statagi=(double)heroTemp->AttributeBaseAgility+(heroTemp->AttributeAgilityGain*(Level-1));
}
else
{
    statagi=heroTemp->AttributeBaseAgility;
}
StatAgiInput->SetValue(wxString::Format(wxT("%i"),statagi));
HeroFillForms("agi");
// ___ INT
if (Level>1)
{
    statint=(double)heroTemp->AttributeBaseIntelligence+(heroTemp->AttributeIntelligenceGain*(Level-1));
}
else
{
    statint=heroTemp->AttributeBaseIntelligence;
}
StatIntInput->SetValue(wxString::Format(wxT("%i"),statint));
HeroFillForms("int");
// ___ Processing secondary parameters
HP=heroTemp->StatusHealth;
if (statstr!=0)
{
    HP=(double)HP+(19*statstr);
}
StatHPInput->SetValue(wxString::Format(wxT("%i"),HP));
// ___ Magic resist
magicResist=1-(heroTemp->MagicalResistance/100);
magicResistanceBuffer.push_back(magicResist);
MagicResistanceInput->SetValue(wxString::Format(wxT("%i"),heroTemp->MagicalResistance));
    return;
}

void DamageAnalysisFrame::HeroFillForms(wxString checkStat)
{
int tmpI;
double tmpD;
if (checkStat=="str")
{
if (statstr!=0)
{
    tmpI=heroTemp->StatusHealth+(19*statstr);
    StatHPInput->SetValue(wxString::Format(wxT("%i"),tmpI));
    tmpD=(double)heroTemp->StatusHealthRegen+(0.03*statstr);
    StatHPRegenInput->SetValue(wxString::Format(wxT("%f"),tmpD));
}
else
{
    tmpI=heroTemp->StatusHealth;
    StatHPInput->SetValue(wxString::Format(wxT("%i"),tmpI));
    tmpD=(double)heroTemp->StatusHealthRegen;
    StatHPRegenInput->SetValue(wxString::Format(wxT("%f"),tmpD));
}
}
else if(checkStat=="agi")
{
if (statagi!=0)
{
    tmpI=(double)heroTemp->ArmorPhysical+(0.14*statagi);
    ArmorInput->SetValue(wxString::Format(wxT("%i"),tmpI));
}
else
{
    tmpI=(double)heroTemp->ArmorPhysical;
    ArmorInput->SetValue(wxString::Format(wxT("%i"),tmpI));
}
}
else if (checkStat=="int")
{
if (statint!=0)
{
    tmpI=heroTemp->StatusMana+(13*statint);
    StatMPInput->SetValue(wxString::Format(wxT("%i"),tmpI));
    tmpD=(double)heroTemp->StatusManaRegen+(0.04*statint);
    StatMPRegenInput->SetValue(wxString::Format(wxT("%f"),tmpD));
}
else
{
    tmpI=heroTemp->StatusMana;
    StatMPInput->SetValue(wxString::Format(wxT("%i"),tmpI));
    tmpD=(double)heroTemp->StatusManaRegen;
    StatMPRegenInput->SetValue(wxString::Format(wxT("%f"),tmpD));
}
}
return;
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

void DamageAnalysisFrame::OnLevelLostFocus(wxFocusEvent& event)
{
if (wxIsEmpty(LevelInput->GetValue()))
{
    LevelInput->SetValue("1");
}
HeroFillForms();
event.Skip();
}

void DamageAnalysisFrame::OnLevelInputTextEnter(wxCommandEvent& event)
{
wxFocusEvent tmpEvt;
DamageAnalysisFrame::OnLevelLostFocus(tmpEvt);
event.Skip();
}

void DamageAnalysisFrame::OnStatStrLostFocus(wxFocusEvent& event)
{
if (wxIsEmpty(StatStrInput->GetValue()))
{
    StatStrInput->SetValue("0");
}
int tmpI;
tmpI=wxAtoi(StatStrInput->GetValue());
statstr=tmpI;
HeroFillForms("str");
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
int tmpI;
tmpI=wxAtoi(StatAgiInput->GetValue());
statagi=tmpI;
HeroFillForms("agi");
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
int tmpI;
tmpI=wxAtoi(StatIntInput->GetValue());
statint=tmpI;
HeroFillForms("int");
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

void DamageAnalysisFrame::OnMagicResistanceLostFocus(wxFocusEvent& event)
{
if (wxIsEmpty(MagicResistanceInput->GetValue()))
{
    MagicResistanceInput->SetValue("0");
}

event.Skip();
}

void DamageAnalysisFrame::OnMagicResistanceInputTextEnter(wxCommandEvent& event)
{
wxFocusEvent tmpEvt;
DamageAnalysisFrame::OnMagicResistanceLostFocus(tmpEvt);
event.Skip();
}

void DamageAnalysisFrame::OnWithstandLostFocus(wxFocusEvent& event)
{
if (wxIsEmpty(WithstandInput->GetValue()))
{
    WithstandInput->SetValue("1");
}
if (WithstandInput->GetValue()=="0")
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

void DamageAnalysisFrame::OnKeyDown(wxKeyEvent& event)
{
if (wxGetKeyState(WXK_RETURN))
{
    if (attackEffectsChoice2->HasFocus())
    {
        wxCommandEvent tmpEvt;
        DamageAnalysisFrame::OnChoice3Select(tmpEvt);
    }
    if (defenseEffectsChoice2->HasFocus())
    {
        wxCommandEvent tmpEvt;
        DamageAnalysisFrame::OnChoice4Select(tmpEvt);
    }
}
event.Skip();
}

void DamageAnalysisFrame::OnMousewheel(wxMouseEvent& event)
{
}

void DamageAnalysisFrame::OnChoice3Select(wxCommandEvent& event)
{
if (!wxGetKeyState(WXK_UP) && !wxGetKeyState(WXK_DOWN) && !wxGetKeyState(WXK_LEFT) && !wxGetKeyState(WXK_RIGHT))
{
    attackEffects.push_back(((basic_effect *)attackEffectsChoice2->GetClientData(event.GetSelection()))->getnewCopy());
    wxListItem tmpListItem;
    tmpListItem.SetId(wxNewId());
    std::vector<basic_effect *>::iterator tempVecIt=attackEffects.end()-1;
    tmpListItem.SetText((*tempVecIt)->Name);
    (*tempVecIt)->index=wxNewId();
    tmpListItem.SetData(&(**tempVecIt));
    //wxMessageBox(((basic_effect *)tmpListItem.GetData())->Name, _("I want you to see this ;)"));
    attackEffectsCtrl->InsertItem(tmpListItem);
}
event.Skip();
}

void DamageAnalysisFrame::OnChoice4Select(wxCommandEvent& event)
{
    if (!wxGetKeyState(WXK_UP) && !wxGetKeyState(WXK_DOWN) && !wxGetKeyState(WXK_LEFT) && !wxGetKeyState(WXK_RIGHT))
    {
        defenceEffects.push_back(((basic_effect *)defenseEffectsChoice2->GetClientData(event.GetSelection()))->getnewCopy());
        wxListItem tmpListItem;
        tmpListItem.SetId(wxNewId());
        std::vector<basic_effect *>::iterator tempVecIt=defenceEffects.end()-1;
        tmpListItem.SetText((*tempVecIt)->Name);
        (*tempVecIt)->index=wxNewId();
        tmpListItem.SetData(&(**tempVecIt));
        defenseEffectsCtrl->InsertItem(tmpListItem);
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
    ((basic_effect *)event.GetItem().GetData())->FillPropertiesGrid(Frame2);
    Frame2->itemID=event.GetId();
    Frame2->Show();
    Frame2->Restore();
    Frame2->Raise();
    }
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
        ((basic_effect *)event.GetItem().GetData())->FillPropertiesGrid(Frame2);
        Frame2->itemID=event.GetId();
        Frame2->Show();
        Frame2->Restore();
        Frame2->Raise();
    }
}
event.Skip();
}
