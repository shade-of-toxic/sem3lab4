#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"
#include <fstream>
#include <functional>
#include <iostream>

void pr_exit(Table& tb) { exit(0); }
void add_Edition(Table& tb)
{
  long code;
  std::cin >> code;
  std::cin.get();
  std::string title, author;
  std::getline(std::cin, title, ';');
  std::getline(std::cin, author, ';');
  long year;
  std::cin >> year;
  std::cin.get();
  std::string publisher;
  std::getline(std::cin, publisher, ';');
  size_t numberOfCopies;
  std::cin >> numberOfCopies;
  std::cin.get();
  std::string editionType;
  std::getline(std::cin, editionType, ';');
  if (editionType == ETypeStrings[Undefined])
  {
    tb << KeyVal(code,
                 BookEdition{title, author, year, publisher, numberOfCopies});
  }
  else if (editionType == ETypeStrings[Learning])
  {
    std::string cource;
    std::getline(std::cin, cource, ';');
    size_t ngroups;
    std::cin >> ngroups;
    std::cin.get();
    long groups[8];
    for (auto i = 0ul; i < ngroups; i++)
    {
      std::cin >> groups[i];
      std::cin.get();
    }
    tb << KeyVal(code,
                 LearningEdition{title, author, year, publisher, numberOfCopies,
                                 cource, groups, ngroups});
  }
  else if (editionType == ETypeStrings[Scientific])
  {
    std::string cources[3];
    size_t ncources;
    std::cin >> ncources;
    std::cin.get();
    for (auto i = 0ul; i < ncources; i++)
      std::getline(std::cin, cources[i], ';');
    tb << KeyVal(code, ScientificEdition{title, author, year, publisher,
                                         numberOfCopies, cources, ncources});
  }
  else if (editionType == ETypeStrings[Fiction])
  {
    std::string subject;
    std::getline(std::cin, subject, ';');
    tb << KeyVal(code, FictionEdition{title, author, year, publisher,
                                      numberOfCopies, subject});
  }
  else
  {
    std::cout << "Edition type error!\n";
    return;
  }
  std::cout << *tb[code] << std::endl;
}
void receive_Book(Table& tb)
{
  long code;
  std::cin >> code;
  auto& el = tb[code];
  if (el)
    ++(*el);
  else
  {
    std::cout << "Edition not found!\n";
    return;
  }
  std::cout << *el << std::endl;
}
void borrow_Book(Table& tb)
{
  long code;
  std::cin >> code;
  auto& el = tb[code];
  if (el)
    --(*el);
  else
  {
    std::cout << "Edition not found!\n";
    return;
  }
  std::cout << *el << std::endl;
}
void print_Table(Table& tb) { std::cout << tb << std::endl; }
void remove_Edition(Table& tb)
{
  long code;
  std::cin >> code;
  try
  {
    std::cout << "Removed: " << tb.erase(code) << std::endl;
  }
  catch (std::out_of_range& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
void save_tofile(Table& tb)
{
  std::string filename;
  std::cin >> filename;
  tb.save(filename);
}
void open_fromfile(Table& tb)
{
  std::string filename;
  std::cin >> filename;
  tb.open(filename);
}

std::vector<std::function<void(Table&)>> options = {
    pr_exit,     add_Edition,    receive_Book, borrow_Book,
    print_Table, remove_Edition, save_tofile,  open_fromfile};

static std::string const optstring =
    "\
[1]Exit\n\
[2]Add Edition\n\
[3]Receive Book\n\
[4]Borrow Book\n\
[5]Print Table\n\
[6]Remove Editon from table\n\
[7]Save to file\n\
[8]Load from file\n\
\n";

int main(int argc, char const* argv[])
{
  int ch = 0;
  Table table;
  while (ch != 1)
  {
    std::cout << optstring;
    std::cin >> ch;
    std::cin.get();
    if (ch < 0 || ch > 8)
    {
      std::cout << "Try again!\n";
      continue;
    }
    options[ch - 1](table);
  }
  return 0;
}
