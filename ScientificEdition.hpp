#ifndef SCIENTIFICEDITION_HPP
#define SCIENTIFICEDITION_HPP
#include "BookEdition.hpp"
#include <vector>

class ScientificEdition : public BookEdition
{
private:
  EditionType m_editionType = Scientific;
  std::string m_courceTitles[3];
  size_t m_numberOfCources;

public:
  ScientificEdition(std::string const& author, std::string const& title,
                    long year, std::string const& publisher,
                    size_t numberOfCopies,
                    std::vector<std::string> const& courceTitles = {});
  ScientificEdition(std::string const& author, std::string const& title,
                    long year, std::string const& publisher,
                    size_t numberOfCopies, std::string const courceTitles[],
                    size_t numberOfCources);
  ScientificEdition(ScientificEdition const& other);
  ScientificEdition(ScientificEdition&& other) = default;
  size_t getNumberOfCources() const;
  std::string const* getCourceTitles() const;
  std::string getCourceTitlesAsString() const;
  std::string& operator[](size_t index) noexcept;
  std::string& at(size_t index);
  std::string eraseCource(size_t index);
  ScientificEdition& operator<<(std::string const& cource);
  std::ostream& output(std::ostream& stream) const override;
};

#endif