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
BaseClass* poly_list<BaseClass>::operator[](size_t index)
{
  auto prev = m_rend;
  for (auto i = 0ul; i < index; i++)
  {
    prev = prev->next;
  }
  return prev->next->item;
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
void poly_list<BaseClass>::remove(BaseClass* item)
{
  for (auto it = begin(); it != end(); ++it)
    if (*it == item)
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
#endif // LIST_CPP