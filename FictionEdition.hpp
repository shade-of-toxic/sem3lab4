#ifndef FICTIONEDITION_HPP
#define FICTIONEDITION_HPP
#include "BookEdition.hpp"

class FictionEdition : public BookEdition
{
private:
  EditionType m_editionType = Fiction;
  std::string m_subject;

public:
  FictionEdition(std::string const& author, std::string const& title, long year,
                 std::string const& publisher, size_t numberOfCopies,
                 std::string const& subject);
  FictionEdition(FictionEdition const& other);
  FictionEdition(FictionEdition&& other) = default;
  std::string const& getSubject();
  virtual std::ostream& output(std::ostream& stream) const;
};

#endif