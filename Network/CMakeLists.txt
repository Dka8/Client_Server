set(ROOT ${PROJECT_SOURCE_DIR}/Network)
set(INCROOT ${PROJECT_SOURCE_DIR}/Network/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/Network/src)

set(SRC
    ${ROOT}/Network.hpp
    ${ROOT}/Config.hpp
    ${INCROOT}/Export.hpp
    ${SRCROOT}/IpAddress.cpp
    ${INCROOT}/IpAddress.hpp
    ${INCROOT}/SafeTypes.hpp
    ${SRCROOT}/Socket.cpp
    ${INCROOT}/Socket.hpp
    ${SRCROOT}/SocketBE.hpp
    ${INCROOT}/SocketHandle.hpp
    ${SRCROOT}/TcpListener.cpp
    ${INCROOT}/TcpListener.hpp
    ${SRCROOT}/TcpSocket.cpp
    ${INCROOT}/TcpSocket.hpp
    ${SRCROOT}/UdpSocket.cpp
    ${INCROOT}/UdpSocket.hpp
)

if(OS_WINDOW)
    set(SRC
        ${SRC}
        ${SRCROOT}/Win32/SocketBE_Win.cpp
        ${SRCROOT}/Win32/SocketBE_Win.hpp
    )
    
else()
    set(SRC
        ${SRC}
        ${SRCROOT}/Unix/SocketBE_Unix.cpp
        ${SRCROOT}/Unix/SocketBE_Unix.hpp
    )

endif()

set(NETWORK_EXT_LIBS)
if(OS_WINDOW)
    set(NETWORK_EXT_LIBS ${NETWORK_EXT_LIBS} ws2_32)

endif()

add_library(Network ${SRC})
set_target_properties(Network PROPERTIES DEFINE_SYMBOL NETWORK_EXPORT)
target_link_libraries(Network ${NETWORK_EXT_LIBS})
