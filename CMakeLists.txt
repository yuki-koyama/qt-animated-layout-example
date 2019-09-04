cmake_minimum_required(VERSION 3.5)

project(qt-custom-layout CXX)

######################################################################
# Compiler settings
######################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

######################################################################
# Prerequisites
######################################################################

find_package(Eigen3 REQUIRED)
if((NOT TARGET Eigen3::Eigen) AND (DEFINED EIGEN3_INCLUDE_DIR))
  add_library(AliasEigen3 INTERFACE)
  target_include_directories(AliasEigen3 INTERFACE ${EIGEN3_INCLUDE_DIR})
  add_library(Eigen3::Eigen ALIAS AliasEigen3)
endif()

if(APPLE AND EXISTS /usr/local/opt/qt)
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt")
endif()
if(APPLE AND EXISTS /usr/local/opt/qt5)
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
endif()
find_package(Qt5 COMPONENTS Widgets REQUIRED)

######################################################################
# Main app
######################################################################

file(
  GLOB
  sources
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(app ${sources})
target_link_libraries(app Eigen3::Eigen Qt5::Widgets)
