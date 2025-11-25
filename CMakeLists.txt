cmake_minimum_required(VERSION 3.16)
project(cpp-script-runner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

add_compile_options(/W4 /WX)

find_package(Qt5
    COMPONENTS
        Core
        Gui
        Widgets        
        Network
)

set(PROJECT_SOURCES
    src/main.cpp
    src/canvas.h
    src/canvas.cpp
    src/ui.h
    src/ui.cpp
    src/script_runner.h
    src/script_runner.cpp
    resources/resources.rc
    resources/resources.qrc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Release")

    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
endif()

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
)

target_compile_options(cpp-script-runner PRIVATE /wd4127)