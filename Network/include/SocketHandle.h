#ifndef SOCKETHANDLE_H
#define SOCKETHANDLE_H

#if defined(WV_SYSTEM_WINDOWS)
    #include <basetsd.h>
#endif

//внутреннее обозначение каждого существующего сокета в системе,
//зависит от операционной системы
namespace wv {

    #if defined(WV_SYSTEM_WINDOWS)
        #include <basetsd.h>
    	typedef UINT_PTR SocketHandle;
    #else
        typedef int SocketHandle;
    #endif // defined
}

#endif // SOCKETHANDLE_H
