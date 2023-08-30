

#include <algorithm>  //serve?
#include <fstream>    // per leggere da file in input
#include <iomanip>    //serve?
#include <iostream>
#include <limits>  //serve?

#include "epidemic.hpp"

namespace pf {
struct Reading {  // va messo qui o nell'header file
  double beta{}, gamma{};
  int S{}, I{}, R{};
  int day{};
};

int main() {
  std::cout << "Valid commands: \n"
            << "- read data from command line [l]\n"
            << "- read data from standard input [i]\n"
            << "- read data from a sample file [f FILE_NAME]\n"
            << "- quit [q]\n";
  char cmd;
  while (std::cin >> cmd) {
    // takes the parameters from command line, beta = 0.8, gamma = 0.4, S =
    // 997, I = 3, R = 0, day = 40.
    if (cmd == 'l') {
      Epidemic epidemic{0.8, 0.4};
      Population initial_population{997, 3, 0};
      int const day{40};
      auto population_state_{epidemic.evolve(initial_population, day)};

      std::cout << "Report for each of the stored states of population:\n";
      std::cout << "Day  S    I   R \n";
      for (int i{0}; i <= day; ++i) {
        std::cout << i << population_state_[i].S << "  "
                  << population_state_[i].I << "  " << population_state_[i].R
                  << '\n';
      }
      std::cout << "To print che graphic to screen use command [g]\n";
      std::cin >> cmd;
      if (cmd == 'g') {
        epidemic.graph(day, population_state_);
      } else {
        std::cout << "To run che program again press one of the commands "
                     "above, otherwise press q\n";
      }
    }

    // lettura parametri da standard input.

    if (cmd == 'i') {  // come si mettono i const?
      std::cout << "Please write epidemic's parameter beta and gamma:\n";
      double beta{}, gamma{};
      std::cin >> beta >> gamma;
      std::cout << "Please write initial population's groups S, I, R:\n";
      int S{}, I{}, R{};
      std::cin >> S >> I >> R;
      std::cout << "Please write the duration of the epidemic in days:\n";
      int day{};
      std::cin >> day;
      Epidemic epidemic{beta, gamma};
      Population initial_population{S, I, R};
      auto population_state_{epidemic.evolve(initial_population, day)};

      std::cout << "Report for each of the stored states of population:\n";
      std::cout << "Day  S    I   R \n";
      for (int i{0}; i <= day; ++i) {
        std::cout << i << population_state_[i].S << "  "
                  << population_state_[i].I << "  " << population_state_[i].R
                  << '\n';
      }
      std::cout << "To print che graphic to screen use command [g]\n";
      std::cin >> cmd;
      if (cmd == 'g') {
        epidemic.graph(day,
                       population_state_);  // funzione ancora da definire
      } else {
        std::cout << "To run che program again press one of the commands "
                     "above, otherwise press q\n";
      }
    }

    // lettura dei parametri da file dove compaiono nel seguente ordine:
    // beta, gamma, S, I, R, day.

    std::string filename;
    if (cmd == 'f' && std::cin >> filename) {
      std::ifstream infile{filename};
      if (!infile) {
        throw std::runtime_error{"Impossible to open file!"};  // usa assert
      } else {                                                 // è necessario?
        double beta_, gamma_;
        int S_, I_, R_;
        int day_;
        Reading parameters{};  // uso una struct e non un vett perchè alcuni
                               // elementi sono int altri double
        while (infile >> beta_ >> gamma_ >> S_ >> I_ >> R_ >> day_) {
          parameters.beta = beta_;
          parameters.gamma = gamma_;
          parameters.S = S_;
          parameters.I = I_;
          parameters.R = R_;
          parameters.day = day_;  // si può scrivere in maniera più rapida?
        }
        std::cout << "Input file read successfully" << '\n';  // lo mettiamo?
        Epidemic epidemic{parameters.beta, parameters.gamma};
        Population initial_population{parameters.S, parameters.I, parameters.R};
        auto population_state_{
            epidemic.evolve(initial_population, parameters.day)};

        std::cout << "Report for each of the stored states of population:\n";
        std::cout << "Day  S    I   R \n";
        for (int i{0}; i <= parameters.day; ++i) {
          std::cout << i << population_state_[i].S << "  "
                    << population_state_[i].I << "  " << population_state_[i].R
                    << '\n';
        }
        std::cout << "To print che graphic to screen use command [g]\n";
        std::cin >> cmd;
        if (cmd == 'g') {
          epidemic.graph(parameters.day,
                         population_state_);  // funzione ancora da definire
        } else {
          std::cout << "To run che program again press one of the commands "
                       "above, otherwise press q\n";
        }
      }
    }

    /*
    // scrivere risultati su documento in output, non è richiesto di metterlo,
    alla peggio ci lavoriamo alla fine

    else if (cmd == 'o') {
     std::ofstream outfile{"results.txt"};

     if (!outfile) {
       throw std::runday_error{"Impossible to open file!"};
     }
     outfile << "- Read data:" << data.size() << '\n';
     const auto stat = data.statistics();
     outfile << "- mean: " << stat.mean << '\n'
             << "- sigma: " << stat.sigma << '\n'
             << "- mean error: " << stat.mean_err << '\n'
             << "- median: " << stat.median << '\n';

     std::cout << "Output file written successfully" << '\n';
    }*/

    // chiudere il programma
    else if (cmd == 'q') {
      return EXIT_SUCCESS;
    } else {  // studia quest algoritmi, cosa vogliono dire? servono?
      std::cout << "Bad format, insert a new command\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
}  // namespace pf
