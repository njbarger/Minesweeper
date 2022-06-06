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
	wxGridSizer* grid;
	bool* countArray;

	// locations of mines
	int* bombArray = nullptr;
	// populates mine field on first click
	bool firstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);
	int CountNeighbors(int x, int y);
	void OpenEmptyTiles(int x, int y);

	// Event handler
	wxDECLARE_EVENT_TABLE();
};

