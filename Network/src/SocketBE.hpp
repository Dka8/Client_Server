#ifndef NETWORK_SOCKETBE_H
#define NETWORK_SOCKETBE_H
#include "../Config.hpp"

#if defined(SYSTEM_WINDOWS)
    #include "Win32/SocketBE_Win.hpp"
#else
    #include "Unix/SocketBE_Unix.hpp"

#endif

#endif
