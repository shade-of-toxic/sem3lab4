#ifndef LIST_HPP
#define LIST_HPP

#include <concepts>
#include <type_traits>
#include <vector>

template <typename BaseClass>
class poly_list
{

private:
  struct ListItem
  {
    BaseClass* item;
    ListItem* next;

    inline constexpr ListItem() : item{nullptr}, next{nullptr} {}
    explicit ListItem(std::derived_from<BaseClass> auto const& aitem);
    explicit ListItem(std::derived_from<BaseClass> auto&& aitem);
    /**
     * @brief ListItem copying is not allowed due to polymorphism potencial loss
     * 
     * @param other 
     */
    ListItem(ListItem const& other) = delete;
    ListItem(ListItem&& other);

    ListItem& operator=(ListItem const& other) = delete;
    ListItem& operator=(ListItem&& other);
    ~ListItem();
  };

  ListItem* m_rend;
  ListItem* m_rbegin;
  size_t m_size;

public:
  class forward_iterator
  {

  private:
    ListItem* m_item;
    friend class poly_list;

    explicit inline forward_iterator(poly_list::ListItem* it) : m_item{it} {}

  public:
    inline forward_iterator& operator=(forward_iterator const& fi)
    {
      m_item = fi.m_item;
      return *this;
    }
    forward_iterator& operator=(std::derived_from<BaseClass> auto const& item);
    forward_iterator& operator=(std::derived_from<BaseClass> auto&& item);
    inline forward_iterator& operator++()
    {
      m_item = m_item->next;
      return *this;
    }
    [[nodiscard]] forward_iterator operator++(int);
    inline BaseClass& operator*() const { return *m_item->next->item; }
    inline BaseClass* operator->() const { return m_item->next->item; }
    inline bool operator==(forward_iterator other) const
    {
      return m_item == other.m_item;
    }
    inline bool operator!=(forward_iterator other) const
    {
      return m_item != other.m_item;
    }
  };
  class const_forward_iterator
  {

  private:
    ListItem const* m_item;

    friend class poly_list;
    explicit inline const_forward_iterator(poly_list::ListItem const* it) : m_item{it} {}

  public:
    inline const_forward_iterator& operator++()
    {
      m_item = m_item->next;
      return *this;
    }
    [[nodiscard]] const_forward_iterator operator++(int);
    inline BaseClass const& operator*() const { return *m_item->next->item; }
    inline BaseClass const* operator->() const { return m_item->next->item; }
    inline bool operator==(const_forward_iterator other) const
    {
      return m_item == other.m_item;
    }
    inline bool operator!=(const_forward_iterator other) const
    {
      return m_item != other.m_item;
    }
  };

  constexpr poly_list();
  ~poly_list();

  inline size_t size() const { return m_size; }
  BaseClass& push_back(std::derived_from<BaseClass> auto const& elem);
  BaseClass& emplace_back(std::derived_from<BaseClass> auto&& elem);
  void pop(size_t index);
  BaseClass& insert(size_t index, std::derived_from<BaseClass> auto&& item);
  BaseClass& insert(size_t index, std::derived_from<BaseClass> auto const& item);
  BaseClass& insert(forward_iterator it, std::derived_from<BaseClass> auto&& item);
  BaseClass& insert(forward_iterator it, std::derived_from<BaseClass> auto const& item);
  forward_iterator operator[](size_t index);
  forward_iterator erase(forward_iterator it);
  void remove(BaseClass& item);
  void clear();
  inline forward_iterator begin() { return forward_iterator{m_rend}; }
  inline forward_iterator end() { return forward_iterator{m_rbegin}; }
  inline const_forward_iterator begin() const { return const_forward_iterator{m_rend}; }
  inline const_forward_iterator end() const { return const_forward_iterator{m_rbegin}; }
};
#include "List.cpp"

#endif // LIST_HPP