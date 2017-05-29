project (app)
cmake_minimum_required (VERSION 2.8.12.2)

add_executable (${PROJECT_NAME} src/pendulum.cpp)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)


target_link_libraries (${PROJECT_NAME} LINK_PUBLIC phys)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

add_custom_command(COMMAND ${PROJECT_NAME}
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   OUTPUT ${CMAKE_BINARY_DIR}/pendulum.data
                   BYPRODUCTS ${CMAKE_BINARY_DIR}/pendulum.data
                   DEPENDS ${PROJECT_NAME}
                   COMMENT "Generating data set")

add_custom_target(data ALL DEPENDS ${CMAKE_BINARY_DIR}/pendulum.data)