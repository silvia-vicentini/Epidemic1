int main()˙{
  // grafico
sf::RenderWindow window((800, 600), "Epidemic evolution"); //crea finestra grafica

  sf::RectangleShape xAxis (sf::Vector2f (window.getSize().x, 2.f); //crea asse x che ha dimensioni: lungo quanto la lunghezza della finestra e alto due unità
 xAxis.setPosition(0.f, window.getSize().y/2); // imposta posizione dell'asse x. posizionato all'inizio della finestra e a metà altezza della finestra
  xAxis.setFillColor (sf::Color::Black); // asse x di colore nero

sf::RectangleShape yAxis (sf::Vector2f(2.f, window.getSize().y));
  yAxis.setPosition(window.getSize().x /2, 0.f);
  yAxis.setFillColor(sf::Color::Black);






window.draw(xAxis);
window.draw(yAxis);

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
        window.clear();

window.draw(infectionCurve);
window.draw(recoveryCurve);
window.draw(susceptibleCurve);
}
}
