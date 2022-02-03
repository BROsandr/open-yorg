#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Game.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "open yorg");
    Game game(&window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // game.input.proccess(event)
        }

        window.clear(sf::Color::White);

        // game.tick()

        window.display();
    }
}





