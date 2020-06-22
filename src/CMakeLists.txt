# Find SDL2 library
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(main main.cpp)

target_link_libraries(main ${SDL2_LIBRARY})
