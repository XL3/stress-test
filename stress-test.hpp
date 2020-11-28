#include <random>
#include <functional>

/**
 * @todo[XL3]: Add a wrapper that does trials for you
 *             Variadic template arguments of parameters
 *
 * @todo[XL3]: Add specialization for vector types
 */
namespace Stress {
  template <typename Ty_dst>
  class discrete_parameter {
    static std::random_device rd;
    static std::mt19937 mersenneEngine;

    Ty_dst min;
    Ty_dst max;
    std::uniform_int_distribution<Ty_dst> distribution;

  public:
    discrete_parameter(Ty_dst _min, Ty_dst _max);
    operator Ty_dst() const;

    const Ty_dst generate() const;
    std::function<Ty_dst()> f_gen;

    template <typename Ty_itr>
    void fill_range(Ty_itr _begin, Ty_itr _end);

    void fill_range(std::vector<Ty_dst> &_vec, int _L, int _R);
    void fill_vector(std::vector<Ty_dst> &_vec);
  };
}
