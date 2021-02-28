#include <functional>
#include <random>

/**
 * @todo[XL3]: Add a wrapper that does trials for you
 *             Variadic template arguments of parameters
 *
 * @todo[XL3]: Add specialization for vector types
 */
namespace Stress {
template <typename Ty_dst>
class discrete_parameter {
  inline static std::random_device rd{};
  inline static std::mt19937 mersenneEngine{rd()};

  Ty_dst min;
  Ty_dst max;
  std::uniform_int_distribution<Ty_dst> distribution;

 public:
  std::function<Ty_dst()> f_gen;

  discrete_parameter(Ty_dst _min, Ty_dst _max) : distribution(_min, _max) {
    min = _min, max = _max;
    f_gen = [this]() { return distribution(mersenneEngine); };
  }

  operator Ty_dst() const {
    return distribution(mersenneEngine);
  }

  const Ty_dst generate() const {
    return distribution(mersenneEngine);
  }

  template <typename Ty_itr>
  void fill_range(Ty_itr _begin, Ty_itr _end) {
    std::generate(_begin, _end, f_gen);
  }

  void fill_range(std::vector<Ty_dst> &_vec, int _L, int _R) {
    std::generate(_vec.begin() + _L, _vec.begin() + _R, f_gen);
  }

  void fill_vector(std::vector<Ty_dst> &_vec) {
    std::generate(_vec.begin(), _vec.end(), f_gen);
  }
};
}  // namespace Stress
