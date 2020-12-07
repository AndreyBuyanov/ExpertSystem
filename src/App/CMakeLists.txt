cmake_minimum_required (VERSION 3.0)

project(App)

file(GLOB HEADERS *.hpp)
file(GLOB SOURSES *.cpp)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURSES})

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)
