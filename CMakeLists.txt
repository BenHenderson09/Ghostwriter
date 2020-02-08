project(ghostwriter)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup third party libs
set(nlohmann_json_DIR lib/json/lib/cmake/nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Setup header files
set(HEADER_FILES
    src/CLIArgumentParser/CLIArgumentParser.hpp
    src/config/FlagConfig.hpp)

# Setup source files
set(SOURCE_FILES 
    src/ghostwriter.cpp 
    src/CLIArgumentParser/CLIArgumentParser.cpp)

# Create executable "ghostwriter"
add_executable(ghostwriter ${SOURCE_FILES} ${HEADER_FILES})

# Link libraries
target_link_libraries(ghostwriter PRIVATE nlohmann_json::nlohmann_json)