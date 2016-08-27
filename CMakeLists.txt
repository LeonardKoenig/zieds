project(zieds)
cmake_minimum_required(VERSION 3.1.0)

# Some variables collecting what to build
set(SRC_LIST "src/bloom_filter.c"
	     "src/hashes.h")
set(INCLUDE_LIST "include/bloom_filter.h")

# Add -Iinclude/ to compiler call
include_directories("include/")

add_executable(example "src/example.c"
		       ${SRC_LIST}
		       ${INCLUDE_LIST})
