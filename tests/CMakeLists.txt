# Setup catch
set(Catch2_DIR ../deps/Catch2/lib/cmake/Catch2)
find_package(Catch2 REQUIRED)

# Setup test files
set(TEST_FILES 
    tests.cpp
    CLIArgumentHolderTests/CLIArgumentHolderTests.cpp
    paraphraseTextTests/paraphraseTextTests.cpp
    writeOutputTextTests/writeOutputTextTests.cpp
    util/createDummyCLIArgHolder/createDummyCLIArgHolder.cpp)

# Setup source files
set(SOURCE_FILES_FOR_TESTING ${SOURCE_FILES})
list(REMOVE_ITEM SOURCE_FILES_FOR_TESTING "src/ghostwriter.cpp")
list(TRANSFORM SOURCE_FILES_FOR_TESTING PREPEND ../)

# Setup header files
set(HEADER_FILES_FOR_TESTING ${HEADER_FILES})
list(TRANSFORM HEADER_FILES_FOR_TESTING PREPEND ../)
list(APPEND HEADER_FILES_FOR_TESTING 
        util/createDummyCLIArgHolder/createDummyCLIArgHolder.hpp)

# Create executable "tests"
add_executable(tests ${TEST_FILES} ${SOURCE_FILES_FOR_TESTING} ${HEADER_FILES_FOR_TESTING})
target_link_libraries(tests PRIVATE Catch2::Catch2)

# Threading
target_link_libraries(tests PRIVATE Threads::Threads)

# Link libraries
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(tests PRIVATE curl)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(tests)