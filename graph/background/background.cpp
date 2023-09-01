#include "background.hpp"

namespace pf {

// draw_background definition
void draw_background() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Epidemic evolution");
}

// set_dimensions definition
void set_dimensions() {
  sf::Vector2f graphSize(600.f, 400.f);
  sf::Vector2f graphPosition(100.f, 100.f);
}

}  // namespace pf
