#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

// Following along from https://www.bfilipek.com/2017/08/cpp17-details-filesystem.html

int main() {
  std::cout << "Hello world !" << std::endl;  // ALWAYS start with this :-)

  fs::path myPath("/tmp");

  std::cout << "Exists? " << fs::exists(myPath) << std::endl
  	    << "Root = " << myPath.root_name() << std::endl;

  // Status: linker error at this point:
  /*
    > $ /usr/local/opt/llvm/bin/clang++ -I/usr/local/opt/llvm/include -I/usr/local/opt/llvm/include/c++/v1 -L/usr/local/opt/llvm/lib  main.cpp -std=c++1z -lc++experimental                                                                                                                                                                                                            [±master ●]
Undefined symbols for architecture x86_64:
  "std::__1::__fs::filesystem::path::__root_name() const", referenced from:
      _main in main-439298.o
ld: symbol(s) not found for architecture x86_64
clang-7: error: linker command failed with exit code 1 (use -v to see invocation)
   */
  
  return 0;
}
