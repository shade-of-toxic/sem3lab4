#ifndef MEMLEAK_TEST_BASIC_HPP
#define MEMLEAK_TEST_BASIC_HPP

namespace std
{
#include <malloc.h>
#include <stdlib.h>
} // namespace std
using std::size_t;
#include <iostream>

// unavaliable to other translation units
static long mem_counter = 0;

void* operator new(size_t size)
{

  void* p          = std::malloc(size);
  long size_actual = static_cast<long>(std::malloc_usable_size(p));
  mem_counter += size_actual;
#if _VERBOSE == 1
  std::cout << "Call to new operator with size(requested): " << size
            << ", size(actual): " << size_actual << "\n";
#endif
  return p;
}

void operator delete(void* p)
{
  long size = static_cast<long>(std::malloc_usable_size(p));
  mem_counter -= size;
#if _VERBOSE == 1
  std::cout << "Call to delete operator with size(actual): " << size << "\n";
#endif
  std::free(p);
}

long get_used_mem_size() { return mem_counter; }

#endif // MEMLEAK_TEST_BASIC_HPP
