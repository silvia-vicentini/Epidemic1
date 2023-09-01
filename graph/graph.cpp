#include "graph.hpp"

#include <stdexcept>
#include <vector>

namespace pf {

void graph(std::vector<Population> population_state_) {
  // to create the backgrownd
  sf::RenderWindow window(sf::VideoMode(800, 600), "Epidemic evolution");

  // to create the x axis
  sf::RectangleShape xAxis(sf::Vector2f(window.getSize().x, 2.f));
  xAxis.setPosition(0.f, window.getSize().y / 2);
  xAxis.setFillColor(sf::Color::Black);

  // to create the y axis
  sf::RectangleShape yAxis(sf::Vector2f(2.f, window.getSize().y));
  yAxis.setPosition(window.getSize().x / 2, 0.f);
  yAxis.setFillColor(sf::Color::Black);

  // to set the axis titles
  sf::Font font;
  sf::Text xAxisName("Days", font, 20);
  sf::Text yAxisName("Number of people", font, 20);
  xAxisName.setPosition(window.getSize().x - 100, window.getSize().y - 40);
  yAxisName.setPosition(20, 20);

  // to set the graph dimensions
  sf::Vector2f graphSize(600.f, 400.f);
  sf::Vector2f graphPosition(100.f, 100.f);

  // to set the cleats on x and y axis
  float maxXValue = population_state_.size();
  float maxYValue =
      population_state_[0].S + population_state_[0].I + population_state_[0].R;

  for (float x = 0; x <= maxXValue; x += 2.f)  // il valore 2.f è a caso
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

  // to create the numbers to insert on axis
  std::vector<sf::Text> xTicks;
  std::vector<sf::Text> yTicks;
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

  // to create the curves
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

  // to draw the graph
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color::White);

    window.draw(xAxis);
    window.draw(yAxis);
    window.draw(xAxisName);
    window.draw(yAxisName);
    for (const sf::Text& tick : xTicks) {
      window.draw(tick);
    }
    for (const sf::Text& tick : yTicks) {
      window.draw(tick);
    }
    window.draw(SusceptibleCurve);
    window.draw(InfectedCurve);
    window.draw(RecoveryCurve);
    window.display();
  }
}

}  // namespace pf
