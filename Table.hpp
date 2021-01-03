#ifndef TABLE_HPP
#define TABLE_HPP
#include "BookEdition.hpp"
#include "List.hpp"
#include <vector>

class Table
{
private:
  poly_list<BookEdition> m_list;

public:
  using forward_iterator       = poly_list<BookEdition>::forward_iterator;
  using const_forward_iterator = poly_list<BookEdition>::const_forward_iterator;
  inline constexpr Table() {}
  inline size_t size() const { return m_list.size(); };
  forward_iterator operator[](long key);
  const_forward_iterator at(long key) const;
  forward_iterator at(long key);
  void add(std::derived_from<BookEdition> auto&& item);
  void add(std::derived_from<BookEdition> auto const& item);
  void erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  std::ostream& output(std::ostream& stream) const;
  void save(std::string file) const;
  void open(std::string file);
  inline forward_iterator begin() { return m_list.begin(); }
  inline forward_iterator end() { return m_list.end(); }
  inline const_forward_iterator begin() const { return m_list.begin(); }
  inline const_forward_iterator end() const { return m_list.end(); }
};
#include "Table.cpp"
#endif // TABLE_HPP
