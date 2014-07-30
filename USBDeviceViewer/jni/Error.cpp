/*
 * Error.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: pavel
 */

#include <Error.h>

using namespace std;

std::string Error::stacktrace()
{
//	const int buffer_size = 1000;
//	void *buffer[buffer_size];
//	int n = backtrace( buffer, buffer_size );
//
//	char** strings = backtrace_symbols( buffer, n );
//	if ( strings == nullptr ) return string( "i can't print stack trace" );
//
//	stringstream res;
//	res << endl << "Call stack" << endl;
//	for ( int i = 1; i < n; ++i )
//	{
//		res << i << ": " << strings[i] << endl;
//	}
//	free( strings );
//	return res.str();
	return "";
}
