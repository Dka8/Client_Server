#ifndef NETWORK_EXPORT_H
#define NETWORK_EXPORT_H

//#include <Network/Config.hpp>
#include "../Config.hpp"

#define NETWORK_EXPORT

#if defined(NETWORK_EXPORT)
    #define NETWORK_API API_EXPORT
    //#define NETWORK_API API_INPORT

#else
    #define NETWORK_API API_INPORT
    //#define NETWORK_API API_EXPORT

#endif

#endif
