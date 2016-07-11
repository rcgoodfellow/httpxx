#-------------------------------------------------------------------------------
# httpxx build file
#
# a simple interface for the proxygen http library
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# setup ........................................................................

cmake_minimum_required(VERSION 3.0)
project(httpxx)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${httpxx_SOURCE_DIR}/cmake"
  "/usr/lib/cmake")

set( CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} \
  -std=c11 \
  -Wall -Wextra" )

set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
  -g -O0 -fno-optimize-sibling-calls -fno-omit-frame-pointer" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -g -std=c++14 \
  -Wall -Wextra \
  -fdiagnostics-color=always" )

set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )

set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
  -g -O0 -fno-optimize-sibling-calls -fno-omit-frame-pointer" )

include_directories( "${httpxx_SOURCE_DIR}" )

# build ........................................................................

add_library( httpxx
  http_request.cxx
  http_server.cxx
  proto.cxx
  glog.cxx
)

target_link_libraries( httpxx
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
target_link_libraries( doorbell httpxx )

install(TARGETS httpxx ARCHIVE DESTINATION lib)
install(DIRECTORY ./ DESTINATION include/httpxx 
  FILES_MATCHING PATTERN "*.hxx"
  PATTERN "build" EXCLUDE)
