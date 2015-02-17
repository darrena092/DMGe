#include "mainFrame.h"
#include "logo.xpm"

mainFrame::mainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    //File Menu
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(MENU_OPEN, "&Open");

    wxMenu* menuEmu = new wxMenu;
    menuEmu->Append(MENU_START, "&Start");
    menuEmu->Append(MENU_STOP, "&Stop");

    #ifdef _DEBUG
    menuEmu->Append(MENU_SUPPRESS, "Suppress debug output. (Not implemented)");
    #endif // _DEBUG

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEmu, "&Emulation");

    SetMenuBar(menuBar);

    wxIcon mainIcon(logo_xpm);
    SetIcon(mainIcon);

    gameboy = new c_GameBoy("roms/tetris.gb");
    gameboy->pause = true;

    //wxTimer* timer = new wxTimer(this, GB_TIMER);
    //timer->Start(1); //Interval in milliseconds.
}

wxBEGIN_EVENT_TABLE(mainFrame, wxFrame)
    //EVT_TIMER(GB_TIMER, mainFrame::Tick)
    EVT_IDLE(mainFrame::Tick)
    EVT_MENU(MENU_START, mainFrame::StartEmulation)
    EVT_MENU(MENU_STOP, mainFrame::StopEmulation)
wxEND_EVENT_TABLE()

void mainFrame::Tick(wxIdleEvent& event)
{
    gameboy->Run();
    event.RequestMore(true);
}

void mainFrame::StartEmulation(wxCommandEvent& event)
{
    gameboy->pause = false;
}

void mainFrame::StopEmulation(wxCommandEvent& event)
{
    gameboy->pause = true;
}