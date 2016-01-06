# Copyright 2012-2013 The srsGUI Project Developers. See the
# COPYRIGHT file at the top-level directory of this distribution.
#
# This file is part of the srsGUI Project.
#
# srsGUI is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# srsGUI is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# A copy of the GNU Lesser General Public License can be found in
# the LICENSE file in the top-level directory of this distribution
# and at http://www.gnu.org/licenses/.
#

########################################################################
# Prevent in-tree builds
########################################################################
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "Prevented in-tree build. This is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

########################################################################
# Project setup
########################################################################
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (srsGUI)
ENABLE_TESTING()
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

########################################################################
# Install Dirs
########################################################################
if (NOT CMAKE_INSTALL_LIBDIR)
  include(GNUInstallDirs)
endif (NOT CMAKE_INSTALL_LIBDIR)
  
# Fall back to just "lib" if the item provided by GNUInstallDirs doesn't exist
# For example, on Ubuntu 13.10 with CMake 2.8.11.2,
# /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} doesn't exist.
if (NOT EXISTS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  message(STATUS "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR} does not exist. Defaulting install location to ${CMAKE_INSTALL_PREFIX}/lib.")
  set(CMAKE_INSTALL_LIBDIR lib)
endif()

SET(RUNTIME_DIR bin)
SET(LIBRARY_DIR ${CMAKE_INSTALL_LIBDIR})
SET(INCLUDE_DIR include)

########################################################################
# Setup Boost
########################################################################
MESSAGE(STATUS "")
MESSAGE(STATUS "Configuring Boost C++ Libraries...")
SET(BOOST_REQUIRED_COMPONENTS
    thread
    unit_test_framework
    system
)

IF(UNIX AND EXISTS "/usr/lib64")
    LIST(APPEND BOOST_LIBRARYDIR "/usr/lib64") #fedora 64-bit fix
ENDIF(UNIX AND EXISTS "/usr/lib64")

IF(MSVC)
    SET(BOOST_ALL_DYN_LINK "${BOOST_ALL_DYN_LINK}" CACHE BOOL "boost enable dynamic linking")
    IF(BOOST_ALL_DYN_LINK)
        ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK) #setup boost auto-linking in msvc
    ELSE(BOOST_ALL_DYN_LINK)
        UNSET(BOOST_REQUIRED_COMPONENTS) #empty components list for static link
    ENDIF(BOOST_ALL_DYN_LINK)
ENDIF(MSVC)

SET(Boost_ADDITIONAL_VERSIONS
    "1.37.0" "1.37" "1.38.0" "1.38" "1.39.0" "1.39" "1.40.0" "1.40"
    "1.41.0" "1.41" "1.42.0" "1.42" "1.43.0" "1.43" "1.44.0" "1.44"
    "1.42.0" "1.42" "1.43.0" "1.43" "1.44.0" "1.44" "1.45.0" "1.45"
    "1.46.0" "1.46" "1.47.0" "1.47" "1.48.0" "1.48" "1.49.0" "1.49"
    "1.50.0" "1.50" "1.51.0" "1.51" "1.52.0" "1.52" "1.53.0" "1.53")
FIND_PACKAGE(Boost 1.37 REQUIRED ${BOOST_REQUIRED_COMPONENTS})
MESSAGE(STATUS "Boost version: ${Boost_VERSION}")

IF(Boost_VERSION LESS 104600)
    ADD_DEFINITIONS( -DBOOST_FILESYSTEM_VERSION=2 ) #use filesystem version 2 in boost < 1.46
    MESSAGE(STATUS "Using Boost Filesystem V2")
ENDIF(Boost_VERSION LESS 104600)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

MESSAGE(STATUS "Boost include directories: ${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "Boost library directories: ${Boost_LIBRARY_DIRS}")
MESSAGE(STATUS "Boost libraries: ${Boost_LIBRARIES}")

########################################################################
# Macro to add -fPIC property to static libs 
########################################################################
MACRO(SG_SET_PIC)
	IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
        SET_TARGET_PROPERTIES(${ARGV} PROPERTIES COMPILE_FLAGS -fPIC)
    ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
ENDMACRO(SG_SET_PIC)

########################################################################
# Add the subdirectories
########################################################################
ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
