#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include "Constants.h"

class Canvas
{
    // Check if the canvas is active or not.
    bool isCanvasActive;

public:

    /**
     * @brief Creates a canvas
     */
    Canvas();

    /**
     * @brief Is the canvas is active, puts a "endGraphics" so the player can exit the game
     */
    void closeCanvas() const;
};

#endif // CANVAS_H
