#ifndef EPIDEMIC_HPP  // verifica tutti i const e i &&
#define EPIDEMIC_HPP

#include <cmath>
#include <vector>

// bisogna modificare i throw con gli assert
// bisogna aggiungere un namespace?

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

  Population solve(Population const, int const) const;

 public:
  Epidemic(double const, double const);

  std::vector<Population> evolve(
      Population,
      int const);  // questa funzione consente di calcolare l'evoluzione
                   // della popolazione ad un istante di tempo t

  /*std::vector<Population> const &state()
      const;  // questa funzione restituisce lo stato della popolazione*/
};

#endif
