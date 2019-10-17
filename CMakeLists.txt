cmake_minimum_required(VERSION 3.15)
project(approx-sparql-querying)

set(CMAKE_CXX_STANDARD 11)
find_package(PkgConfig REQUIRED)

pkg_check_modules(REDLAND REQUIRED IMPORTED_TARGET redland)
pkg_check_modules(RASQAL REQUIRED IMPORTED_TARGET rasqal)
pkg_check_modules(RAPTOR REQUIRED IMPORTED_TARGET raptor2)

add_executable(approx-sparql-querying main.cpp main.cpp)

target_compile_options(approx-sparql-querying PUBLIC ${REDLAND_CFLAGS_OTHER} ${RASQAL_CFLAGS_OTHER} ${RAPTOR_CFLAGS_OTHER})

target_include_directories(approx-sparql-querying PUBLIC ${REDLAND_INCLUDE_DIRS} ${RASQAL_INCLUDE_DIRS} ${RAPTOR_INCLUDE_DIRS})
target_link_libraries(approx-sparql-querying PUBLIC ${REDLAND_LIBRARIES} ${RASQAL_LIBRARIES} ${RAPTOR_LIBRARIES})