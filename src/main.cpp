#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
using namespace sf;

int main() {
    srand(time(nullptr));
    RenderWindow window(VideoMode(WIDTH,HEIGHT), "Asteroids", Style::Default);

    Event ev{};
    Game* game = new Game(&window);

    while (window.isOpen()){
        //Event
        while (window.pollEvent(ev)){
            switch (ev.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if(ev.key.code == Keyboard::Escape){
                        window.close();
                    }
                    if (ev.key.code == Keyboard::Space){
                        game->add_bullet();
                    }
                    break;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) game->get_space_ship()->change_a(Keyboard::W);
        if (Keyboard::isKeyPressed(Keyboard::A)) game->get_space_ship()->change_a(Keyboard::A);
        if (Keyboard::isKeyPressed(Keyboard::S)) game->get_space_ship()->change_a(Keyboard::S);
        if (Keyboard::isKeyPressed(Keyboard::D)) game->get_space_ship()->change_a(Keyboard::D);

        window.clear(Color::White);
        game->generate();
        game->draw();
        game->move();
        game->collide();
        window.display();
    }

    return 0;
}