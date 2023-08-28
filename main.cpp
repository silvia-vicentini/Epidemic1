
#include <algorithm>  //serve?
#include <fstream>    // per leggere da file in input
#include <iomanip>    //serve?
#include <iostream>
#include <limits>  //serve?

#include "epidemic.hpp"

struct Reading {  // va messo qui o nell'header file
  double beta{}, gamma{};
  int S{}, I{}, R{};
  int time{};
};

int main() {
  std::cout << "Valid commands: \n"
            << "- read data from a sample file [f FILE_NAME]\n"
            << "- read data from standard input [i]\n"
            << "- read data from command line [l]\n"
            << "- print graphic to screen [g]\n"
            << "- quit [q]\n";
  char cmd;
  while (std::cin >> cmd) {
    // prende da command line

    if (cmd == 'l') {
      Epidemic epidemic{0.8, 0.4};
      Population initial_population{997, 3, 0};
      int const time{7};
      auto population_state_{epidemic.evolve(initial_population, time)};

      std::cout << "Report for each of the stored states of population:\n";
      std::cout << "S    I   R \n";
      for (int i{0}; i <= time; ++i) {
        std::cout << population_state_[i].S << "  " << population_state_[i].I
                  << "  " << population_state_[i].R << '\n';
      }
    }

    // lettura parametri da standard input

    if (cmd == 'i') {  // come si mettono i const?
      std::cout << "Please write epidemic's parameter beta and gamma:\n";
      double beta{}, gamma{};
      std::cin >> beta >> gamma;
      std::cout << "Please write initial population's groups S, I, R:\n";
      int S{}, I{}, R{};
      std::cin >> S >> I >> R;
      std::cout << "Please write the duration of the epidemic in days:\n";
      int time{};
      std::cin >> time;
      Epidemic epidemic{beta, gamma};
      Population initial_population{S, I, R};
      auto population_state_{epidemic.evolve(initial_population, time)};

      std::cout << "Report for each of the stored states of population:\n";
      std::cout << "S    I   R \n";
      for (int i{0}; i <= time; ++i) {
        std::cout << population_state_[i].S << "  " << population_state_[i].I
                  << "  " << population_state_[i].R << '\n';
      }
    }

    // lettura dei parametri da file dove compaiono nel seguente ordine:
    // beta, gamma, S, I, R, time

    std::string filename;
    if (cmd == 'f' && std::cin >> filename) {
      std::ifstream infile{filename};
      if (!infile) {
        throw std::runtime_error{"Impossible to open file!"};  // usa assert
      }
      double beta_, gamma_;
      int S_, I_, R_;
      int time_;
      Reading parameters{};  // uso una struct e non un vett perchè alcuni
                             // elementi sono int altri double
      while (infile >> beta_ >> gamma_ >> S_ >> I_ >> R_ >>
             time_) {  // bisogna riscriverla questa parte?
        if (beta_ < 0. || beta_ > 1.)
          throw std::runtime_error{
              "Epidemic parameter beta must be such that 0 <= beta <= 1"};
        if (gamma_ < 0. || gamma_ > 1.) {
          throw std::runtime_error{
              "Epidemic parameter gamma must be such that 0 <= gamma <= 1"};
        }
        if (beta_ / gamma_ <= 1) {
          throw std::runtime_error{
              "Epidemic parameter beta must be greather than gamma"};
        }
        parameters.beta = beta_;
        parameters.gamma = gamma_;
        parameters.S = S_;
        parameters.I = I_;
        parameters.R = R_;
        parameters.time = time_;  // si può scrivere in maniera più rapida?
      }
      std::cout << "Input file read successfully" << '\n';  // lo mettiamo?
      Epidemic epidemic{parameters.beta, parameters.gamma};
      Population initial_population{parameters.S, parameters.I, parameters.R};
      auto population_state_{
          epidemic.evolve(initial_population, parameters.time)};

      std::cout << "Report for each of the stored states of population:\n";
      std::cout << "S    I   R \n";
      for (int i{0}; i <= parameters.time; ++i) {
        std::cout << population_state_[i].S << "  " << population_state_[i].I
                  << "  " << population_state_[i].R << '\n';
      }
    }

    /*
    // scrivere risultati su documento in output e non è richiesto di metterlo,
    alla peggio ci lavoriamo alla fine

    else if (cmd == 'o') {
     std::ofstream outfile{"results.txt"};

     if (!outfile) {
       throw std::runtime_error{"Impossible to open file!"};
     }
     outfile << "- Read data:" << data.size() << '\n';
     const auto stat = data.statistics();
     outfile << "- mean: " << stat.mean << '\n'
             << "- sigma: " << stat.sigma << '\n'
             << "- mean error: " << stat.mean_err << '\n'
             << "- median: " << stat.median << '\n';

     std::cout << "Output file written successfully" << '\n';
    }*/

    // disegnare il grafico
    /*else if (cmd == 'g') {
      epidemic.graphic();
    }*/

    // chiudere il programma
    else if (cmd == 'q') {
      return EXIT_SUCCESS;
    } else {
      std::cout << "Bad format, insert a new command\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
