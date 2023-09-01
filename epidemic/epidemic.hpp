#ifndef EPIDEMIC_HPP  // verifica tutti i const e i &&
#define EPIDEMIC_HPP

#include <vector>

// bisogna modificare i throw con gli assert
// bisogna confermare o correggere tutti i const e &
// bisogna scrivere i commenti dove necessario

namespace pf {

// number of people in each group in which the population is divided
struct Population {
  int S;
  int I;
  int R;
};

class Epidemic {
 private:
  double const beta_;
  double const gamma_;
  std::vector<Population> population_state_;

 public:
  Epidemic(double const, double const);

  // to calculate how S, I and R change during a day
  Population solve(Population const, int const);

  // to make the correct approximation from double to int
  Population approx(Population, int const);

  // to calculate the correct number of S, I and R in a day using the correct
  // approximation method
  Population correct(Population, int const);

  // to calculate how S, I and R change during a lockdown
  Population lockdown(Population, int const);  // aggiungere alla relazione!

  // to calculate how S, I and R change when people get vaccines
  Population vaccine(Population, int const);

  // to record the development of the epidemic
  std::vector<Population> evolve(Population, int const);
};
}  // namespace pf

#endif
