
%module(directors="1") WrenchRough

#if !defined(SWIGJAVA)
%begin %{
#include <cmath>
%}
#endif

%{
#include <DiscardedSteel.h>
using namespace discarded_steel;
%}

%include std_vector.i
%include std_string.i
%include exception.i

%exception{
    try {
        $action
    } catch (std::exception const& e) {
        SWIG_exception(SWIG_RuntimeError, (std::string("std::exception: ") + e.what()).c_str());
    } catch (...) {
        SWIG_exception(SWIG_UnknownError, "Unknown error");
    }
}

%include <DiscardedSteel.h>

