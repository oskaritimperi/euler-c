CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(euler_problem10 C)
INCLUDE_DIRECTORIES(../common)
SET(SOURCES main.c ../common/utils.c)
ADD_EXECUTABLE(p10 ${SOURCES})
TARGET_LINK_LIBRARIES(p10 m)
SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES COMPILE_FLAGS -g)
