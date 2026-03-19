cmake_minimum_required(VERSION 3.20)
project(Mocha LANGUAGES C CXX)

# =========================
# Global configuration
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# =========================
# Output directories
# =========================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

if(CMAKE_CONFIGURATION_TYPES)
    foreach(CONF ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER "${CONF}" CONF_UPPER)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF_UPPER} "${CMAKE_SOURCE_DIR}")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF_UPPER} "${CMAKE_SOURCE_DIR}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF_UPPER} "${CMAKE_SOURCE_DIR}")
    endforeach()
endif()

# =========================
# Dependencies
# =========================
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/dependencies")

find_package(OpenGL REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# -------------------------
# Python venv for GLAD
# -------------------------
set(VENV_PYTHON "$ENV{HOME}/.venvs/glad/bin/python")
if(EXISTS ${VENV_PYTHON})
    message(STATUS "Using Python venv for GLAD: ${VENV_PYTHON}")
    set(Python3_EXECUTABLE ${VENV_PYTHON})
else()
    message(STATUS "Using system Python for GLAD: ${Python3_EXECUTABLE}")
endif()

# -------------------------
# GLFW
# -------------------------
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# -------------------------
# GLAD
# -------------------------
set(GLAD_OUT_DIR "${CMAKE_BINARY_DIR}/gladsources/glad_gl_core_33")
set(GLAD_OUT_INCLUDE "${GLAD_OUT_DIR}/include")
set(GLAD_OUT_SRC "${GLAD_OUT_DIR}/src")

# Create placeholder files for IDE indexing
file(MAKE_DIRECTORY ${GLAD_OUT_INCLUDE}/glad)
file(MAKE_DIRECTORY ${GLAD_OUT_INCLUDE}/KHR)
#file(WRITE ${GLAD_OUT_INCLUDE}/glad/glad.h "// placeholder")
#file(WRITE ${GLAD_OUT_INCLUDE}/KHR/khrplatform.h "// placeholder")
#file(WRITE ${GLAD_OUT_SRC}/glad.c "// placeholder")

# Custom command to generate GLAD
add_custom_command(
        OUTPUT ${GLAD_OUT_SRC}/glad.c ${GLAD_OUT_INCLUDE}/glad/glad.h ${GLAD_OUT_INCLUDE}/KHR/khrplatform.h
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GLAD_OUT_INCLUDE}/glad
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GLAD_OUT_INCLUDE}/KHR
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GLAD_OUT_SRC}
        #COMMAND ${Python3_EXECUTABLE} -m glad --out-path ${GLAD_OUT_DIR} --api gl=3.3 --profile core --generator c
        COMMAND ${Python3_EXECUTABLE} -m glad --out-path ${GLAD_OUT_DIR} --api gl=3.3 --profile core --generator c
        COMMENT "Generating GLAD headers and source"
)

add_custom_target(glad_generate
        DEPENDS ${GLAD_OUT_SRC}/glad.c ${GLAD_OUT_INCLUDE}/glad/glad.h ${GLAD_OUT_INCLUDE}/KHR/khrplatform.h
)

add_library(glad_gl_core_33 STATIC ${GLAD_OUT_SRC}/glad.c
        src/core/importing/modelImporting.h
        src/core/importing/modelImporting.cpp
        src/core/importing/modelImporting.h)
add_dependencies(glad_gl_core_33 glad_generate)
target_include_directories(glad_gl_core_33 PUBLIC ${GLAD_OUT_INCLUDE})

# -------------------------
# stb (header-only)
# -------------------------
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# -------------------------
# ImGui
# -------------------------
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
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

# -------------------------
# GLM
# -------------------------
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# -------------------------
# Assimp
# -------------------------
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.3
)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

# =========================
# Main executable
# =========================
add_executable(Mocha
        src/main.cpp
        src/core/rendering.cpp
        src/core/Scene.cpp
        src/core/Window.cpp
        src/interface/logger.cpp
        src/interface/gui.cpp
        src/core/renderobject/Material.cpp
        src/core/renderobject/Shader.cpp
        src/core/renderobject/Mesh.cpp
        src/core/renderobject/RenderObject.cpp
        src/core/renderobject/Texture.cpp
        src/core/lighting/Light.cpp
        src/core/camera/Camera.cpp
        src/core/camera/Camera.h
)

target_link_libraries(Mocha PRIVATE
        OpenGL::GL
        glfw
        glad_gl_core_33
        imgui
        assimp::assimp
)

target_include_directories(Mocha PRIVATE
        ${GLAD_OUT_INCLUDE}
        ${stb_SOURCE_DIR}
)

if(TARGET glm::glm)
    target_link_libraries(Mocha PRIVATE glm::glm)
else()
    target_include_directories(Mocha PRIVATE ${glm_SOURCE_DIR})
endif()

add_dependencies(Mocha glad_generate)
add_dependencies(imgui glad_generate)
add_dependencies(glad_gl_core_33 glad_generate)

message(STATUS "Build output folder: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")