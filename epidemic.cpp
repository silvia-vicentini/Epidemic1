#include "epidemic.hpp"

#include <cmath>
#include <stdexcept>  //per fare i throw
#include <vector>

Epidemic::Epidemic(double const &beta, double const &gamma)
    : beta_{beta}, gamma_{gamma} {
  if (beta_ < 0. || beta_ > 1.) {
    throw std::runtime_error{
        "Epidemic parameter beta must be such that 0 <= beta <= 1"};
  }
  if (gamma_ < 0. || gamma_ > 1.) {
    throw std::runtime_error{
        "Epidemic parameter gamma must be such that 0 <= gamma <= 1"};
  }
}

int Epidemic::solve_S(Population &population_state,  // serve?
                      double const &beta, double const &gamma,
                      int const time) const {
  int const N = population_state.S + population_state.I + population_state.R;
  population_state.S =
      population_state.S - beta * population_state.S * population_state.I / N;

  return population_state.S;
    if (population_state.S < 0.) {throw std::runtime_error { "susceptible must be > 0" } }
}

int Epidemic::solve_I(Population &population_state,  // serve?
                      double const &beta, double const &gamma,
                      int const time) const {
  int const N = population_state.S + population_state.I + population_state.R;
  population_state.I = population_state.I +
                       beta * population_state.S * population_state.I / N -
                       gamma * population_state.I;

  return population_state.I;
    if (population_state.I < 0. ) { throw std::runtime_error { "infected must be > 0" } }
}

int Epidemic::solve_R(Population &population_state,  // serve?
                      double const &beta, double const &gamma,
                      int const time) const {
  int const N = population_state.S + population_state.I + population_state.R;

  population_state.R = population_state.R + gamma * population_state.I;

  return population_state.R;
    if (population_state.R < 0. ) { throw std::runtime_error { "removed must be > 0" } }
}

std::size_t Epidemic::size() const {
  return Epidemic::population_state_.size();
}  // serve?

void Epidemic::push_back(Population &population_state) {
  Epidemic::population_state_.push_back(population_state);
}

void Epidemic::evolve(Population &population_state, double const &beta,
                      double const &gamma, int const time) {
  population_state_.push_back(population_state);

  int const N = population_state.S + population_state.I + population_state.R;
  for (int i{0}; i <= time; ++i) {
    population_state.S = solve_S(population_state, beta, gamma, time);
    population_state.I = solve_I(population_state, beta, gamma, time);
    population_state.R = solve_R(population_state, beta, gamma, time);
    population_state_.push_back(population_state);
  }
    std::round(population_state.S);
    std::round(population_state.I);
    std::round(population_state.R);

    int total = population_state.S + population_state.I + population_state.R
    if (total != N) {int diff = total -N; if (diff > 0) { population_state.R -= diff;} else { population_state.S -= diff;} }
    
}

std::vector<Population> const &Epidemic::state()
    const {  // serve? Come faccio a scrivere il cout?
  return Epidemic::population_state_;
}
