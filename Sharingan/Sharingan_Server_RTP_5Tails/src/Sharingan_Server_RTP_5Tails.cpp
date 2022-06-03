#include "Sharingan_Server_RTP_5Tails.h"

#include "demon.h"
#include "shell.h"

using namespace::std ;

// -------------------------------------------------------------------------------------

unsigned char* Sharingan_Server_RTP_5Tails::insert_filenumber_filelen ( unsigned char* buffer , int buffer_len ,
		std::string file_number_str , int file_number_len ,
		std::string filelen_str     , int filelen_len )
{
	unsigned char* new_unsigned = new unsigned char [ buffer_len + file_number_len + filelen_len ] ;

	memcpy ( new_unsigned                                , buffer                  ,      buffer_len ) ; delete[] buffer ;
	memcpy ( new_unsigned + buffer_len                   , file_number_str.c_str() , file_number_len ) ;
    memcpy ( new_unsigned + buffer_len + file_number_len ,     filelen_str.c_str() ,     filelen_len ) ;
	return   new_unsigned ;
}

// -------------------------------------------------------------------------------------

void Sharingan_Server_RTP_5Tails::sharePictures ( std::list<sockaddr_in>** cliaddr_list , int index , int sockfd , int input_bytes , std::string* md5_list )
{
	list<sockaddr_in>* lista = cliaddr_list [ index-1 ] ;

	while ( true )
	{
		usleep ( Sharingan_Server_RTP_5Tails::MILLISECONDS ) ;

		int i1 = int ( (index-1) / Sharingan_Server_RTP_5Tails::DIMENSION ) + 1 ;
		int i2 = int ( (index-1) % Sharingan_Server_RTP_5Tails::DIMENSION ) + 1 ;

		int posx = ( ( i1 - 1 ) * wdim ) ;
	    int posy = ( ( i2 - 1 ) * hdim ) ;

		std::string str_posx = std::to_string (  posx ) ;
		std::string str_posy = std::to_string (  posy ) ;
		std::string str_file = std::to_string ( index ) ;

		system ( std::string
		(
			"maim --geometry " +

			str_wdim + "x" + str_hdim + "+" +
			str_posx + "+" + str_posy + " " +
			    work + "/" + str_file + "a.jpg && sync"

		).c_str () ) ;

		// -------------------------------------------------------------------------------

		std::string live_file = live + '/' + str_file + "b.jpg" ;

		system ( std::string
		(
		   	"convert " + work + "/" + str_file + "a.jpg " +

			"-resize " + str_wdim2 + "x" + str_hdim2 + "! " +

		    "-colorspace Gray " + live_file + " && sync"

		).c_str () ) ; // skip for -quality $quality

		// -------------------------------------------------------------------------------

		std::string md5_tmp = Shell::exec ( std::string ( "echo `md5sum " + live_file + "`" ).c_str() , 32 ) ;

        // std::cout << "new send for i:" + std::to_string ( file ) << endl ;
		if ( md5_list [ index-1 ] != md5_tmp ) md5_list [ index-1 ] = md5_tmp ;

		else continue ;

		// -------------------------------------------------------------------------------

		std::string file_number_str = ( index < 10  ? "0" : "" ) + str_file ;
		int         file_number_len = file_number_str.length             () ;

		int free_bytes_len = ( Sharingan_Server_RTP_5Tails::MAXLINE * input_bytes ) ;

		FILE* fileptr  = fopen ( live_file.c_str() , "rb" ) ; // Open the file in binary mode
		if (  fileptr !=  NULL )
		{
			fseek ( fileptr , 0 , SEEK_END ) ; // Jump to the end of the file

			long int filelen_long = ftell ( fileptr ) ; // Get the current byte offset in the file

			if      ( filelen_long >= free_bytes_len ) std::cout << "error of bytes: " << filelen_long << " >= " << free_bytes_len << " so skipped" << std::endl ;
			else if ( filelen_long <  free_bytes_len )
			{
				std::string filelen_str = std::to_string ( filelen_long   ) ;

				while ( filelen_str.length() < std::to_string ( free_bytes_len ).length() ) filelen_str = "0" + filelen_str ;
				int     filelen_len          =                                              filelen_str.length () ;

				rewind ( fileptr ) ; // Jump back to the beginning of the file

				unsigned char* buffer_send = new unsigned char [ free_bytes_len ] ;

				fread  ( buffer_send , filelen_long , 1 , fileptr ) ; // Read file length bytes for one time,
				fclose (                                  fileptr ) ; // Close the file

				buffer_send = Sharingan_Server_RTP_5Tails::insert_filenumber_filelen ( buffer_send , free_bytes_len ,

				    file_number_str , file_number_len , filelen_str , filelen_len
				) ;

				// -----------------------------------------------------------------------------------------------------------

				for ( std::list<sockaddr_in>::iterator it = lista->begin () ; it != lista->end () ; it ++ )
				{
					sockaddr_in client_addr   = *it ;
					std::string client_ip_src = inet_ntoa ( client_addr.sin_addr ) ;

					if ( ( client_ip_src == "127.0.0.1" ) || ( client_ip_src.find ( "192.168." ) != std::string::npos ) )

						sendto ( sockfd , buffer_send , free_bytes_len + file_number_len + filelen_len ,

							MSG_CONFIRM , (sockaddr *) &client_addr , sizeof ( client_addr ) ) ;
				}

				delete[] buffer_send ;
		    }
		}
	}
}

