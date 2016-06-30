#-------------------------------------------------------------------------------
# http++ build file
#
# a simple interface for the proxygen http library
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# setup ........................................................................

cmake_minimum_required(VERSION 3.0)

set( CMAKE_CXX_COMPILER /usr/local/bin/clang++ )
set( CMAKE_C_COMPILER /usr/local/bin/clang )

project(http++)

set(BUILD_SHARED_LIBS ON)

include_directories(
  /usr/local/include/c++/v1 
  /usr/local/include/bsoncxx/v_noabi
  /usr/local/include/mongocxx/v_noabi
)

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
  -g -std=c++1z -stdlib=libc++ \
  -Wall -Wextra \
  -fdiagnostics-color=always -fPIC" )

set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
  -O3" )

set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
  -g -O0 -fno-optimize-sibling-calls -fno-omit-frame-pointer" )

include_directories(
  "${http++_SOURCE_DIR}"
  "/usr/local/include/c++/v1"
)

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
  c++abi
  pthread
)

add_executable ( doorbell doorbell.cxx )
target_link_libraries( doorbell http++ )

install(TARGETS http++ LIBRARY DESTINATION lib)
install(DIRECTORY ./ DESTINATION include/http++ 
  FILES_MATCHING PATTERN "*.hxx"
  PATTERN "build" EXCLUDE)
