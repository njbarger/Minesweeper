#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
				  
	int GridWidth = 10;
	int GridHeight = 10;
	wxButton** buttonArray;

	
	// locations of mines
	int* bombArray = nullptr;
	// populates mine field on first click
	bool firstClick = true;


	void OnButtonClicked(wxCommandEvent& evt);
	

	// Event handler
	wxDECLARE_EVENT_TABLE();
};

