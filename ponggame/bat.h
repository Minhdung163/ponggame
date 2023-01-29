#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bat {
private:
    Vector2f batPosition;
    double batSpeed = 0.6f;
    RectangleShape BatObject;
public:
    void setlimitright();
    void setlimitleft();
    Vector2f batposition();
    Bat(double x, double y);
    RectangleShape getBatObject();
    FloatRect getBatHitbox();
    void moveBatLeft();
    void moveBatRight();
    void update();
    void resetposition();
};