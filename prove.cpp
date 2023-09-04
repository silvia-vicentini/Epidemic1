#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Population {
  long int S;
  long int I;
  long int R;
};

class Epidemic {
 private:
  double const m_beta;
  double const m_gamma;
  Population m_initial_population;
  long int m_T;

 public:
  Epidemic(double const beta, double const gamma, Population initial_population,
           long int T)
      : m_beta(beta),
        m_gamma(gamma),
        m_initial_population(initial_population),
        m_T(T) {
    assert(m_beta >= 0. && m_beta <= 1.);
    assert(m_gamma >= 0. && m_gamma <= 1.);
    assert(m_beta / m_gamma > 1);
    assert(m_initial_population.S > 0);
    assert(m_initial_population.I > 0);
    assert(m_initial_population.R > 0);
    assert(m_T > 0);
  }

  long int N() {
    return m_initial_population.S + m_initial_population.I +
           m_initial_population.R;
  };

  Population solve(Population prev_state) {
    Population next_state;
    next_state.S = std::round(prev_state.S - m_beta * prev_state.S *
                                                 prev_state.I / Epidemic::N());
    next_state.I = std::round(
        prev_state.I + m_beta * prev_state.S * prev_state.I / Epidemic::N() -
        m_gamma * prev_state.I);
    next_state.R = std::round(prev_state.R + m_gamma * prev_state.I);
    return next_state;
  };

  Population lockdown(Population prev_state) {
    Population next_state;
    next_state.S = prev_state.S;
    next_state.R = std::round(prev_state.R + m_gamma * prev_state.I);
    next_state.I = Epidemic::N() - prev_state.S - next_state.R;
    return next_state;
  };

  Population approx(Population population_state) {
    long int tot = population_state.S + population_state.I + population_state.R;
    if (tot != Epidemic::N()) {
      long int diff = tot - Epidemic::N();
      if (diff > 0) {
        population_state.R -= diff;
      } else {
        population_state.I -= diff;
      }
    }
    return population_state;
  };

  std::vector<Population> evolve() {
    std::vector<Population> population_state_;
    population_state_.push_back(m_initial_population);
    for (long int i = 0; i < m_T;) {
      if (population_state_[i].I < 0.6 * Epidemic::N()) {
        Population next_state = approx(solve(population_state_[i]));
        population_state_.push_back(next_state);
        ++i;
      } else {
        if (m_T - i < 14) {
          long int b = i;
          for (long int a = 0; a < m_T - i; ++a) {
            Population next_state = lockdown(population_state_[b]);
            population_state_.push_back(next_state);
            ++b;
          }
          i = b;
        } else {
          for (long int a = 0; a < 14; ++a) {
            Population next_state = lockdown(population_state_[i]);
            population_state_.push_back(next_state);
            ++i;
          }
        }
      }
    }
    /*else {
      auto next_state =
          approx(vaccine(population_state_[i], N, beta, gamma), N);
      population_state_.push_back(next_state);
    }
    }*/
    return population_state_;
  };

  void graph() {
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            "Epidemic evolution");  // crea finestra grafica

    sf::RectangleShape xAxis(
        sf::Vector2f(window.getSize().x,
                     2.f));  // crea asse x che ha dimensioni: lungo quanto la
                             // lunghezza della finestra e alto due unità
    xAxis.setPosition(
        0.f, window.getSize().y /
                 2);  // imposta posizione dell'asse x. posizionato all'inizio
                      // della finestra e a metà altezza della finestra
    xAxis.setFillColor(sf::Color::Black);  // asse x di colore nero

    sf::RectangleShape yAxis(sf::Vector2f(2.f, window.getSize().y));
    yAxis.setPosition(window.getSize().x / 2, 0.f);
    yAxis.setFillColor(sf::Color::Black);

    sf::Font font;
    // if (!font.loadFromFile("arial.ttf")) { std::cerr << "Impossible to load
    // font" << std::endl;  }
    // questo serve per il font con cui voglio fare scritte, è necessario?, è
    // giusto?
    sf::Text xAxisName("Days", font, 20);
    sf::Text yAxisName("Number of people", font, 20);
    xAxisName.setPosition(
        window.getSize().x - 100,
        window.getSize().y - 40);  // non ho la minima idea di dove lo abbia
                                   // posizionato,controlla!!!
    yAxisName.setPosition(
        20,
        20)  // non ho la minima idea di dove lo abbia posizionato,controlla!!!

