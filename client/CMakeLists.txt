cmake_minimum_required(VERSION 3.16)

project(client LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WIN32_EXECUTABLE ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

set(SOURCES
  main.cpp
  src/client.cpp
)

set(HEADERS
  include/client.h
)

add_executable(client ${SOURCES} ${HEADERS}
  include/systemInfo.h
  src/systemInfo.cpp)

target_link_libraries(client Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(client Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
