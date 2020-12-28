#include "ScientificEdition.hpp"
#include <sstream>

ScientificEdition::ScientificEdition(
    std::string const& author, std::string const& title, long year,
    std::string const& publisher, size_t numberOfCopies, long code,
    std::vector<std::string> const& courceTitles)
    : BookEdition{author, title, year, publisher, numberOfCopies, code, Scientific}
{
  if (courceTitles.size() > 3)
    throw std::runtime_error("Too many cources. Expected 3 at most.");
  m_numberOfCources = 0;
  for (auto& cource : courceTitles)
    m_courceTitles[m_numberOfCources++] = cource;
}

ScientificEdition::ScientificEdition(std::string const& author,
                                     std::string const& title, long year,
                                     std::string const& publisher,
                                     size_t numberOfCopies, long code,
                                     std::string const courceTitles[],
                                     size_t numberOfCources)
    : BookEdition{author, title, year, publisher, numberOfCopies, code, Scientific}
{
  if (numberOfCources > 3)
    throw std::runtime_error("Too many cources. Expected 3 at most.");
  m_numberOfCources = numberOfCources;
  for (auto i = 0ul; i < numberOfCources; i++)
    m_courceTitles[i] = courceTitles[i];
}

ScientificEdition::ScientificEdition(ScientificEdition const& other): BookEdition{*((BookEdition const*)&other)} {
  m_numberOfCources = other.m_numberOfCources;
  for (auto i = 0ul; i < other.m_numberOfCources; i++)
    m_courceTitles[i] = other.m_courceTitles[i];
}

size_t ScientificEdition::getNumberOfCources() const
{
  return m_numberOfCources;
}

std::string const* ScientificEdition::getCourceTitles() const
{
  return m_courceTitles;
}
std::string ScientificEdition::getCourceTitlesAsString() const
{
  std::stringstream ss;
  for (auto i = 0ul; i < getNumberOfCources(); i++)
    ss << m_courceTitles[i] << ((i == getNumberOfCources() - 1) ? "" : ", ");
  return ss.str();
}
std::string& ScientificEdition::operator[](size_t index) noexcept
{
  return m_courceTitles[index];
}
std::string& ScientificEdition::at(size_t index)
{
  if (index >= getNumberOfCources())
    throw std::out_of_range("Index was out of range.");
  return m_courceTitles[index];
}
std::string ScientificEdition::eraseCource(size_t index)
{
  auto flag = 0ul;
  if (index >= getNumberOfCources())
    throw std::out_of_range("Index was out of range.");
  std::string res;
  for (auto i = 0ul; i < getNumberOfCources(); i++)
    if (i == index)
    {
      flag++;
      res = m_courceTitles[i];
    }
    else
      m_courceTitles[i - flag] = m_courceTitles[i];
  m_numberOfCources -= flag;
  return res;
}
ScientificEdition& ScientificEdition::operator<<(std::string const& cource)
{
  if (getNumberOfCources() == 3)
    throw std::runtime_error(
        "Tried to insert one more cource when already had 3.");
  m_courceTitles[m_numberOfCources++] = cource;
  return *this;
}

std::ostream& ScientificEdition::output(std::ostream& stream) const
{
  this->BookEdition::output(stream);
  stream << m_numberOfCources << ";";
  for (auto i = 0ul; i < m_numberOfCources; i++)
    stream << m_courceTitles[i] << ";";
  return stream;
}