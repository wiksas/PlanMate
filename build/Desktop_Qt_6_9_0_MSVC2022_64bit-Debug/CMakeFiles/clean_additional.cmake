# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PlanMate_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PlanMate_autogen.dir\\ParseCache.txt"
  "PlanMate_autogen"
  )
endif()
