#ifndef NETWORK_SOCKETHANDLE_H
#define NETWORK_SOCKETHANDLE_H

#include "../Config.hpp"

#if defined(SYSTEM_WINDOW)
    #include <basetsd.h>
#endif

//внутреннее обозначение каждого существующего сокета в системе,
//зависит от операционной системы
namespace wv {

    #if defined(SYSTEM_WINDOW)
        typedef UINT_PTR SocketHandle;
    #else
        typedef int SocketHandle;
    #endif // defined
}

#endif // SOCKETHANDLE_H
