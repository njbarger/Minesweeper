#include "cMain.h"

// takes name of class with base class
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)

wxEND_EVENT_TABLE()



// Main application window
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(50, 30), wxSize(600,600))
{
	// Grid of buttons
	buttonArray = new wxButton * [GridWidth * GridHeight];
	wxGridSizer* grid = new wxGridSizer(GridWidth, GridHeight, 0, 0);

	bombArray = new int[GridWidth * GridHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (size_t x = 0; x < GridWidth; x++)
	{
		for (size_t y = 0; y < GridHeight; y++)
		{
			// Adds a button to each position
			buttonArray[y * GridWidth + x] = new wxButton(this, 10000 + (y * GridWidth + x));

			buttonArray[y * GridWidth + x]->SetFont(font);

			// Adds to grid to fill in space?
			grid->Add(buttonArray[y * GridWidth + x], 1, wxEXPAND | wxALL);

			// Binds an click event handler to each button
			buttonArray[y * GridWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			bombArray[y * GridWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[] buttonArray;
	delete[] bombArray;
}


int cMain::CountNeighbors(int x, int y)
{
	int mineCount = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x + 1 >= 0 && x + i < GridWidth && y + j >= 0 && y + j < GridHeight)
			{
				if (bombArray[(y + j) * GridWidth + (x + i)] == -1)
					mineCount++;
			}
		}
	}
	return mineCount;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % GridWidth;
	int y = (evt.GetId() - 10000) / GridWidth;

	if (firstClick)
	{
		int mines = 30;

		while (mines)
		{
			// generate random mine locations
			int rx = rand() % GridWidth;
			int ry = rand() % GridHeight;

			// make sure its not first button clicked, and is not already a mine
			if (bombArray[ry * GridWidth + rx] == 0 && rx != x && ry != y)
			{
				// set to mine
				bombArray[ry * GridWidth + rx] = -1;
				mines--;
			}

		}

		firstClick = false;
	}

	// Disable Button, preventing it being pressed again
	buttonArray[y * GridWidth + x]->Enable(false);
	
	// check if player hit a mine
	if (bombArray[y*GridWidth + x] == -1)
	{
		// lose message
		wxMessageBox("Game over, try again.");

		// reset game
		firstClick = true;
		for (size_t x = 0; x < GridWidth; x++)
		{
			for (size_t y = 0; y < GridHeight; y++)
			{
				bombArray[y * GridWidth + x] = 0;
				buttonArray[y * GridWidth + x]->SetLabel("");
				buttonArray[y * GridWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		// Count neighboring mines
		int mineCount = CountNeighbors(x, y);

		// update button label to show min count if > 0
		if (mineCount > 0)
		{
			buttonArray[y * GridWidth + x]->SetLabel(std::to_string(mineCount));
		}


	}


	evt.Skip();
}