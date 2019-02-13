#include <iostream>
#include <regex>

void simple_searcher(const std::string& s, const std::string& reg_s) {
  std::regex r(reg_s);
  if (std::regex_search(s, r)) {
    std::cout << "Found a match for " << reg_s << std::endl;
  } else {
    std::cout << "Sorry, no match found for " << reg_s << std::endl;
  }
}

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
}

