#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"
#include <fstream>
namespace std
{
#include <malloc.h>
}

using namespace std::string_literals;

// unavaliable to other translation units
static long mem_counter = 0;

void* operator new(size_t size)
{

  void* p          = std::malloc(size);
  long size_actual = static_cast<long>(std::malloc_usable_size(p));
  mem_counter += size_actual;
  std::cout << "Call to new operator with size(requested): " << size
            << ", size(actual): " << size_actual << "\n";
  return p;
}

void operator delete(void* p)
{
  long size = static_cast<long>(std::malloc_usable_size(p));
  mem_counter -= size;
  std::cout << "Call to delete operator with size(actual): " << size << "\n";
  std::free(p);
}

int main1(int argc, char const* argv[])
{
  std::string b = "4321";
  // std::cin >> b;

  BookEdition a{b, ""s, 1l, ""s, 2ul};
  b = "1234";
  FictionEdition c{"1214", "title", 1299, "pub", 12, "New Year"};
  ScientificEdition d{"someauth", "sometitle", -100, "somepbl", 9999};
  d--;
  std::cout << a << c << d << "\n";

  d << "cource 1"
    << "cource 2"
    << "cource 3";
  std::cout << d.getCourceTitlesAsString() << "\n\n";
  std::vector<Table::KeyVal_t> vec{{2, &a}, {-3, &c}, {5, &d}};
  Table tab{vec};
  for (auto i : vec)
    std::cout << i.first << " "; // copy check
  std::cout << "\n\n";
  tab << KeyVal(-5, d);
  tab << KeyVal(1, c);
  tab << KeyVal(6, a);
  std::cout << *tab[6];
  tab[7] =
      ScientificEdition{"someauth77", "sometitle777", -100, "somepbl77", 77};
  tab[7] = std::move(d);
  (*tab[7])++;
  std::cout << "\n\n+++++++\n\n"
            << tab[7]->getNumberOfCopies() << " != " << d.getNumberOfCopies()
            << "\n\n+++++++\n\n"
            << ((FictionEdition&)tab[7]).operator++(0).getNumberOfCopies()
            << " == " << tab[7]->getNumberOfCopies() << "\n\n\n\n";
  /*
  problem solved using concepts and wrapper implemented
  // pretty much the same thing as make_edition
  tab[7] = new ScientificEdition{"someauth77", "sometitle777", -100,
                                 "somepbl77", 77};*/
  // even though make_edition allocates on the heap inside we won't lose
  // pointer bcause now Table object owns it. it will care about memory
  // freeing for us but still there is a problem when you are trying to
  // replace existing pointer so firstly we need to deallocate memory
  // pointed to by previous pointer
  /*if(tab[7]) {
    delete tab[7];
  // or do it by erase()
    // tab.erase(7);
  }
  tab[7] = make_edition<ScientificEdition>("someauth77", "sometitle777",
  -100l, "somepbl77", 77ul);
  */
  // tab[7] = &d;

  tab.save("table.csv");
  tab.open("table.csv");

  std::cout << "\n\n" << tab << "\n\n";
  return 0;
}

int main(int argc, char const* argv[])
{
  main1(argc, argv);
  //auto a = new char[40]; // to test it out
  std::cout << "memory still being used: " << mem_counter << std::endl;
  return 0;
}
