#ifndef EPIDEMIC_HPP  // verifica tutti i const e i &&
#define EPIDEMIC_HPP

#include <cmath>
#include <vector>

// bisogna modificare i throw con gli assert
// bisogna confermare o correggere tutti i const e &
// bisogna scrivere i commenti dove necessario

namespace pf {
struct Population {
  int S{};
  int I{};
  int R{};
};

class Epidemic {
 private:
  double const beta_;
  double const gamma_;
  std::vector<Population> population_state_;

  Population solve(Population const, int const);

 public:
  Epidemic(double const, double const);

  Population approx(Population, int const);  // per fare le approssimazioni

  Population correcting(Population,
                        int const);  // per approssimare in base alle nostre
                                     // approssimazioni population_state;

  std::vector<Population> evolve(
      Population const,
      int const);  // questa funzione consente di calcolare l'evoluzione
                   // della popolazione ad un istante di tempo t

  // void graph(int, std::vector<Population>);

  /*std::vector<Population> const &state()
      const;  // questa funzione restituisce lo stato della popolazione*/
};
}  // namespace pf

#endif
