#include <memtailor.h>

#if defined(EXPECT_MEMT_DEBUG) != defined(MEMT_DEBUG)
#error MEMT_DEBUG must agree with the installed library
#endif
static_assert(__cplusplus >= 201703L, "memtailor requires C++17");

int main() {
  memt::Arena arena;
  void* p = arena.alloc(32);
  arena.freeTop(p);
}
