#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
// #include <vector>

#include "../../epidemic/epidemic.hpp"

namespace pf {

class Key {
 private:
  sf::RenderWindow& window_;
  int margin_;
  int dot_radius_;
  sf::Font font_;

 public:
  Key(sf::RenderWindow&);
  std::vector<sf::VertexArray> key_lines();
  std::vector<sf::CircleShape> key_dots();
  std::vector<sf::Text> key_description();
};
}  // namespace pf
#endif