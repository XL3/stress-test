#pragma once
#include <functional>
#include <random>
#include <tuple>

/**
* @param expression Expression to apply in terms of "el"
* @param tuple Tuple to apply the foreach to
*/
#define __TUPLE_FOREACH(expression, tuple) \
  {                                        \
    std::apply(                            \
      [](auto &&...el) {                   \
        ((expression), ...);               \
      },                                   \
      tuple);                              \
  }

/**
 * @todo[XL3]: Add specialization for vector types
 */
namespace Stress {
template <typename Distribution_t = int>
class Discrete_Parameter {
  inline static std::random_device rd{};
  inline static std::mt19937 mersenneEngine{rd()};

  Distribution_t min;
  Distribution_t max;
  std::uniform_int_distribution<Distribution_t> distribution;

public:
  Distribution_t current_value;
  std::function<Distribution_t()> f_gen;

  Discrete_Parameter() : distribution() {
    f_gen = [this]() { return distribution(mersenneEngine); };
  }

  Discrete_Parameter(Distribution_t _min, Distribution_t _max) : distribution(_min, _max), min(_min), max(_max) {
    generate();
    f_gen = [this]() { return distribution(mersenneEngine); };
  }

  operator Distribution_t() {
    return current_value;
  }

  Distribution_t generate() {
    return current_value = distribution(mersenneEngine);
  }

  template <typename Iterator_t>
  void fill_range(Iterator_t begin, Iterator_t end) {
    std::generate(begin, end, f_gen);
    Iterator_t last = end - 1;
    current_value = *last;
  }

  void fill_range(std::vector<Distribution_t> &vec, int left, int right) {
    std::generate(vec.begin() + left, vec.begin() + right, f_gen);
    auto last = vec.begin() + (right - 1);
    current_value = *last;
  }

  void fill_vector(std::vector<Distribution_t> &vec) {
    std::generate(vec.begin(), vec.end(), f_gen);
    current_value = vec.back();
  }
};

template <typename Impl_A, typename Impl_B, typename Ret, typename... Params>
class Test {
  Impl_A implementation_A;
  Impl_B implementation_B;
  Ret return_A, return_B;
  std::tuple<Params...> parameters;

  bool run_trial() {
    __TUPLE_FOREACH(el.generate(), parameters);

    return_A = std::apply(implementation_A, parameters);
    return_B = std::apply(implementation_B, parameters);

    return return_A != return_B;
  }

  void log_fault() {
    std::cout << "(";

    /**
     * @todo Replace this with a smarter way to print parameters, taking vectors into consideration
     */
    __TUPLE_FOREACH((std::cout << el.current_value << ", "), parameters);

    std::cout << "\b\b)" << std::endl
              << "-> " << return_A << std::endl
              << "-> " << return_B << std::endl;
  }

public:
  Test(Impl_A impl_A, Impl_B impl_B, Ret default_value, Params &...params) : implementation_A(impl_A), implementation_B(impl_B), return_A(), return_B() {
    parameters = std::make_tuple(params...);
  }

  void run() {
    const int scale = (int)1e6;
    int trials = 0;
    bool fault = false;
    while (!fault) {
      if (!(trials % scale))
        std::cout << "\r" << trials / scale << "M trials ";

      fault = run_trial();
      trials++;
    }
    log_fault();
  }
};
}  // namespace Stress