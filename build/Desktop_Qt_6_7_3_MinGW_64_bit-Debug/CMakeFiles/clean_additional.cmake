# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\selim_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\selim_autogen.dir\\ParseCache.txt"
  "selim_autogen"
  )
endif()
