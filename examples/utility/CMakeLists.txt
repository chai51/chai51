# 设置工程名称
project(utilityDemo)

# 要编译的文件
file(GLOB FILE
  *.cpp
  ../../chai51/utility/string.cpp
  ../../chai51/utility/task.cpp
)

# 生成的执行文件名称
add_executable(utilityDemo ${FILE})

target_link_libraries(
  utilityDemo
  boost_locale
  pthread
)
