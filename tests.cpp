#include "FictionEdition.hpp"
#include "LearningEdition.hpp"
#include "ScientificEdition.hpp"
#include "Table.hpp"
#include "catch2/catch.hpp"
#include "memleak_test_basic.hpp"
#include <sstream>

TEST_CASE("adds items to table & outputs to stream")
{
  long pretest_mem = get_used_mem_size();
  {
    Table tab;
    tab.add(BookEdition("abc", "def", 2013, "publ", 3, -14));
    tab.add(
        ScientificEdition("ghi", "def", 2010, "publ2", 5, 12, {"c1", "c2"}));
    tab.add(FictionEdition("fic1", "auth", -10, "publisher1", 2, 11, "sub"));
    tab.add(LearningEdition("le3", "auth1", 2017, "publisher3", 7, -3, "c4",
                            {1, 2, 4, 77, 5, 3, 12, 5}));
    std::stringstream ss;
    REQUIRE(tab.size() == 4);
    tab.output(ss);
    CHECK(ss.str() == R"(-14;abc;def;2013;publ;3;Undefined;
-3;le3;auth1;2017;publisher3;7;Learning;c4;8;1;2;4;77;5;3;12;5;
11;fic1;auth;-10;publisher1;2;Fiction;sub;
12;ghi;def;2010;publ2;5;Scientific;2;c1;c2;
)");
  }
  CHECK(get_used_mem_size() == pretest_mem);
}

TEST_CASE("saves & opens from file")
{

  long pretest_mem = get_used_mem_size();
  {
    Table tab;
    tab.add(BookEdition("abc", "def", 2013, "publ", 3, -14));
    tab.add(
        ScientificEdition("ghi", "def", 2010, "publ2", 5, 12, {"c1", "c2"}));
    tab.add(FictionEdition("fic1", "auth", -10, "publisher1", 2, 11, "sub"));
    tab.add(LearningEdition("le3", "auth1", 2017, "publisher3", 7, -3, "c4",
                            {1, 2, 4, 77, 5, 3, 12, 5}));
    REQUIRE(tab.size() == 4);
    std::stringstream ss1, ss2;
    tab.output(ss1);
    tab.save("table.csv");
    tab.open("table.csv");
    tab.output(ss2);
    CHECK(ss1.str() == ss2.str());
  }
  CHECK(get_used_mem_size() == pretest_mem);
}

TEST_CASE("iterates over the table")
{
  long pretest_mem = get_used_mem_size();
  {
    Table tab;
    tab.add(BookEdition("abc", "def", 2013, "publ", 3, -14));
    tab.add(
        ScientificEdition("ghi", "def", 2010, "publ2", 5, 12, {"c1", "c2"}));
    tab.add(FictionEdition("fic1", "auth", -10, "publisher1", 2, 11, "sub"));
    tab.add(LearningEdition("le3", "auth1", 2017, "publisher3", 7, -3, "c4",
                            {1, 2, 4, 77, 5, 3, 12, 5}));
    REQUIRE(tab.size() == 4);
    std::vector<std::string> checkstrings{
        "-14;abc;def;2013;publ;3;Undefined;",
        "-3;le3;auth1;2017;publisher3;7;Learning;c4;8;1;2;4;77;5;3;12;5;",
        "11;fic1;auth;-10;publisher1;2;Fiction;sub;",
        "12;ghi;def;2010;publ2;5;Scientific;2;c1;c2;"};

    for (int i = 0; auto& book : tab)
    {
      {
        std::stringstream ss;
        book.output(ss);
        CHECK(ss.str() == checkstrings[i++]);
      }
    }
  }
  CHECK(get_used_mem_size() == pretest_mem);
}

TEST_CASE("removes element by code")
{
  long pretest_mem = get_used_mem_size();
  {
    Table tab;
    tab.add(BookEdition("abc", "def", 2013, "publ", 3, -14));
    tab.add(
        ScientificEdition("ghi", "def", 2010, "publ2", 5, 12, {"c1", "c2"}));
    tab.add(FictionEdition("fic1", "auth", -10, "publisher1", 2, 11, "sub"));
    tab.add(LearningEdition("le3", "auth1", 2017, "publisher3", 7, -3, "c4",
                            {1, 2, 4, 77, 5, 3, 12, 5}));
    REQUIRE(tab.size() == 4);
    tab.erase(11);
    REQUIRE(tab.size() == 3);
    std::stringstream ss;
    tab.output(ss);
    CHECK(ss.str() == R"(-14;abc;def;2013;publ;3;Undefined;
-3;le3;auth1;2017;publisher3;7;Learning;c4;8;1;2;4;77;5;3;12;5;
12;ghi;def;2010;publ2;5;Scientific;2;c1;c2;
)");
  }
  CHECK(get_used_mem_size() == pretest_mem);
}

TEST_CASE("gets element by code & sets through wrapper")
{
  long pretest_mem = get_used_mem_size();
  {
    Table tab;
    tab.add(BookEdition("abc", "def", 2013, "publ", 3, -14));
    tab.add(
        ScientificEdition("ghi", "def", 2010, "publ2", 5, 12, {"c1", "c2"}));
    tab.add(FictionEdition("fic1", "auth", -10, "publisher1", 2, 11, "sub"));
    tab.add(LearningEdition("le3", "auth1", 2017, "publisher3", 7, -3, "c4",
                            {1, 2, 4, 77, 5, 3, 12, 5}));
    REQUIRE(tab.size() == 4);
    tab[11] =
        ScientificEdition("qwe", "rty", 2014, "publ5", 8, 11, {"c5", "c6"});
    REQUIRE(tab.size() == 4);
    std::stringstream ss;
    tab.output(ss);
    CHECK(ss.str() == R"(-14;abc;def;2013;publ;3;Undefined;
-3;le3;auth1;2017;publisher3;7;Learning;c4;8;1;2;4;77;5;3;12;5;
11;qwe;rty;2014;publ5;8;Scientific;2;c5;c6;
12;ghi;def;2010;publ2;5;Scientific;2;c1;c2;
)");
  }
  CHECK(get_used_mem_size() == pretest_mem);
}
