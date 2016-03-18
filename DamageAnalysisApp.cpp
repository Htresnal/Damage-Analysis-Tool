/***************************************************************
 * Name:      DamageAnalysisApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2016-02-05
 * Copyright:  ()
 * License:
 **************************************************************/
#include "DamageAnalysisApp.h"
#include "DamageAnalysisMain.h"
#include "AnalysisLogs.h"
#include "effectsProperties.h"
DamageAnalysisFrame *Frame;
AnalysisLogs *Frame1;
effectsProperties *Frame2;

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP(DamageAnalysisApp);

bool DamageAnalysisApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    //*)
    Frame = new DamageAnalysisFrame(NULL,wxNewId());
    Frame1 = new AnalysisLogs(Frame,wxNewId());
    Frame2 = new effectsProperties(Frame,wxNewId());
    Frame->Show();
    SetTopWindow(Frame);
    return wxsOK;
}
