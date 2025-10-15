cmake_minimum_required(VERSION 3.20)

set(VENDORS "/Users/bweisz/vendors")

set(CLIENT_NAME minstrel)
set(SERVER_NAME minstrels)

project(${CLIENT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

# Configuration for Intel based macs
if(APPLE)
    if(DEFINED INTEL_APPLE)
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    ENDIF()
ENDIF()


########################################################################
# Client
########################################################################

add_executable(${CLIENT_NAME} main.cpp)
target_include_directories(${CLIENT_NAME} PUBLIC
    include/client
    ${VENDORS}/glad/include)

# GLAD and GLFW
add_subdirectory(${VENDORS}/glfw-3.4 glfw-3.4)
target_link_libraries(${CLIENT_NAME} PUBLIC glfw)
target_sources(${CLIENT_NAME} PUBLIC ${VENDORS}/glad/src/glad.c) 

# Platform agnostic
# target_sources(${CLIENT_NAME} PUBLIC ...)

# Platform dependent
if(WIN32)
    # target_sources(${CLIENT_NAME} PUBLIC src/win32_impl.c)
elseif(APPLE)
    # target_sources(${CLIENT_NAME} PUBLIC src/macos_impl.c)
else() # Linux
    # target_sources(${CLIENT_NAME} PUBLIC src/linux_impl.c)
endif()

########################################################################
# Server
########################################################################

add_executable(${SERVER_NAME} maind.cpp)
target_include_directories(${SERVER_NAME} PUBLIC
    include/server)

# Platform agnostic
# target_sources(${SERVER_NAME} PUBLIC ...)

# Platform dependent
if(WIN32)
    # target_sources(${SERVER_NAME} PUBLIC src/win32_impl.c)
elseif(APPLE)
    # target_sources(${SERVER_NAME} PUBLIC src/macos_impl.c)
else() # Linux
    # target_sources(${SERVER_NAME} PUBLIC src/linux_impl.c)
endif()