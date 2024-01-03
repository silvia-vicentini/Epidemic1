#include "text.hpp"

namespace pf {

Text::Text(Epidemic const& epidemic, sf::RenderWindow& window)
    : epidemic_(epidemic),
      window_(window),
      margin_(80.f),
      x_partition_(8),
      y_partition_(6),
      axis_name_font_(20),
      title_font_(25) {
  font_.loadFromFile("../Arialn.ttf");
}

// set graph title
sf::Text Text::set_Title() {
  sf::Text Title("Epidemic Evolution", font_, title_font_);
  Title.setFillColor(sf::Color::Black);
  Title.setPosition((window_.getSize().x - 2 * margin_) / 2, 30.f);
  return Title;
}

// set x title
sf::Text Text::x_axis_name() {
  sf::Text xAxisName("Days", font_, axis_name_font_);
  xAxisName.setFillColor(sf::Color::Black);
  xAxisName.setPosition(window_.getSize().x - 150.f,
                        window_.getSize().y - margin_ / 2);
  return xAxisName;
}

// set y title
sf::Text Text::y_axis_name() {
  sf::Text yAxisName("Number of people", font_, axis_name_font_);
  yAxisName.setFillColor(sf::Color::Black);
  yAxisName.setPosition(15.f, 230.f);
  yAxisName.setRotation(-90.f);
  return yAxisName;
}

// set x numbers
std::vector<sf::Text> Text::x_numbers() {
  std::vector<sf::Text> days;
  long int T = epidemic_.getT();
  for (int i = 0; i <= x_partition_; ++i) {
    std::string xstring = std::to_string(T * i / x_partition_);
    sf::Text xnumber(xstring, font_, axis_name_font_);
    xnumber.setFillColor(sf::Color::Black);
    xnumber.setPosition(
        margin_ + (window_.getSize().x - 2 * margin_) * i / x_partition_,
        window_.getSize().y - 70.f);
    days.push_back(xnumber);
  }
  return days;
}

// set y numbers
std::vector<sf::Text> Text::y_numbers() {
  std::vector<sf::Text> people;
  long int N = epidemic_.N();
  for (int i = 0; i <= y_partition_; ++i) {
    std::string ystring = std::to_string(N * i / y_partition_);
    sf::Text ynumber(ystring, font_, axis_name_font_);
    ynumber.setFillColor(sf::Color::Black);
    ynumber.setPosition(
        50.f, (window_.getSize().y - 90.f) -
                  (window_.getSize().y - 2 * margin_) * i / y_partition_);
    people.push_back(ynumber);
  }
  return people;
}
}  // namespace pf
