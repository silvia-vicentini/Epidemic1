#ifndef EPIDEMIC_HPP  // verifica tutti i const e i &&
#define EPIDEMIC_HPP

#include <cmath>  //R0 del testo è diverso rispetto al rapporto beta/gamma? perchè altrimenti i parametri sono meno di 5
#include <vector>

struct Population {  // è giusta questa divisione tra struct e class o
                     // vanno scambiati? Devo inserire un'altra class?
  int S{};
  int I{};
  int R{};
};

class Epidemic {
 private:
  double const beta_;  // devono essere const? devo usare & o * ?
  double const gamma_;
  std::vector<Population> population_state_;

  Population solve(Population const &) const;

 public:
  Epidemic(double const,
           double const);  // è giusto const qui? devo mettere anche la
                           // popolazione iniziale tra le variabili?

  std::size_t size() const;  // non so se serva tato che deve essere uguale a t

  void push_back(Population &);  // per inserire ogni step
                                 // dell'evoluzione della pandemia

  void evolve(Population &,
              int const);  // questa funzione consente di calcolare l'evoluzione
                           // della popolazione ad un istante di tempo t

  std::vector<Population> const &state()
      const;  // questa funzione restituisce lo stato della popolazione
};

#endif
