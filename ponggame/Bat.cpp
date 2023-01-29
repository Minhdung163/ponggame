#include "bat.h"
#include <SFML/Graphics.hpp>
using namespace sf;
// Initialize a shape representing  a rectangle which inherits all the functions of sf::Transformable and sf::Shape
RectangleShape Bat::getBatObject() {
    return BatObject;
}

// Get the current bat position
Vector2f Bat::batposition()
{
    return batPosition;
 }

// Place the paddle to its original position
void Bat::resetposition()
{
    batPosition.x = 500;
    batPosition.y = 680;
}
// We use the class above to initialize the neccessary functions
Bat::Bat(double x, double y) {
    batPosition.x = x;
    batPosition.y = y;
    BatObject.setSize(sf::Vector2f(120, 15)); // Set the size of the aibat
    BatObject.setPosition(batPosition); // Set the position of the object
    BatObject.setFillColor(sf::Color(102, 22, 2)); // Colorize the bat
}

// Avoid the paddle of passing the screen
void Bat::setlimitright()
{
    batPosition.x = 880;
    BatObject.setPosition(batPosition);
}

void Bat::setlimitleft()
{
    batPosition.x = 0;
    BatObject.setPosition(batPosition);
}

// This function returns the bounds of the bat shape in the global 2D world's coordinate system
// Later on we will use this FloatRect class to check the intersections among the ball, the sides and the bats
FloatRect Bat::getBatHitbox() {
    return BatObject.getGlobalBounds();
}


// This function locate the position of the bat as we move it
void Bat::moveBatLeft() {
    batPosition.x -= batSpeed;
}
void Bat::moveBatRight() {
    batPosition.x += batSpeed;
}

// This function updates the current coordinates of the bat
void Bat::update() {
    BatObject.setPosition(batPosition);
}