cmake_minimum_required(VERSION 3.24)

project(pluginloader VERSION 1.0.6)

add_library(_pluginloader_base INTERFACE)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

target_compile_features(_pluginloader_base INTERFACE cxx_std_20)
set_target_properties(_pluginloader_base PROPERTIES
    COMPILE_WARNING_AS_ERROR True
    INTERPROCEDURAL_OPTIMIZATION True
)

if(MSVC)
    target_compile_options(_pluginloader_base INTERFACE /W4)
else()
    target_compile_options(_pluginloader_base INTERFACE -Wall -Wextra -Wpedantic)
endif()
# CMake doesn't understand warnings as errors for MinGW yet
if(MINGW)
    target_compile_options(_pluginloader_base INTERFACE -Werror)
endif()

set(CONFIGURE_FILES_DIR "${CMAKE_CURRENT_BINARY_DIR}/configure")

configure_file(
    "src/version.inl.in"
    "${CONFIGURE_FILES_DIR}/version.inl"
)

set(GIT_PRE_CONFIGURE_FILE "src/git.inl.in")
set(GIT_POST_CONFIGURE_FILE "${CONFIGURE_FILES_DIR}/git.inl")
include(common_cmake/git_watcher.cmake)

# Note not recursive, only top level - we specify proxy explicitly
file(GLOB sources CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")
target_sources(_pluginloader_base PUBLIC
    ${sources}
    ${GIT_POST_CONFIGURE_FILE}
    "src/proxy/proxy.h"
    "src/versioninfo.rc"
)
target_include_directories(_pluginloader_base INTERFACE "src" ${CONFIGURE_FILES_DIR})
target_precompile_headers(_pluginloader_base INTERFACE "src/pch.h")

function(pluginloader_add_impl name)
    add_library(pluginloader_${name} SHARED ${ARGN})
    set_target_properties(pluginloader_${name} PROPERTIES
        PREFIX ""
        OUTPUT_NAME ${name}
        SUFFIX ".dll"
    )
    target_link_libraries(pluginloader_${name} PUBLIC _pluginloader_base)
endfunction()


# ==================================================================================================

pluginloader_add_impl(no_proxy "src/proxy/none.cpp")
pluginloader_add_impl(d3d11 "src/proxy/d3d11.cpp")
pluginloader_add_impl(dsound "src/proxy/dsound.cpp" "src/proxy/dsound.def")
pluginloader_add_impl(winmm "src/proxy/winmm.cpp")
pluginloader_add_impl(xinput1_3 "src/proxy/xinput1_3.cpp" "src/proxy/xinput1_3.def")

install(
    TARGETS
        pluginloader_no_proxy
        pluginloader_d3d11
        pluginloader_dsound
        pluginloader_winmm
        pluginloader_xinput1_3
    RUNTIME DESTINATION .
)
