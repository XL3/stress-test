#include <iostream>

#include "./stress-test.hpp"

#ifdef _WIN32
// cl .\stress-test.cpp /std:c++17 User32.lib Gdi32.lib
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#endif

template <typename Distribution_t>
void test_discrete_parameter(Stress::Discrete_Parameter<Distribution_t> &X);

void print_vector(std::vector<int> vec);

int main() {
  Stress::Discrete_Parameter dice(1, 6);
  Stress::Discrete_Parameter coin(0, 1);
  // test_discrete_parameter(dice);

  auto multiply_incorrect = [](int a, int b) { return a; };
  auto multiply = [](int a, int b) { return a * b; };
  // This test should fail approximately 50% of the time
  Stress::Test test(multiply_incorrect, multiply, 0, dice, coin);
  test.run();

  return 0;
}

#ifdef _WIN32
template <typename Distribution_t>
void test_discrete_parameter(Stress::Discrete_Parameter<Distribution_t> &X) {
  bool key_down = 0;
  Distribution_t x;
  while (true) {
    if (GetKeyState(VK_SPACE) & (1 << 15)) {
      if (key_down) continue;

      x = X.generate();
      std::cout << "\r" << x;
      key_down = true;
    }
    else
      key_down = false;

    if (GetKeyState(VK_ESCAPE) & (1 << 15)) break;
  }
}
#else
template <typename Distribution_t>
void test_discrete_parameter(Stress::discrete_parameter<Distribution_t> &X) {
  std::vector<Distribution_t> vec(20);

  for (auto &x: vec) x = X.generate;
  print_vector(vec);

  X.fill_vector(vec);
  print_vector(vec);

  X.fill_range(vec, 10, 20);
  print_vector(vec);

  std::generate(vec.begin(), vec.end(), X.f_gen);
  print_vector(vec);
}
#endif

void print_vector(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    std::cout << "\r[ ";
    std::cout << std::string(i, '\t');
    std::cout << vec[i] << " ";
  }
  std::cout << "]" << std::endl;
}