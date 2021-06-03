#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "wx/wx.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/wxprec.h"
#include <string>
#include <sstream>
#include "wx/socket.h"

#include "wx/socket.h"

class LoginWindow : public wxFrame
{
    public:
        LoginWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
        virtual ~LoginWindow();
        int test();
};




















/*
#if wxUSE_IPV6
typedef wxIPV6address IPaddress;
#else
typedef wxIPV4address IPaddress;
#endif


class LoginWindow : public wxFrame
{
    public:
        LoginWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
        virtual ~LoginWindow();

	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	// event handlers for Socket menu
	void OnOpenConnection(wxCommandEvent& event);
	void OnCloseConnection(wxCommandEvent& event);
	void OnSend(wxCommandEvent& event);
	void OnSocketEvent(wxSocketEvent& event);

	// convenience functions
	void UpdateStatusBar();

private:

	wxSocketClient *sock;
	wxButton *btnSend;
	wxTextCtrl *txtSend;
	wxTextCtrl *txtRx;
	wxMenu *fileMenu;
	wxMenu *helpMenu;
	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

// IDs for the controls and the menu commands
enum
{
	ID_BTNSEND=101,
	ID_TXTSEND,
	ID_TXTRX,
	SOCKET_ID,
	CLIENT_OPEN=wxID_OPEN,
	CLIENT_CLOSE=wxID_CLOSE,
	// menu items
	Minimal_Quit = wxID_EXIT,
	Minimal_About = wxID_ABOUT
};
*/



#endif // LOGINWINDOW_H
