if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_compile_options(-DMEMT_DEBUG)
endif()

add_library(memtailor STATIC
  memtailor.h
  memtailor.cpp
  memtailor/Arena.cpp
  memtailor/Arena.h
  memtailor/ArenaVector.h
  memtailor/BufferPool.cpp
  memtailor/BufferPool.h
  memtailor/MemoryBlocks.cpp
  memtailor/MemoryBlocks.h
  memtailor/stdinc.h
  )

target_link_libraries(memtailor Threads::Threads)

target_include_directories(memtailor PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  )

include(CTest)
if(BUILD_TESTING)
  add_executable(memtailor-unit-tests
    test/ArenaTest.cpp
    test/BufferPoolTest.cpp
    test/MemoryBlocksTest.cpp
    test/testMain.cpp
    )

  ################################
  # add gtest testing ############
  ################################
  if(NOT GTEST_FOUND)
    find_package(GTest)
  endif()
  include(GoogleTest)
  gtest_discover_tests(memtailor-unit-tests TEST_PREFIX unit-tests:)

  if(GTEST_FOUND)
    target_link_libraries(memtailor-unit-tests memtailor GTest::GTest GTest::Main)
  else()
    include(FetchContent)
    FetchContent_Declare(googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        release-1.11.0
      )
    FetchContent_MakeAvailable(googletest)

    target_link_libraries(memtailor-unit-tests memtailor gtest)
    target_include_directories(memtailor-unit-tests PRIVATE
      ${googletest_SOURCE_DIR}/googletest/include
      ${googletest_SOURCE_DIR}/googletest/src
      ${googletest_SOURCE_DIR}/googletest
      )
  endif()
endif()
