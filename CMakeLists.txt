project(exprfunc)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Development)
find_package(pybind11 REQUIRED)

set(LIBRARY_OUTPUT_PATH exprfunc)

pybind11_add_module(exprfunc exprfunc.C)
target_sources(exprfunc PRIVATE expreval/except.cpp
                                expreval/expr.cpp
                                expreval/func.cpp
                                expreval/funclist.cpp
                                expreval/node.cpp
                                expreval/parser.cpp
                                expreval/vallist.cpp)

target_link_libraries(exprfunc PRIVATE pybind11::pybind11 Python3::Python)

# Installation etc
file(WRITE ${PROJECT_BINARY_DIR}/exprfunc/__init__.py "from exprfunc.exprfunc import *\n")
file(GENERATE OUTPUT ${PROJECT_BINARY_DIR}/setup.py
     INPUT ${PROJECT_SOURCE_DIR}/setup.py.in)

install(CODE "message(\"Please use pip to install the package from build directory\")")
