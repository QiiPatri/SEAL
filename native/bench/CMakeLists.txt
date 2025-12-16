# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

cmake_minimum_required(VERSION 3.13)

project(SEALBench VERSION 4.1.1 LANGUAGES CXX)

# If not called from root CMakeLists.txt
if(NOT DEFINED SEAL_BUILD_BENCH)
    set(SEAL_BUILD_BENCH ON)

    # Import Microsoft SEAL (allow any 4.1.x)
    find_package(SEAL 4.1 REQUIRED)

    # Must define these variables and include macros
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${OUTLIB_PATH})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(SEAL_THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/../../thirdparty)
    set(THIRDPARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
    include(FetchContent)
    mark_as_advanced(FETCHCONTENT_BASE_DIR)
    mark_as_advanced(FETCHCONTENT_FULLY_DISCONNECTED)
    mark_as_advanced(FETCHCONTENT_UPDATES_DISCONNECTED)
    mark_as_advanced(FETCHCONTENT_QUIET)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../cmake)
    include(SEALMacros)
else()
    set(THIRDPARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../thirdparty)
endif()

if(NOT DEFINED SEAL_BUILD_DEPS)
    # [option] SEAL_BUILD_DEPS (default: ON)
    # Download and build missing dependencies, throw error if disabled.
    set(SEAL_BUILD_DEPS_OPTION_STR "Automatically download and build unmet dependencies")
    option(SEAL_BUILD_DEPS ${SEAL_BUILD_DEPS_OPTION_STR} ON)
endif()

# if SEAL_BUILD_BENCH is ON, use GoogleBenchmark
if(SEAL_BUILD_BENCH)
    if(SEAL_BUILD_DEPS)
        seal_fetch_thirdparty_content(ExternalBenchmark)
    else()
        find_package(benchmark REQUIRED)
        if(NOT benchmark_FOUND)
            message(FATAL_ERROR "GoogleBenchmark: not found")
        else()
            message(STATUS "GoogleBenchmark: found")
        endif()
    endif()

    # Create a helper library with common bench sources
    add_library(sealbench_common STATIC
        ${CMAKE_CURRENT_LIST_DIR}/bench.cpp
        ${CMAKE_CURRENT_LIST_DIR}/run_helpers.cpp
        ${CMAKE_CURRENT_LIST_DIR}/keygen.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ntt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bfv.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bfv_enc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bfv_add.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bfv_mul.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bfvsplits.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bgv.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bgv_enc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bgv_add.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bgv_mul.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ckks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ckks_enc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ckks_add.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ckks_mul.cpp
        ${CMAKE_CURRENT_LIST_DIR}/register.cpp
    )
    # If we're targeting WASM, add the appropriate link flags
    if(EMSCRIPTEN)
        set_target_properties(sealbench PROPERTIES LINK_FLAGS "-flto -O3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s MAXIMUM_MEMORY=4GB")
    endif()
    # link common lib with seal/benchmark
    if(TARGET SEAL::seal)
        target_link_libraries(sealbench_common PUBLIC SEAL::seal benchmark::benchmark)
    elseif(TARGET SEAL::seal_shared)
        target_link_libraries(sealbench_common PUBLIC SEAL::seal_shared benchmark::benchmark)
    else()
        message(FATAL_ERROR "Cannot find target SEAL::seal or SEAL::seal_shared")
    endif()

    # Add per-scheme executables
    add_executable(sealbench_ckks ${CMAKE_CURRENT_LIST_DIR}/ckks_main.cpp)
    target_link_libraries(sealbench_ckks PRIVATE sealbench_common)

    add_executable(sealbench_ckks_enc ${CMAKE_CURRENT_LIST_DIR}/ckks_enc_main.cpp)
    target_link_libraries(sealbench_ckks_enc PRIVATE sealbench_common)

    add_executable(sealbench_ckks_add ${CMAKE_CURRENT_LIST_DIR}/ckks_add_main.cpp)
    target_link_libraries(sealbench_ckks_add PRIVATE sealbench_common)

    add_executable(sealbench_ckks_mul ${CMAKE_CURRENT_LIST_DIR}/ckks_mul_main.cpp)
    target_link_libraries(sealbench_ckks_mul PRIVATE sealbench_common)

    add_executable(sealbench_bfv ${CMAKE_CURRENT_LIST_DIR}/bfv_main.cpp)
    target_link_libraries(sealbench_bfv PRIVATE sealbench_common)

    # Add split BFV executables (enc/add/mul)
    add_executable(sealbench_bfv_enc ${CMAKE_CURRENT_LIST_DIR}/bfv_enc_main.cpp)
    target_link_libraries(sealbench_bfv_enc PRIVATE sealbench_common)

    add_executable(sealbench_bfv_add ${CMAKE_CURRENT_LIST_DIR}/bfv_add_main.cpp)
    target_link_libraries(sealbench_bfv_add PRIVATE sealbench_common)

    add_executable(sealbench_bfv_mul ${CMAKE_CURRENT_LIST_DIR}/bfv_mul_main.cpp)
    target_link_libraries(sealbench_bfv_mul PRIVATE sealbench_common)

    add_executable(sealbench_bgv ${CMAKE_CURRENT_LIST_DIR}/bgv_main.cpp)
    target_link_libraries(sealbench_bgv PRIVATE sealbench_common)

    add_executable(sealbench_bgv_enc ${CMAKE_CURRENT_LIST_DIR}/bgv_enc_main.cpp)
    target_link_libraries(sealbench_bgv_enc PRIVATE sealbench_common)

    add_executable(sealbench_bgv_add ${CMAKE_CURRENT_LIST_DIR}/bgv_add_main.cpp)
    target_link_libraries(sealbench_bgv_add PRIVATE sealbench_common)

    add_executable(sealbench_bgv_mul ${CMAKE_CURRENT_LIST_DIR}/bgv_mul_main.cpp)
    target_link_libraries(sealbench_bgv_mul PRIVATE sealbench_common)

    add_executable(sealbench_keygen ${CMAKE_CURRENT_LIST_DIR}/keygen_main.cpp)
    target_link_libraries(sealbench_keygen PRIVATE sealbench_common)

    add_executable(sealbench_util ${CMAKE_CURRENT_LIST_DIR}/util_main.cpp)
    target_link_libraries(sealbench_util PRIVATE sealbench_common)
endif()
