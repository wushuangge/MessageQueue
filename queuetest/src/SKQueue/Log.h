#ifndef _LOG_H_
#define _LOG_H_
#include <sstream>
#include <iostream>
#define  LOG_DEBUG(x) { std::ostringstream o;\
    o << x << "\n";\
    std::cout << o.str().c_str ();\
    }\

#endif