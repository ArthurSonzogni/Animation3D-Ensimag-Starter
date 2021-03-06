cmake_minimum_required (VERSION 2.8)
project (opengl-skeleton)

# put the executable into the bin directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# c++11 activation
#list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
# c++11 activation (Ensimag fallback)
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x") # ensimag fallback c++11

# compilation flags
add_definitions(-Wall)
#add_definitions(-Wno-int-to-void-pointer-cast)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof" )

# find every source file
file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*)

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE STRING "Build the GLFW documentation" FORCE)
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

# glew
add_definitions(-DGLEW_STATIC)
option(glew-cmake_BUILD_SHARED "" OFF)
add_subdirectory(lib/glew)
include_directories(lib/glew/include lib/glew/src)

# glm
include_directories(lib/glm)


include_directories(${PROJECT_SOURCE_DIR}/src)
# executables
add_executable(main ${source_files})
target_link_libraries(main glfw ${GLFW_LIBRARIES} libglew_static)


# 'make run' execute main into the bin directory
add_custom_target(run
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/main
    DEPENDS main
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)
