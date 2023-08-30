int main()˙{
  // grafico
sf::RenderWindow window((800, 600), "Epidemic evolution");
std::ifstream infile ("epidemic.cpp");// metti tra virgolette nome del file da cui prendi dati
if (!infile) { 
    throw std::runtime_error {"Impossible to open file"}
}

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
