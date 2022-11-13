cmake_minimum_required(VERSION 3.14)

project(QMLTableView LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_STANDARD_REQUIRED     ON)
set (CMAKE_CXX_EXTENSIONS            OFF)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_VERBOSE_MAKEFILE          ON)

find_package(Qt5 COMPONENTS Core Quick Widgets PrintSupport REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE HDR_FILES ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SRC_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE QRC_FILES ${SOURCE_DIR}/*.qrc)
file(GLOB_RECURSE QML_FILES ${SOURCE_DIR}/*.qml)

qt5_add_resources(SRC_FILES ${QRC_FILES})

add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES} ${QML_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_definitions(LINUX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
                -Wall \
                -fpic" )
   set (CMAKE_LINKER_FLAGS "-Wl, --start-group -static-libstdc++ -static-libgcc -static -fpic")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_definitions(WINDOWS)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
                -Wall \
                -fpic" )
    set (CMAKE_LINKER_FLAGS "-Wl, --start-group -static-libstdc++ -static-libgcc -static-runtime -static -fpic")
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::PrintSupport )