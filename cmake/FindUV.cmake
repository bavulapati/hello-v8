find_path(UV_INCLUDE_DIR uv.h)
message(STATUS "UV_INCLUDE_DIR ${UV_INCLUDE_DIR}")
find_library(UV_LIBRARY NAMES uv)
message(STATUS "UV_LIBRARY ${V8_LIBRARY}")
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UV DEFAULT_MSG UV_LIBRARY UV_INCLUDE_DIR)

if(UV_FOUND)
  set(UV_LIBS ${UV_LIBRARY})
endif()

