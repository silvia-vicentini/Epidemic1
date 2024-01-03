
#include "draw.hpp"

namespace pf {

Draw::Draw(Epidemic const& epidemic)
    : epidemic_(epidemic),
      window_(sf::VideoMode(1000, 600), ""),
      text_(epidemic, window_),
      grid_(window_),
      curve_(epidemic, window_),
      key_(window_) {}

void Draw::draw_graph() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();
    }
    window_.clear(sf::Color::White);

    sf::Text Title = text_.set_Title();
    window_.draw(Title);

    sf::VertexArray BottomSide = grid_.bottom_side();
    window_.draw(BottomSide);

    sf::VertexArray TopSide = grid_.top_side();
    window_.draw(TopSide);

    sf::VertexArray LeftSide = grid_.left_side();
    window_.draw(LeftSide);

    sf::VertexArray RightSide = grid_.right_side();
    window_.draw(RightSide);

    sf::Text xAxisName = text_.x_axis_name();
    window_.draw(xAxisName);

    sf::Text yAxisName = text_.y_axis_name();
    window_.draw(yAxisName);

    std::vector<sf::VertexArray> HorizontalLines = grid_.horizontal_lines();
    for (const sf::VertexArray& HorizontalLine : HorizontalLines) {
      window_.draw(HorizontalLine);
    }

    std::vector<sf::VertexArray> VerticalLines = grid_.vertical_lines();
    for (const sf::VertexArray& VerticalLine : VerticalLines) {
      window_.draw(VerticalLine);
    }

    std::vector<sf::VertexArray> Susceptible = curve_.S_curve();
    for (const sf::VertexArray& SusceptibleCurve : Susceptible) {
      window_.draw(SusceptibleCurve);
    }

    std::vector<sf::VertexArray> Infected = curve_.I_curve();
    for (const sf::VertexArray& InfectedCurve : Infected) {
      window_.draw(InfectedCurve);
    }

    std::vector<sf::VertexArray> Removed = curve_.R_curve();
    for (const sf::VertexArray& RemovedCurve : Removed) {
      window_.draw(RemovedCurve);
    }

    std::vector<sf::CircleShape> SDots = curve_.S_dots();
    for (const sf::CircleShape& Sdots : SDots) {
      window_.draw(Sdots);
    }

    std::vector<sf::CircleShape> IDots = curve_.I_dots();
    for (const sf::CircleShape& Idots : IDots) {
      window_.draw(Idots);
    }

    std::vector<sf::CircleShape> RDots = curve_.R_dots();
    for (const sf::CircleShape& Rdots : RDots) {
      window_.draw(Rdots);
    }

    std::vector<sf::Text> days = text_.x_numbers();
    for (const sf::Text& xnumber : days) {
      window_.draw(xnumber);
    }

    std::vector<sf::Text> people = text_.y_numbers();
    for (const sf::Text& ynumber : people) {
      window_.draw(ynumber);
    }

    std::vector<sf::VertexArray> lines = key_.key_lines();
    for (const sf::VertexArray& line : lines) {
      window_.draw(line);
    }

    std::vector<sf::CircleShape> Dots = key_.key_dots();
    for (const sf::CircleShape& dots : Dots) {
      window_.draw(dots);
    }

    std::vector<sf::Text> description = key_.key_description();
    for (const sf::Text& desc : description) {
      window_.draw(desc);
    }

    window_.display();
  }
}
}  // namespace pf