// -------------------------------------------------------------------------------------

bool Sharingan_Server_RTP_5Tails::exists_in_list (                 sockaddr_in             el , std::string ip_src ) { return ( inet_ntoa ( el.sin_addr ) == ip_src ) ; }
int  Sharingan_Server_RTP_5Tails::find_cliaddr_in_list ( std::list<sockaddr_in>* cliaddr_list , std::string ip_src )
{
	if ( ! cliaddr_list->empty () )
	{
		std::list<sockaddr_in>::iterator it = cliaddr_list->begin () ;

		for ( int i = 0 ; it != cliaddr_list->end () ; i ++ , it ++ )

			if ( Sharingan_Server_RTP_5Tails::exists_in_list ( *it , ip_src ) ) return i ;
	}

	return (-1) ;
}

// -------------------------------------------------------------------------------------

sockaddr_in Sharingan_Server_RTP_5Tails::getServr1() { return this->servaddr1 ; }
sockaddr_in Sharingan_Server_RTP_5Tails::getServr2() { return this->servaddr2 ; }
sockaddr_in Sharingan_Server_RTP_5Tails::getServr3() { return this->servaddr3 ; }
sockaddr_in Sharingan_Server_RTP_5Tails::getServr4() { return this->servaddr4 ; }
sockaddr_in Sharingan_Server_RTP_5Tails::getServr5() { return this->servaddr5 ; }

int          Sharingan_Server_RTP_5Tails::getInputByte () { return this->input_BYTE ; }
std::string* Sharingan_Server_RTP_5Tails::getMd5List   () { return this->md5_list   ; }


// -------------------------------------------------------------------------------------

