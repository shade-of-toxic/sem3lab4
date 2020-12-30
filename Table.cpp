#include "Table.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

BookEdition*& Table::operator[](long key)
{
  auto it = m_list.begin();
  for (; it != m_list.end(); it++)
    if (key <= it->getCode())
      break;
  if (it == m_list.end() || it->getCode() != key)
    m_list.insert(it, BookEdition{key});

  return *it;
}
BookEdition const* Table::at(long key) const
{
  auto it = m_list.begin();
  for (; it != m_list.end(); it++)
    if (key <= it->getCode())
      break;
  if (it == m_list.end() || it->getCode() != key)
    throw std::out_of_range("Key not found!");
  return *it;
}
BookEdition*& Table::at(long key)
{
  auto it = m_list.begin();
  for (; it != m_list.end(); it++)
    if (key <= it->getCode())
      break;
  if (it == m_list.end() || it->getCode() != key)
    throw std::out_of_range("Key not found!");
  return *it;
}
void Table::erase(long key)
{
  for (auto item : m_list)
    if (item->getCode() == key)
    {
      m_list.remove(item);
      return;
    }

  throw std::out_of_range("Key error.");
}
std::ostream& operator<<(std::ostream& stream, Table const& table)
{
  for (auto item : table.m_list)
    stream << *item;
  return stream;
}

std::ostream& Table::output(std::ostream& stream) const
{
  for (auto item : m_list)
    item->output(stream) << "\n";
  return stream;
}

void Table::save(std::string filename) const
{
  std::ofstream file{filename};
  output(file);
  file.close();
}
void Table::open(std::string filename)
{
  std::ifstream file{filename};
  m_list.clear();
  while (!file.eof() && !file.bad())
  {
    long code;
    file >> code;
    file.get();
    std::string title, author;
    std::getline(file, title, ';');
    std::getline(file, author, ';');
    long year;
    file >> year;
    file.get();
    std::string publisher;
    std::getline(file, publisher, ';');
    size_t numberOfCopies;
    file >> numberOfCopies;
    file.get();
    std::string editionType;
    std::getline(file, editionType, ';');
    if (editionType == ETypeStrings[Undefined])
    {
      m_list.emplace_back(
          BookEdition{title, author, year, publisher, numberOfCopies, code});
    }
    else if (editionType == ETypeStrings[Learning])
    {
      std::string cource;
      std::getline(file, cource, ';');
      size_t ngroups;
      file >> ngroups;
      file.get();
      long groups[8];
      for (auto i = 0ul; i < ngroups; i++)
      {
        file >> groups[i];
        file.get();
      }
      m_list.emplace_back(LearningEdition{title, author, year, publisher,
                                          numberOfCopies, code, cource, groups,
                                          ngroups});
    }
    else if (editionType == ETypeStrings[Scientific])
    {
      std::string cources[3];
      size_t ncources;
      file >> ncources;
      file.get();
      for (auto i = 0ul; i < ncources; i++)
        std::getline(file, cources[i], ';');
      m_list.emplace_back(ScientificEdition{title, author, year, publisher,
                                            numberOfCopies, code, cources,
                                            ncources});
    }
    else if (editionType == ETypeStrings[Fiction])
    {
      std::string subject;
      std::getline(file, subject, ';');
      m_list.emplace_back(FictionEdition{title, author, year, publisher,
                                         numberOfCopies, code, subject});
    }
    else
      continue;
  }
  file.close();
}