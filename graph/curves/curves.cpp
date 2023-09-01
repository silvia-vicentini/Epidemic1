#include "curves.hpp"

#include <vector>

namespace pf {

// to create the curves
void make_curves(std::vector<Population> population_state_) {
  sf::VertexArray SusceptibleCurve(sf::LineStrip);
  sf::VertexArray InfectedCurve(sf::LineStrip);
  sf::VertexArray RecoveryCurve(sf::LineStrip);
  for (int i{0}; i <= population_state_.size(); ++i) {
    int x = i;
    int yS = population_state_[i].S;
    int yI = population_state_[i].I;
    int yR = population_state_[i].R;
    SusceptibleCurve.append(sf::Vertex(
        sf::Vector2f(
            graphPosition.x + (x / maxXValue) * graphSize.x,
            graphPosition.y + graphSize.y - (yS / maxYValue) * graphSize.y),
        sf::Color::Blue));
    InfectedCurve.append(sf::Vertex(
        sf::Vector2f(
            graphPosition.x + (x / maxXValue) * graphSize.x,
            graphPosition.y + graphSize.y - (yI / maxYValue) * graphSize.y),
        sf::Color::Red));
    RecoveryCurve.append(sf::Vertex(
        sf::Vector2f(
            graphPosition.x + (x / maxXValue) * graphSize.x,
            graphPosition.y + graphSize.y - (yR / maxYValue) * graphSize.y),
        sf::Color::Green));
  }
}

}  // namespace pf
