#include "LoginWindow.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080



LoginWindow::LoginWindow(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    LoginWindow::test();


}

int LoginWindow::test(){

   int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    return 0;
}

LoginWindow::~LoginWindow(){



}
































































/*
BEGIN_EVENT_TABLE(LoginWindow::LoginWindow, wxFrame)
EVT_TEXT_ENTER(wxTE_MULTILINE,LoginWindow::Box_lines)
END_EVENT_TABLE()*/
/*
wxBEGIN_EVENT_TABLE(LoginWindow, wxFrame)
EVT_MENU(Minimal_Quit, LoginWindow::OnQuit)
EVT_MENU(Minimal_About, LoginWindow::OnAbout)
EVT_SOCKET(SOCKET_ID, LoginWindow::OnSocketEvent)
EVT_MENU(CLIENT_OPEN, LoginWindow::OnOpenConnection)
EVT_MENU(CLIENT_CLOSE, LoginWindow::OnCloseConnection)
wxEND_EVENT_TABLE()

LoginWindow::LoginWindow(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{

#if wxUSE_MENUS
	// create a menu bar
	fileMenu = new wxMenu;

	// the "About" item should be in the help menu
	helpMenu = new wxMenu;
	helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

	fileMenu->Append(CLIENT_OPEN, "&Open session\tAlt-O","Connect to server");
	fileMenu->Append(CLIENT_CLOSE,"&Close session\tAlt-C","Close connection");
	fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar(2);
	SetStatusText("TCP client using wxWidgets");
#endif // wxUSE_STATUSBAR
	btnSend = new wxButton(this, ID_BTNSEND, wxT("Send"),
        wxPoint(5, 5), wxSize(100, 25));
	txtSend = new wxTextCtrl(this,ID_TXTSEND, wxT("Hello!"),
        wxPoint(120, 5), wxSize(250, 25));
	txtRx = new wxTextCtrl(this,ID_TXTRX, wxT(""),
        wxPoint(5, 35), wxSize(365, 125), wxTE_MULTILINE);

	Connect(ID_BTNSEND, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(LoginWindow::OnSend));

	// Create the socket
	sock = new wxSocketClient();

	// Setup the event handler and subscribe to most events
	sock->SetEventHandler( *this, SOCKET_ID);
	sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
		wxSOCKET_INPUT_FLAG |
		wxSOCKET_LOST_FLAG);
	sock->Notify(true);
}

LoginWindow::~LoginWindow()
{
	// No delayed deletion here, as the frame is dying anyway
	delete sock;
}

// event handlers
void LoginWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void LoginWindow::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	(
		"wxWidgets TCP client sample\n"
		"\n"
		"Author: Cunoo \n"
		"Web: I dont have itlol"
	),
		"About wxWidgets TCP client sample, if you have some errors contact me :)",
		wxOK | wxICON_INFORMATION,
		this);
}

void LoginWindow::OnSend(wxCommandEvent& WXUNUSED(event))
{
	wxString str = txtSend->GetValue();
	wxCharBuffer buffer = str.ToUTF8();
	size_t txn = buffer.length();//for non-ASCII chars, having more than one byte per char

	unsigned char len;
	len = txn;
	sock->Write(&len, 1);//send the length of the message first
	if (sock->Write(buffer.data(), txn).LastCount() != txn)
	{
		txtRx->AppendText(wxT("Write error.\n"));
		return;
	}
	else {
		txtRx->AppendText("Tx: " + str + "\n");
	}
}

void LoginWindow::OnOpenConnection(wxCommandEvent& WXUNUSED(event))
{
	// Create the address - defaults to localhost:0 initially
	IPaddress addr;
	//addr.AnyAddress();
	addr.Hostname("localhost");
	addr.Service(3000);
	txtRx->AppendText(wxString::Format(wxT("Trying to connect to %s:%u \n"),
        addr.IPAddress(), addr.Service()));

	fileMenu->Enable(CLIENT_OPEN, false);
	fileMenu->Enable(CLIENT_CLOSE, false);
	// we connect asynchronously and will get a wxSOCKET_CONNECTION event when
	// the connection is really established
	//
	// if you want to make sure that connection is established right here you
	// could call WaitOnConnect(timeout) instead

	sock->Connect(addr, false);

	//update status
	UpdateStatusBar();
}

void LoginWindow::OnCloseConnection(wxCommandEvent& WXUNUSED(event))
{
	sock->Close();

	//update status
	UpdateStatusBar();
}

void LoginWindow::OnSocketEvent(wxSocketEvent& event)
{
	txtRx->AppendText(wxT("OnSocketEvent: "));
	wxSocketBase *sockBase = event.GetSocket();

	// First, print a message
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT: txtRx->AppendText(wxT("wxSOCKET_INPUT\n")); break;
	case wxSOCKET_LOST: txtRx->AppendText(wxT("wxSOCKET_LOST\n")); break;
	case wxSOCKET_CONNECTION: txtRx->AppendText(wxT("wxSOCKET_CONNECTION\n")); break;
	default: txtRx->AppendText(wxT("Unexpected event !\n")); break;
	}

	// Now we process the event
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT:
	{
		// We disable input events, so that the test doesn't trigger
		// wxSocketEvent again.
		sockBase->SetNotify(wxSOCKET_LOST_FLAG);

		// Receive data from socket and send it back. We will first
		// get a byte with the buffer size, so we can specify the
		// exact size and use the wxSOCKET_WAITALL flag. Also, we
		// disabled input events so we won't have unwanted reentrance.
		// This way we can avoid the infamous wxSOCKET_BLOCK flag.

		sockBase->SetFlags(wxSOCKET_WAITALL);

		// Read the size @ first byte
		unsigned char len;
		sockBase->Read(&len, 1);
		char buf[256];
		// Read the message
		wxUint32 lenRd = sockBase->Read(buf, len).LastCount();
		if (!lenRd) {
			txtRx->AppendText(wxT("Failed to read message.\n"));
			return;
		}
		else {
			txtRx->AppendText(wxString::Format(wxT("Read %d bytes.\n"), lenRd));
		}

		txtRx->AppendText(wxString::Format(wxT("Rx: %s \n"),
            wxString::FromUTF8(buf, len)));
		// Enable input events again.
		sockBase->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
		break;
	}
	default:;
	}

	//update status
	UpdateStatusBar();
}

void LoginWindow::UpdateStatusBar()
{
	fileMenu->Enable(CLIENT_OPEN, !sock->IsConnected());
	fileMenu->Enable(CLIENT_CLOSE, sock->IsConnected());
	if (sock->IsConnected()) {
		//SetStatusText(wxString::Format(wxT("%s:%u"),
        //    addr.IPAddress(), addr.Service()), 1);
		SetStatusText(wxString::Format(wxT("Connected")), 1);
	}
	else {
		SetStatusText(wxString::Format(wxT("Not connected")), 1);
	}
}
*/
