#include "Table.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

constexpr Table::TableItem::TableItem(long acode)
    : code{acode}, book{nullptr}, next{nullptr}
{
}

Table::TableItem::TableItem(long acode, BookEdition const& abook)
    : code{acode}, next{nullptr}
{
  switch (abook.getEditionType())
  {
  case Undefined:
    book = new BookEdition(abook);
    break;
  case Learning:

    book = new LearningEdition(*(LearningEdition const*)&abook);
    break;
  case Scientific:

    book = new ScientificEdition(*(ScientificEdition const*)&abook);
    break;
  case Fiction:

    book = new FictionEdition(*(FictionEdition const*)&abook);
    break;
  }
}

Table::TableItem& Table::TableItem::operator=(Table::TableItem const& other)
{
  delete next;
  delete book;
  code = other.code;
  next = other.next;
  if (other.book)
  {
    switch (other.book->getEditionType())
    {
    case Undefined:
      book = new BookEdition(*other.book);
      break;
    case Learning:

      book = new LearningEdition(*(LearningEdition const*)other.book);
      break;
    case Scientific:

      book = new ScientificEdition(*(ScientificEdition const*)other.book);
      break;
    case Fiction:

      book = new FictionEdition(*(FictionEdition const*)other.book);
      break;
    }
  }
  return *this;
}

Table::TableItem& Table::TableItem::operator=(Table::TableItem&& other)
{
  delete next;
  delete book;
  code       = other.code;
  next       = other.next;
  book       = other.book;
  other.book = nullptr;
  other.next = nullptr;
  return *this;
}

Table::TableItem::TableItem(TableItem&& other)
    : code{other.code}, book{other.book}, next{other.next}
{
  other.book = nullptr;
  other.next = nullptr;
}

Table::TableItem::~TableItem()
{
  delete next;
  delete book;
}

Table::Table() : m_beforeFirst{new Table::TableItem}, m_numberOfEditions{0} {}
Table::Table(std::vector<KeyVal_t> books) : m_numberOfEditions{0}
{
  std::sort(books.begin(), books.end(),
            [](auto& fir, auto& sec) { return fir.first < sec.first; });
  auto prev = (m_beforeFirst = new Table::TableItem);
  for (auto& book : books)
  {
    prev->next = new Table::TableItem{book.first, *book.second};
    prev       = prev->next;
    m_numberOfEditions++;
  }
}

Table::~Table() { delete m_beforeFirst; }

Table& Table::operator<<(Table::TableItem&& item)
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (item.code < prev->next->code)
      break;
    prev = prev->next;
  }
  auto tmp         = prev->next;
  prev->next       = new TableItem{std::move(item)};
  prev->next->next = tmp;
  m_numberOfEditions++;
  return *this;
}

BookEdition*& Table::operator[](long key)
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (key <= prev->next->code)
      break;
    prev = prev->next;
  }
  if (!prev->next || key != prev->next->code)
  {
    auto tmp         = prev->next;
    prev->next       = new TableItem{key};
    prev->next->next = tmp;
    m_numberOfEditions++;
  }

  return prev->next->book;
}
BookEdition Table::erase(long key)
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (key <= prev->next->code)
      break;
    prev = prev->next;
  }
  if (prev->next && key == prev->next->code)
  {
    BookEdition tmp{*prev->next->book};
    auto tmp2        = prev->next->next;
    prev->next->next = nullptr;
    delete prev->next;
    prev->next = tmp2;
    m_numberOfEditions--;
    return tmp;
  }
  throw std::out_of_range("Key error.");
}
std::ostream& operator<<(std::ostream& stream, Table const& table)
{
  auto prev = table.m_beforeFirst;
  for (auto i = 0ul; i < table.size(); i++)
  {
    if (prev->next->book)
      stream << std::setw(5) << prev->next->code << ":" << *prev->next->book;
    prev = prev->next;
  }
  return stream;
}

std::ostream& Table::output(std::ostream& stream) const
{
  auto prev = m_beforeFirst;
  for (auto i = 0ul; i < size(); i++)
  {
    if (prev->next->book)
    {
      stream << prev->next->code << ";";
      prev->next->book->output(stream) << "\n";
    }
    prev = prev->next;
  }
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
  delete m_beforeFirst->next;
  m_beforeFirst->next = nullptr;
  m_numberOfEditions  = 0;
  while (!file.eof())
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
      *this << KeyVal(
          code, BookEdition{title, author, year, publisher, numberOfCopies});
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
      *this << KeyVal(code,
                      LearningEdition{title, author, year, publisher,
                                      numberOfCopies, cource, groups, ngroups});
    }
    else if (editionType == ETypeStrings[Scientific])
    {
      std::string cources[3];
      size_t ncources;
      file >> ncources;
      file.get();
      for (auto i = 0ul; i < ncources; i++)
        std::getline(file, cources[i], ';');
      *this << KeyVal(code,
                      ScientificEdition{title, author, year, publisher,
                                      numberOfCopies, cources, ncources});
    }
    else if (editionType == ETypeStrings[Fiction])
    {
      std::string subject;
      std::getline(file, subject, ';');
      *this << KeyVal(code, FictionEdition{title, author, year, publisher,
                                           numberOfCopies, subject});
    }
    else
      continue;
  }
  file.close();
}