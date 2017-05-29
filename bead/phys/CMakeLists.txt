
project (phys)


cmake_minimum_required (VERSION 2.8.12.2)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")


set(SOURCE_FILES vector.cpp)
set(SOURCE_FILES odeint.cpp)


add_library (${PROJECT_NAME} inc/vector.hpp src/vector.cpp inc/odeint.hpp src/odeint.cpp)


target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

