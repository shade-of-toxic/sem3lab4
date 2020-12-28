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
  constexpr Table() {}
  inline size_t size() const { return m_list.size(); };
  BookEdition*& operator[](long key);
  template <std::derived_from<BookEdition> Edition_t>
  void add(Edition_t&& item)
  {
    size_t i = 0;
    for (auto it : m_list)
    {
      if (item.getCode() < it->getCode())
        break;
      i++;
    }
    m_list.insert(i, std::move(item));
  }
  void erase(long key);
  friend std::ostream& operator<<(std::ostream& stream, Table const& table);
  std::ostream& output(std::ostream& stream) const;
  void save(std::string file) const;
  void open(std::string file);
};

#endif // TABLE_HPP
