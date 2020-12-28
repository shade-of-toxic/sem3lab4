#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "List.hpp"

int main(int argc, char const* argv[])
{
  poly_list<BookEdition> list;
  list.emplace_back(BookEdition{"123", "321", 1, "pub", 4, 12});
  list.emplace_back(BookEdition{"1234", "321", 1, "pub", 5, 4});
  list.emplace_back(FictionEdition{"1234", "321", 1, "pub", 5, 15, "subject"});
  for (auto item : list)
  {
    std::cout << *item;
  }

  // std::cout << *list[0] << *list[1] << *list[2];
  list.pop(0);
  for (auto item : list)
  {
    std::cout << *item;
  }
  list.pop(0);
  // std::cout << list[0];
  std::cout << *list[0] << ((FictionEdition*)list[0])->getSubject();
  return 0;
}
