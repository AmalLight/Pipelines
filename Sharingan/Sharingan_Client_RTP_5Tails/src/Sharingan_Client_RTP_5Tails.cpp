#include "Sharingan_Client_RTP_5Tails.h"

using namespace::std ;

MyFrame::MyFrame ( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ):
         wxFrame ( parent, id, title, pos, size, style )
{
    // begin wxGlade: MyFrame::MyFrame
	SetMinSize ( wxSize ( MyFrame::grid_width , MyFrame::grid_height / 0.7 ) ) ;
	SetMaxSize ( wxSize ( MyFrame::grid_width , MyFrame::grid_height / 0.7 ) ) ;
    SetTitle   ( wxT    ( "Sharingan_Client_RTP_5Tails"                    ) ) ;

    wxIcon icon;
    icon.CopyFromBitmap ( wxBitmap ( wxT ( "./icon/favi.png" ) , wxBITMAP_TYPE_PNG ) ) ;
    SetBackgroundColour ( wxColour ( 47 , 47 , 47          ) ) ;
    SetIcon    ( icon ) ;

    // -------------------------------------------------------------------------------------

    wxBoxSizer* sizer_1 = new wxBoxSizer ( wxVERTICAL   ) ;
    wxBoxSizer* sizer_2 = new wxBoxSizer ( wxVERTICAL   ) ;
    wxBoxSizer* sizer_3 = new wxBoxSizer ( wxHORIZONTAL ) ;

    // -------------------------------------------------------------------------------------

    this->grid_sizer = new wxGridSizer ( 1 , 1 , 0 , 0 ) ;

    sizer_1->Add ( this->grid_sizer , 7 , wxALL|wxEXPAND , 0 ) ;

    this->grid_sizer->Add ( new wxStaticBitmap ( this , wxID_ANY ,
        wxBitmap ( wxT ( "./img/little_vocaloid.jpg" ) , wxBITMAP_TYPE_JPEG ) ) ,
    		                                             wxALL|wxALIGN_CENTER ) ;

    // -------------------------------------------------------------------------------------

    int dimension = pow ( MyFrame::DIMENSION , 2 ) ;

    this->staticArray = new wxStaticBitmap* [ dimension ] ;
    this->imageArray  = new wxImage*        [ dimension ] ;

    for ( int i = 0 ; i < dimension ; i ++ )
    {
    	this->staticArray [ i ] = new wxStaticBitmap ( this , wxID_ANY , wxNullBitmap ) ;
        this->imageArray  [ i ] = new wxImage ( wxT ( "./img/" + std::to_string ( i + 1 ) + "b.jpg" ) , wxBITMAP_TYPE_JPEG ) ;
        this->staticArray [ i ]->Connect ( wxEVT_LEFT_DOWN , wxMouseEventHandler ( MyFrame::OnLeftClick ) ) ;
    }

    // -------------------------------------------------------------------------------------

    sizer_1->Add ( new wxStaticLine ( this , wxID_ANY ) , 0 , wxEXPAND , 0 ) ;
    sizer_1->Add ( sizer_2                              , 3 , wxEXPAND , 0 ) ;
    sizer_2->Add ( sizer_3                              , 1 , wxEXPAND , 0 ) ;

    // -------------------------------------------------------------------------------------

    this->UDP_TEXT1 = new wxTextCtrl ( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL|wxTE_READONLY ) ;
    this->UDP_TEXT1->SetBackgroundColour ( wxColour ( 0 ,   0 , 0 ) ) ;
    this->UDP_TEXT1->SetForegroundColour ( wxColour ( 0 , 255 , 0 ) ) ;

    this->UDP_TEXT2 = new wxTextCtrl ( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_DONTWRAP ) ;
    this->UDP_TEXT2->SetBackgroundColour ( wxColour ( 219 , 212 , 147 ) ) ;
    this->UDP_TEXT2->SetForegroundColour ( wxColour (   0 ,   0 ,   0 ) ) ;
    this->UDP_TEXT2->Enable ( 0 ) ;

    sizer_2->Add ( UDP_TEXT1 , 3 , wxEXPAND , 0 ) ;
    sizer_2->Add ( UDP_TEXT2 , 1 , wxEXPAND , 0 ) ;

    // -------------------------------------------------------------------------------------

    wxStaticText* IP_ADDR = new wxStaticText ( this, wxID_ANY, wxT("IP ADDR:") ) ;
    IP_ADDR->SetForegroundColour ( wxColour ( 255 , 255, 255 ) ) ;
    this->ADDR_TEXT = new wxTextCtrl ( this, wxID_ANY, "127.0.0.1" ) ;

    wxStaticText* FOR_BYTES = new wxStaticText ( this, wxID_ANY, wxT("FOR_BYTES:") ) ;
    FOR_BYTES->SetForegroundColour ( wxColour ( 255 , 255, 255 ) ) ;
    this->BYTES_SPIN = new wxSpinCtrl ( this, wxID_ANY, wxT( "45" ), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 60, 45 ) ;

    this->OK_BUTTON  = new wxButton ( this, wxID_ANY, wxT("OK") ) ;

    sizer_3->Add ( IP_ADDR   , 1 , wxALL , 10 ) ;
    sizer_3->Add ( ADDR_TEXT , 1 , wxALL , 10 ) ;

    sizer_3->Add ( FOR_BYTES  , 1 , wxALL , 10 ) ;
    sizer_3->Add ( BYTES_SPIN , 1 , wxALL , 10 ) ;

    sizer_3->Add ( 0 , 0 , 3 , wxALL|wxEXPAND, 10 ) ;

    sizer_3->Add ( OK_BUTTON , 1, wxALL , 10 ) ;

    // -------------------------------------------------------------------------------------

    SetSizer ( sizer_1 ) ;
    sizer_1->Fit ( this ) ;
    Layout () ;

    this->UDP_TEXT1->SetValue ( "The Main Program is ready." ) ;
}

