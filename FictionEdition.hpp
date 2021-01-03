#ifndef FICTIONEDITION_HPP
#define FICTIONEDITION_HPP
#include "BookEdition.hpp"

class FictionEdition : public BookEdition
{
private:
  std::string m_subject;

public:
  FictionEdition(std::string const& author,
                                 std::string const& title, long year,
                                 std::string const& publisher,
                                 size_t numberOfCopies, long code,
                                 std::string const& subject);
  FictionEdition(FictionEdition const& other);
  std::string const& getSubject();
  std::ostream& output(std::ostream& stream) const override;
};

#endif