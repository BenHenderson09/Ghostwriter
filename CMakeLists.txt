project(ghostwriter)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup third party libs
set(nlohmann_json_DIR deps/nlohmann_json/lib/cmake/nlohmann_json)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(CURL_DIR deps/CURL/lib/cmake/CURL)
find_package(CURL 7.4.0 REQUIRED)

# Setup header files
set(HEADER_FILES
    src/CLIArgumentHolder/CLIArgumentHolder.hpp
    src/paraphraseText/paraphraseText.hpp
    src/util/findSynonymsOfWord/findSynonymsOfWord.hpp
    src/writeOutputText/writeOutputText.hpp
    config/FlagConfig.hpp
    src/util/JSONObjectHasKey/JSONObjectHasKey.hpp
    src/util/readFile/readFile.hpp)

# Setup source files
set(SOURCE_FILES 
    src/ghostwriter.cpp 
    src/CLIArgumentHolder/CLIArgumentHolder.cpp
    src/util/findSynonymsOfWord/findSynonymsOfWord.cpp
    src/paraphraseText/paraphraseText.cpp
    src/writeOutputText/writeOutputText.cpp
    src/util/JSONObjectHasKey/JSONObjectHasKey.cpp
    src/util/readFile/readFile.cpp)

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

# Tests
add_subdirectory(tests)
