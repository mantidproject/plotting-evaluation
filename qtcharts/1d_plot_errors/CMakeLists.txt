cmake_minimum_required (VERSION 2.8.11)

project(1d_plot_errors)

# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set (CMAKE_AUTOMOC ON)

# Qt5
set (CMAKE_PREFIX_PATH /opt/qt54)

# Find the QtWidgets library
find_package(Qt5Widgets)
# Find the QtCharts library
find_package(Qt5Charts)

set (_srcs
  src/main.cpp
  src/Workspace.cpp
)

set (_headers
  src/Workspace.h
)

add_executable (1d_plot_errors WIN32 ${_srcs} ${_headers})
set_property(TARGET 1d_plot_errors PROPERTY CXX_STANDARD 11)
set_property(TARGET 1d_plot_errors PROPERTY CXX_STANDARD_REQUIRED ON)

# Use the Widgets & Charts modules
target_link_libraries(1d_plot_errors Qt5::Widgets Qt5::Charts)
