#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"
#include <fstream>

using namespace std::string_literals;

int main(int argc, char const* argv[])
{
  std::string b;
  std::cin >> b;

  BookEdition a{b, ""s, 1l, ""s, 2ul};
  b = "1234";
  FictionEdition c{"1214", "title", 1299, "pub", 12, "New Year"};
  ScientificEdition d{"someauth", "sometitle", -100, "somepbl", 9999};
  d--;
  std::cout << a << c << d;

  d << "cource 1"
    << "cource 2"
    << "cource 3";
  std::cout << d.getCourceTitlesAsString();
  std::vector<Table::KeyVal_t> vec{{2, &a}, {-3, &c}, {5, &d}};
  Table tab{vec};
  for (auto i : vec)
    std::cout << i.first << " "; // copy check
  tab << KeyVal(-5, d);
  tab << KeyVal(1, c);
  tab << KeyVal(6, a);
  std::cout << *tab[6];
  // pretty much the same thing as make_edition
  tab[7] = new ScientificEdition{"someauth77", "sometitle777", -100,
                                 "somepbl77", 77};
  // even though make_edition allocates on the heap inside we won't lose pointer
  // bcause now Table object owns it. it will care about memory freeing for us
  // but still there is a problem when you are trying to replace existing pointer
  // so firstly we need to deallocate memory pointed to by previous pointer
  if(tab[7]) {
    delete tab[7];
  // or do it by erase()
    // tab.erase(7);
  }
  tab[7] = make_edition<ScientificEdition>("someauth77", "sometitle777", -100l,
                                           "somepbl77", 77ul);


  tab.save("table.csv");
  tab.open("table.csv");

  std::cout << std::endl << std::endl << tab;
  return 0;
}
