cmake_minimum_required(VERSION 3.4.1)
project(OpenCLDemo)

add_definitions(-std=c++11)

# Android 5.0 以上需要在此处设置 PIE
set(CMAKE_C_FLAGS 		    "${CMAKE_C_FLAGS} 		    -fPIE")
set(CMAKE_CXX_FLAGS 	"${CMAKE_CXX_FLAGS}	-fPIE -pie -stdlib=libstdc++")

# 配置使用 NDK Standalone Toolchain 编译
set(NDK_STANDALONE_TOOLCHAIN 	/opt/android-ndk-r14b/android-armv7)
set(CMAKE_SYSTEM_NAME 		Android)
set(CMAKE_SYSTEM_VERSION 	21)
set(CMAKE_C_COMPILER 		${NDK_STANDALONE_TOOLCHAIN}/bin/clang)
set(CMAKE_CXX_COMPILER 		${NDK_STANDALONE_TOOLCHAIN}/bin/clang++)
set(CMAKE_FIND_ROOT_PATH 	${NDK_STANDALONE_TOOLCHAIN})


# 使用 NDK 提供的头文件
add_definitions("--sysroot=${NDK_STANDALONE_TOOLCHAIN}/sysroot")

SET(TARGET_OS_ARCH "android_armv7")
SET(OPENCV_STATIC_LIBS  ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libIlmImf.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libopencv_imgproc.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libopencv_imgcodecs.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libopencv_video.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libopencv_calib3d.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libzlib.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/liblibpng.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/liblibtiff.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/liblibjpeg.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/liblibwebp.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/liblibjasper.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libopencv_highgui.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libcpufeatures.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libopencv_core.a
                        ${CMAKE_CURRENT_SOURCE_DIR}/opencv/opencv3_4_notbb/libs/${TARGET_OS_ARCH}/libtegra_hal.a)



include_directories(${CMAKE_SOURCE_DIR}/OpenCL/include)
link_directories(${CMAKE_SOURCE_DIR}/OpenCL/lib/)

add_subdirectory(oclutil)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/opencv/opencv3_4_notbb/include)

link_libraries(${OPENCV_STATIC_LIBS})

link_libraries(-lm -llog)

add_executable(OpenCLDemo main.cpp)
target_link_libraries(OpenCLDemo OpenCL oclutil ${OPENCV_STATIC_LIBS})



