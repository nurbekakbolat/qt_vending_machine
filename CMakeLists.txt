cmake_minimum_required(VERSION 3.5)
project(water_vending)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Qt5 REQUIRED Qt5Core Qt5Widgets Qt5StateMachine)

include_directories(${Qt5_INCLUDE_DIRS})
link_directories(${Qt5_LIBRARY_DIRS})
add_definitions(${Qt5_CFLAGS_OTHER})

add_executable(water_vending
    main.cpp
    MainWindow.cpp
    BottleWidget.cpp
    VendingFSM.cpp
)

target_link_libraries(water_vending
    ${Qt5_LIBRARIES}
)
