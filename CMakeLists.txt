cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(memtailor VERSION 1.0 LANGUAGES CXX)

find_package(Threads 2.1 REQUIRED QUIET)

add_compile_options(
  -DPACKAGE_NAME="${PROJECT_NAME}"
  -DPACKAGE_TARNAME="${PROJECT_NAME}"
  -DPACKAGE_VERSION="${PROJECT_VERSION}"
  -DPACKAGE_STRING="${PROJECT_NAME} ${PROJECT_VERSION}"
  -DPACKAGE_BUGREPORT=""
  -DPACKAGE_URL=""
  -DPACKAGE="${PROJECT_NAME}"
  )

add_subdirectory(src)

set_target_properties(memtailor PROPERTIES PUBLIC_HEADER src/memtailor.h)

install(TARGETS memtailor LIBRARY DESTINATION lib)
install(DIRECTORY src/memtailor
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
  )
install(FILES README.md license.txt
  DESTINATION licenses/memtailor
  )
