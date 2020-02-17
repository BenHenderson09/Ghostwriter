project(ghostwriter)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup third party libs
set(nlohmann_json_DIR lib/json/lib/cmake/nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(CURL_DIR lib/curl/lib/cmake/CURL)
find_package(CURL 7.4.0 REQUIRED)

# Setup header files
set(HEADER_FILES
    src/CLIArgumentParser/CLIArgumentParser.hpp
    src/TextParaphraser/TextParaphraser.hpp
    src/SynonymFinder/SynonymFinder.hpp
    src/OutputWriter/OutputWriter.hpp
    src/util/JSONUtils/ObjectHasKey.hpp
    src/config/FlagConfig.hpp)

# Setup source files
set(SOURCE_FILES 
    src/ghostwriter.cpp 
    src/CLIArgumentParser/CLIArgumentParser.cpp
    src/SynonymFinder/SynonymFinder.cpp
    src/TextParaphraser/TextParaphraser.cpp
    src/OutputWriter/OutputWriter.cpp
    src/util/JSONUtils/ObjectHasKey.cpp)

# Create executable "ghostwriter"
add_executable(ghostwriter ${SOURCE_FILES} ${HEADER_FILES})

# Threading
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ghostwriter PRIVATE Threads::Threads)

# Link libraries
target_link_libraries(ghostwriter PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(ghostwriter PRIVATE curl)

# Install config
install(TARGETS ghostwriter DESTINATION bin)