cmake_minimum_required (VERSION 2.8.11)

project(change_plot_props)

# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set (CMAKE_AUTOMOC ON)

# Qt5
set (CMAKE_PREFIX_PATH /opt/Qt/qt57/5.7/gcc_64)

# Find the QtWidgets library
find_package(Qt5Widgets)
# Find the QtCharts library
find_package(Qt5Charts)

set (_srcs
  src/main.cpp
  src/Figure.cpp
  src/Workspace.cpp
)

set (_headers
  src/Figure.h
  src/Workspace.h
)

add_executable (change_plot_props WIN32 ${_srcs} ${_headers})
set_property(TARGET change_plot_props PROPERTY CXX_STANDARD 11)
set_property(TARGET change_plot_props PROPERTY CXX_STANDARD_REQUIRED ON)

# Use the Widgets & Charts modules
target_link_libraries(change_plot_props Qt5::Widgets Qt5::Charts)
