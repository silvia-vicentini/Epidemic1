#include <iomanip>
#include <iostream>

#include "epidemic/epidemic.hpp"
#include "graph/draw.hpp"

int main() {
  // stampa in output dei risultati dell'evoluzione della pandemia (epidemic)
  std::cout << "Please write initial population's groups S, I, R:\n";
  pf::Population<double> initial_population;
  std::cin >> initial_population.S >> initial_population.I >>
      initial_population.R;

  std::cout << "Please write epidemic's parameter beta and gamma:\n";
  double beta;
  double gamma;
  std::cin >> beta >> gamma;

  std::cout << "Please write the duration of the epidemic T:\n";
  int T;
  std::cin >> T;

  pf::Epidemic epidemic{beta, gamma, initial_population, T};

  epidemic.print_results();

  // stampa del grafico
  sf::RenderWindow window(sf::VideoMode(1000, 600), "");
  Draw draw(epidemic, window);
  draw.draw_graph();

  // stampa automa cellulare
}