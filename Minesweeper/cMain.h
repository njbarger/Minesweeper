#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
private:
				  
	int GridWidth = 10;
	int GridHeight = 10;
	wxButton** buttonArray;
	wxGridSizer* grid;

	// locations of mines
	int* bombArray = nullptr;

	// bool array for ifCounted;
	bool* countArray;

	// populates mine field on first click
	bool firstClick = true;

	// Counter for right click options
	// 0 = no image
	// 1 = X for bomb flag
	// 2 = ? for unsure flag
	int rightClickCheck = 0;


public:
	cMain();
	~cMain();

	// Click Event
	void OnButtonClicked(wxCommandEvent& evt);

	void OnRightClick(wxCommandEvent& evt);

	// Neighboring Bomb Count
	int CountNeighbors(int x, int y);
	
	// Open all empty tiles adjacent to each other
	void OpenEmptyTiles(int x, int y);


	// Event handler
	wxDECLARE_EVENT_TABLE();
};

