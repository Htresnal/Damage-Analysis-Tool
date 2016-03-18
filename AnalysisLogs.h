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

class AnalysisLogs: public wxFrame
{
public:

    AnalysisLogs(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~AnalysisLogs();
    void RunAnalysis();
    void DamageLogFill(void *p);
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
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
