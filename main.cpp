#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
   
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default);
    sf::CircleShape shape(100.0f);
  

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        
       
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}