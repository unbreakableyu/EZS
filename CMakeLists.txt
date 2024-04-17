Project(HalloWelt)

cmake_minimum_required(VERSION 2.8)

#include CMAKE-Modules from base directory
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

set(NEEDS_MULTIPLEX "OFF" CACHE BOOL "Does this exercise need serial
multiplexing?")

INCLUDE(EZS)

add_definitions("-D EZS_DUMB_SERIAL")

# Library Sources: C libs
set(LIBEZS_C_SOURCES
	libEZS/drivers/${EZS_ARCH}/ezs_gpio.c
	libEZS/src/ezs_delay.c
	libEZS/src/ezs_lcd.c
	libEZS/drivers/${EZS_ARCH}/ezs_lcd.c
	libEZS/drivers/${EZS_ARCH}/ezs_sdram.c
	libEZS/src/ezs_io.c
	)

# Library Sources C++ libs
set(LIBEZS_CPP_SOURCES
#	libEZS/src/ezs_tracer.cpp
	libEZS/drivers/${EZS_ARCH}/ezs_dac.cpp
	libEZS/drivers/${EZS_ARCH}/ezs_serial.cpp
	libEZS/drivers/${EZS_ARCH}/ezs_counter.cpp
	)

# Testing
if(WITH_SANITY_TEST)
	set(LIBEZS_C_SOURCES
		${LIBEZS_C_SOURCES}
		test/data.c
		test/test.c)
endif(WITH_SANITY_TEST)

# Application Libraries: C
# TODO: Add custom source files here if required
SET(SRC_C_LIST
	hello.c
	${LIBEZS_C_SOURCES}
	)

# Application Libraries: C++
# TODO: Add custom source files here if required
SET(SRC_CPP_LIST
	${LIBEZS_CPP_SOURCES}
	)

set(TGT "app")

# Compiler properties
set_source_files_properties(${SRC_C_LIST} PROPERTIES COMPILE_FLAGS "-Wall -Werror -std=c99 -fgnu89-inline -Wno-unused-variable")
set_source_files_properties(${SRC_CPP_LIST} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-unused-variable")

SET(SRC_LIST
	${SRC_C_LIST}
	${SRC_CPP_LIST}
	)

ECOS_ADD_EXECUTABLE(${TGT} ${SRC_LIST})
