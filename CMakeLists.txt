cmake_minimum_required(VERSION 3.10)

# set the project name
project(JetsonSample)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_BUILD_TYPE Debug)

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")
endif (UNIX)

set(tools /opt/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu)
set(CMAKE_C_COMPILER ${tools}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/aarch64-linux-gnu-g++)

# add the executable
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/TracedException.cpp)

if (WIN32)
    #add_library(Dbghelp STATIC Dbghelp.lib)
    target_link_libraries(${CMAKE_PROJECT_NAME} Dbghelp.lib)
endif (WIN32)