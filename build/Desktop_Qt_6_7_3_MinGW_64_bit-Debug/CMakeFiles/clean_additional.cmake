# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GestionRessources_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GestionRessources_autogen.dir\\ParseCache.txt"
  "GestionRessources_autogen"
  )
endif()
