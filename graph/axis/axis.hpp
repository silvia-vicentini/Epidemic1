#ifndef AXIS_HPP
#define AXIS_HPP

#include <SFML/Graphics.hpp>

#include "../../epidemic/epidemic.hpp"

namespace pf {

// to create the horizontal line of the x axis
void make_x_axis();

// to create the horizontal line of the y axis
void make_y_axis();

// to set the cleats on x and y axis
void make_cleats(std::vector<Population>);

// to create the numbers to insert on x axis
void make_x_numbers();

// to create the numbers to insert on y axis
void make_y_numbers();

}  // namespace pf
#endif
