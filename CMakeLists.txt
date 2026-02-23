cmake_minimum_required(VERSION 3.16)

# Ensure compatibility with SFML's old CMake requirements
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(Snake LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SFML 2.5.1 uses std::auto_ptr which was removed in C++17.
# We need to re-enable it for MSVC.
if(MSVC)
    add_compile_definitions(_HAS_AUTO_PTR_ETC=1)
endif()

# Set a single output directory for all configs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SFML Configuration via FetchContent
include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1)

FetchContent_MakeAvailable(SFML)

# Define source files
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

# Create executable
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

# Configure include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Snake
    ${CMAKE_CURRENT_SOURCE_DIR}/Snake/include
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics
    sfml-audio
    sfml-network
)

# Resource Management
# Since assets for this project are mixed in with the source code folder,
# we copy them individually by extension to the output directory.
file(GLOB ASSETS 
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.ogg"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.ttf"
    "${CMAKE_CURRENT_SOURCE_DIR}/Snake/*.txt"
)

# Copy each asset to the bin directory
foreach(ASSET_PATH ${ASSETS})
    get_filename_component(ASSET_NAME ${ASSET_PATH} NAME)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ASSET_PATH}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${ASSET_NAME}"
        COMMENT "Copying ${ASSET_NAME} to output directory"
    )
endforeach()

# Special handling for openal32.dll on Windows if it exists in Snake/
if(WIN32)
    set(OPENAL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/Snake/openal32.dll")
    if(EXISTS "${OPENAL_DLL}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OPENAL_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/openal32.dll"
            COMMENT "Copying openal32.dll to output directory"
        )
    endif()
endif()
