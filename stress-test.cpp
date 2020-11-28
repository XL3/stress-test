#include <random>
#include <functional>
#include <iostream>

#include "./stress-test.hpp"

namespace Stress {
  template <typename Ty_dst>
  std::random_device discrete_parameter<Ty_dst>::rd{};
  template <typename Ty_dst>
  std::mt19937 discrete_parameter<Ty_dst>::mersenneEngine { rd() };

  template <typename Ty_dst>
  discrete_parameter<Ty_dst>::discrete_parameter(Ty_dst _min, Ty_dst _max) : distribution(_min, _max) { 
    min = _min, max = _max;
    f_gen = [this]() {
      return distribution(mersenneEngine);
    };
  }

  template <typename Ty_dst>
  discrete_parameter<Ty_dst>::operator Ty_dst() const { return distribution(mersenneEngine); }

  template <typename Ty_dst>
  const Ty_dst discrete_parameter<Ty_dst>::generate() const {
    return distribution(mersenneEngine);
  }

  template <typename Ty_dst>
  template <typename Ty_it>
  void discrete_parameter<Ty_dst>::fill_range(Ty_it _begin, Ty_it _end) {
    std::generate(_begin, _end, f_gen);
  }

  template <typename Ty_dst>
  void discrete_parameter<Ty_dst>::fill_range(std::vector<Ty_dst> &_vec, int _L, int _R) {
    std::generate(_vec.begin() + _L, _vec.begin() + _R, f_gen);
  }

  template <typename Ty_dst>
  void discrete_parameter<Ty_dst>::fill_vector(std::vector<Ty_dst> &_vec) {
    std::generate(_vec.begin(), _vec.end(), f_gen);
  }
}

void print_vector(std::vector<int> _vec) {
  for (auto &x: _vec) std::printf("%d ", x);
  std::printf("\n");
}

int main() {
  std::vector<int> vec(20);
  Stress::discrete_parameter<int> N(1, 6);

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