/***************************************************************
 * Name:      AmiApp.cpp
 * Purpose:   Code for Application Class
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

#include "AmiApp.h"
#include "AmiMain.h"

IMPLEMENT_APP(AmiApp);

bool AmiApp::OnInit()
{
    AmiFrame* frame = new AmiFrame("Ami", wxPoint(50,50 ), wxSize(800,600));

    frame->Show();

    return true;
}
