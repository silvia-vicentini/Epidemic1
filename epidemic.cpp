#include "epidemic.hpp"

#include <cmath>
#include <stdexcept>  //per fare i throw
#include <vector>

Epidemic::Epidemic(double const beta, double const gamma)
    : beta_{beta}, gamma_{gamma} {
  if (beta_ < 0. || beta_ > 1.) {
    throw std::runtime_error{
        "Epidemic parameter beta must be such that 0 <= beta <= 1"};
  }
  if (gamma_ < 0. || gamma_ > 1.) {
    throw std::runtime_error{
        "Epidemic parameter gamma must be such that 0 <= gamma <= 1"};
  }
  if (beta_ <= gamma_) {
    throw std::runtime_error{
        "Epidemic parameter beta must be greather than gamma"};
  }
}

Population Epidemic::solve(Population const &prev_state) const {
  int const N =
      prev_state.S + prev_state.I +
      prev_state
          .R;  // forse è più efficiente se non deve ricalcolare N ad ogni loop?
  double const beta{Epidemic::beta_}; //è giusto scritto così?
  double const gamma{Epidemic::gamma_};
  int const S_i = prev_state.S - beta * prev_state.S * prev_state.I / N;
  int const I_i = prev_state.I + beta * prev_state.S * prev_state.I / N -
                  gamma * prev_state.I;
  int const R_i = prev_state.R + gamma * prev_state.I;

  return Population{S_i, I_i, R_i};
}

void Epidemic::evolve(Population &initial_population, int const time) {
  population_state_.push_back(initial_population);

  auto population_it = Epidemic::population_state_.begin();

  for (int i{1}; i <= time; ++i) {
    *population_it = solve(*population_it);
    population_state_.push_back(*population_it);
  }
}

std::vector<Population> const &Epidemic::state()
    const {  // serve? Come faccio a scrivere il cout?
  return Epidemic::population_state_;
}
