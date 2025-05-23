# Note: also update version in CMakeLists.txt and src/memtailor.cpp
dnl AC_INIT sets up autoconf and must be first macro.
AC_INIT([memtailor], [1.0]) # package, version, bug-report-email

# set up information about directories
AC_CONFIG_MACRO_DIR([build/autotools/m4]) # directory of extra autoconf macroes
AC_CONFIG_AUX_DIR([build/autotools]) # directory for auxiliary build tools (install-sh etc)

# check that source directory is correct
dnl  if autoconf is told the source code is in a directory that does not
dnl  contain this file then it knows that the directory is wrong.
AC_CONFIG_SRCDIR([src/memtailor.h])

AM_PROG_AR

dnl ----- The gtest dependency

AC_ARG_WITH([gtest],
    [AS_HELP_STRING([--with-gtest],
        [use gtest, which is required for running the unit tests
         with make check [default=yes].])],,
    [with_gtest=yes])

AC_DEFUN([NO_GTEST_ERROR],
    [AC_MSG_ERROR([gtest not found; try again using --without-gtest])])

AS_IF([test "x$with_gtest" != "xno"],
     [AC_LANG([C++])
      AC_CHECK_HEADER([gtest/gtest.h],
         [AC_MSG_CHECKING([for library containing testing::InitGoogleTest])
          SAVELIBS=$LIBS
          LIBS="$LIBS -lgtest -pthread"
          AC_LINK_IFELSE(
              [AC_LANG_PROGRAM([
                  #include <gtest/gtest.h>
                  ], [
                  testing::InitGoogleTest()])],
              [AC_MSG_RESULT([-lgtest])],
              [AC_MSG_RESULT([no])
               NO_GTEST_ERROR])
          LIBS=$SAVELIBS],
         [NO_GTEST_ERROR])])

AM_CONDITIONAL([with_gtest], [test "x$with_gtest" != "xno"])

# Enable optional maintainer mode (off by default)
dnl AM_MAINTAINER_MODE turns off automatic reconstruction of the build
dnl files if the source build files have changed. A developer will want
dnl those automatic reconstructions to happen so that changes to the
dnl build system are actually carried out. However, a user might not
dnl have the tools required to reconfigure and the need for
dnl reconstruction might be spurious if the last-modified date is set
dnl incorrectly on the build files.
dnl
dnl Passing the option [enable] to AM_MAINTAINER_MODE makes the
dnl non-reconstruction feature available, but only when turned on by
dnl passing the option –disable-maintainer-mode. This option is
dnl apparently useful to some package distributors.
AM_MAINTAINER_MODE([enable])

# Set up Automake
dnl foreign: do not create the GNU-specific file COPYING and do not complain
dnl   that GNU-specific files like NEWS, README, AUTHORS and ChangeLog are
dnl   missing.
dnl -Wall: set Automake to emit all warnings it can. Is NOT RELATED to setting
dnl   warnings for other tools. For example, it wil not make the compiler
dnl   get a -Wall option.
dnl subdir-objects: Put object files in a directory structure based on
dnl   the directory structure of the source files. This way, two source
dnl   files with the same name in different directories do not conflict.
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall])

# if --enable-silent-rules is passed to ./configure or if V=0 is passed
# to make, then the compilation output will be much less verbose making
# it possible to spot warnings and errors as they go by.
AM_SILENT_RULES()

# Set up the $(LN_S) macro, which creates symbolic links
AC_PROG_LN_S

# set output variable INSTALL to the name of a BSD-compatible install program.
# Requires install-sh to be present as a fallback, even on systems where
# the fallback is not used.
AC_PROG_INSTALL

# Locate the C++ compiler.
AC_PROG_CXX

# Set up LibTool
LT_INIT([disable-shared])

dnl Set the version for the library -- this concerns compatibility of the
dnl source and binary interface of the library and is not the same as the
dnl version of the project.
AC_SUBST([MEMTAILOR_SO_VERSION], [0:0:0])

dnl Set up AC_OUTPUT to create each file by copying an input file
dnl while substituting the output variable values.
AC_CONFIG_FILES([Makefile
  build/autotools/memtailor.pc:build/autotools/memtailor.pc.in])

dnl Macro that is required to be at the end of any Autoconf script.
dnl Creates config.status and launches it.
AC_OUTPUT
