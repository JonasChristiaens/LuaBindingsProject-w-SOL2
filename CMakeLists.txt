cmake_minimum_required(VERSION 3.29)

include(FetchContent)

FetchContent_Declare(vcpkg
    URL https://github.com/microsoft/vcpkg/archive/refs/tags/2024.12.16.tar.gz
    URL_HASH SHA1=b1cbc7c2198c7828cfdffd278df260ccaf2cb744
)

FetchContent_MakeAvailable(vcpkg)

set(CMAKE_TOOLCHAIN_FILE 
    "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" 
    CACHE FILEPATH "")

project(GameEngine)
find_package(Lua REQUIRED)

add_executable(GameEngine WIN32
    "src/AbstractGame.cpp"
    "src/AbstractGame.h"
    "src/Game.cpp"
    "src/Game.h"
    "src/GameEngine.cpp"
    "src/GameEngine.h"
    "src/GameWinMain.cpp"
    "src/GameWinMain.h"
    "src/LuaEngine.cpp"
    "src/LuaEngine.h"
    "src/GameEngineBindingsLua.h"
    "src/GameEngineBindingsLua.cpp"
)

target_compile_features(GameEngine PRIVATE
    cxx_std_17
)

target_compile_definitions(GameEngine PRIVATE
    _UNICODE UNICODE
    SOL_ALL_SAFETIES_ON
)

target_include_directories(GameEngine PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(GameEngine PRIVATE ${LUA_LIBRARIES})

set(LUA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua) 

add_custom_command(
    TARGET GameEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${LUA_DIR} $<TARGET_FILE_DIR:GameEngine>/lua
)

# Copy resources to output folder
set(RESOURCES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
file(GLOB_RECURSE RESOURCE_FILES
    "${RESOURCES_SOURCE_DIR}/*.jpg"
    "${RESOURCES_SOURCE_DIR}/*.png"
    "${RESOURCES_SOURCE_DIR}/*.obj"
    "${RESOURCES_SOURCE_DIR}/*.fx"
)
set(RESOURCES_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources/")
file(MAKE_DIRECTORY ${RESOURCES_OUT_DIR})
foreach(RESOURCE ${RESOURCE_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCE}
    ${RESOURCES_OUT_DIR})
endforeach(RESOURCE)