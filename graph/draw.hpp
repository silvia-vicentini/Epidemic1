#ifndef DRAW_HPP
#define DRAW_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../axis/axis.hpp"
#include "../background/background.hpp"
#include "../curves/curves.hpp"

namespace pf {

// to draw the graph
void draw_all();

// to draw a graph from the stored data
void graph(std::vector<Population>);

}  // namespace pf
#endif
