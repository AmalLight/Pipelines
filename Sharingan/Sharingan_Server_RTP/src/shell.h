#ifndef SHELL_H_
#define SHELL_H_

#include <string>

using namespace::std ;

class Shell {

    public: static string exec ( string command , int size )
    {
    	char buffer [ size ] ;

    	string result = "" ;

    	// Open pipe to file

    	FILE* pipe = popen ( command.c_str() , "r" ) ;

    	// read till end of process:

    	while ( !feof ( pipe ) )

    		if ( fgets ( buffer , size , pipe ) != NULL )

    		    { pclose ( pipe ) ; return ( result = buffer ) ; }

    	return "" ;
    }
};

#endif /* SHELL_H_ */
