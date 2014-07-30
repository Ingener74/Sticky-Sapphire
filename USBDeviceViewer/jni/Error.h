/*
 * Error.h
 *
 *  Created on: Jul 30, 2014
 *      Author: pavel
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <Common.h>

class Error: public std::runtime_error
{
public:
    Error( const std::string& message ) :
            runtime_error(message + stacktrace())
    {
    }
    virtual ~Error() throw () = default;

    static std::string stacktrace();
};

#endif /* ERROR_H_ */
