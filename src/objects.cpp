//
// Created by user on 20.05.2021.
//
#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

// ANIMATION
Animation::Animation(sf::Texture &texture, int x, int y, int w, int h, int count, float speed) {
    Frame = 0;
    this->speed = speed;
    for (int i=0;i<count;i++)
        frames.emplace_back(x+i*w, y, w, h );

    sprite.setTexture(texture);
    sprite.setOrigin(float(w)/2,float(h)/2);
    sprite.setTextureRect(frames[0]);
}

void Animation::next_frame() {
    Frame+=speed;
    int n = frames.size();
    if (Frame >= float(n)) Frame -= float(n);
    if (n>0) sprite.setTextureRect(frames[int(Frame)]);
}


//OBJECT
void Object::draw(sf::RenderWindow &app) {
    animation.get_sprite()->setPosition(x,y);
    animation.get_sprite()->setRotation(alfa+90);
    app.draw(*animation.get_sprite());
}

void Object::set_parameters(float x, float y, float vx, float vy, float r, float alfa, Texture texture) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->r = r;
    this->alfa = alfa;
    this->texture = texture;
}

void Object::stay_in_boundaries() {
    if(x>WIDTH){x=0;}
    else if(x<0){x = WIDTH;}
    if(y>HEIGHT){y=0;}
    else if(y<0){y= HEIGHT;}
}

bool Object::collide(Object* other) const {
    if(other == this) return false;
    if(other->name == "bullet" & name == "space_ship") return false;
    if(other->name == "space_ship" & name == "bullet") return false;
    if(other->name == "bullet" & name == "bullet") return false;
    if(other->name == "explosion" || name == "explosion") return false;
    float dist = (x - other->x)*(x - other->x) + (y - other->y)*(y - other->y);
    float r_dist = (r + other->r) * (r + other->r);

    return r_dist > dist;
}


//SPACE SHIP
void SpaceShip::change_a(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::A:
            alfa -= 0.3;
            break;
        case sf::Keyboard::W:
            forward = true;
            break;
        case sf::Keyboard::D:
            alfa += 0.3;
            break;
        default:
            forward = false;
            break;
    }
}

void SpaceShip::move() {
    if(forward) {
        vx += float(std::cos(alfa * DEGTORAD) * 0.0023);
        vy += float(std::sin(alfa * DEGTORAD) * 0.0023);
    } else{
        vx *= 0.9992;
        vy *= 0.9992;
    }
    float maxSpeed=0.42;
    float speed = std::sqrt(vx*vx+vy*vy);
    if (speed>maxSpeed){
        vx *= maxSpeed/speed;
        vy *= maxSpeed/speed; }

    x+=vx;
    y+=vy;

    stay_in_boundaries();
    forward = false;
}

SpaceShip::SpaceShip(float x, float y, sf::Texture& t, float vx, float vy, float r, float alfa) {
    set_parameters(x,y,vx,vy,r,alfa,t);
    texture.setSmooth(true);
    animation = Animation(texture, 0, 0,1002,1818,1,0);
    animation.get_sprite()->setScale(0.07,0.07);
    name = "space_ship";
}

//ROCK
Rock::Rock(float x, float y, sf::Texture& t) {
    float vx = float(rand()%300 -150) / 1000;
    float vy = float(rand()%300 -150) / 1000;
    set_parameters(x,y,vx,vy,20,rand()%360,t);
    name = "rock";
    animation = Animation(texture, 0, 0,134,130,1,0);
    animation.get_sprite()->setScale(0.3,0.3);
}

void Rock::move() {
    y+= vy;
    x+= vx;
    alfa += 0.015;
    stay_in_boundaries();

}


SmallRock::SmallRock(Object *rock) {
    name = "small_rock";
    vx = float(rand()%300 -150) / 1000;
    vy = float(rand()%300 -150) / 1000;
    int num = rand()%2;
    if(num == 1){
        vy = std::abs(vy);
    } else{
        vy = -std::abs(vy);
    }
    set_parameters(rock->get_x(),rock->get_y(),vx,vy,10,rand()%360,rock->get_texture());
    animation = Animation(texture, 0, 0,134,130,1,0);
    animation.get_sprite()->setScale(0.15,0.15);
}

//EXPLOSION

Explosion::Explosion(float x, float y,sf::Texture& t) {
    set_parameters(x,y,0,0,1,rand()%360,t);
    animation = Animation(texture, 0, 0,256,256,30,0.03);
    animation.get_sprite()->setScale(0.25,0.25);
    name = "explosion";
}

void Explosion::move() {
    animation.next_frame();
    if(animation.is_end()) alive = false;
}


//BULLET
void Bullet::move() {
    vx=float(std::cos(alfa*DEGTORAD)*0.5);
    vy=float(std::sin(alfa*DEGTORAD)*0.5);
    //alfa+=rand()%7-3;
    x+=vx;
    y+=vy;
    if(x>WIDTH || x<0 || y>HEIGHT || y<0){
        alive = false;
    }
}

Bullet::Bullet(float x, float y, float alfa, sf::Texture& t) {
    set_parameters(x,y,0,0,1,alfa,t);
    animation = Animation(texture, 0, 0,1000,840,1,0);
    animation.get_sprite()->setScale(0.01,0.01);
    name = "bullet";
}

