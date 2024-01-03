#include "grid.hpp"

namespace pf {
Grid::Grid(sf::RenderWindow& window)
    : window_(window), margin_(80.f), x_partition_(8), y_partition_(6) {}

sf::VertexArray Grid::bottom_side() {
  sf::VertexArray BottomSide(sf::Lines, 2);
  BottomSide[0].position = sf::Vector2f(margin_, window_.getSize().y - margin_);
  BottomSide[1].position = sf::Vector2f(window_.getSize().x - margin_,
                                        window_.getSize().y - margin_);
  BottomSide[0].color = sf::Color::Black;
  BottomSide[1].color = sf::Color::Black;
  return BottomSide;
}

sf::VertexArray Grid::top_side() {
  sf::VertexArray TopSide(sf::Lines, 2);
  TopSide[0].position = sf::Vector2f(margin_, window_.getSize().y - margin_);
  TopSide[1].position = sf::Vector2f(margin_, margin_);
  TopSide[0].color = sf::Color::Black;
  TopSide[1].color = sf::Color::Black;
  return TopSide;
}

sf::VertexArray Grid::left_side() {
  sf::VertexArray LeftSide(sf::Lines, 2);
  LeftSide[0].position = sf::Vector2f(margin_, margin_);
  LeftSide[1].position = sf::Vector2f(window_.getSize().x - margin_, margin_);
  LeftSide[0].color = sf::Color::Black;
  LeftSide[1].color = sf::Color::Black;
  return LeftSide;
}

sf::VertexArray Grid::right_side() {
  sf::VertexArray RightSide(sf::Lines, 2);
  RightSide[0].position = sf::Vector2f(window_.getSize().x - margin_,
                                       window_.getSize().y - margin_);
  RightSide[1].position = sf::Vector2f(window_.getSize().x - margin_, margin_);
  RightSide[0].color = sf::Color::Black;
  RightSide[1].color = sf::Color::Black;
  return RightSide;
}

std::vector<sf::VertexArray> Grid::vertical_lines() {
  std::vector<sf::VertexArray> VerticalLines;
  for (int i = 1; i < x_partition_; ++i) {
    sf::VertexArray VerticalLine(sf::Lines, 2);
    VerticalLine[0].position = sf::Vector2f(
        margin_ + (window_.getSize().x - margin_ * 2) * i / x_partition_,
        window_.getSize().y - margin_);
    VerticalLine[1].position = sf::Vector2f(
        margin_ + (window_.getSize().x - 2 * margin_) * i / x_partition_,
        margin_);
    VerticalLine[0].color = sf::Color(175, 238, 238);
    VerticalLine[1].color = sf::Color(175, 238, 238);
    VerticalLines.push_back(VerticalLine);
  }
  return VerticalLines;
}

std::vector<sf::VertexArray> Grid::horizontal_lines() {
  std::vector<sf::VertexArray> HorizontalLines;
  for (int i = 1; i < y_partition_; ++i) {
    sf::VertexArray HorizontalLine(sf::Lines, 2);
    HorizontalLine[0].position =
        sf::Vector2f(margin_, margin_ + (window_.getSize().y - margin_ * 2) *
                                            i / y_partition_);
    HorizontalLine[1].position = sf::Vector2f(
        window_.getSize().x - margin_,
        margin_ + (window_.getSize().y - margin_ * 2) * i / y_partition_);
    HorizontalLine[0].color = sf::Color(175, 238, 238);
    HorizontalLine[1].color = sf::Color(175, 238, 238);
    HorizontalLines.push_back(HorizontalLine);
  }
  return HorizontalLines;
}
}  // namespace pf