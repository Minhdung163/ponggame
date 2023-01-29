#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class AIBat {
private:
    Vector2f aiBatPosition;
    double aiBatSpeed = 24;
    double p2batspeed = 0.6f;
    RectangleShape aiBatObject;
public:
    void aisetlimitright();
    void aisetlimitleft();
    Vector2f aibatposition();
    AIBat(double x, double y);
    RectangleShape getAIBatObject();
    FloatRect getAIBatHitbox();
    void moveAIBatLeft();
    void moveAIBatRight();
    void update();
    void AIBatSpeedReverse();
    void movep2BatLeft();
    void movep2BatRight();
};
