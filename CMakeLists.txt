cmake_minimum_required(VERSION 3.15)
project(Noise)

set(CMAKE_CXX_STANDARD 11)

# Remove "-Wno-deprecated-register" flag raised in Eigen library
set(CMAKE_CXX_FLAGS "-Wno-deprecated-register")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

# Import utilities
include(common/config.cmake)
include(common/Eigen.cmake)
include(common/OpenGP.cmake)
include(common/OpenGL.cmake)
include(common/GLEW.cmake)
include(common/GLFW.cmake)

# Import Assimp
include(common/Assimp.cmake)

# Import OpenCV
if(APPLE)
    set(OpenCV_DIR "/usr/local/Cellar/opencv/4.0.1/lib/cmake/opencv4")
endif()
find_package(OpenCV REQUIRED)
message(STATUS "Found OpenCV: ${OpenCV_LIBRARIES}")
link_directories(${OpenCV_LIBRARY_DIRS})

# import matplotlib-cpp
find_package(Python2 COMPONENTS Development NumPy)

add_executable(Noise
        Driver.cpp
        Perlin.cpp
        Marble.cpp
        Gabor.cpp
        Worley.cpp
        ExperimentalNoise.cpp
        Splatter.cpp
        Wood.cpp
        Fractal.cpp
        Noise.cpp
        HashFunctions.cpp
        Analysis.cpp
        ImageOutput.cpp
        loadTexture.h
        Mesh.cpp
        Texture.cpp
        Camera.cpp
        Renderer.cpp
        Shader.h
        external/tinycolormap/tinycolormap.hpp
        external/stb_image/stb_image.cpp
        external/stb_image/stb_image_write.cpp
        external/imgui/imconfig.h
        external/imgui/imgui.cpp
        external/imgui/imgui.h
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_impl_glfw.cpp
        external/imgui/imgui_impl_glfw.h
        external/imgui/imgui_impl_opengl3.cpp
        external/imgui/imgui_impl_opengl3.h
        external/imgui/imgui_internal.h
        external/imgui/imgui_widgets.cpp
        external/imgui/imstb_rectpack.h
        external/imgui/imstb_textedit.h
        external/imgui/imstb_truetype.h
        external/imgui/imgui_user.h
        external/imgui/imgui_user.inl
        )

target_link_libraries(Noise ${ASSIMP_LIBRARIES} m)
target_link_libraries(Noise ${EIGEN3_LIBRARIES} m)
target_link_libraries(Noise ${OPENGP_LIBRARIES} m)
target_link_libraries(Noise ${OPENGL_LIBRARIES} m)
target_link_libraries(Noise ${GLEW_LIBRARIES} m)
target_link_libraries(Noise ${GLFW3_LIBRARIES} m)
target_link_libraries(Noise ${OpenCV_LIBS} m)
target_include_directories(Noise PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
target_link_libraries(Noise Python2::Python Python2::NumPy)
