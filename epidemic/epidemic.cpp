#include "epidemic.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>
// devo definire vaccine
namespace pf {

// constructor initialization
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
  if (beta_ / gamma_ <= 1) {
    throw std::runtime_error{
        "Epidemic parameter beta must be greather than gamma"};
  }
}

// definition of solve function
Population Epidemic::solve(Population const prev_state, int const N) {
  double const beta{Epidemic::beta_};
  double const gamma{Epidemic::gamma_};
  int S_i = std::round(prev_state.S - beta * prev_state.S * prev_state.I / N);
  int I_i = std::round(prev_state.I + beta * prev_state.S * prev_state.I / N -
                       gamma * prev_state.I);
  int R_i = std::round(prev_state.R + gamma * prev_state.I);

  if (S_i < 0 || I_i < 0 || R_i < 0) {
    throw std::runtime_error{"All the parameters must be > 0"};
  }

  return Population{S_i, I_i, R_i};
}

// definition of approx function
Population Epidemic::approx(Population population_state, int const N) {
  int tot = population_state.S + population_state.I + population_state.R;
  if (tot != N) {
    int diff = tot - N;
    if (diff > 0) {
      population_state.R -= diff;
    } else {
      population_state.I -= diff;
    }
  }
  return Population{population_state.S, population_state.I, population_state.R};
}

// definition of correct function
Population Epidemic::correct(Population population_state, int const N) {
  return Population{approx(solve(population_state, N), N)};
}

// definition of lockdown function
Population Epidemic::lockdown(Population prev_state, int const N) {
  double const beta{Epidemic::beta_};
  double const gamma{Epidemic::gamma_};
  int R_i = std::round(prev_state.R + gamma * prev_state.I);
  int I_i = N - prev_state.S - R_i;

  return Population{prev_state.S, I_i, R_i};
}

// se si fanno dei vaccini parte dei sani entra nei R perché diventano immuni
Population Epidemic::vaccine(Population prev_state, int const N) {
  double const beta{Epidemic::beta_};
  double const gamma{Epidemic::gamma_};
  int S_i = std::round(prev_state.S - beta * prev_state.S * prev_state.I / N -
                       0.05 * prev_state.S);
  int R_i =
      std::round(prev_state.R + gamma * prev_state.I + 0.05 * prev_state.S);
  int I_i = N - prev_state.S - R_i;

  return Population{prev_state.S, I_i, R_i};
}

// definition of evolve function
std::vector<Population> Epidemic::evolve(Population initial_population,
                                         int const days) {
  population_state_.push_back(initial_population);

  int const N =
      initial_population.S + initial_population.I + initial_population.R;

  for (int i{0}; i <= days;) {
    if (days < 60) {
      if (population_state_[i].I < 0.6 * N) {
        auto next_state = correct(population_state_[i], N);
        population_state_.push_back(next_state);
        ++i;
      } else {
        if (days - i < 14) {
          for (int a{0}; a < days - i; ++a) {
            auto next_state = lockdown(population_state_[i], N);
            population_state_.push_back(next_state);
          }
        } else {
          for (int a{0}; a < 14; ++a) {
            auto next_state = lockdown(population_state_[i], N);
            population_state_.push_back(next_state);
          }
          i += 14;
        }
      }
    } else {
      auto next_state = vaccine(population_state_[i], N);
      population_state_.push_back(next_state);
    }
  }
  return Epidemic::population_state_;
}

}  // namespace pf
