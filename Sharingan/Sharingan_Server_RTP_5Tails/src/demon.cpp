#include "demon.h"

using namespace::std ;

void initDemon ()
{
	cout << endl ;

	cout << "Working: " << work << endl ;
	cout <<    "Live: " << live << endl ;

	cout << "Started and doing files..." << endl ;

	system ( std::string ( "mkdir -p " + live + " && chmod 777 -R " + live ).c_str() ) ;
	system ( std::string ( "mkdir -p " + work + " && chmod 777 -R " + work ).c_str() ) ;

	system ( std::string ( "ls " + home + " | grep Sharingan" ).c_str () ) ;

	cout << endl ;

	cout << "correction x for conversion: " << correctionX << endl ;
	cout << "correction y for conversion: " << correctionY << endl ;

	cout << endl ;
}
