# CMakeLists.txt文件具有c_cpp_properties.json、tasks.json两个文件的功能，
# 一般如果C++工程较小，可以编写tasks.json文件，否则更适合编写CMakeLists.txt文件。
# 每次编写程序的时候编写一下c_cpp_properties.json，
# 该文件中includePath参数可以很好指定头文件目录，
# 这样就算没有CMakeLists.txt文件，
# 在vscode编写程序的时候它也自动包含了头文件，这样就可以具有代码提示功能

cmake_minimum_required(VERSION 3.0.0)
project(cppcomplier VERSION 0.1.0)

include(CTest)
enable_testing()
# add_executable(可执行文件名 源文件)根据源文件生成可执行文件

add_executable(cppcomplier main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
#编译选项
add_compile_options(-std=c++11)
 
# 头文件路径
include_directories("include")
 
#链接库
link_libraries(event)
 
# 生成可执行的文件