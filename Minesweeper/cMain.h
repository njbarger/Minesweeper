#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
private:
				  
	int GridWidth = 10;
	int GridHeight = 10;
	wxButton** buttonArray;

	
	// locations of mines
	int* bombArray = nullptr;

	// bool array for ifCounted;
	bool* countArray;

	// populates mine field on first click
	bool firstClick = true;


public:
	cMain();
	~cMain();

	// Click Event
	void OnButtonClicked(wxCommandEvent& evt);

	// Neighboring Bomb Count
	int CountNeighbors(int x, int y);
	
	// Open all empty tiles adjacent to each other
	void OpenEmptyTiles(int x, int y);

	// Event handler
	wxDECLARE_EVENT_TABLE();
};

