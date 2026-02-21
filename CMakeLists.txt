cmake_minimum_required(VERSION 3.15)
project(ifc_fmt CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externals/Catch2)

add_executable(ifc_fmt src/main.cpp "src/ifcParser.cpp" "src/ifcParser.h" "src/ifcBlock.h" "src/ifcBlock.cpp" "src/helpers.h" "src/helpers.cpp"  )
add_executable(tests  "src/helpers.h" "src/helpers.cpp" "tests/tests.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