// ---------------------------------------------------------------------------------------------

BEGIN_EVENT_TABLE ( MyFrame , wxFrame )

    EVT_COMMAND ( NUMBER_UPDATE_ID , wxEVT_COMMAND_TEXT_UPDATED , MyFrame::onNumberUpdate )

    EVT_BUTTON ( wxID_ANY , MyFrame::OKpressed )

END_EVENT_TABLE () ;

// ---------------------------------------------------------------------------------------------

void MyFrame::initImages ( std::string path , int N )
{
    int col = 0 , row = 0 ;

    if ( N == 0 ) // loading for background images
    {
    	for ( int i = 0 ; i < pow ( MyFrame::DIMENSION , 2 ) ; i ++ )
	    {
    	    std::string new_i = std::to_string ( i + 1 ) ;
    		std::string fname = std::string ( path + "/" + new_i + "b.jpg" ) ;

    		if ( i % MyFrame::DIMENSION != 0 ) row += MyFrame::DIMENSION ;

    		this->staticArray [ row ]->SetBitmap (
		   	this->imageArray  [  i  ]->Scale ( MyFrame::grid_width  / MyFrame::DIMENSION ,
                                               MyFrame::grid_height / MyFrame::DIMENSION ,
	     	                                   wxIMAGE_QUALITY_HIGH ) ) ;

    	    if ( ( i + 1 ) % MyFrame::DIMENSION == 0 ) row = ( ++ col ) ;
	    }
    }

    else if ( N > 0 ) // takes N - 1 from before
    {
    	std::string new_i = std::to_string ( N ) ;
    	std::string fname = std::string ( path + "/" + new_i + "b.jpg" ) ;

    	col =       ( N - 1 ) % MyFrame::DIMENSION   ;
    	row = int ( ( N - 1 ) / MyFrame::DIMENSION ) ;
    	col = ( col * MyFrame::DIMENSION ) /* + 1 */ ; //staticArray starting from 0

    	this->staticArray [ col + row ]->SetBitmap (
		this->imageArray  [ N   - 1   ]->Scale ( MyFrame::grid_width  / MyFrame::DIMENSION ,
                                                 MyFrame::grid_height / MyFrame::DIMENSION ,
    	                                         wxIMAGE_QUALITY_HIGH ) ) ;
    }

	this->grid_sizer->Layout () ;
}

