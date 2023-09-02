#include <iostream>
#include <string>

#include "result/result.hpp"

int main() {
  std::cout << "Valid commands: \n"
            << "- read data from command line [l]\n"
            << "- read data from standard input [i]\n"
            << "- read data from a sample file [f FILE_NAME]\n"
            << "- print results on file result.txt [o]\n"
            << "- print the graph of the variables [g]\n"
            << "- quit [q]\n";
  char in;
  while (std::cin >> in) {
    // simulation taking the parameters from command line: beta = 0.8, gamma =
    // 0.4, S = 997, I = 3, R = 0, day = 40.
    if (in == 'l') {
      command_line();
    }

    // reading parameters from standard input
    if (in == 'i') {
      standard_input();
    }

    // reading parameters from file in the order:
    // beta, gamma, S, I, R, day.
    std::string filename;
    if (in == 'f' && std::cin >> filename) {
      infile(filename);
    }

    // close the program
    else if (in == 'q') {
      return EXIT_SUCCESS;
    }

    // other cases
    else {
      std::cout << "Bad format, insert a new command\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}


hello
