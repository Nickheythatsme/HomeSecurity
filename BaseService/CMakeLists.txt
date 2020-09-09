# Initialize cmake
cmake_minimum_required (VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
project (BaseService)

# Add subdirs
add_subdirectory (src)
add_subdirectory (tests)

# Build main app
add_executable(BaseService main.cpp)

# Link libraries
target_link_libraries (BaseService LINK_PUBLIC Networking)