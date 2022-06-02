#include "cMain.h"

// takes name of class with base class
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)

wxEND_EVENT_TABLE()



// Main application window
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(50, 30), wxSize(600,600))
{
	// Grid of buttons
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	for (size_t x = 0; x < nFieldWidth; x++)
	{
		for (size_t y = 0; y < nFieldHeight; y++)
		{
			// Adds a button to each position
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			// Adds to grid to fill in space?
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	
}