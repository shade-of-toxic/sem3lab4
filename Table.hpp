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
  template <std::derived_from<BookEdition> Edition_t>
  void add(Edition_t&& item)
  {
    size_t i = 0;
    for (auto &it : m_list)
    {
      if (item.getCode() < it.getCode())
        break;
      i++;
    }
    m_list.insert(i, std::move(item));
  }
  template <std::derived_from<BookEdition> Edition_t>
  void add(Edition_t const& item)
  {
    size_t i = 0;
    for (auto &it : m_list)
    {
      if (item.getCode() < it.getCode())
        break;
      i++;
    }
    m_list.insert(i, item);
  }
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

#endif // TABLE_HPP
