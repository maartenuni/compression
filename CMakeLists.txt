
cmake_minimum_required(VERSION 2.8)
project(huffman CXX) 

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -pedantic")


# source files to build the library.
set (HUFF_SOURCES
        BitReader.cpp
        BitWriter.cpp
        HuffmanNode.cpp
        HuffmanStats.cpp
        HuffmanTree.cpp
        )

# headers to build the library
set (HUFF_HEADERS
        BitReader.h
        BitWriter.h
        HuffmanNode.h
        HuffmanStats.h
        HuffmanTree.h
        )

set (HUFF_LIB huffy)

add_library(${HUFF_LIB} SHARED ${HUFF_SOURCES} ${HUFF_HEADERS})
set_property(TARGET ${HUFF_LIB} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${HUFF_LIB} PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(huffman huffman.cpp)
set_property(TARGET huffman PROPERTY CXX_STANDARD 11)
set_property(TARGET huffman PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(huffman ${HUFF_LIB})

add_executable(decomp decompressor.cpp)
set_property(TARGET decomp PROPERTY CXX_STANDARD 11)
set_property(TARGET decomp PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(decomp ${HUFF_LIB})
