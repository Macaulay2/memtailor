memtailor
=========

Memtailor is a C++ library of special purpose memory allocators. It
currently offers an arena allocator and a memory pool.

The main motivation to use a memtailor allocator is better and more
predictable performance than you get with new/delete. Sometimes a
memtailor allocator can also be more convenient due to the ability to
free many allocations at one time.

The Memtailor memory pool is useful if you need to do many allocations
of a fixed size. For example a memory pool is well suited to allocate
the nodes in a linked list.

You can think of the Memtailor arena allocator as being similar to
stack allocation. Both kinds of allocation are very fast and require
you to allocate/deallocate memory in last-in-first-out order. Arena
allocation has the further benefits that it stays within the C++
standard, it will not cause a stack overflow, you can have multiple
arena allocators at the same time and allocation is not tied to a
function invocation.

Requirements
------------

Memtailor requires C++17 or later.

Building and using with CMake
-----------------------------

```sh
cmake -S . -B build-dir -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON
cmake --build build-dir
ctest --test-dir build-dir --output-on-failure
cmake --install build-dir --prefix /your/install/prefix
```

Use `-DBUILD_TESTING=OFF` to omit unit tests and their GoogleTest dependency.
Install directories follow GNUInstallDirs; for example,
`-DCMAKE_INSTALL_LIBDIR=lib64` selects a 64-bit library directory.
The default library type remains static; `BUILD_SHARED_LIBS=ON` selects shared.

Consumers can use the installed package:

```cmake
find_package(memtailor 1.4 CONFIG REQUIRED)
target_link_libraries(my_program PRIVATE memtailor::memtailor)
```

Set `CMAKE_PREFIX_PATH` to the installation prefix if it is outside the normal
system search paths. The exported target carries include directories, C++17,
the Threads dependency, and the ABI-affecting `MEMT_DEBUG` definition when
applicable. The installation also provides `memtailor.pc` for pkg-config users;
configure `CMAKE_INSTALL_PREFIX` to the final prefix when using that file.

Debugging
---------

Defining MEMT_DEBUG turns on memtailor's internal consistency checks. Pass
--enable-debug to configure, or build with cmake and -DCMAKE_BUILD_TYPE=Debug.

Be aware that MEMT_DEBUG adds a member to memt::Arena, so it changes the size
of that class and hence the ABI of the library. It must match between the
library and every translation unit that includes these headers. Mixing the
two compiles and links without complaint, but the two sides then disagree
about the layout of memt::Arena and the result is undefined behavior.

Both builds record the debug setting in the Cflags of memtailor.pc. Use those
Cflags in full: `pkg-config --cflags-only-I` drops the definition, as does any
build system that keeps just the include directories. CMake consumers linking
`memtailor::memtailor` inherit the setting automatically, even when the consumer
and library use different build configurations.

---

The following copyright and license notice applies to all of the files in
memtailor.

Copyright 2013 Bjarke Hammersholt Roune (http://www.broune.com) and Cornell
University.  MemTailor is distributed under the Modified BSD License. See
license.txt.
