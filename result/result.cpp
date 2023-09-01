#include "../result/result.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../graph/graph.hpp"

namespace pf {

// definition of output function
void output(std::vector<Population> population_state_) {
  std::cout << "Report for each of the stored states of population:\n";
  std::cout << "Day  S    I   R \n";
  for (int i = 0; i <= population_state_.size(); ++i) {
    std::cout << i << population_state_[i].S << "  " << population_state_[i].I
              << "  " << population_state_[i].R << '\n';
  }
}

// definition of outgraph
void outgraph(std::vector<Population> population_state_) {
  char in;
  std::cout << "To print the graphic un the screen use command [g]\n";
  std::cin >> in;
  if (in == 'g') {
    graph(population_state_);
  } else {
    std::cout << "To run che program again press one of the commands above,
        otherwise press[q] \n " ;
  }
}

// definition of outfile function
void outfile(std::vector<Population> population_state_) {
  char in;
  std::cout << "To print the results on file results.txt use command [o]\n";
  std::cin >> in;
  if (in == 'o') {
    std::ofstream outfile{"result.txt"};
    if (!outfile) {
      throw std::runtime_error{"Impossible to open file!"};
    }
    outfile << "Report for each of the stored states of population:\n";
    outfile << "Day  S    I   R \n";
    for (int i = 0; i <= population_state_.size(); ++i) {
      outfile << i << population_state_[i].S << "  " << population_state_[i].I
              << "  " << population_state_[i].R << '\n';
    }
    std::cout << "Output file written successfully" << '\n';
  } else {
    std::cout << "To run che program again press one of the commands above,
        otherwise press[q] \n " ;
  }
}

// definition of command_line function
void command_line() {
  Epidemic epidemic{0.8, 0.4};
  Population initial_population{997, 3, 0};
  int days = 40;
  std::vector<Population> population_state_ =
      epidemic.evolve(initial_population, days);
  output(population_state_);
  outgraph(population_state_);
  outfile(population_state_);
}

// definition of standard_input function
void standard_input() {
  std::cout << "Please write epidemic's parameter beta and gamma:\n";
  double beta;
  double gamma;
  std::cin >> beta >> gamma;
  std::cout << "Please write initial population's groups S, I, R:\n";
  int S;
  int I;
  int R;
  std::cin >> S >> I >> R;
  std::cout << "Please write the duration of the epidemic in days:\n";
  int days;
  std::cin >> days;
  Epidemic epidemic(beta, gamma);
  // non sono sicura di avergli attribuito i valori che voglio --> chiedi a
  // Luca
  Population initial_population{S, I, R};
  std::vector<Population> population_state_ =
      epidemic.evolve(initial_population, days);
  output(population_state_);
  outgraph(population_state_);
  outfile(population_state_);
}

// definition of infile function
void infile(std::string filename) {
  std::ifstream infile;
  infile.open(filename);
  if (!infile) {
    throw std::runtime_error{"Impossible to open file!"};
  }
  double beta_;
  double gamma_;
  int S_;
  int I_;
  int R_;
  int days_;
  double beta{};
  double gamma{};
  Epidemic epidemic(beta, gamma);
  Population initial_population;
  int days{};
  while (infile >> beta_ >> gamma_ >> S_ >> I_ >> R_ >> days_) {
    beta = beta_;
    gamma = gamma_;
    initial_population.S = S_;
    initial_population.I = I_;
    initial_population.R = R_;
    days = days_;
  }
  auto population_state_{epidemic.evolve(initial_population, days)};
  output(population_state_);
  outgraph(population_state_);
  outfile(population_state_);
}

}  // namespace pf
