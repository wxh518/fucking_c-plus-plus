cmake_minimum_required(VERSION 3.31)

project(QtC++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Qt6_DIR "D:/Qt/6.9.1/msvc2022_64/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(MyQtApp
    main.cpp
    shared_ptr.cpp
)

target_link_libraries(MyQtApp PRIVATE
    Qt6::Core
    Qt6::Widgets
)