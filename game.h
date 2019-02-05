/// "Copyright 2019 BOUVIER-GATELLIER-GIRAUDON-SANTET"

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include "Canvas.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Plane.h"
#include "Trooper.h"
#include "controller.h"


namespace patch {
template < typename T > std::string to_string(const T& n ) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
}


void generateRandom() {
    srand(time(0));
}


void game() {
    generateRandom();

    Canvas canvas;
    Cannon cannon;

    // 0 : Start Menu / 1 : Game / 2 : Option / 3 : Quit
    int mode = 0;
    bool developper_mode = true;
    int countdown = 0;
    int direction = 0;
    int count = shootFrequency;
    int player_lives = 7;
    int player_score = 0;

    canvas.startMenu(mode);

    while ((0 <= mode) && (mode <= 3)) {
        if (mode == 0) {
            canvas.startMenu(mode);
        }

        if (mode == 1) {
            Imagine::fillRect(0, windowHeight-groundHeight,
                              windowWidth, groundHeight, groundColor);
            Imagine::drawString(150, 595, "Score :",
                                Imagine::WHITE, 12, 0, true);
            Imagine::drawString(650, 595, "Lives :",
                                Imagine::WHITE, 12, 0, true);



            while (player_lives != 0) {
                Imagine::noRefreshBegin();

                int letterSize = 12;

                if (countdown % 30 == 0) {
                    planes.push_back(Plane());
                }

                countdown++;
                handleCannon(direction, count, cannon, bullets);
                handlePlanes(player_score);
                handleBullets(player_score);
                handleTroopers(player_lives, player_score);
                handleHitboxes();


                if (developper_mode) {
                    Imagine::fillRect(700, 595-letterSize, 30,
                                      15, Imagine::BLUE);
                    Imagine::drawString(700, 595,
                                        patch::to_string(player_lives), Imagine::WHITE);
                }
                Imagine::fillRect(200, 595-letterSize, 30, 15, Imagine::BLUE);
                Imagine::drawString(200, 595,
                                    patch::to_string(player_score), Imagine::WHITE);

                Imagine::noRefreshEnd();


                Imagine::milliSleep(20);
            }

            if (player_lives == 0) {
                canvas.gameOverScreen(mode, player_lives, player_score);
                resetVariables(player_score, player_lives, bullets, troopers, planes);
            }

            Imagine::fillRect(0, 0, windowWidth,
                              windowHeight, windowBackgroundColor);
        }

        if (mode == 3) {
            canvas.closeCanvas();
            break;
        }
    }
}
