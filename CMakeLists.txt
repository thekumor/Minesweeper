cmake_minimum_required(VERSION 3.29.2)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)

file(GLOB_RECURSE MINESWEEPER_SRC_FILES CONFIGURE_DEPENDS
	"${SOURCE_DIR}/src/Minesweeper/*.cpp"
	"${SOURCE_DIR}/src/Minesweeper/*.h"
)
message("Files: ${SOURCE_DIR}")
add_executable(Minesweeper ${MINESWEEPER_SRC_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Minesweeper)

target_include_directories(Minesweeper PRIVATE src/)
target_link_options(Minesweeper PRIVATE "/SUBSYSTEM:WINDOWS")
target_compile_definitions(Minesweeper PRIVATE UNICODE) # WinAPI A/Ex macro stuff