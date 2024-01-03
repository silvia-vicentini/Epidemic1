#ifndef CURVE_HPP
#define CURVE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

#include "../../epidemic/epidemic.hpp"

namespace pf {

class Curve {
 private:
  Epidemic epidemic_;
  std::vector<Population<int>> population_state_;
  sf::RenderWindow& window_;
  long int T_;
  long int N_;
  float xscale_;
  float yscale_;
  float margin_;
  float dot_radius_;

  std::vector<sf::VertexArray> S_curve();

  std::vector<sf::VertexArray> I_curve();

  std::vector<sf::VertexArray> R_curve();

  std::vector<sf::CircleShape> S_dots();

  std::vector<sf::CircleShape> I_dots();

  std::vector<sf::CircleShape> R_dots();

 public:
Curve(const Epidemic&, sf::RenderWindow&);
  void draw_curve();
};
}  // namespace pf
#endif
