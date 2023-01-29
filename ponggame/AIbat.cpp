#include "aibat.h"
#include <SFML/Graphics.hpp>
using namespace sf;

// Initialize a shape representing  a rectangle which inherits all the functions of sf::Transformable and sf::Shape 
RectangleShape AIBat::getAIBatObject() {
    return aiBatObject;
}
// Get the current bat position
Vector2f AIBat::aibatposition()
{
    return aiBatPosition;
}
// We use the class above to initialize the neccessary functions
AIBat::AIBat(double x, double y) {
    aiBatPosition.x = x;
    aiBatPosition.y = y;
    aiBatObject.setSize(sf::Vector2f(120, 15)); // Set the size of the aibat
    aiBatObject.setPosition(aiBatPosition); // Set the position of the object
    aiBatObject.setFillColor(sf::Color(1, 43, 25)); // Colorize the bat
}

// Avoid the paddle of passing the screen

void AIBat::aisetlimitright()
{
    aiBatPosition.x = 880;
    aiBatObject.setPosition(aiBatPosition);
}

void AIBat::aisetlimitleft()
{
    aiBatPosition.x = 0;
    aiBatObject.setPosition(aiBatPosition);
}
// This function returns the bounds of the bat shape in the global 2D world's coordinate system
// Later on we will use this FloatRect class to check the intersections among the ball, the sides and the bats
FloatRect AIBat::getAIBatHitbox() {
    return aiBatObject.getGlobalBounds();
}
// The aibat moves automatically to the left
void AIBat::moveAIBatLeft() {
    aiBatPosition.x -= aiBatSpeed;
}// The aibat moves automatically to the right
void AIBat::moveAIBatRight() {
    aiBatPosition.x += aiBatSpeed;
}
// This function updates the current coordinates of the aibat
void AIBat::update() {
    aiBatObject.setPosition(aiBatPosition);
}
// Thí function will change the side of where the aibat towards
void AIBat::AIBatSpeedReverse() {
    aiBatSpeed *= -1;
}
// 2 player mode
void AIBat::movep2BatLeft() {
    aiBatPosition.x -= p2batspeed;
}
void AIBat::movep2BatRight() {
    aiBatPosition.x += p2batspeed;
}