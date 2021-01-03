#ifndef BOOKEDITION_HPP
#define BOOKEDITION_HPP
#include <iostream>
#include <string>

enum EditionType
{
  Undefined  = 0,
  Learning   = 1,
  Scientific = 2,
  Fiction    = 3
};

char const* const ETypeStrings[] = {"Undefined", "Learning", "Scientific",
                                    "Fiction"};

class BookEdition
{
protected:
  std::string m_author;
  std::string m_title;
  long m_year;
  std::string m_publisher;
  size_t m_numberOfCopies;
  EditionType m_editionType;
  long m_code;
  BookEdition(std::string const& author, std::string const& title, long year,
              std::string const& publisher, size_t numberOfCopies, long code,
              EditionType editionType);

public:
  BookEdition(long code = 0);
  BookEdition(std::string const& author, std::string const& title, long year,
              std::string const& publisher, size_t numberOfCopies, long code);
  virtual ~BookEdition() = default;
  friend std::ostream& operator<<(std::ostream&, BookEdition const&);
  virtual std::ostream& output(std::ostream& stream) const;
  inline long getCode() const { return m_code; }
  EditionType getEditionType() const;
  size_t getNumberOfCopies() const;
  size_t setNumberOfCopies(size_t nc);
  BookEdition& operator++();
  [[nodiscard("Ignoring created object. Maybe you should use prefix form.")]] BookEdition operator++(int);
  BookEdition& operator--();
  [[nodiscard("Ignoring created object. Maybe you should use prefix form.")]] BookEdition operator--(int);
};
#endif