#ifndef NETWORK_SOCKETBE_H
#define NETWORK_SOCKETBE_H
//#include <Network/Config.hpp>
#include "../Config.hpp"

#if defined(SYSTEM_WINDOWS)
    //#include <Network/src/Win/SocketBE_Win.hpp>
    #include "Win32/SocketBE_Win.hpp"
#else
    //#include <Network/src/Unix/SocketBE_Unix.hpp>
    #include "Unix/SocketBE_Unix.hpp"

#endif

#endif
