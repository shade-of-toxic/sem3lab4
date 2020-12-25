#ifndef BOOKEDITION_HPP
#define BOOKEDITION_HPP
#include <iostream>
#include <string>

enum EditionType
{
  Undefined = 0,
  Learning = 1,
  Scientific = 2,
  Fiction = 3
};

char const* const ETypeStrings[] = {"Undefined", "Learning",
                                             "Scientific", "Fiction"};

class BookEdition
{
protected:
  std::string m_author;
  std::string m_title;
  long m_year;
  std::string m_publisher;
  size_t m_numberOfCopies;
  EditionType m_editionType;
  BookEdition(std::string const& author, std::string const& title, long year,
              std::string const& publisher, size_t numberOfCopies,
              EditionType editionType);

public:
  BookEdition();
  BookEdition(std::string const& author, std::string const& title, long year,
              std::string const& publisher, size_t numberOfCopies);
  friend std::ostream& operator<<(std::ostream&, BookEdition const&);
  virtual std::ostream& output(std::ostream& stream) const;
  EditionType getEditionType() const;
  size_t getNumberOfCopies() const;
  size_t setNumberOfCopies(size_t nc);
  BookEdition& operator++();
  BookEdition& operator++(int);
  BookEdition& operator--();
  BookEdition& operator--(int);
};
#endif