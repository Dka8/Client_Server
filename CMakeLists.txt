cmake_minimum_required(VERSION 2.8)
project(Client_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(OS_WINDOW 1)
    
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(OS_UNIX 1)
    
else()
    message(FATAL_ERROR "Unsupported operating system") 

endif()

########################################


add_subdirectory(Network)

########################################

set(SERVER_INCROOT ${PROJECT_SOURCE_DIR}/Server/include)
set(SERVER_SRCROOT ${PROJECT_SOURCE_DIR}/Server/src)

set(SERVER_SRC
    ${PROJECT_SOURCE_DIR}/NetworkDefinition.hpp
    ${SERVER_SRCROOT}/Server.cpp
    ${SERVER_INCROOT}/Server.hpp
)

set(SERVER_EXT_LIBS)
set(SERVER_EXT_LIBS ${SERVER_EXT_LIBS} Network)

add_library(Server ${SERVER_SRC})
target_link_libraries(Server ${SERVER_EXT_LIBS})

########################################

set(CLIENT_INCROOT ${PROJECT_SOURCE_DIR}/Client/include)
set(CLIENT_SRCROOT ${PROJECT_SOURCE_DIR}/Client/src)

set(CLIENT_SRC
    ${PROJECT_SOURCE_DIR}/NetworkDefinition.hpp
    ${CLIENT_INCROOT}/Client.hpp
    ${CLIENT_SRCROOT}/Client.cpp
    ${CLIENT_INCROOT}/Protocol.h
)

set(CLIENT_EXT_LIBS)
set(CLIENT_EXT_LIBS ${CLIENT_EXT_LIBS} Network)

add_library(Client ${CLIENT_SRC})
target_link_libraries(Client ${CLIENT_EXT_LIBS})

########################################

add_executable(Server_main Server_main.cpp)
target_link_libraries(Server_main Server)

########################################

add_executable(Client_main Client_main.cpp)
target_link_libraries(Client_main Client)
