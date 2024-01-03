#include "curve.hpp"

namespace pf {

Curve::Curve(Epidemic const& epidemic, sf::RenderWindow& window)
    : epidemic_(epidemic),
      window_(window),
      T_(epidemic_.getT()),
      dot_radius_(4.f),
      margin_(80.f),
      xscale_((window_.getSize().x - 2 * margin_) / (T_ + 1)),
      yscale_((window_.getSize().y - 2 * margin_) / epidemic_.getN()),
      population_state_(std::make_shared<std::vector<Population<int>>>(
          epidemic_.evolution())) {}

std::vector<sf::VertexArray> Curve::S_curve() {
  std::vector<sf::VertexArray> Susceptible;
  for (int i = 0; i <= T_; ++i) {
    sf::VertexArray SusceptibleCurve(sf::Lines, 2);
    SusceptibleCurve[0].position = sf::Vector2f(
        margin_ + xscale_ * i,
        -margin_ + window_.getSize().y - yscale_ * population_state_[i].S);
    SusceptibleCurve[1].position = sf::Vector2f(
        margin_ + xscale_ * (i + 1),
        -margin_ + window_.getSize().y - yscale_ * population_state_[i + 1].S);
    SusceptibleCurve[0].color = sf::Color(0, 0, 255);
    SusceptibleCurve[1].color = sf::Color(0, 0, 255);
    Susceptible.push_back(SusceptibleCurve);
  }
  return Susceptible;
}

std::vector<sf::VertexArray> Curve::I_curve() {
  std::vector<sf::VertexArray> Infected;
  for (int i = 0; i <= T_; ++i) {
    sf::VertexArray InfectedCurve(sf::Lines, 2);
    InfectedCurve[0].position = sf::Vector2f(
        margin_ + xscale_ * i,
        -margin_ + window_.getSize().y - yscale_ * population_state_[i].I);
    InfectedCurve[1].position = sf::Vector2f(
        margin_ + xscale_ * (i + 1),
        -margin_ + window_.getSize().y - yscale_ * population_state_[i + 1].I);
    InfectedCurve[0].color = sf::Color(230, 0, 0);
    InfectedCurve[1].color = sf::Color(230, 0, 0);
    Infected.push_back(InfectedCurve);
  }
  return Infected;
}

std::vector<sf::VertexArray> Curve::R_curve() {
  std::vector<sf::VertexArray> Removed;
  for (int i = 0; i <= T_; ++i) {
    sf::VertexArray RemovedCurve(sf::Lines, 2);
    RemovedCurve[0].position = sf::Vector2f(
        margin_ + xscale_ * i,
        -margin_ + window_.getSize().y - yscale_ * population_state_[i].R);
    RemovedCurve[1].position = sf::Vector2f(
        margin_ + xscale_ * (i + 1),
        -margin_ + window_.getSize().y - yscale_ * population_state_[i + 1].R);
    RemovedCurve[0].color = sf::Color(20, 230, 0);
    RemovedCurve[1].color = sf::Color(20, 230, 0);
    Removed.push_back(RemovedCurve);
  }
  return Removed;
}

std::vector<sf::CircleShape> Curve::S_dots() {
  std::vector<sf::CircleShape> SDots;
  for (int i = 0; i <= T_; ++i) {
    sf::CircleShape Sdots(dot_radius_);
    Sdots.setFillColor(sf::Color(0, 0, 255));
    Sdots.setPosition(sf::Vector2f(margin_ + xscale_ * (i + 1),
                                   -margin_ + window_.getSize().y -
                                       yscale_ * population_state_[i + 1].S -
                                       dot_radius_ / 2));
    SDots.push_back(Sdots);
  }
  return SDots;
}

std::vector<sf::CircleShape> Curve::I_dots() {
  std::vector<sf::CircleShape> IDots;
  for (int i = 0; i <= T_; ++i) {
    sf::CircleShape Idots(dot_radius_);
    Idots.setFillColor(sf::Color(230, 0, 0));
    Idots.setPosition(sf::Vector2f(margin_ + xscale_ * (i + 1),
                                   -margin_ + window_.getSize().y -
                                       yscale_ * population_state_[i + 1].I -
                                       dot_radius_ / 2));
    IDots.push_back(Idots);
  }
  return IDots;
}

std::vector<sf::CircleShape> Curve::R_dots() {
  std::vector<sf::CircleShape> RDots;
  for (int i = 0; i <= T_; ++i) {
    sf::CircleShape Rdots(dot_radius_);
    Rdots.setFillColor(sf::Color(20, 230, 0));
    Rdots.setPosition(sf::Vector2f(margin_ + xscale_ * (i + 1),
                                   -margin_ + window_.getSize().y -
                                       yscale_ * population_state_[i + 1].R -
                                       dot_radius_ / 2));
    RDots.push_back(Rdots);
  }
  return RDots;
}

void Curve::draw_curve() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();
    }
    window_.clear(sf::Color::White);

    std::vector<sf::VertexArray> Susceptible = S_curve();
    for (const sf::VertexArray& SusceptibleCurve : Susceptible) {
      window_.draw(SusceptibleCurve);
    }

    std::vector<sf::VertexArray> Infected = I_curve();
    for (const sf::VertexArray& InfectedCurve : Infected) {
      window_.draw(InfectedCurve);
    }

    std::vector<sf::VertexArray> Removed = R_curve();
    for (const sf::VertexArray& RemovedCurve : Removed) {
      window_.draw(RemovedCurve);
    }

    std::vector<sf::CircleShape> SDots = S_dots();
    for (const sf::CircleShape& Sdots : SDots) {
      window_.draw(Sdots);
    }

    std::vector<sf::CircleShape> IDots = I_dots();
    for (const sf::CircleShape& Idots : IDots) {
      window_.draw(Idots);
    }

    std::vector<sf::CircleShape> RDots = R_dots();
    for (const sf::CircleShape& Rdots : RDots) {
      window_.draw(Rdots);
    }

    window_.display();
  }
}
}  // namespace pf