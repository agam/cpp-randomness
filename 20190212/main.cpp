#include <iostream>
#include <regex>

namespace {
  void simple_searcher(const std::string& s, const std::string& reg_s) {
    std::regex r(reg_s);
    if (std::regex_search(s, r)) {
      std::cout << "Found a match for " << reg_s << std::endl;
    } else {
      std::cout << "Sorry, no match found for " << reg_s << std::endl;
    }
  }

  void show_matches(const std::string& s, const std::string& reg_s) {
    std::regex r(reg_s);

    for (auto it = std::sregex_iterator(s.begin(), s.end(), r); it != std::sregex_iterator(); ++it) {
      std::cout << "Match: [" << it->str() << "]" << std::endl;
    }
  }
}  // namespace

int main() {
  std::cout << "Ain't this a fine pickle ?" << std::endl;
  std::string str("By the pricking of my thumbs, something wicked this way comes ...");

  // Test 1.
  {
    simple_searcher(str, "thumbs");
  }

  // Test 2.
  {
    simple_searcher(str, "\\w[a-z]+s ");
  }

  // Test 3.
  {
    show_matches(str, "th..");
  }
}

