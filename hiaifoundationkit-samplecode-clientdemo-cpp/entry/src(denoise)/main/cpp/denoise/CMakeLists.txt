cmake_minimum_required(VERSION 3.4.1)
project(denoise)

# 链接 HiAI SDK 和 OpenCV
find_library(hiai_ai_lib HIAI_AI)
find_package(OpenCV REQUIRED)

add_library(denoise_manager SHARED DenoiseManager.cpp)
target_link_libraries(denoise_manager 
    ${hiai_ai_lib} 
    ${OpenCV_LIBS}
    hilog_shared # 鸿蒙日志库
)