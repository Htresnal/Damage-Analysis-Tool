/***************************************************************
 * Name:      DamageAnalysisApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2016-02-05
 * Copyright:  ()
 * License:
 **************************************************************/
#include "DamageAnalysisApp.h"
#include "GameSettings.h"
#include "DamageAnalysisMain.h"
#include "AnalysisLogs.h"
#include "effectsProperties.h"

DamageAnalysisFrame *Frame;

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP(DamageAnalysisApp);

bool DamageAnalysisApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        Frame=new DamageAnalysisFrame(NULL,wxNewId());
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;
}