        sf::Vector2f graphSize(600.f, 400.f);  // i valori sono a caso
    sf::Vector2f graphPosition(
        100.f,
        100.f);  // i valori sono a caso. Definizione delle
                 // dimesioni e posizioni del grafico.
    long int maxXValue =
        m_T + 1;  // stabilisci quale è il valore max sull'asse delle x
    long int maxYValue =
        N();  // stabilisci quale è il valore max sull'asse delle y
    for (float y = 0; y <= maxYValue; y += 20.f)  // il valore 20.f è a caso
    {
      sf::Vertex line[] = {
          sf::Vertex(
              sf::Vector2f(graphPosition.x, graphPosition.y + graphSize.y -
                                                (y / maxYvalue) * graphSize.y),
              sf::Color::Black),
          sf::Vertex(sf::Vector2f(graphPosition.x + graphSize.x,
                                  graphPosition.y + graphSize.y -
                                      (y / maxYValue) * graphSize.y),
                     sf::Color::Black)};
      window.draw(line, 2, sf::Lines);
    }
    for (float x = 0; x <= maxXValue; x += 2.f)  // il valore 2.f è a caso
    {
      sf::Vertex line[] = {
          sf::Vertex(
              sf::Vector2f(graphPosition.x + (x / maxXValue) * graphSize.x,
                           graphPosition.y + graphSize.y),
              sf::Color::Black),
          sf::Vertex(
              sf::Vector2f(graphPosition.x + (x / maxXValue) * graphSize.x,
                           graphPosition.y),
              sf::Color::Black)};
      window.draw(line, 2, sf::Lines);
    }

    std::vector<sf::Text>
        xTicks;  // creazione degli oggetti di testo per le tacchette sugli assi
    std::vector<sf::Text> yTicks;
    for (float x = 0.f; x <= maxXValue; x += 2.f) {
      sf::Text tickName;  // o devo mettere sf::text tickLabel ???
      tickName.setFont(font);
      tickName.setCharacterSize(14);
      tickName.setFillColor(sf::Color::Black);
      tickName.setString(std::to_string(static_cast<int>(
          x)));  // qui viene impostato il contenuto del testo dell'oggetto
                 // tickName CON IL VALORE numerico DI X.std::to_string converte
                 // il valore numerico in una stringa. static_cast<int> ci
                 // assicura che il valore di y venga convertito in un intero
                 // prima di essere convertito in stringa.
      tickName.setPosition(
          graphPosition.x + (x / maxXValue) * graphSize.x - 10,
          graphPosition.y + graphSize.y + 10);  // valori a caso
      xTicks.push_back(
          tickName);  // l'oggeto tickName viene aggiunto al vettore
                      // xTicks che conterrà tutte le etichette delle
                      // tacchette lungo l'asse delle x
    }
    for (float y = 0.f; y <= maxXValue; y += 20.f) {
      sf::Text tickName;  // o devo mettere sf::text tickLabel ???
      tickName.setFont(font);
      tickName.setCharacterSize(14);
      tickName.setFillColor(sf::Color::Black);
      tickName.setString(std::to_string(static_cast<int>(
          y)));  // qui viene impostato il contenuto del testo dell'oggetto
                 // tickName CON IL VALORE numerico DI Y.std::to_string converte
                 // il valore numerico in una stringa. static_cast<int> ci
                 // assicura che il valore di y venga convertito in un intero
                 // prima di essere convertito in stringa.
      tickName.setPosition(graphPosition.x - 30,
                           graphPosition.y + graphSize.y -
                               (y / maxYValue) * graphSize.y -
                               7);  // valori a caso
      yTicks.push_back(
          tickName);  // l'oggeto tickName viene aggiunto al vettore
                      // xTicks che conterrà tutte le etichette delle
                      // tacchette lungo l'asse delle x
    }

    sf::VertexArray SusceptibleCurve(sf::LineStrip);  // creo le curve
    sf::VertexArray InfectionCurve(sf::LineStrip);
    sf::VertexArray RecoveryCurve(sf::LineStrip);
    std::vector<Population> population_state_ = evolve();
    for (int i{0}; i <= day; ++i) {
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
      // crea un oggetto sf::Vertex che rappresenta un punto. con sf::Vector
      // calcolo le cordinate del punto (dove x e y sono quelli correnti nel
      // ciclo)
    }

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
      }  // ciclo range-based . Serve per disegnare l'oggetto tick (corrente)
         // sulla finestra. Tutte le etichette vengono disegnate una dopo
         // l'altra seguendo l'ordine in cui sono nel vettore xTicks.
      for (const sf::Text& tick : yTicks) {
        window.draw(tick);
      }
      window.draw(SusceptibleCurve);
      window.draw(InfectedCurve);
      window.draw(RecoveryCurve);
      window.display();
    }
  };
}

int main() {
  std::cout << "Please write initial population's groups S, I, R:\n";
  Population initial_population;
  std::cin >> initial_population.S >> initial_population.I >>
      initial_population.R;

  std::cout << "Please write epidemic's parameter beta and gamma:\n";
  double beta;
  double gamma;
  std::cin >> beta >> gamma;
  Epidemic epidemic(beta, gamma, initial_population);

  std::cout << "Please write the duration of the epidemic T:\n";
  int T;
  std::cin >> T;

  epidemic.graph();
}
