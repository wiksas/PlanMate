# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\applicationTODO_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\applicationTODO_autogen.dir\\ParseCache.txt"
  "applicationTODO_autogen"
  )
endif()
