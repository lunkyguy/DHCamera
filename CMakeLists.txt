# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)
# 项目信息
project (OpenCamera)
#设定QT core目录
#set(Qt5Core_DIR "D:/Qt/Qt5.9.6/5.9.6/msvc2015/lib/cmake/Qt5Core")
#添加QT库
#find_package(Qt5Core)
#设定opencv目录
set(Opencv_DIR "D:/opencv2.4.13.6/build")
#添加opencv库
find_package(Opencv REQUIRED)
# 添加包含目录
include_directories("include")
# 添加库文件目录
link_directories(${CMAKE_SOURCE_DIR}/lib)
#添加库文件目录
# link_libraries("libeay32.lib")
# link_libraries("ssleay32.lib")
# 添加子目录
# add_subdirectory(plugin)
#add_subdirectory(onvif)
#add_subdirectory(soap)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(OpenCamera ${DIR_SRCS})
# 添加链接库
target_link_libraries(OpenCamera ${OpenCV_LIBS})