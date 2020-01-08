# 设置工程名称
project(stringDemo)

# 要编译的文件
file(GLOB FILE
  *.cpp
  ../../chai51/utility/string.cpp
)

# 生成的执行文件名称
add_executable(stringDemo ${FILE})

target_link_libraries(
  stringDemo
  boost_locale
)
