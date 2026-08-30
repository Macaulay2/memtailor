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

Debugging
---------

Defining MEMT_DEBUG turns on memtailor's internal consistency checks. Pass
--enable-debug to configure, or build with cmake and -DCMAKE_BUILD_TYPE=Debug.

Be aware that MEMT_DEBUG adds a member to memt::Arena, so it changes the size
of that class and hence the ABI of the library. It must match between the
library and every translation unit that includes these headers. Mixing the
two compiles and links without complaint, but the two sides then disagree
about the layout of memt::Arena and the result is undefined behavior.

The autotools build records the setting in the Cflags of memtailor.pc. That
only helps if you use those Cflags in full, as pkg-config --cflags-only-I
drops it, and so does any build system that keeps just the include
directories. The cmake build installs no memtailor.pc at all. So it is
ultimately up to you to keep the library and its users consistent.

---

The following copyright and license notice applies to all of the files in
memtailor.

Copyright 2013 Bjarke Hammersholt Roune (http://www.broune.com) and Cornell
University.  MemTailor is distributed under the Modified BSD License. See
license.txt.
