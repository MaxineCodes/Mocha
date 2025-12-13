cmake_minimum_required(VERSION 3.20)
project(Mocha LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Place all built artifacts (exe/lib/archive) into a single folder inside the build tree
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/binaries")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/binaries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/binaries")

# Also handle multi-config generators (e.g., Visual Studio) so each config goes to the same folder
if(CMAKE_CONFIGURATION_TYPES)
    foreach(CONF ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER "${CONF}" CONF_UPPER)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF_UPPER} "${CMAKE_BINARY_DIR}/binaries")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF_UPPER} "${CMAKE_BINARY_DIR}/binaries")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF_UPPER} "${CMAKE_BINARY_DIR}/binaries")
    endforeach()
endif()

# Force static libraries to simplify linking
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Store all third-party sources in dependencies/ folder
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/dependencies")

# System OpenGL
find_package(OpenGL REQUIRED)

# GLFW (window/context creation)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLAD (OpenGL 3.3 core loader)
# Use Python glad 0.1.x generator: produces glad/glad.h and glad.c
find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(GLAD_OUT_DIR "${CMAKE_BINARY_DIR}/gladsources/glad_gl_core_33")
set(GLAD_OUT_INCLUDE "${GLAD_OUT_DIR}/include")
set(GLAD_OUT_SRC "${GLAD_OUT_DIR}/src")

add_custom_command(
    OUTPUT
        ${GLAD_OUT_INCLUDE}/KHR/khrplatform.h
        ${GLAD_OUT_INCLUDE}/glad/glad.h
        ${GLAD_OUT_SRC}/glad.c
        ${GLAD_OUT_DIR}/args.txt
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning ${GLAD_OUT_DIR}"
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${GLAD_OUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GLAD_OUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GLAD_OUT_INCLUDE}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GLAD_OUT_SRC}
    COMMAND ${CMAKE_COMMAND} -E echo "Generating with args --out-path ${GLAD_OUT_DIR} --api gl=3.3 --profile core --generator c"
    COMMAND ${Python3_EXECUTABLE} -m glad --out-path ${GLAD_OUT_DIR} --api gl=3.3 --profile core --generator c
    COMMAND ${CMAKE_COMMAND} -E echo "Writing ${GLAD_OUT_DIR}/args.txt"
    COMMAND ${CMAKE_COMMAND} -E echo "--out-path ${GLAD_OUT_DIR} --api gl=3.3 --profile core --generator c" > ${GLAD_OUT_DIR}/args.txt
    COMMENT "Generating GLAD (OpenGL 3.3 core, C generator, 0.1.x)"
)

add_custom_target(glad_generate
    DEPENDS
        ${GLAD_OUT_INCLUDE}/KHR/khrplatform.h
        ${GLAD_OUT_INCLUDE}/glad/glad.h
        ${GLAD_OUT_SRC}/glad.c
        ${GLAD_OUT_DIR}/args.txt
)

add_library(glad_gl_core_33 STATIC
    ${GLAD_OUT_SRC}/glad.c
)
add_dependencies(glad_gl_core_33 glad_generate)
target_include_directories(glad_gl_core_33 PUBLIC ${GLAD_OUT_INCLUDE})

# stb (header-only)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Dear ImGui + backends
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    # Use the docking branch of Dear ImGui
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    glfw
    glad_gl_core_33
    OpenGL::GL
)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

# GLM (header-only math library)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# Assimp (3D model loading)
# Keep it lightweight: disable tools and tests; use static lib to match global setting
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.4.3
)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
# Assimp defines its own zlib by default; keep defaults to simplify setup
FetchContent_MakeAvailable(assimp)

# Main executable
add_executable(Mocha src/main.cpp
        src/core/rendering.cpp
        src/core/rendering.h
        src/core/scene.cpp
        src/core/scene.h
        src/interface/logger.cpp
        src/interface/logger.h
        src/interface/logger.cpp
        src/interface/gui.cpp
        src/interface/gui.h
        src/core/window.cpp
        src/core/window.h
        src/core/renderobject/Material.cpp
        src/core/renderobject/Material.h
        src/core/renderobject/Shader.cpp
        src/core/renderobject/Shader.h
        src/core/renderobject/Mesh.cpp
        src/core/renderobject/Mesh.h
        src/core/renderobject/RenderObject.cpp
        src/core/renderobject/RenderObject.h
        src/core/renderobject/Texture.cpp
        src/core/renderobject/Texture.h
        src/core/Object.h
        src/core/lighting/Light.cpp
        src/core/lighting/Light.h
)

target_link_libraries(Mocha PRIVATE
    OpenGL::GL
    glfw
    glad_gl_core_33
    imgui
    assimp::assimp
)

target_include_directories(Mocha PRIVATE
    ${stb_SOURCE_DIR}
)

# Link or include GLM depending on targets provided by the fetched project
if(TARGET glm::glm)
    target_link_libraries(Mocha PRIVATE glm::glm)
elseif(TARGET glm)
    target_link_libraries(Mocha PRIVATE glm)
else()
    # Fallback: include headers directly (header-only)
    target_include_directories(Mocha PRIVATE ${glm_SOURCE_DIR})
endif()

# Ensure GLAD is generated before compiling Mocha (for headers)
add_dependencies(Mocha glad_generate)