// ---------------------------------------------------------------------------------------------

void MyFrame::OKpressed ( wxCommandEvent &event )  // wxGlade: MyFrame.<event_handler>
{
	this->ip_addr  =  ADDR_TEXT->GetValue().ToStdString() ;
    this->forbytes = BYTES_SPIN->GetValue() ;

	bool   error = false ;
	if ( ( error = this-> ip_addr.empty() ) ) UDP_TEXT1->AppendText ( "\n error: IP_ADDR is empty" ) ;
	if ( ! error )
	{
		for ( int i = 0 ; i < 4 ; i ++ )
		{
			this->servaddr1 = new sockaddr_in ;
			this->servaddr2 = new sockaddr_in ;
			this->servaddr3 = new sockaddr_in ;
			this->servaddr4 = new sockaddr_in ;
			this->servaddr5 = new sockaddr_in ;

		    this->sock_descriptor1 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
		    this->sock_descriptor2 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
		    this->sock_descriptor3 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
		    this->sock_descriptor4 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;

		    this->servaddr1->sin_family      = AF_INET   ; // IPv4
		    this->servaddr1->sin_addr.s_addr = inet_addr ( ip_addr.c_str() ) ;
		    this->servaddr1->sin_port        = htons     ( MyFrame::PORT1  ) ;

		    this->servaddr2->sin_family      = AF_INET   ; // IPv4
		    this->servaddr2->sin_addr.s_addr = inet_addr ( ip_addr.c_str() ) ;
		    this->servaddr2->sin_port        = htons     ( MyFrame::PORT2  ) ;

		    this->servaddr3->sin_family      = AF_INET   ; // IPv4
		    this->servaddr3->sin_addr.s_addr = inet_addr ( ip_addr.c_str() ) ;
		    this->servaddr3->sin_port        = htons     ( MyFrame::PORT3  ) ;

		    this->servaddr4->sin_family      = AF_INET   ; // IPv4
		    this->servaddr4->sin_addr.s_addr = inet_addr ( ip_addr.c_str() ) ;
		    this->servaddr4->sin_port        = htons     ( MyFrame::PORT4  ) ;

		    this->servaddr5->sin_family      = AF_INET   ; // IPv4
		    this->servaddr5->sin_addr.s_addr = inet_addr ( ip_addr.c_str() ) ;
		    this->servaddr5->sin_port        = htons     ( MyFrame::PORT5  ) ;
		}

		for ( int i = 0 ; i < 8 ; i ++ )
		{
			sendto ( this->sock_descriptor1 , "connect" , 7 , MSG_CONFIRM , (sockaddr *) this->servaddr1 , sizeof ( *this->servaddr1 ) ) ;
			sendto ( this->sock_descriptor2 , "connect" , 7 , MSG_CONFIRM , (sockaddr *) this->servaddr2 , sizeof ( *this->servaddr2 ) ) ;
			sendto ( this->sock_descriptor3 , "connect" , 7 , MSG_CONFIRM , (sockaddr *) this->servaddr3 , sizeof ( *this->servaddr3 ) ) ;
			sendto ( this->sock_descriptor4 , "connect" , 7 , MSG_CONFIRM , (sockaddr *) this->servaddr4 , sizeof ( *this->servaddr4 ) ) ;
		}

		this->UDP_TEXT1->AppendText ( "\n communicating to this address: " + this->ip_addr                     ) ;
		this->UDP_TEXT1->AppendText ( "\n using this destination port1: "  + std::to_string ( MyFrame::PORT1 ) ) ;
		this->UDP_TEXT1->AppendText ( "\n using this destination port2: "  + std::to_string ( MyFrame::PORT2 ) ) ;
		this->UDP_TEXT1->AppendText ( "\n using this destination port3: "  + std::to_string ( MyFrame::PORT3 ) ) ;
		this->UDP_TEXT1->AppendText ( "\n using this destination port4: "  + std::to_string ( MyFrame::PORT4 ) ) ;

		// ----------------------------------------------------------------------

	    this->UDP_TEXT1->AppendText ( "\n sent Connection request" ) ;

	    if ( ( ! working ) && ( working = true ) )
	    {
	    	this->BYTES_SPIN->Enable ( 0 ) ;
	    	this->ADDR_TEXT-> Enable ( 0 ) ;

	    	wxFile addr ( std::string ( "./save/addr.txt" ).c_str() , wxFile::write ) ;
	    	addr.Write ( this->ip_addr ) ; addr.Close () ;

	    	int free_bytes_int = MyFrame::MAXLINE * forbytes ;
	    	this->SUPPORT = 2 + ( std::to_string ( free_bytes_int ).length() ) ;

	    	this->UDP_TEXT1->AppendText ( "\n waiting for file bytes: "            + std::to_string ( free_bytes_int ) ) ;
	    	this->UDP_TEXT1->AppendText ( "\n waiting for buffer SUPPORT length: " + std::to_string (  this->SUPPORT ) ) ;
	    	this->UDP_TEXT1->AppendText ( "\n starting thread" ) ;

	    	this->UDP_TEXT2->SetValue ( "working bad." ) ;

	    	this->grid_sizer->Clear ( 1 ) ;
	    	this->grid_sizer->SetRows ( MyFrame::DIMENSION ) ;
	    	this->grid_sizer->SetCols ( MyFrame::DIMENSION ) ;
	    	for ( int i = 0 ; i < pow ( MyFrame::DIMENSION , 2 ) ; i ++ ) this->grid_sizer->Add ( this->staticArray [ i ] ) ;

	    	this->initImages ( "./img" , 0 ) ;

	    	RTP_thread_5Tails* RTP1 = new RTP_thread_5Tails ( this , this->UDP_TEXT1 , this->imageArray [ 0 ] , free_bytes_int , this->SUPPORT , this->sock_descriptor1 , false ) ;
	    	RTP_thread_5Tails* RTP2 = new RTP_thread_5Tails ( this , this->UDP_TEXT1 , this->imageArray [ 1 ] , free_bytes_int , this->SUPPORT , this->sock_descriptor2 ,  true ) ;
	    	RTP_thread_5Tails* RTP3 = new RTP_thread_5Tails ( this , this->UDP_TEXT1 , this->imageArray [ 2 ] , free_bytes_int , this->SUPPORT , this->sock_descriptor3 ,  true ) ;
	    	RTP_thread_5Tails* RTP4 = new RTP_thread_5Tails ( this , this->UDP_TEXT1 , this->imageArray [ 3 ] , free_bytes_int , this->SUPPORT , this->sock_descriptor4 ,  true ) ;

		    wxThreadError err ;
		    if      ( (   err = RTP1->Create () ) != wxTHREAD_NO_ERROR ) this->UDP_TEXT2->SetValue ( "working bad: Couldn't create thread!" ) ;
		    else if ( (   err = RTP1->Run    () ) != wxTHREAD_NO_ERROR ) this->UDP_TEXT2->SetValue ( "working bad: Couldn't run thread!"    ) ;
		    else
		    {
		    	this->UDP_TEXT2->SetValue ( "working well: waiting for the first correct buffer_request." ) ;

		        if  ( RTP2->Create () == wxTHREAD_NO_ERROR ) RTP2->Run () ;
		        if  ( RTP3->Create () == wxTHREAD_NO_ERROR ) RTP3->Run () ;
		        if  ( RTP4->Create () == wxTHREAD_NO_ERROR ) RTP4->Run () ;
		    }
	    }
    }
}

