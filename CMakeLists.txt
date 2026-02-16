cmake_minimum_required(VERSION 3.15)
project(ifc_fmt CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externals/Catch2)


#set(Catch2_CHECK_PATHS c:/src/catchorg-Catch2-31b1109/CMake)
#set(Catch2_CHECK_PATHS c:/src/BentleySynchro/ifc_fmt_assignment/vcpkg_installed/x64-windows/share/catch2)
#set(Catch2_DIR c:/src/BentleySynchro/ifc_fmt_assignment/vcpkg_installed/x64-windows/share/catch2)

#find_package(Catch2 REQUIRED)

#set(DBoost_DEBUG ON)
#
#set(Boost_USE_STATIC_LIBS ON)
##find_package(Boost 1.90.0 REQUIRED COMPONENTS regex)
#
#
#find_package(Boost 1.90.0 REQUIRED)
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS}) 
#    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
add_executable(ifc_fmt src/main.cpp "src/ifcParser.cpp" "src/ifcParser.h" "src/ifcBlock.h" "src/ifcBlock.cpp" "src/helpers.h" "src/helpers.cpp"  )
add_executable(tests  "tests/test_helpers.cpp"  "tests/main.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
#else()
#    message(STATUS "Fail  asdasd!")
#endif()
#