cmake_minimum_required(VERSION 3.5)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

# Tell CMake where to find OATPP (local installation)
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

# Set oatpp library paths explicitly
set(OATPP_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/oatpp-1.4.0")
set(OATPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/oatpp-1.4.0/oatpp")

# Find oatpp package
find_package(oatpp REQUIRED)

include_directories(src)

file(GLOB SRC_FILES
    src/*.cpp
    src/controller/*.cpp
)

add_library(${project_name}-lib ${SRC_FILES})
target_link_libraries(${project_name}-lib ${OATPP_LIB_DIR}/liboatpp.a)
target_include_directories(${project_name}-lib
  PRIVATE
    ${OATPP_INCLUDE_DIR}
)

## add executables

add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib ${OATPP_LIB_DIR}/liboatpp.a)
target_include_directories(${project_name}-exe
  PRIVATE
    ${OATPP_INCLUDE_DIR}
)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        test/MyControllerTest.cpp
        test/MyControllerTest.hpp
)

target_link_libraries(${project_name}-test ${project_name}-lib ${OATPP_LIB_DIR}/liboatpp.a ${OATPP_LIB_DIR}/liboatpp-test.a)
add_dependencies(${project_name}-test ${project_name}-lib)
target_include_directories(${project_name}-test
  PRIVATE
    ${OATPP_INCLUDE_DIR}
)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
