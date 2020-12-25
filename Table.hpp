#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include <vector>

class Table
{
private:
  struct TableItem
  {
    long code;
    BookEdition* book;
    TableItem* next;
    constexpr TableItem(long acode = 0);
    TableItem(long acode, BookEdition const& abook);
    TableItem(TableItem const&) = delete;
    TableItem(TableItem&&);
    TableItem& operator=(TableItem const& other);
    TableItem& operator=(TableItem&& other);
    ~TableItem();
  };
  TableItem* m_beforeFirst;
  size_t m_numberOfEditions;

public:
  using KeyVal_t = std::pair<long, BookEdition*>;
  Table();
  Table(std::vector<KeyVal_t> books);
  ~Table();
  inline size_t size() const { return m_numberOfEditions; };
  Table& operator<<(TableItem&& keyval);
  BookEdition*& operator[](long key);
  BookEdition erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  std::ostream& output(std::ostream& stream) const;
  void save(std::string file) const;
  void open(std::string file);
  template <typename Edition_t>
  friend Table::TableItem KeyVal(long key, Edition_t const& val);
};

template <typename Edition_t>
Table::TableItem KeyVal(long key, Edition_t const& val)
{
  return Table::TableItem{key, val};
}

template <typename Edition_t, typename... Initializers>
Edition_t* make_edition(Initializers... inits)
{
  return new Edition_t{inits...};
}

#endif // TABLE_HPP
