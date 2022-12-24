#ZAPDUtils

zapd_utils_srcs = ['./Utils/BinaryReader.cpp', './Utils/BinaryWriter.cpp', './Utils/MemoryStream.cpp']

zapd_utils_inc = include_directories('.', './Utils')

#todo, added some, need to reconcile rest: CXXFLAGS ?= -Wall -Wextra -O2 -g -std=c++17
libZAPDUtils = static_library('ZAPDUtils', zapd_utils_srcs, cpp_args:['-Wextra', '-std=c++17'])
