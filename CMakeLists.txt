cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(memtailor VERSION 1.4 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

find_package(Threads REQUIRED QUIET)

add_compile_options(
  -DPACKAGE_NAME="${PROJECT_NAME}"
  -DPACKAGE_TARNAME="${PROJECT_NAME}"
  -DPACKAGE_VERSION="${PROJECT_VERSION}"
  -DPACKAGE_STRING="${PROJECT_NAME} ${PROJECT_VERSION}"
  -DPACKAGE_BUGREPORT=""
  -DPACKAGE_URL=""
  -DPACKAGE="${PROJECT_NAME}"
  -Wall -Wextra
  )

add_subdirectory(src)

# Match the ABI version used by the Autotools build (libtool 0:4:0).
set_target_properties(memtailor PROPERTIES
  VERSION 0.0.4 SOVERSION 0 PUBLIC_HEADER src/memtailor.h)

install(TARGETS memtailor EXPORT memtailorTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY src/memtailor
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h")
install(FILES README.md license.txt DESTINATION ${CMAKE_INSTALL_DOCDIR})

set(memtailor_cmakedir "${CMAKE_INSTALL_LIBDIR}/cmake/memtailor")
configure_package_config_file(cmake/memtailorConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/memtailorConfig.cmake.in"
  INSTALL_DESTINATION "${memtailor_cmakedir}")
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/memtailorConfig.cmake"
  INPUT "${CMAKE_CURRENT_BINARY_DIR}/memtailorConfig.cmake.in")
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/memtailorConfigVersion.cmake"
  VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion)
install(EXPORT memtailorTargets NAMESPACE memtailor::
  DESTINATION "${memtailor_cmakedir}")
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/memtailorConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/memtailorConfigVersion.cmake"
  DESTINATION "${memtailor_cmakedir}")

# Keep pkg-config consumers supported, including the ABI-affecting debug flag.
configure_file(cmake/memtailor.pc.in memtailor.pc.in @ONLY)
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/memtailor.pc"
  INPUT "${CMAKE_CURRENT_BINARY_DIR}/memtailor.pc.in")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/memtailor.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
