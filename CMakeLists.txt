cmake_minimum_required(VERSION 3.5)

project(3DV2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -ggdb  -fsanitize=address")
# -pg (for debug)



find_package(QT NAMES Qt6 Qt5 COMPONENTS Core OpenGLWidgets OpenGL Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core OpenGLWidgets OpenGL Gui REQUIRED)

include_directories(./lib/QtGifImage/src/gifimage/)
include_directories(./lib/MatrixLib/src/)

cmake_host_system_information(RESULT PRETTY_NAME QUERY OS_NAME)
message(STATUS "${PRETTY_NAME}")

if (${PRETTY_NAME} STREQUAL "Linux")
    add_compile_definitions(__LINUX__)
else()
    add_compile_definitions(__MACOS__)
endif()

file(GLOB_RECURSE QTPROPERTY_BROWSER_SOURCES
./lib/QtGifImage/src/gifimage/qtgifimage.pri)


set(PROJECT_SOURCES
        srcs/main.cc
        srcs/View/mainwindow.cc
        srcs/View/mywidgetopengl.cc

        srcs/Controller/controller.cc

        srcs/Model/model.cpp
        srcs/Model/modelviewer.cc

        srcs/Model/facademodel.cc

        srcs/Model/datamanager.cc
        srcs/Model/imagecapture.cc
        ${QTPROPERTY_BROWSER_SOURCES}
)

set(PROJECT_HEADERS
        includes/View/mainwindow.hpp
        includes/View/iwidgetopenglobserver.hpp
        includes/View/mywidgetopengl.hpp

        includes/Controller/icontrollerinterface.hpp
        includes/Controller/controller.hpp

        includes/Model/customtypes.hpp
        includes/Model/model.hpp
        includes/Model/modelviewer.hpp
        includes/Model/ifacademodel.hpp
        includes/Model/facademodel.hpp

        includes/Model/datamanager.hpp
        includes/Model/imagecapture.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DV2
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
else()
    add_executable(3DV2
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        )
endif()

add_subdirectory(lib)

target_include_directories(3DV2
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/includes
  ${CMAKE_CURRENT_LIST_DIR}/objects
  ${CMAKE_CURRENT_LIST_DIR}/libBin
)

target_link_libraries(3DV2
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::OpenGLWidgets
  Qt${QT_VERSION_MAJOR}::OpenGL
  GifImages
  MatrixLib
)