// ---------------------------------------------------------------------------------------------

void MyFrame::onNumberUpdate( wxCommandEvent &event )
{
	int n ; switch ( ( n = event.GetInt () ) )
	{
	    case 1: // working good

	        this->OK_BUTTON->Hide () ;
		    this->UDP_TEXT1->AppendText ( "\n OK hidden, Connection successful" ) ;
		    this->UDP_TEXT2->SetBackgroundColour    ( wxColour ( 0, 255 , 127 ) ) ;
		    this->UDP_TEXT2->SetValue               (           "working good." ) ;

		    SetTitle ( std::string ( "5tails " + this->ip_addr ) ) ;

		    break ;

	    default: // >= 2

	    	this->initImages ( "./save" , n - 1 ) ;

	    	wxImage* Image = NULL ;

	    	int sockfd = 0 ;
	    	switch ( n - 1 )
	    	{
	    		case 1:  { sockfd = this->sock_descriptor1 ; Image = this->imageArray [ 0 ] ; break ; }
	    		case 2:  { sockfd = this->sock_descriptor2 ; Image = this->imageArray [ 1 ] ; break ; }
	    	    case 3:  { sockfd = this->sock_descriptor3 ; Image = this->imageArray [ 2 ] ; break ; }
	    		default: { sockfd = this->sock_descriptor4 ; Image = this->imageArray [ 3 ] ; break ; }
	        }

	    	RTP_thread_5Tails* RTP = new RTP_thread_5Tails ( this , this->UDP_TEXT1 , Image , ( MyFrame::MAXLINE * forbytes ) , this->SUPPORT , sockfd , true ) ;

	    	if ( RTP->Create () == wxTHREAD_NO_ERROR ) RTP->Run () ;

	    	break ;
	}
}

