#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

//(*Headers(GameSettings)
#include <wx/grid.h>
#include <wx/frame.h>
//*)

#include "commonIncludes.h"
#include "DamageAnalysisMain.h"

class GameSettings: public wxFrame
{
	public:

		GameSettings(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~GameSettings();

		//(*Declarations(GameSettings)
		wxGrid* Grid1;
		//*)

	protected:

		//(*Identifiers(GameSettings)
		static const long ID_GRID1;
		//*)

	private:

		//(*Handlers(GameSettings)
		void OnSettingsGrid1CellChange(wxGridEvent& event);
		void OnGrid1CellLeftClick(wxGridEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

void GetGameRules();
void ApplyDefaultRules();
void SaveChangestoFile(const std::string path);

#endif
