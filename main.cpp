
#include <algorithm>  //serve?
#include <fstream>    // per leggere da file in input
#include <iomanip>    //serve?
#include <iostream>
#include <limits>  //serve?

#include "epidemic.hpp"

int main() {
  try {
    char cmd;

    std::string filename;

    std::cout << "Valid commands: \n"
              << "- read data from a sample file [f FILE_NAME]\n"
              << "- read data from standard input [i FILE_NAME]\n"
              << "- read data from command line [l FILE_NAME]\n"
              << "- print graphic to screen [g POPULATION_TREND]\n";

    while (std::cin >> cmd) {
      // prende da command line

      if (cmd == 'l') {
        double const beta{};
        double const gamma{};
        int S{};
        int I{};
        int R{};
        int const time{};
      }

      // prendere in input e restituire in output

      auto simulate(Chain & chain, double duration, int steps, int prescale) {
        std::vector<std::vector<ParticleState>> v_states;
        std::vector<std::vector<ParticleState>> states;

        int time;

        for (int step{0}; step != steps; ++step) {
          if (step % prescale == 0) {
            v_states.push_back(chain.state());
            states.push_back(chain.state());
          }
          chain.evolve(delta_t);
        }

        return v_states;
        return states;
      }

      int main() {
        // Molla con:
        // k = 1 N/m
        // l = 1 cm
        Hooke const hooke{1.0, 0.01};
        // Catena con 10 punti materiali:
        // m: 50 g per ogni punto
        // x: un punto ogni 1.1 cm (partendo da 0.0)
        // v: tutti i punti hanno v_0 = 0 m/s
        Chain chain(hooke);
        double const p_m{0.05};
        double p_x{0.0};
        double delta_x{0.011};
        for (auto const p_v :
             {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}) {
          chain.push_back({p_m, p_x, p_v});
          p_x += delta_x;
        }
        // Esegue una simulazione:
        // - per una durata di 20 s
        // - suddividendola in 20000 intervalli di tempo
        // - registrando lo stato della catena ogni 100 intervalli di tempo
        std::double const duration{20.0};
        int const steps{20000};
        int const prescale{100};
        const auto v_states = simulate(chain, duration, steps, prescale);
        // Analisi:
        double sum_length{0.0};
        std::cout << "Report for each of the stored states:\n";
        std::cout << "  length  : center of mass x : center of mass v\n";
        for (const auto& state : v_states) {
          auto length = state.back().x - state.front().x;
          sum_length += length;
          double sum_m{0.0};
          double sum_mx{0.0};
          double sum_mv{0.0};
          for (const auto& pps : state) {
            sum_m += pps.m;
            sum_mx += pps.m * pps.x;
            sum_mv += pps.m * pps.v;
          }
          std::cout << std::setprecision(4) << std::fixed << std::setw(8)
                    << length << "  : " << std::setw(14) << (sum_mx / sum_m)
                    << "   : " << std::setw(14) << (sum_mv / sum_m) << '\n';
        };
        std::cout << "\nSummary:\n";
        std::cout << "Average length: " << (sum_length / v_states.size())
                  << '\n';
      }

      // lettura dei parametri iniziali da file
      if (cmd == 'f' && std::cin >> filename) {
        std::ifstream infile{filename};
        if (!infile) {
          throw std::runtime_error{"Impossible to open file!"};
        }
        double epidemic_parameters;
        void Epidemic::evolve(Population population_state, int const time);

        Epidemic epidemic(epidemic_parameters, epidemic_parameters);
        for (int i{0}; i < 2; ++i) {
          infile >> epidemic_parameters;
          data.add(x);
        }
        std::cout << "Input file read successfully" << '\n';
      }
      // scrittura risultato su schermo
      else if (cmd == 's') {
        std::cout << "- Generated data: " << epidemic.state() << '\n';
        const auto stat = epidemic.evolve();
       for
         std::cout << "- mean: " << stat.mean << '\n'
                   << "- sigma: " << stat.sigma << '\n'
                   << "- mean error: " << stat.mean_err << '\n'
                   << "- median: " << stat.median << '\n';
      }
      // scrivere risultati su documento in output
      else if (cmd == 'o') {
       std::ofstream outfile{"results.txt"};

       if (!outfile) {
         throw std::runtime_error{"Impossible to open file!"};
       }
       outfile << "- Read data:" << data.size() << '\n';
       const auto stat = data.statistics();
       outfile << "- mean: " << stat.mean << '\n'
               << "- sigma: " << stat.sigma << '\n'
               << "- mean error: " << stat.mean_err << '\n'
               << "- median: " << stat.median << '\n';

       std::cout << "Output file written successfully" << '\n';
      }
      // disegnare il grafico
      else if (cmd == 'g') {
       epidemic.graphic();
      }
      // chiudere il programma
      else if (cmd == 'q') {
       return EXIT_SUCCESS;
      } else {
       std::cout << "Bad format, insert a new command\n";
       std::cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  } catch (std::exception const& e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
