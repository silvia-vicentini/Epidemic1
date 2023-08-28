
#include <algorithm>  //serve?
#include <fstream>    // per leggere da file in input
#include <iomanip>    //serve?
#include <iostream>
#include <limits>  //serve?

#include "epidemic.hpp"

int main() {
  try {
    char cmd;

    std::string filename;

    std::cout << "Valid commands: \n"
              << "- read data from a sample file [f FILE_NAME]\n"
              << "- read data from standard input [i FILE_NAME]\n"
              << "- read data from command line [l FILE_NAME]\n"
              << "- print graphic to screen [g POPULATION_TREND]\n";

    while (std::cin >> cmd) {
      // prende da command line

      if (cmd == 'l') {
        Epidemic epidemic{0.8, 0.4};
        Population initial_population{997, 3, 0};
        int const time{7};
        epidemic.evolve(initial_population, time);
        auto population_state_{epidemic.state()};

        std::cout << "Report for each of the stored states of population:\n";
        std::cout << "  S  : I : R :\n";
        for (int i{0}; i <= time; ++i) {
          std::cout << population_state_[i].S << "  " << population_state_[i].I
                    << "  " << population_state_[i].R << '\n';
        }
