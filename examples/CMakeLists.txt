
# 开始执行子项目
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/string)

# 拷贝依赖库
#exec_program(mkdir ARGS " -p ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_thread.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_log.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_system.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_locale.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libboost_filesystem.so.1.63.0 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libcrypto.so.1.1 ${PROJECT_BINARY_DIR}/lib")
#exec_program(cp ARGS "/usr/local/lib/libssl.so.1.1 ${PROJECT_BINARY_DIR}/lib")
