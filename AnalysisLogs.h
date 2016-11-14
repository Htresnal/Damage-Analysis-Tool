#ifndef ANALYSISLOGS_H
#define ANALYSISLOGS_H

//(*Headers(AnalysisLogs)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include "DamageAnalysisMain.h"
#include "effects.h"

class effect_critical_damage;
class effect_block_damage;

class AnalysisLogs: public wxFrame
{

public:

    AnalysisLogs(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~AnalysisLogs();
    void RunAnalysis();
    void DamageLogFill(void *p);
    void TMPDamageSave();
    void TMPDamageLoad();
    void FlushDamage();
    void ApplyResists();
    inline void recalculateAttackSpeed();
    double getArmorReduction();
    void calcCrits(std::vector<effect_critical_damage *> &);
    void calcShieldBlock(std::vector<effect_block_damage *> &);
    //(*Declarations(AnalysisLogs)
    wxRichTextCtrl* RichTextCtrl1;
    wxButton* Button1;
    wxPanel* Panel1;
    //*)

protected:

    //(*Identifiers(AnalysisLogs)
    static const long ID_RICHTEXTCTRL1;
    static const long ID_BUTTON1;
    static const long ID_PANEL1;
    //*)

private:

    //(*Handlers(AnalysisLogs)
    void OnClose(wxCloseEvent& event);
    void OnButton1Click(wxCommandEvent& event);
    void OnRichTextCtrl1Text(wxCommandEvent& event);
    void OnRichTextCtrl1RichTextContentInserted(wxRichTextEvent& event);
    void OnRichTextCtrl1RichTextStylesheetReplacing(wxRichTextEvent& event);
    void OnRichTextCtrl1RichTextContentInserted1(wxRichTextEvent& event);
    void OnRichTextCtrl1RichTextStylesheetReplaced(wxRichTextEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};
#endif
