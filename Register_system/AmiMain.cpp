/***************************************************************
 * Name:      AmiMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Cunoo ()
 * Created:   2021-02-16
 * Copyright: Cunoo ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "AmiMain.h"

#include "register_frame.h"
#include "mysql.h"
#include "LoginWindow.h"
#include <string>
#include <sstream>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(AmiFrame, wxFrame)
    EVT_CLOSE(AmiFrame::OnClose)
    EVT_MENU(idMenuQuit, AmiFrame::OnQuit)
    EVT_MENU(idMenuAbout, AmiFrame::OnAbout)
    EVT_BUTTON(idRegister, AmiFrame::register_button)
    EVT_BUTTON(idLoginIn,AmiFrame::LoginIn_button)
END_EVENT_TABLE()

AmiFrame::AmiFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR


    Buttons_together();
    Boxes();

}


AmiFrame::~AmiFrame()
{
}

const void AmiFrame::Buttons_together(){


    //REGISTER BUTTON
    wxPanel *wxPanel_register_button = new wxPanel(this, wxID_ANY);

   wxButton *register_button = new wxButton(this, idRegister, "Register", wxPoint(400, 300), wxSize(70,50), 0);

    wxButton *Login_button = new wxButton(this,idLoginIn, "Login", wxPoint(300,300), wxSize(70,50), 0);

}

void AmiFrame::Boxes(){


    wxStaticText * LoginIN_username_static = new wxStaticText(this, wxID_ANY,"username:", wxPoint(60,64), wxSize(70,70));
    wxStaticText * LoginIN_password_static = new wxStaticText(this, wxID_ANY,"password:", wxPoint(60,114), wxSize(70,70));
    loginIN_text;
    passwordIN_text;

}

/////BUTONCLICKED/////////////

void AmiFrame::LoginIn_button(wxCommandEvent &event){


    ///CONNECT TO DB
    MYSQL * conn = mysql_init(NULL);

    conn = mysql_real_connect(conn, "127.0.0.1", "cuno123", "password", "AMI", 3306, NULL, 0);
    if(!conn) {
        wxLogMessage("failed to connect database");
    }

    std::stringstream loginin_string;
    loginin_string  <<   "SELECT id FROM users WHERE username='"    <<  loginIN_text->GetValue()    << "'   AND password = '"   <<    passwordIN_text->GetValue()   <<  "' ;";
    std::string query_login_string = loginin_string.str();
    const char* string_to_cstring = query_login_string.c_str();

    if(mysql_query(conn,string_to_cstring)) {
        // chyba
        wxLogMessage("Failed to connect DB");
        }

    MYSQL_RES *result = mysql_store_result(conn);

    my_ulonglong pocet = mysql_num_rows(result);
    if(pocet == 1) {
        // prihlásenie OK
        LoginWindow* login_frame = new LoginWindow("Ami_IN", wxPoint(50,50 ), wxSize(410,400));
        login_frame->Show();
    } else {
    wxLogMessage("username doesn't exist or wrong password");
    }

}


void AmiFrame::register_button(wxCommandEvent &event)
{
   //wxLogMessage("Button clicked");
    register_frame* register_f = new register_frame("Register", wxPoint(50,50 ), wxSize(400,400));

    register_f->Show();

}


void AmiFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void AmiFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void AmiFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
//////////BUTON CLICKED END//////////////
