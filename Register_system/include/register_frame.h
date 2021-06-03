#ifndef REGISTER_FRAME_H
#define REGISTER_FRAME_H
#include "wx/panel.h"
#include "wx/url.h"
#include "wx/wx.h"
#include "wx/textctrl.h"
#include "wx/stattext.h"
#include "mysql.h"





class register_frame: public wxFrame
{
    public:
        register_frame(const wxString& title, const wxPoint& pos, const wxSize& size);

        virtual ~register_frame();
        const void Text_box_register();
        const void Text_info_box_register();
        void button_accept();
        void button_accept_clicked(wxCommandEvent &event);
        void test();
            /////USERNAME AND PASSWORD BOXES
        wxTextCtrl* login_text = new wxTextCtrl(this,wxID_ANY, "", wxPoint(150,64), wxSize(100,25),
        wxTE_LEFT | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);

        wxTextCtrl *password_text = new wxTextCtrl(this,wxID_ANY, "", wxPoint(150,114), wxSize(100,25),
        wxTE_PASSWORD | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);


    private:
};



#endif // REGISTER_FRAME_H
