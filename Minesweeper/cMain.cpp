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

	nField = new int[nFieldWidth * nFieldHeight];

	for (size_t x = 0; x < nFieldWidth; x++)
	{
		for (size_t y = 0; y < nFieldHeight; y++)
		{
			// Adds a button to each position
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			// Adds to grid to fill in space?
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			// Binds an click event handler to each button
			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick)
	{
		int mines = 30;

		while (mines)
		{
			// generate random mine locations
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			// make sure its not first button clicked, and is not already a mine
			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				// set to mine
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}

		}

		bFirstClick = false;
	}

	// Disable Button, preventing it being pressed again
	btn[y * nFieldWidth + x]->Enable(false);
	
	// check if player hit a mine
	if (nField[y*nFieldWidth + x] == -1)
	{
		// lose message
		wxMessageBox("Get rekt loser, try again.");

		// reset game
		bFirstClick = true;
		for (size_t x = 0; x < nFieldWidth; x++)
		{
			for (size_t y = 0; y < nFieldHeight; y++)
			{
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		// Count neighboring mines
		int mineCount = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + 1 >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mineCount++;
				}
			}
		}

		// update button label to show min count if > 0
		if (mineCount > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mineCount));
		}


	}


	evt.Skip();
}