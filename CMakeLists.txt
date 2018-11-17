# 设置工程名称
project (RASP_NB_IOT)
# 设置可执行文件名称
set(MY_TARGET RaspNB)
# CMAKE version
cmake_minimum_required (VERSION 2.6)
# set the host
set(CMAKE_SYSTEM_NAME Linux)

# set compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_EXTENSIONS "-pipe -g -Wall -W -fPIE")
set(CMAKE_CXX_EXTENSIONS "-pipe -g -Wall -W -fPIE")

# set bin dir
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# set lib dir
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

message("++++++++++++++Start Build+++++++++++++++++")

# add header file dir
include_directories(${PROJECT_SOURCE_DIR}/hardware)
include_directories(${PROJECT_SOURCE_DIR}/tools)
include_directories(${PROJECT_SOURCE_DIR}/usr)

# add source file dir
aux_source_directory(${PROJECT_SOURCE_DIR}/hardware HARDWARESRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/tools TOOLSRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/usr USRSRC)

# add sub dir
#ADD_SUBDIRECTORY(src)


# add lib
link_libraries(m pthread ${EXTRA_LIBS})

add_executable(${MY_TARGET} ${USRSRC} ${HARDWARESRC} ${TOOLSRC})

TARGET_LINK_LIBRARIES(${MY_TARGET} ${EXTRA_LIBS})

