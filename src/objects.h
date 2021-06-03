//
// Created by user on 20.05.2021.
//

#ifndef NIBBLES_04_OBJECTS_H
#define NIBBLES_04_OBJECTS_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

#define WIDTH 1024
#define HEIGHT 768
#define DEGTORAD 0.017453f


class Animation{
    float Frame{}, speed{};
    Sprite sprite;
    std::vector<sf::IntRect> frames;

public:
    Animation()= default;
    void next_frame();
    bool is_end(){return Frame+speed >= frames.size();}
    Animation(sf::Texture &texture, int x, int y,int w, int h, int count, float Speed);
    sf::Sprite* get_sprite(){return &sprite;}
};


class Object{
protected:
    std::string name{};
    float x{},y{},vx{},vy{},r{},alfa{};
    bool alive{true};
    Animation animation;
    sf::Texture texture;

public:
    Object(float x,float y, sf::Texture& t,float vx =0, float vy =0, float r =0, float alfa =0) {set_parameters(x,y,vx,vy,r,alfa,t);}
    Object() = default;
    virtual ~Object() = default ;
    virtual void move(){};
    void draw(sf::RenderWindow &app);
    void stay_in_boundaries();
    bool collide(Object* other) const;


    void set_parameters(float x, float y, float vx, float vy, float r, float alfa, Texture t);
    float get_x() const{return x;}
    float get_y() const{return y;}
    Texture get_texture() const{return texture;}
    float get_alfa() const{return alfa;}
    bool is_alive() const{return alive;}
    void set_die(){alive = false;}
    std::string get_name(){return name;}
};


class SpaceShip: public Object{
    bool forward{false};
public:
    SpaceShip(float x,float y, sf::Texture& t,float vx =0, float vy =0, float r = 25, float alfa =90);
    void move() override;
    void change_a(sf::Keyboard::Key key);
};


class Rock: public Object{
public:
    Rock(float x,float y,sf::Texture& t);
    Rock() = default;

    void move() override;
};

class SmallRock: public Rock{
public:
    explicit SmallRock(Object *rock);
};

class Bullet: public Object{
public:
    Bullet(float x,float y, float alfa,sf::Texture& t);
    void move() override;;
};



class Explosion: public Object{
public:
    Explosion(float x,float y,sf::Texture& t);
    void move() override;;
};




#endif //NIBBLES_04_OBJECTS_H
