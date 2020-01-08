# 设置CMAKE最小版本
cmake_minimum_required(VERSION 3.9)

# 设置工程名称
project(examples)

# 设置编译选项
set(CMAKE_CXX_FLAGS "-std=c++11 -DBOOST_ALL_DYN_LINK")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
 
# 设置要忽略的编译警告
add_compile_options()
 
# 头文件目录
include_directories(
   $ENV{LIB_ROOT}/include
   .
)

# 链接动态库目录
link_directories(
    $ENV{LIB_ROOT}/lib
)

# 可执行文件存放
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tmp)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# 开始执行子项目
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
#add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/string)

# 拷贝依赖库
#exec_program(mkdir ARGS " -p ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_thread.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_log.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_system.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_locale.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_filesystem.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libcrypto.so.1.1 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libssl.so.1.1 ${PROJECT_BINARY_DIR}/lib")
