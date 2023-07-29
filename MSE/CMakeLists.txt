cmake_minimum_required(VERSION 3.25)
project(MSE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(EXECUTABLE_OUTPUT_PATH ../CanvasOutput)

IF (WIN32)
    set(GLFW_H ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/3.3.8_Windows/include/)
    set(ASSIMP_H ${PROJECT_SOURCE_DIR}/ThirdParty/assimp/5.2.5_Window/include)
ELSEIF (APPLE)
    set(GLFW_H ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/3.3.8_MacOS/include/)
    set(ASSIMP_H ${PROJECT_SOURCE_DIR}/ThirdParty/assimp/5.2.5_MacOS/include)
    set(JSON_H ${PROJECT_SOURCE_DIR}/ThirdParty/jsoncpp/1.9.5_MacOS/include)
ENDIF()

# 添加头文件
set(CUSTOM_H ${PROJECT_SOURCE_DIR}/Include/Framework/Custom/)
set(MAPMACRO_H ${PROJECT_SOURCE_DIR}/ThirdParty/map_macro/)
set(GLAD_H ${PROJECT_SOURCE_DIR}/ThirdParty/glad/4.6/include/)
set(CEREAL_H ${PROJECT_SOURCE_DIR}/ThirdParty/cereal/)
set(STB_IMAGE_H ${PROJECT_SOURCE_DIR}/ThirdParty/stb_image)
set(GLM_H ${PROJECT_SOURCE_DIR}/ThirdParty/glm/0.9.9.8/include)

include_directories(${CUSTOM_H} ${MAPMACRO_H} ${GLFW_H} ${GLAD_H} ${CEREAL_H} ${STB_IMAGE_H} ${ASSIMP_H} ${JSON_H} ${GLM_H})

IF (APPLE)
    set(GLFW_LINK ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/3.3.8_MacOS/lib/libglfw.3.dylib)
    set(ASSIMP_LINK ${PROJECT_SOURCE_DIR}/ThirdParty/assimp/5.2.5_MacOS/lib/libassimp.dylib)
    set(JSON_LINK ${PROJECT_SOURCE_DIR}/ThirdParty/jsoncpp/1.9.5_MacOS/lib/libjsoncpp.dylib)
    link_libraries(${OPENGL} ${GLFW_LINK} ${ASSIMP_LINK} ${JSON_LINK})
ENDIF()

#--------------------------------------------- framework info ---------------------------------------------
set(
        FRAMEWORK
        Include/Framework/Custom/CustomPtr.h Source/CustomPtr.cpp
        Include/Framework/Custom/CustomVal.h Source/CustomVal.cpp
        Include/Framework/GarbageCollection.h Source/GarbageCollection.cpp
        Include/Framework/Custom/Static.h Source/Static.cpp)

#--------------------------------------------- core info ---------------------------------------------
set(
        CORE
        Source/Asset.cpp Include/Core/Asset/Asset.h
        Source/AssetManager.cpp Include/Core/Asset/AssetManager.h)


#--------------------------------------------- general info ---------------------------------------------
#--------------------------------------------- container info ---------------------------------------------
set(
        CONTAINER
        Include/General/Container/Queue.h Source/Queue.cpp
        Include/General/Container/Map.h Source/MapMacro.cpp
        Source/Queue.cpp Include/General/Container/Queue.h
        Source/Map.cpp Include/General/Container/Map.h Source/Vector.cpp Include/General/Container/Vector.h)
#--------------------------------------------- tool info ---------------------------------------------
set(
        TOOL
        Include/General/Tool/Debug.h Source/Debug.cpp
        Include/General/Tool/Time.h Source/Time.cpp
        Source/IO.cpp Include/General/Tool/IO.h
)

set(GENERAL ${TOOL} ${CONTAINER})

add_executable(MSE main.cpp Include/Framework/Custom/Reflect.h Source/Reflect.cpp ${FRAMEWORK} ${CORE} ${GENERAL} Source/Canvas.cpp Include/Canvas.h)

## 添加目标链接
IF (WIN32)
    set(GLFW_LINK ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/3.3.8_Windows/lib-mingw-w64/libglfw3.a)
    target_link_libraries(Canvas_1_0 ${GLFW_LINK})
ENDIF()