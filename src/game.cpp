#include <SFML/Graphics/RenderWindow.hpp>
#include "game.h"
#include <algorithm>

#define MAX_ROCKS_NUM 23

Game::Game(RenderWindow *win) {
    window = win;
    explosion_texture.loadFromFile("../assets/explosion1.png");
    space_ship_texture.loadFromFile("../assets/rocket.png");
    rock1_texture.loadFromFile("../assets/rock1.png");
    rock2_texture.loadFromFile("../assets/rock2.png");
    rock3_texture.loadFromFile("../assets/rock3.png");
    rock4_texture.loadFromFile("../assets/rock4.png");
    bullet_texture.loadFromFile("../assets/bullet.png");
    background_texture.loadFromFile("../assets/background.jpg");
    font.loadFromFile("../assets/KenneyRocketSquare.ttf");

    best_score_text.setFont(font);
    score_text.setFont(font);
    best_score_title.setFont(font);
    score_title.setFont(font);
    best_score_title.setString("Best score: ");
    score_title.setString("Score: ");
    best_score_title.setScale(0.5,0.5);
    score_title.setScale(0.5,0.5);
    score_text.setPosition(0,10);
    best_score_title.setPosition(0,60);
    best_score_text.setPosition(0,70);


    background_texture.setSmooth(true);
    background = Sprite(background_texture);
    background.setScale(0.57,1);

    add_space_ship();
}



void Game::add_rock() {
    sf::Texture rock_texture;
    int texture = rand()%4;
    switch (texture) {
        case 0: rock_texture = rock1_texture;
            break;
        case 1: rock_texture = rock2_texture;
            break;
        case 2: rock_texture = rock3_texture;
            break;
        case 3: rock_texture = rock4_texture;
            break;
    }

    int wall = rand()%4;
    switch (wall) {
        case 0: objects.push_back(new Rock(0,rand()%HEIGHT,rock_texture));
            break;
        case 1: objects.push_back(new Rock(WIDTH,rand()%HEIGHT,rock_texture));
            break;
        case 2: objects.push_back(new Rock(0,rand()%HEIGHT,rock_texture));
            break;
        case 3: objects.push_back(new Rock(rand()%WIDTH,HEIGHT,rock_texture));
            break;
    }
}

void Game::add_bullet() {
    auto* new_bullet = new Bullet(get_space_ship()->get_x(),get_space_ship()->get_y(),get_space_ship()->get_alfa(),bullet_texture);
    objects.push_back(new_bullet);
}

void Game::draw() {
    window->draw(background);
    for(Object* obj: objects){
        obj->draw(*window);
    }
    draw_text();
}

void Game::draw_text() {
    best_score_text.setString(std::to_string(int(best_score)));
    score_text.setString(std::to_string(int(score)));
    window->draw(score_text);
    window->draw(score_title);
    window->draw(best_score_text);
    window->draw(best_score_title);
}


void Game::move() {
    for(Object* obj: objects){
        if(!obj->is_alive()){
            objects.remove(obj);
            delete obj;
        }else{
            obj->move();
        }
    }
    score+=0.01;
}

void Game::collide() {
    std::list<Object*> collide_objects;
    for(Object* obj: objects){
        bool is_in = std::find(collide_objects.begin(), collide_objects.end(), obj) != collide_objects.end();
        if(!is_in){
            for(Object* other: objects){
                if(obj->collide(other)){
                    collide_objects.push_back(obj);
                    collide_objects.push_back(other);
                    float collide_x = (obj->get_x() + other->get_x())/2;
                    float collide_y = (obj->get_y() + other->get_y())/2;
                    objects.push_back(new Explosion(collide_x,collide_y,explosion_texture));
                }
            }
        }
    }
    for(Object* obj: collide_objects){
        if(obj->get_name() == "rock") {
            rock_num--;
            objects.push_back(new SmallRock(obj));
        }
        if(obj->get_name() == "space_ship") {
            add_space_ship();
            best_score = std::max(score,best_score);
            score=0;
        }
        objects.remove(obj);
        obj->set_die();
    }
}

void Game::generate() {
    if (MAX_ROCKS_NUM > rock_num)
        if (rand()% 100 == 0) {
            add_rock();
            rock_num++;
        }
}

void Game::add_space_ship() {
    space_ship = new SpaceShip(float(WIDTH)/2,float(HEIGHT)/2,space_ship_texture);
    objects.push_back(space_ship);
}




