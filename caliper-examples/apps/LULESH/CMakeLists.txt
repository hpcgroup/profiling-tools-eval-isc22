cmake_minimum_required(VERSION 3.0)

project(LULESH CXX)

set(CMAKE_CXX_STANDARD 11)

option(WITH_MPI    "Build LULESH with MPI"          TRUE)
option(WITH_OPENMP "Build LULESH with OpenMP"       TRUE)
option(WITH_SILO   "Build LULESH with silo support" FALSE)
option(WITH_CALIPER   "Build LULESH with Caliper support" FALSE)
option(WITH_HPCTOOLKIT   "Build LULESH with HPCToolkit support" FALSE)
option(WITH_SCOREP   "Build LULESH with Score-P support" FALSE)
option(WITH_TAU   "Build LULESH with TAU sampling support" FALSE)
option(WITH_TAU_SOURCE   "Build LULESH with TAU source instrumentation support" FALSE)
option(WITH_TAU_COMPILER   "Build LULESH with TAU compiler instrumentation support" FALSE)

set(LULESH_USE_CALIPER FALSE)
set(LULESH_USE_HPCTOOLKIT FALSE)
set(LULESH_USE_SCOREP FALSE)
set(LULESH_USE_TAU FALSE)
set(LULESH_USE_TAU_SOURCE FALSE)
set(LULESH_USE_TAU_COMPILER FALSE)

# add Caliper Support
if (WITH_CALIPER)
  find_package(caliper REQUIRED)
  include_directories(${caliper_INCLUDE_DIR})
  add_definitions("-DWITH_CALIPER=1")
  list(APPEND LULESH_EXTERNAL_LIBS caliper)
  set(LULESH_USE_CALIPER TRUE)
endif()
message(STATUS "Caliper support is ${LULESH_USE_CALIPER}")


# add HPCToolkit Support
if (WITH_HPCTOOLKIT)
  include_directories(${hpctoolkit_INCLUDE_DIR})
  link_directories(${hpctoolkit_LIB_DIR})
  add_definitions("-DWITH_HPCTOOLKIT=1")
  list(APPEND LULESH_EXTERNAL_LIBS hpctoolkit)
  set(LULESH_USE_HPCTOOLKIT TRUE)
endif()
message(STATUS "HPCToolkit support is ${LULESH_USE_HPCTOOLKIT}")

# add Score-P Support
if (WITH_SCOREP)
  include_directories(${scorep_INCLUDE_DIR})
  #link_directories(${scorep_LIB_DIR})
  add_definitions("-DWITH_SCOREP=1")
  #list(APPEND LULESH_EXTERNAL_LIBS scorep)
  set(LULESH_USE_SCOREP TRUE)
endif()
message(STATUS "Score-P support is ${LULESH_USE_SCOREP}")

if (WITH_TAU)
  # run cmake with -DCMAKE_CXX_COMPILER=tau_cxx.sh??
  set(LULESH_USE_TAU TRUE)
endif()
message(STATUS "TAU sampling support is ${LULESH_USE_TAU}")

if (WITH_TAU_SOURCE)
  # run cmake with -DCMAKE_CXX_COMPILER=tau_cxx.sh??
  set(LULESH_USE_TAU_SOURCE TRUE)
endif()
message(STATUS "TAU source instrumentation support is ${LULESH_USE_TAU_SOURCE}")

if (WITH_TAU_COMPILER)
  # run cmake with -DCMAKE_CXX_COMPILER=tau_cxx.sh??
  set(LULESH_USE_TAU_COMPILER TRUE)
endif()
message(STATUS "TAU compiler instrumentation support is ${LULESH_USE_TAU_COMPILER}")

if (WITH_MPI)
  find_package(MPI REQUIRED)
  include_directories(${MPI_C_INCLUDE_PATH} ${MPI_CXX_INCLUDE_PATH})
  add_definitions("-DUSE_MPI=1")
  list(APPEND LULESH_EXTERNAL_LIBS ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})
else()
  add_definitions("-DUSE_MPI=0")
endif()

