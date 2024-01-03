#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../epidemic/epidemic.hpp"

namespace pf {

class Text {
 private:
  sf::Font font_;
  Epidemic epidemic_;
  sf::RenderWindow& window_;

  const float margin_;
  const int x_partition_;
  const int y_partition_;
  const int axis_name_font_;
  const int title_font_;

 public:
  // Constructor
  Text(Epidemic const&, sf::RenderWindow&);

  // Graph's title
  sf::Text set_Title();

  // x axis title
  sf::Text x_axis_name();

  // y axis title
  sf::Text y_axis_name();

  // numbers on the x axis
  std::vector<sf::Text> x_numbers();

  // numbers on the y axis
  std::vector<sf::Text> y_numbers();
};
}  // namespace pf
#endif
