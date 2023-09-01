#include "draw.hpp"

// draw_all definition
void draw_all() {
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

  // definition of graph
  void graph(std::vector<Population> population_state_) { draw_all(); }

}  // namespace pf
