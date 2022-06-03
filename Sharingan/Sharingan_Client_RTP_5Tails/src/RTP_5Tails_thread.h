#ifndef RTP_5TAILS_THREAD_H_
#define RTP_5TAILS_THREAD_H_

const int NUMBER_UPDATE_ID = 1440630 ;

#include <string>
#include <stdio.h>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/image.h>
#include <wx/imagjpeg.h>
#include <wx/bitmap.h>
#include <wx/mstream.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/thread.h>
#include <wx/log.h>

#include "Sharingan_Client_RTP_5Tails.h"

using namespace::std ;

class RTP_thread_5Tails : public wxThread
{
	protected: wxTextCtrl* UDP_TEXT1 ;
	protected: wxImage*        IMAGE ;

	protected: int sock_descriptor    ;
	protected: int free_bytes_int = 0 ;
	protected: int SUPPORT        = 2 ; // example for 2: 01 for file number

	// --------------------------------------

	protected: wxFrame* m_parent = NULL ;
	protected: bool working = false ;

	// --------------------------------------

    public: RTP_thread_5Tails ( wxFrame* parent , wxTextCtrl* UDP_TEXT1 , wxImage* Image , int forbytes , int SUPPORT , int sock_descriptor , bool working ) ;

    protected: virtual ExitCode Entry () ;
};

#endif

