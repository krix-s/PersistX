cmake_minimum_required(VERSION 3.16)

project(PersistX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(PersistX
	${SOURCES}
)

target_include_directories(PersistX PRIVATE include)
