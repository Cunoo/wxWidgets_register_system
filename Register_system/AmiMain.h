/***************************************************************
 * Name:      AmiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Cunoo ()
 * Created:   2021-02-16
 * Copyright: Cunoo ()
 * License:
 **************************************************************/

#ifndef AMIMAIN_H
#define AMIMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wx/panel.h"
#include "wx/url.h"

#include "AmiApp.h"
#include "LoginWindow.h"

class AmiFrame: public wxFrame
{
    public:
        AmiFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
        ~AmiFrame();
        void register_button(wxCommandEvent &event);
        void LoginIn_button(wxCommandEvent &event);
        const void Buttons_together();
        void Boxes();
        wxTextCtrl* loginIN_text = new wxTextCtrl(this,wxID_ANY, "", wxPoint(150,64), wxSize(100,25),
        wxTE_LEFT | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);

        wxTextCtrl *passwordIN_text = new wxTextCtrl(this,wxID_ANY, "", wxPoint(150,114), wxSize(100,25),
        wxTE_PASSWORD | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idLoginIn ,
            idRegister
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // AMIMAIN_H
