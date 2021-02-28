// cl .\stress-test.cpp /std:c++17 /Fe:se User32.lib Gdi32.lib

#include <iostream>

#include "./stress-test.hpp"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include "winuser.h"

void print_vector(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    std::cout << "\r[ ";
    std::cout << std::string(i, '\t');
    std::cout << vec[i] << " ";
  }
  std::cout << "]" << std::endl;
}

int main() {
  std::vector<int> vec(20);
  Stress::discrete_parameter<int> N(1, 6);

  bool key_down = 0;
  while (false) {
    if (GetKeyState(VK_SPACE) & (1 << 15)) {
      if (key_down) continue;
      key_down = true;
      std::cout << "\r" << (int)N;
    }
    else
      key_down = false;
  }

  for (auto &x: vec) x = N;
  print_vector(vec);

  N.fill_vector(vec);
  print_vector(vec);

  N.fill_range(vec, 10, 20);
  print_vector(vec);

  std::generate(vec.begin(), vec.end(), N.f_gen);
  print_vector(vec);

  return 0;
}