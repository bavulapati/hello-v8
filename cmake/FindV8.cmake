find_path(V8_INCLUDE_DIR v8.h)
find_library(V8_LIBRARY NAMES v8 monolith)
find_library(V8_PLATFORM_LIBRARY NAMES v8_libplatform)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(V8 DEFAULT_MSG V8_LIBRARY V8_INCLUDE_DIR)

if(V8_FOUND)
  set(V8_LIBS ${V8_LIBRARY} ${V8_PLATFORM_LIBRARY})
endif()

