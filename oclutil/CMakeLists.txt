include_directories(${PROJECT_SOURCE_DIR}/include)
AUX_SOURCE_DIRECTORY(. DIR_OCL_TUIL_SRCS)
ADD_LIBRARY(oclutil ${DIR_OCL_TUIL_SRCS})
