#ifndef SHARINGAN_CLIENT_RTP_5TAILS_H_
#define SHARINGAN_CLIENT_RTP_5TAILS_H_

#include "RTP_5Tails_thread.h"

using namespace::std ;

class MyFrame: public wxFrame {

    public: MyFrame  (

    	wxWindow*  parent,
		wxWindowID id,

		const wxString& title,
		const wxPoint&  pos=wxDefaultPosition,
		const wxSize&   size=wxDefaultSize,

		long style=wxDEFAULT_FRAME_STYLE
	);

    // --------------------------------------

    protected: wxTextCtrl* ADDR_TEXT ;
    protected: wxSpinCtrl* BYTES_SPIN ;
    protected: wxButton*   OK_BUTTON  ;

    protected: wxTextCtrl* UDP_TEXT1 ;
    protected: wxTextCtrl* UDP_TEXT2 ;

    // --------------------------------------

    protected: wxGridSizer*      grid_sizer ;
    protected: wxImage**         imageArray ;
    protected: wxStaticBitmap** staticArray ;

	// --------------------------------------

	protected: int sock_descriptor1 = 0 ;
	protected: int sock_descriptor2 = 0 ;
	protected: int sock_descriptor3 = 0 ;
	protected: int sock_descriptor4 = 0 ;

	protected: sockaddr_in* servaddr1 = NULL ;
	protected: sockaddr_in* servaddr2 = NULL ;
	protected: sockaddr_in* servaddr3 = NULL ;
	protected: sockaddr_in* servaddr4 = NULL ;
	protected: sockaddr_in* servaddr5 = NULL ;

    protected: std::string ip_addr = "" ;

    protected: int forbytes = 0 ;
    protected: int SUPPORT  = 2 ; // example for 2: 01 for file number

    // --------------------------------------

    protected: bool working = false ; // for protect UDP_thread* UDP ;

	public: static const int MAXLINE = 1024 ;
    public: static const int DIMENSION =  2 ;

    public: static const int PORT1 = 7778 ;
    public: static const int PORT2 = 7779 ;
    public: static const int PORT3 = 7780 ;
    public: static const int PORT4 = 7781 ;
    public: static const int PORT5 = 7782 ;

    public: static const int grid_width  = 1440 ;
    public: static const int grid_height =  630 ;

    public: static const int correctionX =  1 ;
    public: static const int correctionY = 24 ;

    // --------------------------------------

    DECLARE_EVENT_TABLE() ;

    public: virtual void OKpressed ( wxCommandEvent &event    ) ; // wxGlade: <event_handler>
    public: void onNumberUpdate    ( wxCommandEvent &event    ) ;
    public: void initImages        ( std::string path , int N ) ;

    public: void OnLeftClick ( wxMouseEvent & event ) ;

}; // wxGlade: end class

class MyApp: public wxApp { public: bool OnInit () ; } ;

#endif // SHARINGAN_CLIENT_RTP_5TAILS_H_
