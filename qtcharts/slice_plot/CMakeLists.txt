cmake_minimum_required (VERSION 2.8.11)

project(slice_plot)

# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set (CMAKE_AUTOMOC ON)

# Qt5
set (CMAKE_PREFIX_PATH /opt/Qt/qt57/5.7/gcc_64)

# Find the QtWidgets library
find_package(Qt5Widgets)
# Find the QtDatavisualization library
find_package(Qt5DataVisualization)

set (_srcs
  src/main.cpp
)

set (_headers
)

add_executable (slice_plot WIN32 ${_srcs} ${_headers})
set_property(TARGET slice_plot PROPERTY CXX_STANDARD 11)
set_property(TARGET slice_plot PROPERTY CXX_STANDARD_REQUIRED ON)

# Use the Widgets & Charts modules
target_link_libraries(slice_plot Qt5::Widgets Qt5::DataVisualization)
