#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include <vector>
class BookEditionWrapper;
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
    TableItem(long acode, BookEdition*&& abook);
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
  BookEditionWrapper operator[](long key);
  BookEdition erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  std::ostream& output(std::ostream& stream) const;
  void save(std::string file) const;
  void open(std::string file);
  template <typename Edition_t>
  friend Table::TableItem KeyVal(long key, Edition_t const& val);
  friend class BookEditionWrapper;
};

template <typename Edition_t>
Table::TableItem KeyVal(long key, Edition_t const& val)
{
  return Table::TableItem{key, val};
}

template <typename _Ty>
concept not_reference = !std::is_reference_v<_Ty>;

template <typename _Ty>
concept edition = std::is_base_of_v<BookEdition, _Ty>;

class BookEditionWrapper
{
private:
  Table::TableItem& m_item;

public:
  inline BookEditionWrapper(Table::TableItem& item) : m_item{item} {};
  inline BookEdition& operator*() { return *(m_item.book); }
  inline BookEdition* operator&() { return m_item.book; };
#if 1
  template <not_reference Edition_t>
  BookEditionWrapper& operator=(Edition_t const& item)
  {
    auto tmp    = m_item.next;
    m_item.next = 0;
    m_item      = Table::TableItem{m_item.code, item};
    m_item.next = tmp;
    return *this;
  }
  template <not_reference Edition_t>
  BookEditionWrapper& operator=(Edition_t&& item)
  {
    auto tmp    = m_item.next;
    m_item.next = 0;
    m_item      = Table::TableItem{m_item.code, std::move(item)};
    m_item.next = tmp;
    return *this;
  }
#else
  // retrieved pointer is always an rvalue.
  BookEditionWrapper& operator=(BookEdition*&& item)
  {
    auto tmp    = m_item.next;
    m_item.next = 0;
    m_item      = Table::TableItem{m_item.code, std::move(item)};
    m_item.next = tmp;
    return *this;
  }
  // hense this overloading never gets called
  BookEditionWrapper& operator=(BookEdition* const& item)
  {
    auto tmp    = m_item.next;
    m_item.next = 0;
    m_item      = Table::TableItem{m_item.code, *item};
    m_item.next = tmp;
    return *this;
  }
#endif
  template <edition Edition>
  operator Edition&()
  {
    return *(Edition*)m_item.book;
  }
  // operator BookEdition&() { return *m_item.book; }
  // operator FictionEdition&() { return *(FictionEdition*)m_item.book; }
  // operator ScientificEdition&() { return *(ScientificEdition*)m_item.book; }
  // operator LearningEdition&() { return *(LearningEdition*)m_item.book; }
  template <edition Edition>
  operator Edition*()
  {
    return (Edition*)m_item.book;
  }
  // operator BookEdition*() { return m_item.book; }
  // operator FictionEdition*() { return (FictionEdition*)m_item.book; }
  // operator ScientificEdition*() { return (ScientificEdition*)m_item.book; }
  // operator LearningEdition*() { return (LearningEdition*)m_item.book; }

  inline BookEdition* operator->() { return m_item.book; }
};

#endif // TABLE_HPP
