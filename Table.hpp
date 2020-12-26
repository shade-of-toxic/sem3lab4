#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include <vector>

/**
 * @brief Type concept accepts only non-reference types
 * 
 * @tparam _Ty 
 */
template <typename _Ty>
concept not_reference = !std::is_reference_v<_Ty>;

/**
 * @brief Type concept accepts only types derived from BookEdition  
 * 
 * @tparam _Ty 
 */
template <typename _Ty>
concept edition = std::is_base_of_v<BookEdition, _Ty>;

class BookEditionWrapper;
/**
 * @brief Table representation
 *
 */
class Table
{
private:
  /**
   * @brief Table element private structure
   *
   */
  struct TableItem
  {
    long code;
    BookEdition* book;
    TableItem* next;
    constexpr TableItem(long acode = 0);
    TableItem(long acode, BookEdition const& abook);
    TableItem(long acode, BookEdition*&& abook);
    TableItem(TableItem const&) = delete; // no need to copy
    TableItem(TableItem&&);
    TableItem& operator=(TableItem const& other);
    TableItem& operator=(TableItem&& other);
    ~TableItem(); // non-trivial destructor
  };
  /**
   * @brief rbegin list item pointer
   *
   */
  TableItem* m_beforeFirst;
  /**
   * @brief number of list elements
   *
   */
  size_t m_numberOfEditions;

public:
  /**
   * @brief Key-Value pair type
   *
   */
  using KeyVal_t = std::pair<long, BookEdition*>;
  /**
   * @brief Construct a new Table object (default)
   *
   */
  Table();
  /**
   * @brief Construct a new Table object from vector of Key-Value pairs
   *
   * @param books pairs
   */
  Table(std::vector<KeyVal_t> books);
  /**
   * @brief Destroy the Table object - free memory used by list
   *
   */
  ~Table();
  /**
   * @brief Returns current table size
   *
   * @return size_t
   */
  inline size_t size() const { return m_numberOfEditions; };
  /**
   * @brief add an element by key. Use KeyVal() helper function to create table
   * item
   *
   * @param keyval
   * @return Table&
   */
  Table& operator<<(TableItem&& keyval);
  /**
   * @brief Get table element by index. Returns Wrapper to access element.
   * Creates place in table if key is not found.
   *
   * @param key
   * @return BookEditionWrapper
   */
  BookEditionWrapper operator[](long key);
  /**
   * @brief Remove element from table by index
   *
   * @param key
   * @return BookEdition
   */
  BookEdition erase(long key);
  /**
   * @brief Output table to stream (formated)
   * 
   * @param stream ostream object reference
   * @param table Table object const reference
   * @return std::ostream& 
   */
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  /**
   * @brief Output table to stream (unformated)
   * 
   * @param stream ostream object reference
   * @return std::ostream& 
   */
  std::ostream& output(std::ostream& stream) const;
  /**
   * @brief Save table to file by name
   * 
   * @param file File name
   */
  void save(std::string file) const;
  /**
   * @brief Load table from file by name (csv format)
   * 
   * @param file File name
   */
  void open(std::string file);
  /**
   * @brief Makes a Key-Value pair to add to table
   * 
   * @tparam Edition_t
   * @param key Edition code
   * @param val Edition object
   * @return Table::TableItem 
   */
  template <edition Edition_t>
  friend Table::TableItem KeyVal(long key, Edition_t const& val);
  /**
   * @brief Wrapper to access to table element
   * 
   */
  friend class BookEditionWrapper;
};

template <typename Edition_t>
Table::TableItem KeyVal(long key, Edition_t const& val)
{
  return Table::TableItem{key, val};
}

class BookEditionWrapper
{
private:
  Table::TableItem& m_item;

public:
  inline BookEditionWrapper(Table::TableItem& item) : m_item{item} {};
  inline BookEdition& operator*() { return *(m_item.book); }
  inline BookEdition* operator&() { return m_item.book; };
  inline size_t getCode() { return m_item.code; }
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
