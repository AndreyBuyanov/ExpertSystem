cmake_minimum_required (VERSION 3.0)

project(Engine)

file(GLOB HEADERS *.hpp)
file(GLOB SOURSES *.cpp)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURSES})

target_link_libraries(${PROJECT_NAME} PRIVATE pugixml)
