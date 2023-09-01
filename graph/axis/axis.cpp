#include "axis.hpp"

#include <vector>

namespace pf {

// make_x_axis definition
void make_x_axis() {
  sf::RectangleShape xAxis(sf::Vector2f(window.getSize().x, 2.f));
  xAxis.setPosition(0.f, window.getSize().y / 2);
  xAxis.setFillColor(sf::Color::Black);
}

// make_y_axis definition
void make_y_axis() {
  sf::RectangleShape yAxis(sf::Vector2f(2.f, window.getSize().y));
  yAxis.setPosition(window.getSize().x / 2, 0.f);
  yAxis.setFillColor(sf::Color::Black);
}
/////////////////////non sarebbe più furbo fare le tacchette suddividendo l'asse in n parti ugu
ali, a prescindere da quanto lungo esso sia?
// make_cleats definition
void make_cleats(std::vector<Population> population_state_) {
  float maxXValue = population_state_.size();
  float maxYValue =
      population_state_[0].S + population_state_[0].I + population_state_[0].R;

  for (float x = 0; x <= maxXValue; x += 20.f)
  {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(graphPosition.x + (x / maxXValue) * graphSize.x,
                                graphPosition.y + graphSize.y),
                   sf::Color::Black),
        sf::Vertex(sf::Vector2f(graphPosition.x + (x / maxXValue) * graphSize.x,
                                graphPosition.y),
                   sf::Color::Black)};
    window.draw(line, 2, sf::Lines);
  }

  for (float y = 0; y <= maxYValue; y += 20.f) {
    sf::Vertex line[] = {
        sf::Vertex(
            sf::Vector2f(graphPosition.x, graphPosition.y + graphSize.y -
                                              (y / maxYValue) * graphSize.y),
            sf::Color::Black),
        sf::Vertex(sf::Vector2f(graphPosition.x + graphSize.x,
                                graphPosition.y + graphSize.y -
                                    (y / maxYValue) * graphSize.y),
                   sf::Color::Black)};
    window.draw(line, 2, sf::Lines);
  }
}

// make_x_numbers definition
void make_x_numbers() {
  std::vector<sf::Text> xTicks;
  for (float x = 0.f; x <= maxXValue; x += 2.f) {
    sf::Text tickName;
    tickName.setFont(font);
    tickName.setCharacterSize(14);
    tickName.setFillColor(sf::Color::Black);
    tickName.setString(std::to_string(static_cast<int>(x)));
    tickName.setPosition(graphPosition.x + (x / maxXValue) * graphSize.x - 10,
                         graphPosition.y + graphSize.y + 10);
    xTicks.push_back(tickName);
  }
}

// make_y_numbers definition
void make_y_numbers() {
  std::vector<sf::Text> yTicks;
  for (float y = 0.f; y <= maxXValue; y += 20.f) {
    sf::Text tickName;  // o devo mettere sf::text tickLabel ???
    tickName.setFont(font);
    tickName.setCharacterSize(14);
    tickName.setFillColor(sf::Color::Black);
    tickName.setString(std::to_string(static_cast<int>(y)));
    tickName.setPosition(
        graphPosition.x - 30,
        graphPosition.y + graphSize.y - (y / maxYValue) * graphSize.y - 7);
    yTicks.push_back(tickName);
  }
}
}  // namespace pf
