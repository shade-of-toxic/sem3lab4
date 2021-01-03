#ifndef LIST_CPP
#define LIST_CPP

#include "List.hpp"
#include "stdexcept"

template <typename BaseClass>
poly_list<BaseClass>::ListItem&
poly_list<BaseClass>::ListItem::operator=(ListItem&& other)
{
  delete item;
  item       = other.item;
  other.item = nullptr;
  return *this;
}

template <typename BaseClass>
poly_list<BaseClass>::ListItem::~ListItem()
{
  delete item;
  delete next;
}

template <typename BaseClass>
constexpr poly_list<BaseClass>::poly_list()
    : m_rend{new ListItem}, m_rbegin{m_rend}, m_size{0} {};

template <typename BaseClass>
poly_list<BaseClass>::~poly_list()
{
  delete m_rend;
}

template <typename BaseClass>
void poly_list<BaseClass>::pop(size_t index)
{
  if (index >= size())
    throw std::out_of_range("Index was out of range.");
  auto prev = m_rend;
  m_size--;
  for (auto i = 0ul; i < index; i++)
  {
    prev = prev->next;
  }
  if (prev->next == m_rbegin)
  {
    delete prev->next;
    prev->next = nullptr;
    m_rbegin   = prev;
  }
  else
  {
    auto tmp         = prev->next->next;
    prev->next->next = nullptr;
    delete prev->next;
    prev->next = tmp;
  }
}

template <typename BaseClass>
poly_list<BaseClass>::forward_iterator
poly_list<BaseClass>::operator[](size_t index)
{
  auto prev = m_rend;
  for (auto i = 0ul; i < index; i++)
  {
    prev = prev->next;
  }
  return prev;
}

template <typename BaseClass>
poly_list<BaseClass>::forward_iterator
poly_list<BaseClass>::erase(poly_list<BaseClass>::forward_iterator it)
{
  auto tmp              = it.m_item->next->next;
  it.m_item->next->next = nullptr;
  delete it.m_item->next;
  it.m_item->next = tmp;
  if (it == end())
    m_rbegin = tmp;
  m_size--;
  return it;
}
template <typename BaseClass>
void poly_list<BaseClass>::remove(BaseClass& item)
{
  for (auto it = begin(); it != end(); ++it)
    if (&*it == &item)
    {
      erase(it);
      break;
    }
}
template <typename BaseClass>
void poly_list<BaseClass>::clear()
{
  delete m_rend->next;
  m_rend->next = nullptr;
  m_rbegin     = m_rend;
  m_size       = 0;
}

template <typename BaseClass>
poly_list<BaseClass>::ListItem::ListItem(
    std::derived_from<BaseClass> auto&& aitem)
    : item{new (std::remove_reference_t<decltype(aitem)>){std::move(aitem)}},
      next{nullptr}
{
}
template <typename BaseClass>
poly_list<BaseClass>::ListItem::ListItem(
    std::derived_from<BaseClass> auto const& aitem)
    : item{new (std::remove_reference_t<decltype(aitem)>){aitem}}, next{nullptr}
{
}

template <typename BaseClass>
poly_list<BaseClass>::ListItem::ListItem(ListItem&& other)
    : item{other.item}, next{nullptr}
{
  other.item = nullptr;
}

template <typename BaseClass>
poly_list<BaseClass>::forward_iterator&
poly_list<BaseClass>::forward_iterator::operator=(
    std::derived_from<BaseClass> auto const& item)
{
  *m_item->next = ListItem{item};
  return *this;
}

template <typename BaseClass>
poly_list<BaseClass>::forward_iterator&
poly_list<BaseClass>::forward_iterator::operator=(
    std::derived_from<BaseClass> auto&& item)
{
  *m_item->next = ListItem{std::move(item)};
  return *this;
}
template <typename BaseClass>
poly_list<BaseClass>::forward_iterator
poly_list<BaseClass>::forward_iterator::operator++(int)
{
  forward_iterator ret{m_item};
  m_item = m_item->next;
  return ret;
}
template <typename BaseClass>
BaseClass&
poly_list<BaseClass>::push_back(std::derived_from<BaseClass> auto const& elem)
{
  m_size++;
  m_rbegin->next = new ListItem{elem};
  m_rbegin       = m_rbegin->next;
  return *m_rbegin->item;
}
template <typename BaseClass>
BaseClass&
poly_list<BaseClass>::emplace_back(std::derived_from<BaseClass> auto&& elem)
{
  m_size++;
  m_rbegin->next = new ListItem{std::move(elem)};
  m_rbegin       = m_rbegin->next;
  return *m_rbegin->item;
}
template <typename BaseClass>
BaseClass&
poly_list<BaseClass>::insert(size_t index,
                             std::derived_from<BaseClass> auto&& item)
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
  return *prev->next->item;
}
template <typename BaseClass>
BaseClass&
poly_list<BaseClass>::insert(size_t index,
                             std::derived_from<BaseClass> auto const& item)
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
  return *prev->next->item;
}
template <typename BaseClass>
BaseClass&
poly_list<BaseClass>::insert(forward_iterator it,
                             std::derived_from<BaseClass> auto&& item)
{
  m_size++;
  auto tmp = it.m_item->next;
  // if constexpr() {
  // static_assert(std::is_rvalue_reference_v<decltype(item)>);
  // }else if constexpr(std::is_lvalue_reference_v<decltype(item)>) {
  // static_assert(std::is_lvalue_reference_v<decltype(item)>);
  // }
  it.m_item->next       = new ListItem{std::move(item)};
  it.m_item->next->next = tmp;
  if (tmp == nullptr)
    m_rbegin = it.m_item->next;
  return *it;
}
template <typename BaseClass>
BaseClass&
poly_list<BaseClass>::insert(forward_iterator it,
                             std::derived_from<BaseClass> auto const& item)
{
  m_size++;
  auto tmp              = it.m_item->next;
  it.m_item->next       = new ListItem{item};
  it.m_item->next->next = tmp;
  if (tmp == nullptr)
    m_rbegin = it.m_item->next;
  return *it;
}

template <typename BaseClass>
poly_list<BaseClass>::const_forward_iterator
poly_list<BaseClass>::const_forward_iterator::operator++(int)
{
  const_forward_iterator ret{m_item};
  m_item = m_item->next;
  return ret;
}
#endif // LIST_CPP