// ---------------------------------------------------------------------------------------------

void MyFrame::OnLeftClick ( wxMouseEvent & event )
{
    int wPosition [ 2 ] ;
        wPosition [ 0 ] = wPosition [ 1 ] = 0 ;

    int x1 = 0 , y1 = 0 ;
    int x2 = 0 , y2 = 0 ;

    this->GetParent()->GetPosition ( &x1 , &y1 ) ;
                wxGetMousePosition ( &x2 , &y2 ) ;

    wPosition [ 0 ] = x2 - x1 - MyFrame::correctionX ;
    wPosition [ 1 ] = y2 - y1 - MyFrame::correctionY ;

    // ---------------------------------------------------------

	std::string message ( "on:" + std::to_string ( wPosition [ 0 ] ) + "," +
			                      std::to_string ( wPosition [ 1 ] ) ) ;

	size_t len = strlen ( message.c_str () ) ;

	cout << "click " + message + " with length: " + std::to_string ( len ) << endl ;

	wxString str_addr ;
	wxFile addr ( std::string ( "./save/addr.txt" ).c_str() , wxFile::read ) ;
	       addr.ReadAll ( &str_addr , *wxConvUTF8Ptr ) ;
	       addr.Close () ;

	sockaddr_in servaddr ;
	            servaddr.sin_family      = AF_INET   ; // IPv4
	            servaddr.sin_addr.s_addr = inet_addr ( str_addr.c_str() ) ;
                servaddr.sin_port        = htons     ( 7782 ) ;

    sendto ( socket ( AF_INET ,   SOCK_DGRAM ,           0 ) ,
			 message.c_str () , (size_t) len , MSG_CONFIRM   ,
			 (sockaddr *) &servaddr , sizeof  ( servaddr ) ) ;
}

// ---------------------------------------------------------------------------------------------

IMPLEMENT_APP ( MyApp )

bool MyApp::OnInit()
{
	remove ( std::string ( "./save/addr.txt" ).c_str () ) ;

    wxInitAllImageHandlers () ;

    MyFrame* frame = new MyFrame ( NULL , wxID_ANY , wxEmptyString ) ;

    wxLogStderr::Suspend () ;

    SetTopWindow ( frame ) ;

    frame->Show () ;

    return true ;
}
