#ifndef EFFECTSPROPERTIES_H
#define EFFECTSPROPERTIES_H

//(*Headers(effectsProperties)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include "DamageAnalysisMain.h"

class effectsProperties : public wxFrame
{
	public:
		effectsProperties(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~effectsProperties();
		void *currEditObject;
		void AppendCell(double &);
        void AppendCell(int &);
        void AppendRow(const wxString &);
        void AppendReadOnly();
        void AppendChoiceCell(unsigned, const wxString [], unsigned &);
        void AppendFullRow(const wxString,double &);
        void AppendFullRow(const wxString,int &);
        void AppendDamageTypeSelector(unsigned &);
        void AppendCustomSelector(unsigned &, int, wxString const, wxString const []);
        template<typename Tstring, typename Tval1, typename Tval2> void AppendFullRow(const Tstring headerText, Tval1 &val1, Tval2 &val2);
        void Clear();
        unsigned gridLines;
        unsigned cellColumn;
        void *ptrtoItem;

		//(*Declarations(effectsProperties)
		wxButton* Button1;
		wxPanel* Panel1;
		wxGrid* Grid1;
		wxButton* Button2;
		//*)

	protected:

		//(*Identifiers(effectsProperties)
		static const long ID_GRID1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(effectsProperties)
		void OnClose(wxCloseEvent& event);
		void OnGrid1CellChange(wxGridEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnMouseWheel(wxMouseEvent& event);
		void OnGrid1CellLeftClick(wxGridEvent& event);
		void OnGrid1KeyDown(wxKeyEvent& event);
		void OnGrid1EditorHidden(wxGridEvent& event);
		void OnGrid1KeyDown1(wxKeyEvent& event);
		void OnGrid1CellSelect(wxGridEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

class cellDataObject;

#endif