int main ( int argc, char *argv[] )
{
	if ( argc < 2 ) // want tree , given 3 + 1 ( name of program ) == 4
	{
		// int BYTE , std::string ADDR , std::string PATH

		std::cout << "arguments error, valid count: " << argc - 1 << std::endl ;

		std::cout << "arg1: IP server address"           << std::endl ;
		std::cout << "arg2: for buffer bytes (optional)" << std::endl ;

		return 0 ;
	}

	std::string bytes = ( argc > 2 ? argv [ 2 ] : "45" ) ;

	Sharingan_Server_RTP_5Tails Server_RTP_5Tails = Sharingan_Server_RTP_5Tails (

		argv [ 1 ] , std::atoi ( bytes.c_str() ) ) ;

	std::cout << "started RTP Server" << std::endl ;

	// -------------------------------------------------------------------------------------

	// Creating socket file descriptor
    int sockfd1 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
    int sockfd2 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
    int sockfd3 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
    int sockfd4 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;
    int sockfd5 = socket ( AF_INET , SOCK_DGRAM , 0 ) ;

    sockaddr_in servaddr1 = Server_RTP_5Tails.getServr1 () ;
    sockaddr_in servaddr2 = Server_RTP_5Tails.getServr2 () ;
    sockaddr_in servaddr3 = Server_RTP_5Tails.getServr3 () ;
    sockaddr_in servaddr4 = Server_RTP_5Tails.getServr4 () ;
    sockaddr_in servaddr5 = Server_RTP_5Tails.getServr5 () ;

    // Bind the socket with the server address
    bind ( sockfd1 , (struct sockaddr *) &servaddr1 , sizeof ( servaddr1 ) ) ;
    bind ( sockfd2 , (struct sockaddr *) &servaddr2 , sizeof ( servaddr2 ) ) ;
    bind ( sockfd3 , (struct sockaddr *) &servaddr3 , sizeof ( servaddr3 ) ) ;
    bind ( sockfd4 , (struct sockaddr *) &servaddr4 , sizeof ( servaddr4 ) ) ;
    bind ( sockfd5 , (struct sockaddr *) &servaddr5 , sizeof ( servaddr5 ) ) ;

    usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    std::cout << "listening on port1 " << Sharingan_Server_RTP_5Tails::PORT1 << std::endl ;
    std::cout << "listening on port2 " << Sharingan_Server_RTP_5Tails::PORT2 << std::endl ;
    std::cout << "listening on port3 " << Sharingan_Server_RTP_5Tails::PORT3 << std::endl ;
    std::cout << "listening on port4 " << Sharingan_Server_RTP_5Tails::PORT4 << std::endl ;
    std::cout << "listening on port5 " << Sharingan_Server_RTP_5Tails::PORT5 << std::endl ;

    // Preparing for client address list
    std::list<sockaddr_in>** cliaddr_list = new std::list<sockaddr_in>* [ 4 ] ;

    for ( int i = 0 ; i < 4 ; i ++ ) cliaddr_list [ i ] = new std::list<sockaddr_in> ;

    // -------------------------------------------------------------------------------------

    initDemon () ; usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    // -------------------------------------------------------------------------------------

    new std::thread ( Sharingan_Server_RTP_5Tails::sharePictures , cliaddr_list , 1 , sockfd1 , Server_RTP_5Tails.getInputByte () , Server_RTP_5Tails.getMd5List() ) ;
    usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    new std::thread ( Sharingan_Server_RTP_5Tails::sharePictures , cliaddr_list , 2 , sockfd2 , Server_RTP_5Tails.getInputByte () , Server_RTP_5Tails.getMd5List() ) ;
    usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    new std::thread ( Sharingan_Server_RTP_5Tails::sharePictures , cliaddr_list , 3 , sockfd3 , Server_RTP_5Tails.getInputByte () , Server_RTP_5Tails.getMd5List() ) ;
    usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    new std::thread ( Sharingan_Server_RTP_5Tails::sharePictures , cliaddr_list , 4 , sockfd4 , Server_RTP_5Tails.getInputByte () , Server_RTP_5Tails.getMd5List() ) ;
    usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    new std::thread ( Sharingan_Server_RTP_5Tails::listen_mouse , sockfd5 ) ; usleep ( Sharingan_Server_RTP_5Tails::ONESECOND ) ;

    // -------------------------------------------------------------------------------------

    Sharingan_Server_RTP_5Tails::listen_connections ( cliaddr_list , sockfd1, sockfd2, sockfd3, sockfd4 ) ; return 0 ;
}

// -------------------------------------------------------------------------------------

void Sharingan_Server_RTP_5Tails::listen_connection ( std::list<sockaddr_in>** cliaddr_list , int index , char* buffer_request , int n ,
                                                                sockaddr_in     client_addr , socklen_t client_len )
{
	std::list<sockaddr_in>* lista = cliaddr_list [ index-1 ] ;

	buffer_request [ n ] = '\0' ;

	char* ip_src = inet_ntoa ( client_addr.sin_addr ) ;

	if ( ( std::string ( ip_src ) ==     "127.0.0.1"   ) ||
	  	 ( std::string ( ip_src ).find ( "192.168."    ) != std::string::npos &&
	  	 ( std::string ( buffer_request ) == "connect" ) ))
	{
	    int  i_it = Sharingan_Server_RTP_5Tails::find_cliaddr_in_list ( lista , ip_src ) ;
	    if ( i_it < 0 )

	        lista->push_back ( client_addr ) ;
	    else
	    {
	       	std::list<sockaddr_in>::iterator it = lista->begin () ;

	       	for ( int i = 0 ; i < i_it ; i ++ ) it ++ ;

	            it->sin_port = client_addr.sin_port ;
	    }

	    cout << "------------------" << endl ;

	    cout << "for socket " << std::to_string ( index )
	         << ", client requested connection from port: "
	         << client_addr.sin_port
		     << endl ;
	}
}

