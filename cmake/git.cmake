include_guard()

find_package(Git QUIET)

if(NOT GIT_FOUND)
    message(FATAL_ERROR "Git is required")
endif()

# find root

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --show-superproject-working-tree
    OUTPUT_VARIABLE APX_GIT_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${APX_SOURCE_DIR}
)
if(NOT APX_GIT_ROOT)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
        OUTPUT_VARIABLE APX_GIT_ROOT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY ${APX_SOURCE_DIR}
    )
endif()
if(NOT APX_GIT_ROOT)
    message(FATAL_ERROR "git root directory not found")
endif()

# Update submodules as needed
# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#     option(GIT_SUBMODULE "Check submodules during build" ON)
#     if(GIT_SUBMODULE)
#         message(STATUS "Submodule update")
#         execute_process(
#             COMMAND ${GIT_EXECUTABLE} submodule update --recursive
#             WORKING_DIRECTORY ${APX_GIT_ROOT}
#             RESULT_VARIABLE GIT_SUBMOD_RESULT
#         )
#         if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#             message(FATAL_ERROR "git submodule update failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#         endif()
#     endif()
# endif()

execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --always --tags
    OUTPUT_VARIABLE APX_GIT_IDENTITY
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${APX_GIT_ROOT}
)

execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --always --tags --match "v*.*"
    OUTPUT_VARIABLE APX_GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${APX_GIT_ROOT}
)
string(REPLACE "v" "" APX_GIT_VERSION ${APX_GIT_VERSION})
string(REPLACE "-" "." APX_GIT_VERSION ${APX_GIT_VERSION})
string(REGEX MATCH "^([0-9]*\.[0-9]*\.[0-9]*)" APX_GIT_VERSION ${APX_GIT_VERSION})

execute_process(
    COMMAND ${GIT_EXECUTABLE} branch --show-current
    OUTPUT_VARIABLE APX_GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${APX_GIT_ROOT}
)

message(STATUS "APX version: ${APX_GIT_VERSION} (${APX_GIT_BRANCH})")
