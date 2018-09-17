
cmake_minimum_required(VERSION 2.8)
project(helloGL)

aux_source_directory(src SRC_LIST)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

set(CMAKE_CXX_FLAGS "-Wall")

add_executable(main ${SRC_LIST})
target_link_libraries(main 
                      GLEW glfw3 dl GL X11 pthread Xrandr Xi)
		      Xxf86vm
		      Xcursor
		      Xinerama
                      )
