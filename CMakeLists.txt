cmake_minimum_required(VERSION 3.1)

project(PET_GAME_ENGINE)

# Search in the `cmake' directory for additional CMake modules.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" "${PROJECT_SOURCE_DIR}/cmake/Modules")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

option(WANT_ZLIB "use zlib (ability to decompress layers data) ?" on)
option(WANT_XML "use libXml2 (ability to read .tmx maps) ?" on)
option(WANT_JSON "use JSON (ability to read .json maps) ?" on)

if(WANT_ZLIB)
    add_definitions(-DWANT_ZLIB)
    include(FindZLIB)
    find_package(ZLIB REQUIRED)
    include_directories(${ZLIB_INCLUDE_DIR})
else(WANT_ZLIB)
    message("Zlib not wanted")
endif(WANT_ZLIB)

if(WANT_XML)
    add_definitions(-DWANT_XML)
    include(FindLibXml2)
    find_package(LibXml2 REQUIRED)
    include_directories(${LIBXML2_INCLUDE_DIR})
else(WANT_XML)
    message("LibXml not wanted")
endif(WANT_XML)

if(WANT_JSON)
    add_definitions(-DWANT_JSON)
    include(FindJansson)
    find_package(Jansson REQUIRED)
    include_directories(${JANSSON_INCLUDE_DIR})
else(WANT_JSON)
    message("Json not wanted")
endif(WANT_JSON)

set(TMX_INC "/usr/local/include")
set(TMX_LIB "/usr/local/lib")

set(SOURCES_ENGINE "src/PETGameEngine/surface.cpp" 
            "src/PETGameEngine/Component.cpp" 
            "src/PETGameEngine/ComponentSet.cpp" 
            "src/PETGameEngine/VisualComponent.cpp" 
            "src/PETGameEngine/Sprite.cpp" 
            "src/PETGameEngine/vetor2D.cpp" 
            "src/PETGameEngine/messageSender.cpp" 
            "src/PETGameEngine/Cronometro.cpp" 
            "src/PETGameEngine/LightSurface.cpp" 
            "src/PETGameEngine/ResourceManager.cpp" 
            "src/PETGameEngine/Screen.cpp" 
            "src/PETGameEngine/TiledMap.cpp" 
            "src/PETGameEngine/videobufferexception.cpp" 
            "src/PETGameEngine/videoiniterrorexception.cpp" 
            "src/PETGameEngine/screenexception.cpp" 
            "src/PETGameEngine/LoadImageException.cpp" 
            "src/PETGameEngine/NoTargetException.cpp" 
            "src/PETGameEngine/NoVideoBufferException.cpp" 
            )
set(INC_ENGINE "include/PETGameEngine")

set(SOURCES_GAME "src/PETGameDemo/Alien.cpp" 
                 "src/PETGameDemo/Ghost.cpp" 
                 "src/PETGameDemo/Item.cpp" 
                 "src/PETGameDemo/Mariama.cpp" 
                 "src/PETGameDemo/Monstro.cpp" 
                 "src/PETGameDemo/Personagem.cpp" 
                 "src/PETGameDemo/Zombie.cpp" 
                 "src/PETGameDemo/main.cpp" 
                 )
set(INC_GAME "include/PETGameDemo")

include_directories(${INC_ENGINE})

link_directories("${TMX_LIB}")


add_library(${PROJECT_NAME} ${SOURCES_ENGINE})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}" "${SDL2IMAGE_INCLUDE_DIR}" "${TMX_INC}")
target_link_libraries(${PROJECT_NAME}  "${SDL2_LIBRARY}" "${SDL2IMAGE_LIBRARY}" tmx)



add_executable(demoGame ${SOURCES_GAME})
target_include_directories(demoGame SYSTEM PRIVATE "${SDL2_INCLUDE_DIR}" "${SDL2IMAGE_INCLUDE_DIR}" "${INC_GAME}")
target_link_libraries(demoGame "${SDL2_LIBRARY}" "${SDL2IMAGE_LIBRARY}" "${PROJECT_NAME}")
if(WANT_ZLIB)
    target_link_libraries(demoGame z)
endif()
if(WANT_XML)
    target_link_libraries(demoGame xml2)
endif()
if(WANT_JSON)
    target_link_libraries(demoGame jansson)
endif()



