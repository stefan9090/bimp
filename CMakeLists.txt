cmake_minimum_required(VERSION 3.5)

project(imp-beer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC OFF)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH cmake/)
set(CMAKE_PREFIX_PATH C:\\Qt\\6.1.2\\msvc2019_64\\lib\\cmake)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets LinguistTools REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/Logger.cpp src/Logger.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(imp-beer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(imp-beer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(imp-beer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_subdirectory(lib/spdlog)

target_link_libraries(imp-beer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets spdlog)

set_target_properties(imp-beer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(imp-beer)
endif()
