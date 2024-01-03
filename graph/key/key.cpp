#include "key.hpp"

namespace pf {
Key::Key(sf::RenderWindow& window) : window_(window) {
  margin_ = 80.f;
  dot_radius_ = 4.f;
  font_.loadFromFile("../Arialn.ttf");
}

// righe colorate
// qui potresti usare un ciclo per creare i tre oggetti:
std::vector<sf::VertexArray> Key::key_lines() {
  std::vector<sf::VertexArray> lines;
  sf::VertexArray SusceptibleLine(sf::Lines, 2);
  SusceptibleLine[0].position =
      sf::Vector2f(200.f, window_.getSize().y - margin_ / 2);
  SusceptibleLine[1].position =
      sf::Vector2f(250.f, window_.getSize().y - margin_ / 2);
  SusceptibleLine[0].color = sf::Color(0, 0, 255);
  SusceptibleLine[1].color = sf::Color(0, 0, 255);
  lines.push_back(SusceptibleLine);

  sf::VertexArray InfectedLine(sf::Lines, 2);
  InfectedLine[0].position =
      sf::Vector2f(400.f, window_.getSize().y - margin_ / 2);
  InfectedLine[1].position =
      sf::Vector2f(450.f, window_.getSize().y - margin_ / 2);
  InfectedLine[0].color = sf::Color(230, 0, 0);
  InfectedLine[1].color = sf::Color(230, 0, 0);
  lines.push_back(InfectedLine);

  sf::VertexArray RemovedLine(sf::Lines, 2);
  RemovedLine[0].position =
      sf::Vector2f(600.f, window_.getSize().y - margin_ / 2);
  RemovedLine[1].position =
      sf::Vector2f(650.f, window_.getSize().y - margin_ / 2);
  RemovedLine[0].color = sf::Color(20, 230, 0);
  RemovedLine[1].color = sf::Color(20, 230, 0);
  lines.push_back(RemovedLine);

  return lines;
}

// puntini
std::vector<sf::CircleShape> Key::key_dots() {
  std::vector<sf::CircleShape> dots;
  sf::CircleShape Sdot(dot_radius_);
  sf::CircleShape Idot(dot_radius_);
  sf::CircleShape Rdot(dot_radius_);
  Sdot.setFillColor(sf::Color(0, 0, 255));
  Idot.setFillColor(sf::Color(230, 0, 0));
  Rdot.setFillColor(sf::Color(20, 230, 0));
  Sdot.setPosition(223.f, window_.getSize().y - 43.f);
  Idot.setPosition(423.f, window_.getSize().y - 43.f);
  Rdot.setPosition(623.f, window_.getSize().y - 43.f);
  dots.push_back(Sdot);
  dots.push_back(Idot);
  dots.push_back(Rdot);
  return dots;
}

// scritte
std::vector<sf::Text> Key::key_description() {
  std::vector<sf::Text> description;
  sf::Text desc1("Susceptible", font_, 20);
  desc1.setFillColor(sf::Color::Black);
  desc1.setPosition(270.f, window_.getSize().y - 50.f);
  description.push_back(desc1);
  sf::Text desc2("Infected", font_, 20);
  desc2.setFillColor(sf::Color::Black);
  desc2.setPosition(470.f, window_.getSize().y - 50.f);
  description.push_back(desc2);
  sf::Text desc3("Removed", font_, 20);
  desc3.setFillColor(sf::Color::Black);
  desc3.setPosition(670.f, window_.getSize().y - 50.f);
  description.push_back(desc3);
  return description;
}
}  // namespace pf