//
// Created by user on 20.05.2021.
//

#ifndef NIBBLES_04_HEADER_H
#define NIBBLES_04_HEADER_H
#include "objects.h"
#include <list>

class Game {
private:
    std::list<Object*> objects;
    RenderWindow* window;
    SpaceShip* space_ship{};
    int rock_num{0};
    Texture explosion_texture{};
    Texture space_ship_texture{};
    Texture rock1_texture{};
    Texture rock2_texture{};
    Texture rock3_texture{};
    Texture rock4_texture{};
    Texture bullet_texture{};
    Texture background_texture{};
    Sprite background;
    sf::Font font;
    sf::Text score_text;
    sf::Text best_score_text;
    sf::Text best_score_title;
    sf::Text score_title;
    float score{};
    float best_score{};

public:
    explicit Game(RenderWindow *window);
    void add_bullet();
    void add_rock();
    void add_space_ship();
    SpaceShip *get_space_ship() { return space_ship; }
    void draw();
    void draw_text();
    void move();
    void collide();
    void generate();
};




#endif //NIBBLES_04_HEADER_H
