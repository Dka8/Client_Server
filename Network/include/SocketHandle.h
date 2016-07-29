#ifndef SOCKETHANDLE_H
#define SOCKETHANDLE_H

#include <basetsd.h>

//внутреннее обозначение каждого существующего сокета в системе,
//зависит от операционной системы
namespace wv {
	typedef UINT_PTR SocketHandle;
}

#endif // SOCKETHANDLE_H
