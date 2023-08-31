#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()˙{
  // grafico
sf::RenderWindow window((800, 600), "Epidemic evolution"); //crea finestra grafica

  sf::RectangleShape xAxis (sf::Vector2f (window.getSize().x, 2.f); //crea asse x che ha dimensioni: lungo quanto la lunghezza della finestra e alto due unità
 xAxis.setPosition(0.f, window.getSize().y/2); // imposta posizione dell'asse x. posizionato all'inizio della finestra e a metà altezza della finestra
  xAxis.setFillColor (sf::Color::Black); // asse x di colore nero
  
sf::RectangleShape yAxis (sf::Vector2f(2.f, window.getSize().y));
  yAxis.setPosition(window.getSize().x /2, 0.f);
  yAxis.setFillColor(sf::Color::Black);

sf::Font font;
  if (!font.loadFromFile("arial.ttf")) { std::cerr << "Impossible to load font" << std::endl;  }
//questo serve per il font con cui voglio fare scritte, è necessario?, è giusto?
  sf::Text xAxisName("Time", font, 20);
  sf::Text yAxisName ("Number of people", font, 20); 
  xAxisName.setPosition (window.getSize().x -100, window.getSize().y - 40); //non ho la minima idea di dove lo abbia posizionato,controlla!!!
  yAxisName.setPosition (20,20) //non ho la minima idea di dove lo abbia posizionato,controlla!!!

  float maxXValue =  //stabilisci quale è il valore max sull'asse delle x
  float maxYValue =  //stabilisci quale è il valore max sull'asse delle y
  for (float y = 0; y <= maxYValue; y += 20.f) //il valore 20.f è a caso
    { sf::Vertex line [] =  sf::Vertex ( sf::Vector2f (graphPosition.x, graphPosition.y + graphSize.y -(y/ maxYvalue)* graphSize.y)  }





window.draw(xAxis);
window.draw(yAxis);
window.draw (xAxisName);
window.draw (yAxisName);
  window.display();
  

  


std::vector<int> time; // serve?
std::vector<int> population_state; //oppure devoinserire singolarmente S,I e R???

sf::VertexArray infectionCurve(sf::LineStrip);
sf::VertexArray recoveryCurve(sf::LineStrip);
sf:VertexArray susceptibleCurve(sf::LineStrip);

while (window.isOpen())
{
     sf::Event event;
        while (window.pollEvent(event))
        {if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

window.draw(infectionCurve);
window.draw(recoveryCurve);
window.draw(susceptibleCurve);
}
}