void Sharingan_Server_RTP_5Tails::listen_connections ( std::list<sockaddr_in>** cliaddr_list , int sockfd1 , int sockfd2 , int sockfd3 , int sockfd4 )
{
	cout << "------------------"             << endl ;
	cout << "listen for socket connections " << endl ;

	// Filling server information
	sockaddr_in client_addr    ;
	socklen_t   client_len = 0 ;

	// Preparing for buffer
	char buffer_request [ 20 ] ; int n = 0 ;

    // receive from for connection
    while ( true )
    {
    	n = recvfrom        ( sockfd1 , buffer_request , 20 , MSG_WAITALL ,        (sockaddr *) &client_addr , &client_len ) ;
    	Sharingan_Server_RTP_5Tails::listen_connection ( cliaddr_list , 1 , buffer_request , n , client_addr ,  client_len ) ;

    	n = recvfrom        ( sockfd2 , buffer_request , 20 , MSG_WAITALL ,        (sockaddr *) &client_addr , &client_len ) ;
    	Sharingan_Server_RTP_5Tails::listen_connection ( cliaddr_list , 2 , buffer_request , n , client_addr ,  client_len ) ;

    	n = recvfrom        ( sockfd3 , buffer_request , 20 , MSG_WAITALL ,        (sockaddr *) &client_addr , &client_len ) ;
    	Sharingan_Server_RTP_5Tails::listen_connection ( cliaddr_list , 3 , buffer_request , n , client_addr ,  client_len ) ;

    	n = recvfrom        ( sockfd4 , buffer_request , 20 , MSG_WAITALL ,        (sockaddr *) &client_addr , &client_len ) ;
    	Sharingan_Server_RTP_5Tails::listen_connection ( cliaddr_list , 4 , buffer_request , n , client_addr ,  client_len ) ;
    }
}

void Sharingan_Server_RTP_5Tails::listen_mouse ( int sockfd )
{
	cout << "------------------"      << endl ;
	cout << "listen for socket mouse" << endl ;

	// Filling server information
	sockaddr_in client_addr    ;
	socklen_t   client_len = 0 ;

	// Preparing for buffer
	char buffer_request [ 20 ] ; int n = 0 ;

	// Preparing for buffer position
	int wPosition [ 2 ] ;

    // receive from for connection
    while ( ( n = recvfrom ( sockfd , buffer_request , 20 , MSG_WAITALL , (sockaddr *) &client_addr , &client_len ) ) )
    {
    	buffer_request [ n ] = '\0' ;

    	char* ip_src = inet_ntoa ( client_addr.sin_addr ) ;

    	if ( ( std::string ( ip_src ) ==       "127.0.0.1" ) ||
    	   	 ( std::string ( ip_src ).find  (  "192.168."  ) != std::string::npos   &&
    	   	 ( std::string ( buffer_request ).find ( "on:" ) != std::string::npos ) ))
    	{
    		cout << "------------------"       << endl ;
    		cout << "received remote control." << endl ;

    		wPosition [ 0 ] = wPosition [ 1 ] = 0 ;

    		char* buffer = buffer_request + 3 ; // 3 for on:

    		int value = 0 ;

    		while ( buffer [ value ] !=  ',' ) value ++ ;

    		wPosition [ 0 ] = std::atoi ( std::string ( buffer , value     ).c_str() ) ;
    		wPosition [ 1 ] = std::atoi ( std::string ( buffer + value + 1 ).c_str() ) ;

    		cout << "------------------" << endl ;

    		cout << "received x: " << std::to_string ( wPosition [ 0 ] ) <<
    				        " y: " << std::to_string ( wPosition [ 1 ] ) << endl ;

    		wPosition [ 0 ] = int ( double ( wPosition [ 0 ] ) * correctionX ) ;
    		wPosition [ 1 ] = int ( double ( wPosition [ 1 ] ) * correctionY ) ;

    		cout << "------------------" << endl ;

    		cout << "New x: " << std::to_string ( wPosition [ 0 ] ) <<
                       " y: " << std::to_string ( wPosition [ 1 ] ) << endl ;

    		std::string mousemove (

    			"xdotool mousemove " + std::to_string ( wPosition [ 0 ] ) +
				                 " " + std::to_string ( wPosition [ 1 ] )
			) ;

    		if ( system ( mousemove.c_str() ) == 0 )
    		     system ( "sleep 0.1 && xdotool click 1" ) ; // left
        }
    }
}
