#ifndef LIST_HPP
#define LIST_HPP

#include <concepts>
#include <vector>

namespace std
{

template <typename _One, typename... _Others>
concept same_as_one_of = (same_as<_One, _Others> || ...);

} // namespace std

template <typename BaseClass>
class poly_list
{
  struct ListItem
  {
    BaseClass* item;
    ListItem* next;

    constexpr ListItem() : item{nullptr}, next{nullptr} {}
    template <std::derived_from<BaseClass> Derived>
    ListItem(Derived const& aitem) : item{new Derived{aitem}}, next{nullptr}
    {
    }
    template <std::derived_from<BaseClass> Derived>
    ListItem(Derived&& aitem)
        : item{new Derived{std::move(aitem)}}, next{nullptr}
    {
    }
    template <std::derived_from<BaseClass> Derived>
    ListItem(ListItem const& other)
        : item{new Derived{other.item}}, next{nullptr}
    {
    }
    template <std::derived_from<BaseClass> Derived>
    ListItem(ListItem&& other)
        : item{new Derived{std::move(other.item)}}, next{nullptr}
    {
    }

    ListItem& operator=(ListItem const& other) = delete;
    ListItem& operator                         =(ListItem&& other);
    ~ListItem();
  };

public:
  class forward_iterator
  {
    ListItem* m_item;
    friend class poly_list;
    forward_iterator(poly_list::ListItem* it) : m_item{it} {}

  public:
    inline forward_iterator& operator++()
    {
      m_item = m_item->next;
      return *this;
    }
    forward_iterator operator++(int)
    {
      forward_iterator ret{m_item};
      m_item = m_item->next;
      return ret;
    }
    inline BaseClass*& operator*() const { return m_item->next->item; }
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
    ListItem const* m_item;

    friend class poly_list;
    const_forward_iterator(poly_list::ListItem const* it) : m_item{it} {}

  public:
    const_forward_iterator& operator++()
    {
      m_item = m_item->next;
      return *this;
    }
    const_forward_iterator operator++(int)
    {
      const_forward_iterator ret{m_item};
      m_item = m_item->next;
      return ret;
    }
    BaseClass const* operator*() const { return m_item->next->item; }
    BaseClass const* operator->() const { return m_item->next->item; }
    inline bool operator==(const_forward_iterator other) const
    {
      return m_item == other.m_item;
    }
    inline bool operator!=(const_forward_iterator other) const
    {
      return m_item != other.m_item;
    }
  };

private:
  ListItem* m_rend;
  ListItem* m_rbegin;
  size_t m_size;

public:
  constexpr poly_list();
  ~poly_list();

  inline size_t size() const { return m_size; }
  template <std::derived_from<BaseClass> Derived>
  BaseClass* push_back(Derived const& elem)
  {
    m_size++;
    m_rbegin->next = new ListItem{elem};
    m_rbegin       = m_rbegin->next;
    return m_rbegin->item;
  }
  template <std::derived_from<BaseClass> Derived>
  BaseClass* emplace_back(Derived&& elem)
  {
    m_size++;
    m_rbegin->next = new ListItem{std::move(elem)};
    m_rbegin       = m_rbegin->next;
    return m_rbegin->item;
  }
  void pop(size_t index);
  template <std::derived_from<BaseClass> Derived>
  BaseClass* insert(size_t index, Derived&& item)
  {
    auto prev = m_rend;
    m_size++;
    for (auto i = 0ul; i < index; i++)
    {
      prev = prev->next;
    }
    if (prev->next != nullptr)
    {
      auto tmp         = prev->next;
      prev->next       = new ListItem{std::move(item)};
      prev->next->next = tmp;
    }
    else
    {
      prev->next = new ListItem{std::move(item)};
      m_rbegin   = prev->next;
    }
    return prev->next->item;
  }
  template <std::derived_from<BaseClass> Derived>
  BaseClass* insert(size_t index, Derived const& item)
  {
    auto prev = m_rend;
    m_size++;
    for (auto i = 0ul; i < index; i++)
    {
      prev = prev->next;
    }
    if (prev->next != nullptr)
    {
      auto tmp         = prev->next;
      prev->next       = new ListItem{item};
      prev->next->next = tmp;
    }
    else
    {
      prev->next = new ListItem{item};
      m_rbegin   = prev->next;
    }
    return prev->next->item;
  }
  template <std::derived_from<BaseClass> Derived>
  BaseClass* insert(forward_iterator it, Derived&& item)
  {
    m_size++;
    auto tmp              = it.m_item->next;
    it.m_item->next       = new ListItem{std::move(item)};
    it.m_item->next->next = tmp;
    if (tmp == nullptr)
      m_rbegin = it.m_item->next;
    return *it;
  }
  template <std::derived_from<BaseClass> Derived>
  BaseClass* insert(forward_iterator it, Derived const& item)
  {
    m_size++;
    auto tmp              = it.m_item->next;
    it.m_item->next       = new ListItem{item};
    it.m_item->next->next = tmp;
    if (tmp == nullptr)
      m_rbegin = it.m_item->next;
    return *it;
  }
  BaseClass* operator[](size_t index);
  forward_iterator erase(forward_iterator it);
  void clear();
  inline forward_iterator begin() { return m_rend; }
  inline forward_iterator end() { return m_rbegin; }
  inline const_forward_iterator begin() const { return m_rend; }
  inline const_forward_iterator end() const { return m_rbegin; }
};
#include "List.cpp"

#endif // LIST_HPP