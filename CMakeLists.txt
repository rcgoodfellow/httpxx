#-------------------------------------------------------------------------------
# http++ build file
#
# a simple interface for the proxygen http library
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# setup ........................................................................

cmake_minimum_required(VERSION 3.0)
project(http++)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${http++_SOURCE_DIR}/cmake"
  "/usr/local/lib/cmake")

set( CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} \
  -std=c11 \
  -Wall -Wextra -fPIC" )

set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
  -g -O0 -fno-optimize-sibling-calls -fno-omit-frame-pointer" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -g -std=c++14 \
  -Wall -Wextra \
  -fdiagnostics-color=always -fPIC" )

set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )

set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
  -g -O0 -fno-optimize-sibling-calls -fno-omit-frame-pointer" )

include_directories( "${http++_SOURCE_DIR}" )

# build ........................................................................

add_library( http++
  http_request.cxx
  http_server.cxx
  proto.cxx
  glog.cxx
)

target_link_libraries( http++
  proxygenhttpserver
  proxygenlib
  wangle
  folly
  double-conversion
  z
  ssl
  crypto
  dl
  cap
  event
  gflags
  glog
  pthread
)

add_executable ( doorbell doorbell.cxx )
target_link_libraries( doorbell http++ )

install(TARGETS http++ LIBRARY DESTINATION lib)
install(DIRECTORY ./ DESTINATION include/http++ 
  FILES_MATCHING PATTERN "*.hxx"
  PATTERN "build" EXCLUDE)
