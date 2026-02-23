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
    Snake/Debug_Window.cpp
    Snake/Game.cpp
    Snake/Game_Over_State.cpp
    Snake/main.cpp
    Snake/Menu_State.cpp
    Snake/Options_State.cpp
    Snake/Pause_State.cpp
    Snake/Play_State.cpp
    Snake/Snake.cpp
    Snake/Snake_Controller.cpp
    Snake/Snake_Rule_Monitor.cpp
    Snake/Static_Graphic.cpp
)

set(HEADERS
    Snake/Debug_Window.hpp
    Snake/Game.h
    Snake/Game_Over_State.hpp
    Snake/ICommand.hpp
    Snake/IContext.hpp
    Snake/IReceiver.hpp
    Snake/IState.hpp
    Snake/Menu_State.hpp
    Snake/Options_State.hpp
    Snake/Pause_State.hpp
    Snake/Play_State.hpp
    Snake/Snake.h
    Snake/Snake_Controller.h
    Snake/Snake_Rule_Monitor.h
    Snake/Static_Graphic.h
)

# Executable target
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

# Include and linking
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Snake
    ${CMAKE_CURRENT_SOURCE_DIR}/Snake/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics
    sfml-audio
    sfml-network
)

# Resource deployment
file(GLOB ASSETS 
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.ogg"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.ttf"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.txt"
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
    set(OPENAL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/Snake/openal32.dll")
    if(EXISTS "${OPENAL_DLL}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OPENAL_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/openal32.dll"
            COMMENT "Deploying openal32.dll"
        )
    endif()
endif()
