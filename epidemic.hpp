#ifndef EPIDEMIC_HPP  // verifica tutti i const e i &&
#define EPIDEMIC_HPP

#include <cmath>  
#include <vector>

struct Population {  // è sensata questa divisione tra struct e class?
  int S{};
  int I{};
  int R{};
};

class Epidemic { //verifica tutti i const
 private:
  double const beta_;
  double const gamma_;
  std::vector<Population> population_state_;

  Population solve(Population const &) const;

 public:
  Epidemic(double const,
           double const);

  std::size_t size() const;  // <-- non so se serva dato che deve essere uguale a t

  void push_back(Population &);  // serve? serve il &?

  void evolve(Population &,
              int const);  // questa funzione consente di calcolare l'evoluzione
                           // della popolazione ad un istante di tempo t

  std::vector<Population> const &state()
      const;  // questa funzione restituisce lo stato della popolazione
};

#endif
