
cmake_minimum_required(VERSION 2.8)
project(helloGL)

aux_source_directory(src SRC_LIST)

set(CMAKE_CXX_FLAGS "-Wall")

add_executable(main ${SRC_LIST})
target_link_libraries(main 
                      GLEW glfw3 
                      dl GL X11 
                      pthread Xrandr Xi
                      )