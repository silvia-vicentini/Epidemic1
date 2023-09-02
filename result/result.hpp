#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP
#include <string>
#include <vector>

#include "../epidemic/epidemic.hpp"
#include "../graph/draw.hpp"

namespace pf {

// to print on screen the variables S I R
void output(std::vector<Population>){};

// to print the graph
void outgraph(std::vector<Population>);

// to print on file the results
void outfile(std::vector<Population>);

// to run the program using variables saved on command line
void command_line();

// to run the program using variables saved on command line
void standard_input();

// to run the program using variables saved on a file in the order: beta,
// gamma, S, I, R, days.
void infile(std::string);

}  // namespace pf
#endif
