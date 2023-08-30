#include "epidemic.hpp"

#include <Graph.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <stdexcept>  //per fare i throw
#include <vector>

namespace pf {
Epidemic::Epidemic(double const beta, double const gamma)
    : beta_{beta}, gamma_{gamma} {
  if (beta_ < 0. || beta_ > 1.) {
    throw std::runtime_error{
        "Epidemic parameter beta must be such that 0 <= beta <= 1"};
  }
  if (gamma_ < 0. || gamma_ > 1.) {
    throw std::runtime_error{
        "Epidemic parameter gamma must be such that 0 <= gamma <= 1"};
  }
  if (beta_ / gamma_ <= 1) {
    throw std::runtime_error{
        "Epidemic parameter beta must be greather than gamma"};
  }
}


//dobbiamo mettere altre condizioni di verifica: che S I R siano sempre naturali

Population Epidemic::solve(Population const prev_state, int const N)
    const {  // bisogna verificare che le approssimazioni a numeri interi
             // vengano svolte nella maniera corretta
  double const beta{Epidemic::beta_};
  double const gamma{Epidemic::gamma_};
  int const S_i = prev_state.S - beta * prev_state.S * prev_state.I / N;
  int const I_i = prev_state.I + beta * prev_state.S * prev_state.I / N -
                  gamma * prev_state.I;
  int const R_i = prev_state.R + gamma * prev_state.I;

  return Population{S_i, I_i, R_i};
}

std::vector<Population> Epidemic::evolve(Population initial_population,
                                         int const time) {
  population_state_.push_back(initial_population);

  int const N =
      initial_population.S + initial_population.I + initial_population.R;

  for (int i{0}; i < time; ++i) {
    auto next_state = solve(population_state_[i], N);
    population_state_.push_back(next_state);
  }
  return Epidemic::population_state_;
}








void Epidemic::graph(int time, std::vector<Population> population_state_) {
  // bisogna creare tre grafici da sovrapporre, uno per l'andamento di S uno per
  // quello di I uno per quello di R
  if (Epidemic::population_state_.size() < 2) {
    throw std::runtime_error{"Not enough entries to draw a graphic"};
  }

  if (time <= 0) {
    throw std::runtime_error{"Not enough time to draw a graphic"};
  }

  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600),
                          "Epidemic evolution");  // che libreria bisogna usare?

  Simple_window window{100, 100, 600, 400, "Epidemic development"};
  window.set_color(Color::white);
  Axis time{Axis::x, Point{20, 300}, 280, 10, "time"};
  window.attach(time);
  Axis people{Axis::y, Point{20, 300}, 280, 10, "number of people"};
  window.attach(people);

  // Create points
  for (int i{}; i <= time; ++i) {
    Point S{i, population_state_[i].S};
    S.set_color(Cotor::blue);
    Point I{i, population_state_[i].I};
    I.set_color(Cotor::red);
    Point R{i, population_state_[i].R};
    R.set_color(Cotor::green);
    window.attach(S, I, R);
  }

  // non so se serva
  sf::VertexArray Infection_Curve(sf::LineStrip);
  sf::VertexArray Recovery_Curve(sf::LineStrip);
  sf::VertexArray Susceptible_Curve(sf::LineStrip);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color::White);
    window.draw(Infection_Curve);
    window.draw(Recovery_Curve);
    window.draw(Susceptible_Curve);
    window.display();
  }
}
}  // namespace pf

/*std::vector<Population> const &Epidemic::state() const {}*/
