cmake_minimum_required(VERSION 2.8.9)
project(Client_Server)
#add_subdirectory(Network)

include_directories(Network/include)
include_directories(Server/include)
include_directories(Client/include)
include_directories(NetworkDefinition)

file(GLOB LIB_SOURCES_NETWORK "Network/src/*.cpp" )
set(HEADERS_NETWORK "Network/include/Config.h" "Network/include/IpAddress.h" "Network/include/Network.h" "Network/include/SafeTypes.h" "Network/include/Socket.h" "Network/include/SocketHandle.h" "Network/include/UdpSocket.h" "Network/include/TcpSocket.h")
add_library( Network_lib STATIC ${LIB_SOURCES_NETWORK} ${HEADERS_NETWORK})
target_link_libraries(Network_lib ws2_32)

file(GLOB LIB_SOURCES_SERVER "Server/src/*.cpp")
set(HEADERS_SERVER "Server/include/Server.h" "NetworkDefinition/NetworkDefinition.h")
add_library( Server_lib STATIC ${LIB_SOURCES_SERVER} ${HEADERS_SERVER})
target_link_libraries(Server_lib Network_lib ws2_32)

file(GLOB LIB_SOURCES_CLIENT "Client/src/*.cpp")
set(HEADERS_CLIENT "Client/include/Client.h" "NetworkDefinition/NetworkDefinition.h" "Client/include/ClientTCP.h" "Client/include/ClientUDP.h")
add_library( Client_lib STATIC ${LIB_SOURCES_CLIENT} ${HEADERS_CLIENT})
target_link_libraries(Client_lib Network_lib ws2_32)

add_executable(Server_main Server_main.cpp)
target_link_libraries(Server_main Server_lib Network_lib ws2_32)

add_executable(Client_main Client_main.cpp)
target_link_libraries(Client_main Client_lib Network_lib ws2_32)