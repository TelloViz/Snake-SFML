# Set minimum version for SFML 2.5.1 compatibility
cmake_minimum_required(VERSION 3.16)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(Snake LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SFML 2.5.1 uses std::auto_ptr which was removed in C++17
if(MSVC)
    add_compile_definitions(_HAS_AUTO_PTR_ETC=1)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure dependencies
include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)

FetchContent_MakeAvailable(SFML)

# Project sources
set(SOURCES
    src/Debug_Window.cpp
    src/Game.cpp
    src/Game_Over_State.cpp
    src/main.cpp
    src/Menu_State.cpp
    src/Options_State.cpp
    src/Pause_State.cpp
    src/Play_State.cpp
    src/Snake.cpp
    src/Snake_Controller.cpp
    src/Snake_Rule_Monitor.cpp
    src/Static_Graphic.cpp
)

set(HEADERS
    src/Debug_Window.hpp
    src/Game.h
    src/Game_Over_State.hpp
    src/ICommand.hpp
    src/IContext.hpp
    src/IReceiver.hpp
    src/IState.hpp
    src/Menu_State.hpp
    src/Options_State.hpp
    src/Pause_State.hpp
    src/Play_State.hpp
    src/Snake.h
    src/Snake_Controller.h
    src/Snake_Rule_Monitor.h
    src/Static_Graphic.h
)

# Executable target
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

# Include and linking
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics
    sfml-audio
    sfml-network
)

# Resource deployment
# Assets are now cleanly separated in the resources/ directory
file(GLOB ASSETS 
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.ogg"
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.ttf"
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.txt"
)

foreach(ASSET_PATH ${ASSETS})
    get_filename_component(ASSET_NAME ${ASSET_PATH} NAME)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ASSET_PATH}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${ASSET_NAME}"
        COMMENT "Deploying ${ASSET_NAME}"
    )
endforeach()

# Specific handling for OpenAL runtime on Windows
if(WIN32)
    set(OPENAL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/resources/openal32.dll")
    if(EXISTS "${OPENAL_DLL}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OPENAL_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/openal32.dll"
            COMMENT "Deploying openal32.dll"
        )
    endif()
endif()
