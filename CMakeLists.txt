cmake_minimum_required(VERSION 3.10)
project(tir_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -g")

include_directories(headers)
include_directories(Interface)

file(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}
		${SOURCE_FILES}
        main.cpp)

if (UNIX)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/unix)
endif (UNIX)

if(WIN32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/win)
endif(WIN32)

set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

message("SFML library path: ${SFML_ROOT}")

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_ROOT}/include)
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
endif()

find_package(Threads)
if (THREADS_FOUND)
    message("Threads Found")
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()
