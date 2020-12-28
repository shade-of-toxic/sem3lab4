#include "BookEdition.hpp"
#include <cstring>
#include <iomanip>
#include <memory>

std::ostream& operator<<(std::ostream& stream, EditionType type)
{
  return stream << ETypeStrings[(uint16_t)type];
}

BookEdition::BookEdition(long code)
    : m_year{0}, m_numberOfCopies{0}, m_editionType{Undefined}, m_code{code}
{
}

BookEdition::BookEdition(std::string const& author, std::string const& title,
                         long year, std::string const& publisher,
                         size_t numberOfCopies, long code)
    : m_year{year}, m_numberOfCopies{numberOfCopies},
      m_editionType{Undefined}, m_code{code}
{
  m_author    = author;
  m_title     = title;
  m_publisher = publisher;
}

BookEdition::BookEdition(std::string const& author, std::string const& title,
                         long year, std::string const& publisher,
                         size_t numberOfCopies, long code,
                         EditionType editionType)
    : m_year{year}, m_numberOfCopies{numberOfCopies},
      m_editionType{editionType}, m_code{code}
{
  m_author    = author;
  m_title     = title;
  m_publisher = publisher;
}

std::ostream& operator<<(std::ostream& stream, BookEdition const& book)
{
  return stream << std::setw(5) << book.m_code << std::setw(15) << book.m_author
                << ";" << std::setw(15) << book.m_title << ";" << std::setw(15)
                << book.m_year << ";" << std::setw(15) << book.m_publisher
                << ";" << std::setw(15) << book.m_numberOfCopies << ";"
                << std::setw(15) << book.m_editionType << "\n";
}

std::ostream& BookEdition::output(std::ostream& stream) const
{
  return stream << m_code << ";" << m_author << ";" << m_title << ";" << m_year
                << ";" << m_publisher << ";" << m_numberOfCopies << ";"
                << m_editionType << ";";
}

EditionType BookEdition::getEditionType() const { return m_editionType; };
size_t BookEdition::getNumberOfCopies() const { return m_numberOfCopies; };
size_t BookEdition::setNumberOfCopies(size_t nc)
{
  return m_numberOfCopies = nc;
};
BookEdition& BookEdition::operator++()
{
  m_numberOfCopies++;
  return *this;
}
BookEdition& BookEdition::operator++(int)
{
  m_numberOfCopies++;
  return *this;
}
BookEdition& BookEdition::operator--()
{
  m_numberOfCopies--;
  return *this;
}
BookEdition& BookEdition::operator--(int)
{
  m_numberOfCopies--;
  return *this;
}