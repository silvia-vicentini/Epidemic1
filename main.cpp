#include <iostream>
#include <string>

#include "result/result.hpp"

namespace pf {

int main() {
  std::cout << "Valid commands: \n"
            << "- read data from command line [l]\n"
            << "- read data from standard input [i]\n"
            << "- read data from a sample file [f FILE_NAME]\n"
            << "- print results on screen [s]\n"
            << "- print the graph of the variables [g]\n"
            << "- quit [q]\n";
  char in;
  char out;
  while (std::cin >> in) {

    // simulation taking the parameters from command line: beta = 0.8, gamma =
    // 0.4, S = 997, I = 3, R = 0, day = 40.
    if (in == 'l') {
      command_line();

      /////////////////////// scrivi codice

      /*
      std::cout << "To print the graphic to screen use command [g]\n";
      std::cin >> out;
      if (in == 'g') {
        epidemic.graph(day, population_state_);
      } else {
        std::cout << "To run che program again press one of the commands above,
      otherwise press q\n";
      }
      */
    }

    // reading parameters from standard input
    if (in == 'i') {  // come si mettono i const?
      standard_input();
      /*
      std::cout << "To print the graphic to screen use command [g]\n";
            std::cin >> out;
            if (in == 'g') {
              epidemic.graph(day, population_state_);
            } else {
              std::cout << "To run che program again press one of the commands "
                           "above, otherwise press q\n";
            }
      */
    }

    // reading parameters from file in the order:
    // beta, gamma, S, I, R, day.
    std::string filename;
    if (in == 'f' && std::cin >> filename) {
      infile(filename);
      /*
      std::cout << "To print the graphic to screen use command [g]\n";
      std::cin >> in;
      /*if (in == 'g') {
        epidemic.graph(parameters.day,
                       population_state_);  // funzione ancora da definire
      } else {
        std::cout << "To run che program again press one of the commands "
                     "above, otherwise press q\n";
      }*/
    }

    /* // write results on results.txt file
        else if (in == 'o') {
          outfile();
        }*/

    // close the program
    else if (in == 'q') {
      return EXIT_SUCCESS;
    } else {
      std::cout << "Bad format, insert a new command\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
}  // namespace pf
