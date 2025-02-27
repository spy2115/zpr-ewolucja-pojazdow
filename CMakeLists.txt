cmake_minimum_required(VERSION 3.10)
project(GeneticCars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(${PROJECT_NAME}
./main.cc
./include/Box.h
./src/Box.cc
./include/Triangle.h
./src/Triangle.cc
./include/Circle.h
./src/Circle.cc
./include/Car.h
./src/Car.cc
./include/Render.h
./src/Render.cc
./include/Globals.h
./src/Globals.cc
./include/GA.h
./src/GA.cc
./include/Button.h
./src/Button.cc
./include/TextField.h
./src/TextField.cc
./include/ScrollableList.h
./src/ScrollableList.cc
./include/FileOperations.h
./src/FileOperations.cc
./include/Init.h
./src/Init.cc
./include/Utils.h
./src/Utils.cc
./include/EventHandlers.h
./src/EventHandlers.cc
)

add_executable(tests
./tests/tests.cc
./include/Box.h
./src/Box.cc
./include/Triangle.h
./src/Triangle.cc
./include/Circle.h
./src/Circle.cc
./include/Car.h
./src/Car.cc
./include/Render.h
./src/Render.cc
./include/Globals.h
./src/Globals.cc
./include/GA.h
./src/GA.cc
./include/Button.h
./src/Button.cc
./include/TextField.h
./src/TextField.cc
./include/ScrollableList.h
./src/ScrollableList.cc
./include/FileOperations.h
./src/FileOperations.cc
./include/Init.h
./src/Init.cc
./include/Utils.h
./src/Utils.cc
./include/EventHandlers.h
./src/EventHandlers.cc
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system box2d)
target_link_libraries(tests Boost::unit_test_framework sfml-graphics sfml-window sfml-system box2d)