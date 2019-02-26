#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

class scoped_thread {
  std::thread inner_thread_;

public:
  // CTOR
  explicit scoped_thread(std::thread && inner_thread) : inner_thread_(std::move(inner_thread)) {
    if (!inner_thread_.joinable()) {
      throw std::logic_error("Require a joinable thread !");
    }
  }

  // MOVE ctor
  scoped_thread(scoped_thread && other) : inner_thread_(std::move(other.inner_thread_)) {}

  // DTOR
  ~scoped_thread() {
    if (inner_thread_.joinable()) {
      inner_thread_.join();
    }
  }

  // No copy/assign
  scoped_thread(scoped_thread &) = delete;
  scoped_thread& operator=(scoped_thread const &) = delete;
};

static constexpr int kNumThreads = 10;

void Test1() {
  std::cout << "***** Test 1 *****" << std::endl;

  std::vector<std::thread> mythreads;
  for (int i = 0; i < kNumThreads; ++i) {
    mythreads.emplace_back([i]{
			     std::cout << "This thread (" << std::this_thread::get_id() << ")sees: " << i << std::endl;
			    });
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "Main program thread is: " << std::this_thread::get_id() << std::endl;

  std:: cout << "Will join threads now ..." << std::endl;

  for (auto & thr : mythreads) {
    thr.join();
  }

  std::cout << std::endl;
}

void Test2(std::vector<std::string> &output) {
  std::cout << std::endl  << "***** Test 2 *****" << std::endl;

  std::vector<scoped_thread> mythreads;
  mythreads.reserve(kNumThreads);
  for (int i = 0; i < kNumThreads; ++i) {
    std::thread thr {[i, &output]{
		       std::ostringstream ostr;
		       std::this_thread::sleep_for(std::chrono::milliseconds(10));
		       ostr << "This thread (" << std::this_thread::get_id() << ") sees: " << i << std::endl;
		       std::this_thread::sleep_for(std::chrono::milliseconds(10));
		       ostr << "Done with thread ## " << i << std::endl;

		       output[i] = ostr.str();
		     }};

    mythreads.emplace_back(std::move(thr));
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  // Implicit join!
}

int main() {
  std ::cout << "Hello world !" << std::endl;

  Test1();

  std::vector<std::string> output(kNumThreads);
  Test2(output);
  for (const auto& line : output) {
    std::cout << line;
  }

  return 0;
}

/*

Sample output:
---------------

> $ ./a.out                                                                                                                                                                                  
Hello world !
***** Test 1 *****
This thread (This thread (This thread (0x700003b4d0000x700003aca000)sees: )sees: 0x700003bd0000)sees: This thread (0x700003c53000)sees: This thread (0x700003cd6000)sees: This thread (0x700003d59000)sees: This thread (0x700003ddc000)sees: This thread (0x700003e5f000)sees: This thread (0x700003ee2000)sees: This thread (0x700003f65000)sees: 905
4
1
2
763



8

Main program thread is: 0x1130c35c0
Will join threads now ...


***** Test 2 *****
This thread (0x700003aca000) sees: 0
Done with thread ## 0
This thread (0x700003b4d000) sees: 1
Done with thread ## 1
This thread (0x700003bd0000) sees: 2
Done with thread ## 2
This thread (0x700003c53000) sees: 3
Done with thread ## 3
This thread (0x700003cd6000) sees: 4
Done with thread ## 4
This thread (0x700003d59000) sees: 5
Done with thread ## 5
This thread (0x700003ddc000) sees: 6
Done with thread ## 6
This thread (0x700003e5f000) sees: 7
Done with thread ## 7
This thread (0x700003ee2000) sees: 8
Done with thread ## 8
This thread (0x700003f65000) sees: 9
Done with thread ## 9


 */