if (WITH_OPENMP)
  find_package(OpenMP REQUIRED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

if (WITH_SILO)
  find_path(SILO_INCLUDE_DIR silo.h
    HINTS ${SILO_DIR}/include)
  find_library(SILO_LIBRARY
    NAMES siloh5
    HINTS ${SILO_DIR}/lib)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(SILO DEFAULT_MSG
    SILO_LIBRARY
    SILO_INCLUDE_DIR)

  if (SILO_FOUND)
    add_definitions("-DVIZ_MESH")
    include_directories(${SILO_INCLUDE_DIR})
    #   Note: silo needs to be built as a dynamic lib, otherwise
    # there are additional dependencies (hdf5) which we don't know.
    # This would be fixed by silo providing a CMake package.
    list(APPEND LULESH_EXTERNAL_LIBS ${SILO_LIBRARY})
  endif()
endif()

execute_process(COMMAND whoami OUTPUT_VARIABLE LULESH_BUILT_BY OUTPUT_STRIP_TRAILING_WHITESPACE)
configure_file(lulesh-build-metadata.cc.in ${CMAKE_CURRENT_BINARY_DIR}/lulesh-build-metadata.cc)

set(LULESH_SOURCES
  lulesh-comm.cc
  lulesh-init.cc
  lulesh-util.cc
  lulesh-viz.cc
  ${CMAKE_CURRENT_BINARY_DIR}/lulesh-build-metadata.cc
  lulesh.cc)

if (WITH_CALIPER)  
  set(LULESH_EXEC lulesh-caliper2.0)
elseif (WITH_HPCTOOLKIT)
  set(LULESH_EXEC lulesh-hpctoolkit2.0)
elseif (WITH_SCOREP)
  set(LULESH_EXEC lulesh-scorep2.0)
elseif (WITH_TAU)
  set(LULESH_EXEC lulesh-tau2.0)
elseif (WITH_TAU_SOURCE)
  set(LULESH_EXEC lulesh-tau-source2.0)
elseif (WITH_TAU_COMPILER)
  set(LULESH_EXEC lulesh-tau-compiler2.0)
else ()
  set(LULESH_EXEC lulesh2.0)
endif ()

add_executable(${LULESH_EXEC} ${LULESH_SOURCES})
target_link_libraries(${LULESH_EXEC} ${LULESH_EXTERNAL_LIBS})

# How to Build 
# Without Tools
# cmake -DCMAKE_CXX_COMPILER=`which mpicxx` -DMPI_CXX_COMPILER=`which mpicxx` -DWITH_MPI=On -DWITH_OPENMP=Off -DCMAKE_CXX_FLAGS="-g -O3" ..

# With Caliper
# export CALI_DIR=$(spack location --install-dir caliper)
# cmake -DCMAKE_CXX_COMPILER=`which mpicxx` -DMPI_CXX_COMPILER=`which mpicxx` -DCMAKE_PREFIX_PATH=$CALI_DIR/share/cmake/caliper -DWITH_MPI=On -DWITH_OPENMP=Off -DWITH_CALIPER=1 -DCMAKE_CXX_FLAGS="-g -O3" ..

# With HPCToolkit
# export HPCTOOLKIT_DIR=$(spack location --install-dir hpctoolkit)
# cmake -DCMAKE_CXX_COMPILER=`which mpicxx` -DMPI_CXX_COMPILER=`which mpicxx` -DCMAKE_CXX_FLAGS="-g -O3" -DWITH_MPI=On -DWITH_OPENMP=Off -Dhpctoolkit_INCLUDE_DIR=$HPCTOOLKIT_DIR/include -Dhpctoolkit_LIB_DIR=$HPCTOOLKIT_DIR/lib/hpctoolkit -DWITH_HPCTOOLKIT=1 ..

# With Score-P
# export SCOREP_DIR=$(HOME)/tools/scorep/scorep-7.1/_build_with_gnu
# SCOREP_WRAPPER=off cmake -DCMAKE_CXX_COMPILER=`which scorep-g++` -DMPI_CXX_COMPILER=`which scorep-mpicxx` -DCMAKE_CXX_FLAGS="-g -O3" -DWITH_MPI=On -DWITH_OPENMP=Off -Dscorep_INCLUDE_DIR=$SCOREP_DIR/include -DWITH_SCOREP=1 ..

# With TAU
# export TAU_LIB_DIR=/g/g92/cankur1/spack/opt/spack/linux-rhel7-broadwell/gcc-8.3.1/tau-2.30.1-b5a7yxge2rcaxqzblg4qywm7v5oozmlv/lib
# sampling      -> cmake -DCMAKE_CXX_FLAGS="-g -O3" -DCMAKE_BUILD_TYPE=Release -DWITH_MPI=On -DWITH_OPENMP=Off -DWITH_TAU=1 .. 
# source inst   -> cmake -DCMAKE_CXX_FLAGS="-g -O3 -tau_makefile=$TAU_LIB_DIR/Makefile.tau-papi-mpi-pthread-pdt" -DCMAKE_BUILD_TYPE=Release -DWITH_MPI=On -DWITH_OPENMP=Off -DWITH_TAU_SOURCE=1 -DCMAKE_CXX_COMPILER=tau_cxx.sh ..
# compiler inst -> cmake -DCMAKE_CXX_FLAGS="-g -O3 -tau_makefile=$TAU_LIB_DIR/Makefile.tau-papi-mpi-pthread-pdt -optCompInst" -DCMAKE_BUILD_TYPE=Release -DWITH_MPI=On -DWITH_OPENMP=Off -DWITH_TAU_COMPILER=1 -DCMAKE_CXX_COMPILER=tau_cxx.sh .. 
# add -DCMAKE_CXX_COMPILER=tau_cxx.sh to instrument
