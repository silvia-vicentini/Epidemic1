#include "epidemic.hpp"

namespace pf {

// constructor

Epidemic::Epidemic(const double beta, const double gamma,
                   const Population<double>& initial_population, const int T)
    : beta_(beta),
      gamma_(gamma),
      initial_population_(initial_population),
      T_(T),
      N_(initial_population_.S + initial_population_.I + initial_population_.R),
      critic_level_(0.6),
      lockdown_duration_(14) {
  ////////////////////////////////////////////////////////////////////////////////
  // Asserts
  ////////////////////////////////////////////////////////////////////////////////
  assert(
      (beta_ >= 0. && beta_ <= 1.)
          ? true
          : (std::cerr << "Error: \u03B2 must be between 0 and 1.\n", false));
  assert(
      (gamma_ >= 0. && gamma_ <= 1.)
          ? true
          : (std::cerr << "Error: \u03B3 must be between 0 and 1.\n", false));
  assert((beta_ / gamma_ > 1)
             ? true
             : (std::cerr << "Error: \u03B2/\u03B3 must be greater than 1.\n",
                false));
  assert((initial_population_.S >= 0)
             ? true
             : (std::cerr << "Error: the initial number of susceptible people "
                             "must be greater than or equal to 0.\n",
                false));
  assert((initial_population_.I >= 0)
             ? true
             : (std::cerr << "Error: the initial number of infected people "
                             "must be greater than or equal to 0.\n",
                false));
  assert((initial_population_.R >= 0)
             ? true
             : (std::cerr << "Error: the initial number of removed people "
                             "must be greater than or equal to 0.\n",
                false));
  assert((T_ >= 0) ? true
                   : (std::cerr << "Error: the epidemic can't last a negative "
                                   "number of days.\n",
                      false));

  ////////////////////////////////////////////////////////////////////////////////
  // Creation of the simulation_double_ vector (storage of the state of the
  // epidemic in double). If the number of infectious is lower than the 60%
  // (critic_level_) of the population N_, the epidemic spreads according to the
  // rules expressed by the calculate function. If the number of infectious is
  // greather than the 60% of N_ a lockdown occurs. The lockdown lasts for 14
  // days.
  ////////////////////////////////////////////////////////////////////////////////
  simulation_double_.push_back(initial_population_);
  int i = 0;
  while (i < T_) {
    if (simulation_double_[i].I < critic_level_ * N_) {
      Population<double> next_state = calculate(simulation_double_[i]);
      simulation_double_.push_back(next_state);
      ++i;
    } else {
      int lockdownDays = std::min(T_ - i, lockdown_duration_);
      for (int a = 0; a < lockdownDays; ++a) {
        Population<double> next_state = lockdown(simulation_double_[i]);
        simulation_double_.push_back(next_state);
        ++i;
      }
    }
  }
}

// private methods

Population<double> Epidemic::calculate(
    const Population<double>& prev_state) const {
  Population<double> next_state;
  next_state.S = prev_state.S - beta_ * prev_state.S * prev_state.I / N_;
  next_state.I = prev_state.I + beta_ * prev_state.S * prev_state.I / N_ -
                 gamma_ * prev_state.I;
  next_state.R = prev_state.R + gamma_ * prev_state.I;
  return next_state;
}

Population<double> Epidemic::lockdown(
    const Population<double>& prev_state) const {
  Population<double> next_state;
  next_state.S = prev_state.S;
  next_state.R = prev_state.R + gamma_ * prev_state.I;
  next_state.I = N_ - prev_state.S - next_state.R;
  return next_state;
}

Population<int> Epidemic::round(const Population<double>& double_state) const {
  Population<int> int_state;
  int_state.S = std::round(double_state.S);
  int_state.I = std::round(double_state.I);
  int_state.R = std::round(double_state.R);
  return int_state;
}

Population<int> Epidemic::keepTotalConstant(
    const Population<int>& population_state) const {
  Population<int> modified_state = population_state;
  int tot = modified_state.S + modified_state.I + modified_state.R;
  if (tot != N_) {
    int diff = tot - N_;
    if (diff > 0) {
      modified_state.R -= diff;
    } else {
      modified_state.I -= diff;
    }
  }
  return modified_state;
}

// public methods

std::vector<Population<int> > Epidemic::evolution() const {
  std::vector<Population<int> > simulation_int_;
  for (const auto& population_state_double : simulation_double_) {
    simulation_int_.push_back(
        keepTotalConstant(round(population_state_double)));
  }
  return simulation_int_;
}

std::vector<Population<double> > Epidemic::get_simulation_double() const {
  return simulation_double_;
}

int Epidemic::getN() const { return N_; }
int Epidemic::getT() const { return T_; }

void Epidemic::print_results() const {
  std::cout << "Report for each of the stored states of population:\n";
  std::vector<pf::Population<int> > population_state_ = evolution();
  std::cout << std::setw(12) << std::left << "Day " << std::setw(12)
            << std::left << "S " << std::setw(12) << std::left << "I "
            << std::setw(6) << std::left << "R " << '\n';
  int i{0};
  for (const auto& state : population_state_) {
    std::cout << std::setw(12) << std::left << i << std::setw(12) << std::left
              << state.S << std::setw(12) << std::left << state.I
              << std::setw(6) << std::left << state.R << '\n';
    ++i;
  }
}
}  // namespace pf
