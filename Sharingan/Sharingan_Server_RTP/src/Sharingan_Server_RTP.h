#ifndef SHARINGAN_SERVER_RTP_H_
#define SHARINGAN_SERVER_RTP_H_

#include <unistd.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <string>
#include <thread>
#include <iostream>
#include <list>

using namespace::std ;

// -----------------------------------------------------------

class Sharingan_Server_RTP
{
    protected: int         input_BYTE =  0 ;
    protected: std::string input_ADDR = "" ;

    protected: sockaddr_in servaddr1 ;
    protected: sockaddr_in servaddr2 ;
    protected: sockaddr_in servaddr3 ;
    protected: sockaddr_in servaddr4 ;
    protected: sockaddr_in servaddr5 ;

    protected: std::string* md5_list ;

    // --------------------------------------

    public: static const int MAXLINE   = 1024 ;
    public: static const int DIMENSION =    2 ;

    public: static const int PORT1 = 7778 ;
    public: static const int PORT2 = 7779 ;
    public: static const int PORT3 = 7780 ;
    public: static const int PORT4 = 7781 ;
    public: static const int PORT5 = 7782 ;

    public: static const int   ONESECOND  = 1000000     ; //   1      second  = 1000000 microseconds
    public: static const int MILLISECONDS =  100000 / 1 ; // 100 milliseconds =  100000 microseconds

    // --------------------------------------

    public: Sharingan_Server_RTP ( std::string ADDR , int BYTE )
	{
		this->input_BYTE = BYTE ;
		this->input_ADDR = ADDR ;

		this->servaddr1.sin_family      = AF_INET ; // IPv4 ;
        this->servaddr1.sin_addr.s_addr = inet_addr ( ADDR.c_str() ) ;
        this->servaddr1.sin_port        = htons     ( Sharingan_Server_RTP::PORT1 ) ;

        this->servaddr2.sin_family      = AF_INET ; // IPv4 ;
        this->servaddr2.sin_addr.s_addr = inet_addr ( ADDR.c_str() ) ;
        this->servaddr2.sin_port        = htons     ( Sharingan_Server_RTP::PORT2 ) ;

        this->servaddr3.sin_family      = AF_INET ; // IPv4 ;
        this->servaddr3.sin_addr.s_addr = inet_addr ( ADDR.c_str() ) ;
        this->servaddr3.sin_port        = htons     ( Sharingan_Server_RTP::PORT3 ) ;

        this->servaddr4.sin_family      = AF_INET ; // IPv4 ;
        this->servaddr4.sin_addr.s_addr = inet_addr ( ADDR.c_str() ) ;
        this->servaddr4.sin_port        = htons     ( Sharingan_Server_RTP::PORT4 ) ;

        this->servaddr5.sin_family      = AF_INET ; // IPv4 ;
        this->servaddr5.sin_addr.s_addr = inet_addr ( ADDR.c_str() ) ;
        this->servaddr5.sin_port        = htons     ( Sharingan_Server_RTP::PORT5 ) ;

        this->md5_list = new std::string [ 4 ] ;
        for ( int i = 0 ; i < 4 ; i ++ ) this->md5_list [ i ] = "" ;
	}

    // --------------------------------------

    public: static bool exists_in_list      (           sockaddr_in             el , std::string ip_src ) ;
    public: static int find_cliaddr_in_list ( std::list<sockaddr_in>* cliaddr_list , std::string ip_src ) ;

	// --------------------------------------

	public: sockaddr_in getServr1 () ;
	public: sockaddr_in getServr2 () ;
	public: sockaddr_in getServr3 () ;
	public: sockaddr_in getServr4 () ;
	public: sockaddr_in getServr5 () ;

	public: int          getInputByte () ;
	public: std::string* getMd5List   () ;

	// --------------------------------------

	public: static void sharePictures      ( std::list<sockaddr_in>** cliaddr_list , int sockfd1 , int sockfd2 , int sockfd3 , int sockfd4 , int input_bytes , std::string* md5_list ) ;
	public: static void listen_connections ( std::list<sockaddr_in>** cliaddr_list , int sockfd1 , int sockfd2 , int sockfd3 , int sockfd4 ) ;
	public: static void listen_connection  ( std::list<sockaddr_in>** cliaddr_list , int index   , char* buffer_request , int n ,
			                                           sockaddr_in     client_addr , socklen_t client_len ) ;
	public: static void listen_mouse ( int sockfd ) ;

	public: static unsigned char* insert_filenumber_filelen ( unsigned char* buffer , int buffer_len ,

		std::string file_number_str , int file_number_len ,
		std::string     filelen_str , int     filelen_len
	) ;
};

#endif /* BASH_SHARINGAN_H_ */
