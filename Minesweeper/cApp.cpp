#include "cApp.h"

// Entry point "main"
wxIMPLEMENT_APP(cApp);


cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
	// Initializes new application
	m_frame1 = new cMain();
	m_frame1->Show();

	return true;
}