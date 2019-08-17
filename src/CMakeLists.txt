project(LSCRP)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/amx
)

add_definitions(-DSAMPGDK_AMALGAMATION)

add_samp_plugin(LSCRP
  amxplugin.cpp
  main.cpp
  lscrp.def

  Amxstring.cpp
  Array.cpp
  ArrayItem.cpp
  Entity.cpp
  EntityInfo.cpp
  Lists.cpp
  Structure.cpp
  Tokenizer.cpp
  utils.cpp
)

if(UNIX)
  set_property(TARGET LSCRP APPEND_STRING PROPERTY COMPILE_FLAGS " -fpermissive")
endif()