cmake_minimum_required(VERSION 3.15)

project(tst_calculator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test)

set(OUT_NAME tst_calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror  -fprofile-arcs -ftest-coverage ")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(HEADERS
    includes/tst_model_calculator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/modelcalculator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/polishnotation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/validatetext.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/imodelcredit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/modelcredit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/imodeldeposit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/modeldeposit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../includes/custom_types.hpp
)

set(SOURCES
    srcs/main.cc
    srcs/tst_model_calculator.cc
    srcs/tst_model_credit.cc
    srcs/tst_model_deposit.cc
    srcs/tst_polishnotation.cc
    srcs/tst_validatortext.cc
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/modelcalculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/polishnotation.cc
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/validatetext.cc
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/modelcredit.cc
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/modeldeposit.cc
)

add_executable(${OUT_NAME} ${SOURCES} ${HEADERS})

enable_testing()

include_directories(
    ./include
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/
)

target_include_directories(${OUT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/includes
    ${CMAKE_CURRENT_LIST_DIR}/../includes/Model/
    ${CMAKE_CURRENT_LIST_DIR}/../srcs/Model/
)


target_link_libraries(${OUT_NAME}
    PUBLIC
    ${GTEST_LIBRARIES}
    Threads::Threads
    Qt${QT_VERSION_MAJOR}::Widgets
    gcov
)

add_custom_target(coverage
  COMMAND lcov --capture --directory ./CMakeFiles/tst_calculator.dir/home/* --output-file coverage.info
  COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
  COMMAND lcov --list coverage.info
)

add_custom_target(coverage_report
    COMMAND genhtml coverage.info --output-directory coverage_report
)

add_custom_target(make_coverage
    COMMAND ${CMAKE_COMMAND} --build . --target ${OUT_NAME}
    COMMAND ${CMAKE_COMMAND} --build . --target coverage
    COMMAND ${CMAKE_COMMAND} --build . --target coverage_report
)

add_test(NAME ${OUT_NAME} COMMAND ${OUT_NAME})

set_tests_properties(${OUT_NAME} PROPERTIES ENVIRONMENT "QT_PLUGIN_PATH=${QT_PLUGINS_DIR}")
