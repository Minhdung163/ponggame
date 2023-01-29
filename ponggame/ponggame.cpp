#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "aibat.h"
#include <iostream>
#include "ball.h"
#include "bat.h"
#include <SFML/Main.hpp>

using namespace sf;
int p1 = 0;
int p2 = 5;
int windowWidth = 1000;
int windowHeight = 700;
int batscore = 0;
int lives = 27; // lives must not be 0 to initialize gamestart later on
int aibatcounter = 0;
int a = 0;
unsigned highscoree;
// INT MAIN

int main() {
    
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong!"); //Create a window with given width, height name Pong! 
    window.setPosition(Vector2i(0, 0)); //Place the window anywhere you want
    // creating objects with initial position of the objects
    AIBat aibat(windowWidth / 2, 10);
    Bat bat1(windowWidth / 2, windowHeight - 20);
    Ball ball(windowWidth / 2 , windowHeight / 2);

    // while loop as the game 
    while (window.isOpen()) {

        Event event;
        // while loop to interact with the window
        while (window.pollEvent(event)) { // Neccessary in a loop to make sure that there are no pending event
            if (event.type == Event::Closed) // The Closed event. It is triggered when you use any method to close the window
                window.close();
        }
        // User input as we play the game
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            Vector2f pos = bat1.batposition();
            if (pos.x < 0)
            {
                bat1.setlimitleft();
            }
            else
            {
                bat1.moveBatLeft();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            Vector2f pos = bat1.batposition();
            if (pos.x > windowWidth - 120)
            {
                bat1.setlimitright();
            }
            else
            {
                bat1.moveBatRight();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::A)) {
            Vector2f pos = aibat.aibatposition();
            if (pos.x < 0)
            {
                if (a % 2 == 0) //determine which mode we are playing
                {
                    aibat.aisetlimitleft();
                }
            }
            else
            {
                if (a % 2 == 0)
                    aibat.movep2BatLeft();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            Vector2f pos = aibat.aibatposition();
            if (pos.x > windowWidth - 120)
            {
                if (a % 2 == 0)
                {
                    aibat.aisetlimitright();
                }
            }
            else
            {
                if (a % 2 == 0)
                {
                    aibat.movep2BatRight();
                }
            }
        }
        // Logic part of this game
        ball.reboundSides(); // function of what would happen if the ball touches the edges of the window created
        ball.passTop(); // function of what would happen if the ball passes through the top side of the window
        ball.passBottom(); // function of what would happen if the ball passes through the bot side of the window

        // we use those FloatRect which we created before to check if there are any intersections between the objects and then process what happen to them after the intersection
        if (ball.getBallHitbox().intersects(bat1.getBatHitbox())) {
            ball.rebound();
        }
        if (ball.getBallHitbox().intersects(aibat.getAIBatHitbox())) {
            ball.rebound();
        }
        // these two if statements allow the aibat to be "smarter" like a human so that they can change direction 
        // if the ball is 50 units in length compare to the aibat to the right at any time, the bat will navigate to the right and that also applies to the left case
        // the aibatcounter functions as a timer as how fast the aibat realize that it is far from the ball
        if (ball.getBallHitbox().left > (aibat.getAIBatHitbox().left) + 50) {
            if (aibatcounter % 60 == 0) // if you increase the number to 70, it will make the game easier and vice versa
            {
                if (a % 2 == 1) //determine which mode we are playing
                {
                    aibat.moveAIBatRight();
                }
            }
        }
        if (ball.getBallHitbox().left < (aibat.getAIBatHitbox().left) + 50) {
            if (aibatcounter % 60 == 0)
            {
                if (a % 2 == 1)
                {
                    aibat.moveAIBatLeft();
                }
            }
        }
        // also if the ball touches the sides, the aibat also reacts to it by navigate to the opposite direction
        if (ball.getBallPosition.x > 995 || ball.getBallPosition.x < 0)
        {
            if (a % 2 == 1)
            {
                aibat.AIBatSpeedReverse();
            }
        }
        // In-game text
        std::stringstream ss1;
        ss1 << "Score: " << batscore << "       Lives: " << lives;
        Text op;
        Font font;
        font.loadFromFile("game_over.ttf");
        op.setFont(font);
        op.setCharacterSize(45);
        op.setFillColor(sf::Color::White);
        op.setString(ss1.str());

        std::stringstream ss2;
        ss2 << "P1: " << p1 << "       P2: " << p2;
        Text tp;
        tp.setFont(font);
        tp.setCharacterSize(45);
        tp.setFillColor(sf::Color::White);
        tp.setString(ss2.str());

        // Gameover message
        std::stringstream ss3;
        ss3 << "You ran out of lives. \n\nYour score is " << batscore << ".\n\nPress A to play again.\nPress R to return to the menu.\nPress H to view highscore.";
        Text gameoverMessage1;
        gameoverMessage1.setCharacterSize(50);
        gameoverMessage1.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        gameoverMessage1.setFont(font);
        gameoverMessage1.setString(ss3.str());

        std::stringstream ss6;
        if (p1 > p2)
        {
            ss6 << "The winner is Player 1.\nPlayer 1: " << p1 << "\nPlayer 2: " << p2 << "\n\nPress A to play again.\nPress R to return to the menu.";
        }
        if (p1 < p2)
        {
            ss6 << "The winner is Player 2.\nPlayer 1: " << p1 << "\nPlayer 2: " << p2 << "\n\nPress A to play again.\nPress R to return to the menu.";
        }
        Text gameoverMessage2;
        gameoverMessage2.setCharacterSize(50);
        gameoverMessage2.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        gameoverMessage2.setFont(font);
        gameoverMessage2.setString(ss6.str());

        // Gamestart message

        std::stringstream sss;
        sss << "Welcome to Pong.\n\nSelect mode:\nPress O for one player\nPress T for two player: ";
        Text startMessage;
        startMessage.setCharacterSize(50);
        startMessage.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        startMessage.setFont(font);
        startMessage.setString(sss.str());

        std::stringstream ss4;
        ss4 << "Welcome to Pong.\n\nYou are in 1 player mode.\n\nPress any key to play.";
        Text startMessage1;
        startMessage1.setCharacterSize(50);
        startMessage1.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        startMessage1.setFont(font);
        startMessage1.setString(ss4.str());

        std::stringstream ss5;
        ss5 << "Welcome to Pong.\n\nYou are in 2 player mode.\n\nPress any key to play.";
        Text startMessage2;
        startMessage2.setCharacterSize(50);
        startMessage2.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        startMessage2.setFont(font);
        startMessage2.setString(ss5.str());

        // High score text
        std::stringstream ss7;
        ss7 << "Your high score is: " << highscoree << "\n\nPress R to return to the menu.\n\nPress A to play again.";
        Text highscore;
        highscore.setCharacterSize(50);
        highscore.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        highscore.setFont(font);
        highscore.setString(ss7.str());
        // UPDATE
        if (aibatcounter == 1000000) { // if statements to return the value of aicounter if the game is too long
            aibatcounter = 0;
        }
        aibatcounter++;
        ball.update();
        bat1.update();
        aibat.update();
        // Display visual
        window.clear(Color(4, 0, 26));
        switch (a)
        { 
        case -1: // High score window
            window.draw(highscore);
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                a = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                a = 0;
            }
            window.display();
            break;
        case 0: // Menu window
            window.draw(startMessage);
            if (Keyboard::isKeyPressed(Keyboard::O))
            {
                a = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::T))
            {
                a = 2;
            }
            window.display();
            break;
        case 1: // 1 player mode window
              if (lives == 0) {
                  highscoree = batscore;
                std::ifstream file;
                file.open("pong.txt");
                if (file.is_open())
                {
                    while (!file.eof())
                    {
                        file >> highscoree;
                    }
                }
                file.close();
                std::ofstream file2;
                file2.open("pong.txt");
                if (file2.is_open())
                {
                    if (batscore > highscoree)
                    {
                        highscoree = batscore;
                        
                   }
                    file2 << highscoree;
                }
                file2.close();
                window.draw(gameoverMessage1);
                ball.stop();
                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    bat1.resetposition();
                    lives = 3;
                    batscore = 0;
                    ball.go();
                }
                else if (Keyboard::isKeyPressed(Keyboard::R))
                {
                    bat1.resetposition();
                    a = 0;
                    lives = 27;
                }
                else if (Keyboard::isKeyPressed(Keyboard::H))
                {
                    a = -1;
                    
                }
            }
              else if (lives == 27) {

                  ball.stop();
                  window.draw(startMessage1);
                  if (event.type == event.KeyPressed)
                  {

                      lives = 3;
                      batscore = 0;
                      ball.go();
                  }
              }
            else {
                if (a % 2 == 1)
                {
                    window.draw((aibat.getAIBatObject()));
                    window.draw(bat1.getBatObject());
                    window.draw(ball.getBallObject());
                    window.draw(op);
                }
            }
            window.display();
            break;
        case 2: // 2 player mode window
            if (p1 == 10 || p2 == 10) {

                window.draw(gameoverMessage2);
                ball.stop();
                if (Keyboard::isKeyPressed(Keyboard::A)) {

                    bat1.resetposition();
                        p1 = 0;
                        p2 = 0;
                        ball.go();
                    
                }
                else if (Keyboard::isKeyPressed(Keyboard::R))
                {
                    bat1.resetposition();
                    a = 0;
                    p1 = 0;
                    p2 = 5;
                }
            }
            else if (p1 == 0 && p2 == 5) {

                ball.stop();
                window.draw(startMessage2);
                if (event.type == event.KeyPressed)
                {
                    p1 = 0;
                    p2 = 0;
                    ball.go();
                }
            }
            else {
                    window.draw((aibat.getAIBatObject()));
                    window.draw(bat1.getBatObject());
                    window.draw(ball.getBallObject());
                    window.draw(tp);
            }
            window.display();
            break;
        }
    }
    return 0;
}

// Ball functions that includes given parameter in pong game sourcefile
void Ball::reboundSides() {
    if (ballPosition.x > windowWidth)
        ballVelocityX *= -1;

    else if (ballPosition.x < 0)
        ballVelocityX *= -1;
}
void Ball::passTop() {

    if (ballPosition.y < 0)
    {
        if (a == 2)
        {
            p1++;
        }
        if (a == 1)
        {
            batscore++;
        }
        ballPosition.x = windowWidth / 2;
        ballPosition.y = windowHeight / 2;
        // These if statements make it harder to predict where the ball is gonna launch to after a point
        if (rand() % 2 == 1) ballVelocityY *= -1;
        if (rand() % 2 == 0) ballVelocityX *= -1;
    }
}
void Ball::passBottom() {
    if (ballPosition.y > windowHeight)
    {
        ballPosition.x = windowWidth / 2;
        ballPosition.y = windowHeight / 2;
        if (a == 2)
        {
            p2++;
        }
        if (a == 1)
        {
            lives--;
        }
        if (rand() % 2 == 1) ballVelocityY *= -1;
        if (rand() % 2 == 0) ballVelocityX *= -1;
    }
}
    