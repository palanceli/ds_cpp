project(ds_cpp)
cmake_minimum_required(VERSION 3.1.3)
set(CMAKE_CXX_STANDARD 11)  # 添加C++11支持
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # not necessary, but encouraged

option(ENABLE_STATIC "Build static library" True)

# 添加模块gflag、glog、GTest
find_package(gflags REQUIRED)
include_directories (${gflags_INCLUDE_DIR})

find_package(glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS}) 

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# 加上下面这行以屏蔽Warning: MACOSX_RPATH is not specified
SET(CMAKE_MACOSX_RPATH 1)

set(prefix      ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX})
set(bindir ${prefix}/bin)
set(libdir ${LIB_INSTALL_DIR})
set(datadir ${CMAKE_INSTALL_PREFIX}/share)
set(localedir ${CMAKE_INSTALL_PREFIX}/share/locale)
set(includedir  ${CMAKE_INSTALL_PREFIX}/include/googlepinyin)
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")

#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAG}")  # 在mac OS下会报错，用下面这行替换
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-undefined,error ${CMAKE_SHARED_LINKER_FLAG}")

file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

message(STATUS "source files: " ${SRC})
add_executable(ds_cpp ${SRC})

set(LINKER_LIBS "")
list(APPEND LINKER_LIBS glog::glog)
list(APPEND LINKER_LIBS  ${GTEST_BOTH_LIBRARIES})
target_link_libraries(ds_cpp ${LINKER_LIBS})

