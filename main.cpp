#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"
#include <fstream>


int main(int argc, char const* argv[])
{
  std::string b = "abc";
  // std::cin >> b;

  BookEdition a{b, "", 1l, "", 2ul, 5};
  b = "1234";
  FictionEdition c{"1214", "title", 1299, "pub", 12, 7, "New Year"};
  ScientificEdition d{"someauth", "sometitle", -100, "somepbl", 9999, 10};
  d--;
  std::cout << a << c << d;

  d << "cource 1"
    << "cource 2"
    << "cource 3";
  std::cout << d.getCourceTitlesAsString();
  // std::vector<Table::KeyVal_t> vec{{2, &a}, {-3, &c}, {5, &d}};
  //Table tab{vec};
  Table tab;
  std::cout << "\nd = " << d;
  tab.add(std::move(a));
  tab.add(d);
  tab.add(std::move(c));
  std::cout << '\n' << *tab[14];
  tab[6];
  tab[-4];
  d++; // shows warning due to ignoring the result
  std::cout << "\nd = " << d;
  // for (auto i : vec)
  //   std::cout << i.first << " "; // copy check
  // tab << KeyVal(-5, d);
  // tab << KeyVal(1, c);
  // tab << KeyVal(6, a);
  // std::cout << *tab[6];
  // pretty much the same thing as make_edition
  // tab[7] = new ScientificEdition{"someauth77", "sometitle777", -100,
                                //  "somepbl77", 77};
  // even though make_edition allocates on the heap inside we won't lose pointer
  // bcause now Table object owns it. it will care about memory freeing for us
  // but still there is a problem when you are trying to replace existing pointer
  // so firstly we need to deallocate memory pointed to by previous pointer
  // if(tab[7]) {
  //   delete tab[7];
  // // or do it by erase()
  //   // tab.erase(7);
  // }
  // tab[7] = make_edition<ScientificEdition>("someauth77", "sometitle777", -100l,
                                          //  "somepbl77", 77ul);


  tab.save("table.csv");
  tab.open("table.csv");

  std::cout << std::endl << std::endl << tab;
  return 0;
}
