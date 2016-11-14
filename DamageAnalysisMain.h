/***************************************************************
 * Name:      DamageAnalysisMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2016-02-05
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DAMAGEANALYSISMAIN_H
#define DAMAGEANALYSISMAIN_H

//(*Headers(DamageAnalysisFrame)
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include "commonIncludes.h"
#include "GameSettings.h"
#include "heroData.h"
#include "effects.h" // <--- contains effectProperties.h
#include "AnalysisLogs.h"
#include "heroDataLoad.h" // <--- contains Vectors.h

class DamageAnalysisFrame: public wxFrame
{
    public:
        DamageAnalysisFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DamageAnalysisFrame();
        void WhiteDamageCount();
        void HeroFillForms();
        void HeroFillForms(StatTypes checkStat);
        void AttackerFillForms();
        void AttackerFillForms(StatTypes checkStat);
        void EffectChoiceFill();
        void OnBADamageMinLostFocus(wxFocusEvent& event);
        void OnBADamageMaxLostFocus(wxFocusEvent& event);
        void OnWhiteDamageLostFocus(wxFocusEvent& event);
        void OnGreenDamageLostFocus(wxFocusEvent& event);
        void OnBATLostFocus(wxFocusEvent& event);
        void OnAttackSpeedLostFocus(wxFocusEvent& event);
        void OnLevelLostFocus(wxFocusEvent& event);
        void OnStatStrLostFocus(wxFocusEvent& event);
        void OnStatAgiLostFocus(wxFocusEvent& event);
        void OnStatIntLostFocus(wxFocusEvent& event);
        void OnStatHPLostFocus(wxFocusEvent& event);
        void OnStatMPLostFocus(wxFocusEvent& event);
        void OnStatHPRegenLostFocus(wxFocusEvent& event);
        void OnStatMPRegenLostFocus(wxFocusEvent& event);
        void OnArmorLostFocus(wxFocusEvent& event);
        void OnMagicResistanceLostFocus(wxFocusEvent& event);
        void OnLevel2LostFocus(wxFocusEvent& event);
        void OnStatStr2LostFocus(wxFocusEvent& event);
        void OnStatAgi2LostFocus(wxFocusEvent& event);
        void OnStatInt2LostFocus(wxFocusEvent& event);
        void OnStatHP2LostFocus(wxFocusEvent& event);
        void OnStatMP2LostFocus(wxFocusEvent& event);
        void OnWithstandLostFocus(wxFocusEvent& event);
        template<typename T> bool isSameRefAddress(T &, T &);
        //(*Handlers(DamageAnalysisFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnTextCtrl3Text(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnTextCtrl3Text1(wxCommandEvent& event);
        void OnTextCtrl4Text(wxCommandEvent& event);
        void OnTextCtrl5Text(wxCommandEvent& event);
        void OnNotebook1PageChanged(wxNotebookEvent& event);
        void OnClose1(wxCloseEvent& event);
        void OnNotebook1PageChanged1(wxNotebookEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnLeftDClick(wxMouseEvent& event);
        void OnTextCtrl1Text1(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnTextCtrl1Text2(wxCommandEvent& event);
        void OnTextCtrl2Text1(wxCommandEvent& event);
        void OnBaseAttackDamageMinInputText(wxCommandEvent& event);
        void OnBaseAttackDamageMaxInputText(wxCommandEvent& event);
        void OnWhiteDamageInputText(wxCommandEvent& event);
        void OnPanel1KillFocus(wxFocusEvent& event);
        void OnKillFocus(wxFocusEvent& event);
        void OnGreenDamageInputTextEnter(wxCommandEvent& event);
        void OnBATInputTextEnter(wxCommandEvent& event);
        void OnAttackSpeedInputTextEnter(wxCommandEvent& event);
        void OnChoice1Select(wxCommandEvent& event);
        void OnLevelInputTextEnter(wxCommandEvent& event);
        void OnStatStrInputTextEnter(wxCommandEvent& event);
        void OnStatAgiInputTextEnter(wxCommandEvent& event);
        void OnStatIntInputTextEnter(wxCommandEvent& event);
        void OnStatHPInputTextEnter(wxCommandEvent& event);
        void OnStatMPInputTextEnter(wxCommandEvent& event);
        void OnStatHPRegenInputTextEnter(wxCommandEvent& event);
        void OnStatMPRegenInputTextEnter(wxCommandEvent& event);
        void OnArmorInputTextEnter(wxCommandEvent& event);
        void OnMagicResistanceInputTextEnter(wxCommandEvent& event);
        void OnWithstandInputTextEnter(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnattackEffectsChoiceSelect(wxCommandEvent& event);
        void OnattackEffectsCtrlBeginDrag(wxListEvent& event);
        void OnattackEffectsCtrlItemFocused(wxListEvent& event);
        void OnattackEffectsCtrlItemActivated(wxListEvent& event);
        void OnattackEffectsCtrlKeyDown(wxListEvent& event);
        void OnattackEffectsCtrlBeginDrag1(wxListEvent& event);
        void OnButton3Click1(wxCommandEvent& event);
        void OnattackEffectsCtrlBeginDrag2(wxListEvent& event);
        void OnChoice2Select(wxCommandEvent& event);
        void OndefenseEffectsCtrlItemActivated2(wxListEvent& event);
        void OnattackEffectsCtrlBeginDrag3(wxListEvent& event);
        void OnaECBButtonAddClick(wxCommandEvent& event);
        void OnaECBButtonRemoveClick(wxCommandEvent& event);
        void OndECBButtonAddClick(wxCommandEvent& event);
        void OndECBButtonRemoveClick(wxCommandEvent& event);
        void OnMagicResistanceInputText(wxCommandEvent& event);
        void OnChoice2Select1(wxCommandEvent& event);
        void OnStatHPInput2TextEnter(wxCommandEvent& event);
        void OnStatMPInput2TextEnter(wxCommandEvent& event);
        void OnStatStrInput2TextEnter(wxCommandEvent& event);
        void OnStatAgiInput2TextEnter(wxCommandEvent& event);
        void OnStatIntInput2TextEnter(wxCommandEvent& event);
        void OnLevelInput2TextEnter(wxCommandEvent& event);
        void OnMenuSettingsSelected(wxCommandEvent& event);
        //*)
        void OnChoice3Select(wxCommandEvent& event);
        void OnChoice4Select(wxCommandEvent& event);
        //(*Identifiers(DamageAnalysisFrame)
        static const long ID_CHOICE1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_TEXTCTRL5;
        static const long ID_TEXTCTRL7;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_TEXTCTRL6;
        static const long ID_TEXTCTRL8;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL9;
        static const long ID_TEXTCTRL10;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL11;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT11;
        static const long ID_TEXTCTRL12;
        static const long ID_STATICTEXT12;
        static const long ID_TEXTCTRL13;
        static const long ID_TEXTCTRL14;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT14;
        static const long ID_TEXTCTRL15;
        static const long ID_STATICTEXT15;
        static const long ID_TEXTCTRL16;
        static const long ID_STATICTEXT16;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT18;
        static const long ID_TEXTCTRL17;
        static const long ID_LISTCTRL1;
        static const long ID_LISTCTRL2;
        static const long ID_BITMAPBUTTON1;
        static const long ID_BITMAPBUTTON3;
        static const long ID_BITMAPBUTTON4;
        static const long ID_BITMAPBUTTON5;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT19;
        static const long ID_TEXTCTRL18;
        static const long ID_STATICTEXT20;
        static const long ID_TEXTCTRL19;
        static const long ID_STATICTEXT21;
        static const long ID_TEXTCTRL20;
        static const long ID_STATICTEXT22;
        static const long ID_TEXTCTRL21;
        static const long ID_STATICTEXT23;
        static const long ID_STATICTEXT24;
        static const long ID_TEXTCTRL22;
        static const long ID_TEXTCTRL23;
        static const long ID_BITMAPBUTTON2;
        static const long ID_PANEL1;
        static const long ID_PANEL3;
        static const long ID_NOTEBOOK1;
        static const long idMenuQuit;
        static const long idSettings;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_CHOICE3;
        static const long ID_CHOICE4;

        //(*Declarations(DamageAnalysisFrame)
        wxTextCtrl* StatHPRegenInput;
        wxTextCtrl* LevelInput;
        wxStaticText* LvlInputText2;
        wxTextCtrl* WhiteDamageInput;
        wxStaticText* WhiteDamageText;
        wxTextCtrl* StatStrInput2;
        wxTextCtrl* BATInput;
        wxTextCtrl* StatHPInput;
        wxStaticText* BATText;
        wxTextCtrl* StatIntInput;
        wxTextCtrl* MagicResistanceInput;
        wxTextCtrl* StatAgiInput2;
        wxNotebook* Notebook1;
        wxBitmapButton* dECBButtonAdd;
        wxTextCtrl* BaseAttackDamageMaxInput;
        wxStaticText* StaticText2;
        wxTextCtrl* StatStrInput;
        wxMenu* Menu3;
        wxTextCtrl* LevelInput2;
        wxTextCtrl* StatMPInput2;
        wxStaticText* StatStrText;
        wxStaticText* WithstandText2;
        wxStaticText* StatAgiText2;
        wxTextCtrl* StatIntInput2;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxBitmapButton* BitmapButton1;
        wxListCtrl* defenseEffectsCtrl;
        wxStaticText* LvlInputText;
        wxPanel* Panel3;
        wxStaticText* StatManaText2;
        wxBitmapButton* aECBButtonAdd;
        wxTextCtrl* WithstandInput;
        wxMenuItem* MenuItem3;
        wxStaticText* StatStrText2;
        wxStaticText* StatAgiText;
        wxStaticText* AttackSpeedText;
        wxStaticText* BaseAttackDamageText;
        wxBitmapButton* aECBButtonRemove;
        wxStatusBar* StatusBar1;
        wxTextCtrl* StatHPInput2;
        wxStaticText* ArmorText;
        wxTextCtrl* StatAgiInput;
        wxTextCtrl* GreenDamageInput;
        wxListCtrl* attackEffectsCtrl;
        wxBitmapButton* dECBButtonRemove;
        wxStaticText* StatIntText;
        wxStaticText* MagicalResistanceText;
        wxStaticText* StatHealthText2;
        wxStaticText* RegenText;
        wxTextCtrl* BaseAttackDamageMinInput;
        wxStaticText* StatIntText2;
        wxStaticText* StatHealthText;
        wxStaticText* GreenDamageText;
        wxTextCtrl* StatMPRegenInput;
        wxStaticText* StatManaText;
        wxTextCtrl* ArmorInput;
        wxChoice* Choice1;
        wxChoice* Choice2;
        wxTextCtrl* StatMPInput;
        wxStaticText* WithstandText;
        wxTextCtrl* AttackSpeedInput;
        //*)
        wxChoice* attackEffectsChoice2;
        wxChoice* defenseEffectsChoice2;
        DECLARE_EVENT_TABLE()
};

template<typename T>bool DamageAnalysisFrame::isSameRefAddress(T &var1, T &var2)
{
return &var1 == &var2;
}

#endif // DAMAGEANALYSISMAIN_H
