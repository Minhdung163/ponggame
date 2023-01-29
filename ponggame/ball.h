#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Ball {
private:
    CircleShape BallObject;
    Vector2f ballPosition;
public:
    CircleShape getBallObject();
    Ball(double x, double y);
    FloatRect getBallHitbox();
    void reboundSides();
    void passTop();
    Vector2f getBallPosition;
    void passBottom();
    void rebound();
    void update();
    // initialize the ball velocity 
    double ballVelocityX = 0.5f;
    double ballVelocityY = 0.5f;
    void stop();
    void go();

};