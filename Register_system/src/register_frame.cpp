#include "register_frame.h"
#include "wx/button.h"
#include "wx/wxprec.h"
#include <string>
#include <sstream>


register_frame::register_frame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    wxPanel *wxPanel_register_frame = new wxPanel(this, wxID_ANY);



//    register_frame::Text_box_register();
    register_frame::Text_info_box_register();
    register_frame::button_accept();

    password_text;
    login_text;


}
register_frame::~register_frame()
{
    //dtor
}



const void register_frame::Text_info_box_register(){

    wxStaticText * register_username_static = new wxStaticText(this, wxID_ANY,"username:", wxPoint(60,64), wxSize(70,70));
    wxStaticText * register_password_static = new wxStaticText(this, wxID_ANY,"password:", wxPoint(60,114), wxSize(70,70));


}


void register_frame::button_accept(){


    wxPanel *wxPanel_register_button = new wxPanel(this, wxID_ANY);

    wxButton *button_accept_clicked = new wxButton(this, wxID_ANY, "Register", wxPoint(150, 150), wxSize(100,25),0);
    button_accept_clicked->Bind(wxEVT_BUTTON, &register_frame::button_accept_clicked, this);


}

void register_frame::button_accept_clicked(wxCommandEvent &event)
{

    ///CONNECT TO DB
        MYSQL * conn = mysql_init(NULL);

    conn = mysql_real_connect(conn, "127.0.0.1", "cuno123", "password", "AMI", 3306, NULL, 0);
    if(!conn) {
    wxLogMessage("failed to connect database");
    }

    //CHECK IF USER EXIST
    //checkexist  <<   "SELECT username FROM users WHERE EXISTS (SELECT username FROM users WHERE username = '" << login_text->GetValue() <<   " ') = 0  ;"   ;

    std::stringstream checkexist;

    checkexist << "INSERT INTO users (username,password) VALUES('" << login_text->GetValue() << "','"  <<  password_text->GetValue() << "');" ;

    int checkqstate = 0;
    std::string query_check_exist = checkexist.str();
    const char* testing = query_check_exist.c_str();

    wxString mystring = testing;
    wxLogMessage(mystring);

    checkqstate = mysql_query(conn,testing);

    //wxLogMessage(checkexist);
   if(checkqstate == 0) {
    wxLogMessage("succesful");
    Destroy();

    }
    else {
        wxLogMessage ("Username already exist! try again");
    }

}
