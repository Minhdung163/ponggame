#include "ball.h"
#include <SFML/Graphics.hpp>
using namespace sf;
// Initialize a shape representing  a rectangle which inherits all the functions of sf::Transformable and sf::Shape 
CircleShape Ball::getBallObject() {
    return BallObject;                
}


// We use the class above to initialize the neccessary functions
Ball::Ball(double x, double y) { 
    ballPosition.x = x;
    ballPosition.y = y;
    BallObject.setRadius(5.f);
    BallObject.setPosition(ballPosition); // Set the position of the object
    BallObject.setOrigin(5.f, 5.f);
    BallObject.setFillColor(sf::Color::White); // Colorize the ball
}

void Ball::update() {
    // As the ball moves forward, the position of it changes according to the velocity
    // The velocity can be both be a positive or a negative value based on its statu
    ballPosition.x += ballVelocityX; 
    ballPosition.y += ballVelocityY;
    BallObject.setPosition(ballPosition); // This overwrites the previous position 
}

// This function returns the bounds of the ball shape in the global 2D world's coordinate system
// Later on we will use this FloatRect class to check the intersections among the ball, the sides and the bats
FloatRect Ball::getBallHitbox() { return BallObject.getGlobalBounds(); }

// This functions reallocate the ball position after hitting a bat
void Ball::rebound() {
    ballPosition.y -= (ballVelocityY * 30); // The ball position changes direction vertically as the ball touch the bat
    ballVelocityY *= -1; // The above logic also applies to the ball's velocity

}

// This function set the velocity to 0
void Ball::stop() {
    ballVelocityY = 0;
    ballVelocityX = 0;
}

// This function set the initial velocity
void Ball::go() {
    ballVelocityY = 0.5f;
    ballVelocityX = 0.5f;
}