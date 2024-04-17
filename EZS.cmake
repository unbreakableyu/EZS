
# first check that ecosconfig is available
FIND_PROGRAM(ECOSCONFIG_EXECUTABLE NAMES ecosconfig)

IF("$ENV{EZS_BASE}" STREQUAL "")
  MESSAGE(FATAL_ERROR "EZS_BASE not set. Did you run 'source ../ecosenv.sh'?")
ELSE()
message(STATUS "EZS_BASE: $ENV{EZS_BASE}")
  IF(NOT IS_DIRECTORY "$ENV{EZS_BASE}")
    MESSAGE(FATAL_ERROR "EZS_BASE set but not a directory. Check your settings in ../ecosenv.sh and your installation'?")
  ENDIF()
  IF(NOT IS_DIRECTORY "$ENV{EZS_CMAKE_MODULE_DIR}")
    MESSAGE(FATAL_ERROR "EZS_CMAKE_MODULE_DIR is not a directory. Check your settings in ../ecosenv.sh and your installation'?")
  ENDIF()
  MESSAGE(STATUS "USING $ENV{EZS_BASE}")
  MESSAGE(STATUS "USING $ENV{EZS_CMAKE_MODULE_DIR} as cmake module path")
  set(CMAKE_MODULE_PATH "$ENV{EZS_CMAKE_MODULE_DIR}" ${CMAKE_MODULE_PATH})
  set(EZS_TOOLS_DIR "$ENV{EZS_CMAKE_MODULE_DIR}")
  MESSAGE(STATUS "USING ${EZS_TOOLS_DIR} as tools path")
ENDIF("$ENV{EZS_BASE}" STREQUAL "")

IF(NOT ECOSCONFIG_EXECUTABLE)
  MESSAGE(FATAL_ERROR "ecosconfig was not found. Do you have a valid ecos repository?")
ENDIF(NOT ECOSCONFIG_EXECUTABLE)

IF("$ENV{EZS_LIBOPENCM3_DIR}" STREQUAL "")
  MESSAGE(WARNING "OPENCM3_PATH not set. Did you run 'source ../ecosenv.sh'")
ELSE()
  set(OPENCM3_PATH $ENV{EZS_LIBOPENCM3_DIR})
ENDIF()

set(EZS_CPU_FLAGS "-mcpu=cortex-m3 -mthumb")

add_definitions( "-D STM32F4")
INCLUDE(EZSconvenience)
INCLUDE(EZSSubmission)
INCLUDE(ezs_ecos_stm32)

set(EZS_ARCH stm32f4)

include_directories(${OPENCM3_PATH}/include)
ECOS_EZS_ADDLIB("${OPENCM3_PATH}/lib/libopencm3_stm32f4.a")

include_directories(${PROJECT_SOURCE_DIR}/libEZS/include)

FIND_PROGRAM(MELD_EXECUTABLE NAMES meld)
IF(MELD_EXECUTABLE)
  add_custom_target(diff_src
    COMMAND ${MELD_EXECUTABLE} "/proj/i4ezs/vorgaben/${CMAKE_PROJECT_NAME}/" "${PROJECT_SOURCE_DIR}"
    COMMENT "Invoking diff")
ENDIF()

option(WITH_SANITY_TEST "Build sanity tests" OFF)

if(WITH_SANITY_TEST)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSANITY_TEST")
endif(WITH_SANITY_TEST)

find_program(EZSSANITYTEST NAMES sanity-test.sh)
IF(NOT EZSSANITYTEST)
  MESSAGE(FATAL_ERROR "sanity-test.sh was not found.")
ENDIF(NOT EZSSANITYTEST)
add_custom_target(sanity-test
	COMMAND ${EZSSANITYTEST} ${CMAKE_SOURCE_DIR})
