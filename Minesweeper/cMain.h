#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btn;
	
	// locations of mines
	int* nField = nullptr;
	// populates mine field on first click
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	// Event handler
	wxDECLARE_EVENT_TABLE();
};

