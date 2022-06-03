#include "RTP_thread.h"

using namespace::std ;

// ----------------------------------------------------------------------------------------------------------

RTP_thread::RTP_thread ( wxFrame* parent , wxTextCtrl* UDP_TEXT1 , wxImage* Image , int free_bytes_int , int SUPPORT , int sock_descriptor , bool working )
{
	this->m_parent  =    parent ;
	this->UDP_TEXT1 = UDP_TEXT1 ;
	this->IMAGE     =     Image ;

	this->free_bytes_int = free_bytes_int ;
	this->SUPPORT = SUPPORT ;

	this->sock_descriptor = sock_descriptor ;
	this->working = working ;
}

// ----------------------------------------------------------------------------------------------------------

wxThread::ExitCode RTP_thread::Entry ()
{
	if ( ! this->working ) UDP_TEXT1->AppendText ( "\n thread is ready" ) ;

	int buffer_len = free_bytes_int + SUPPORT ;
	unsigned char* buffer_request = new unsigned char [ buffer_len ] ;

	bool to_stop = false ; int number = 0 ;

	int       n  = 0 ;
	while ( ( n  = read ( this->sock_descriptor , buffer_request , buffer_len ) ) )
		if  ( n == buffer_len ) // != receives from ==> receives only from server = recv
		{
			char* char_buffer_request = new char [ SUPPORT ] ; int i = 0 ;

			for ( i = free_bytes_int ; i < n && ( ( i - free_bytes_int ) < SUPPORT ) ; i ++ )

			    char_buffer_request [ i - free_bytes_int ] = (char) buffer_request [ i ] ;

			if ( ( i - free_bytes_int ) != SUPPORT )
			{
				cout << "find error A on receive" << endl ;

				delete[] char_buffer_request ;
				delete[] buffer_request ;
			}

			else
			{
				std::string file_number ( char_buffer_request , 2 ) ;
				std::string file_bytes  ( char_buffer_request + 2 , SUPPORT - 2 ) ;

				int int_number = std::atoi   ( file_number.c_str() ) ;
				int int_bytes  = std::atoi   (  file_bytes.c_str() ) ;
				file_number = std::to_string (  int_number         ) ;

				if ( int_number >= 1 && int_number <= pow ( MyFrame::DIMENSION , 2 ) && int_bytes <= free_bytes_int )
				{
					wxMemoryInputStream* stream = new wxMemoryInputStream ( buffer_request , int_bytes ) ;

        	        to_stop = this->IMAGE->LoadFile ( * stream , wxBITMAP_TYPE_JPEG ) ;

        	        if ( ( ! working ) && to_stop )
        	        {
        	        	if ( wxFile::Exists ( std::string ( "./save/addr.txt" ).c_str () ) )
        	        	{
        	        	    wxCommandEvent event ( wxEVT_COMMAND_TEXT_UPDATED , NUMBER_UPDATE_ID ) ;

            	            event.SetInt ( 1 ) ; // pass some data along the event, a number in this case

            	            m_parent->GetEventHandler()->AddPendingEvent ( event ) ;
        	        	}

        	        	else to_stop = false ;
        	        }

        	        else if ( working && to_stop ) number = ( int_number + 1 ) ;

        	        delete stream ;
        	    }

				else cout << "find error B on receive" << endl ;
        	}

        	delete[] char_buffer_request ; // delete[] buffer_request ; not disposable

        	if ( (  ! working ) && to_stop ) working = true ;
        	else if ( working   && to_stop )          break ;
        }

	wxCommandEvent event ( wxEVT_COMMAND_TEXT_UPDATED , NUMBER_UPDATE_ID ) ;

	event.SetInt ( number ) ; // pass some data along the event, a number in this case

	m_parent->GetEventHandler()->AddPendingEvent ( event ) ;

	// this->Kill () ; a thread can't kill itself

	return 0 ;
}
