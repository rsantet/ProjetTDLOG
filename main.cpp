#include <iostream>
#include "Cannon.h"
#include "Bullet.h"
#include <Imagine/Graphics.h>

/// Vector of bullets
std::vector<Bullet> bullets;


/**
 * @brief keyboard management function for the cannon and the shooting
 * @param direction -1 if it goes to the left, 1 if it goes to the right, 2 if the user shoots, 0 otherwise.
 */
void keyboard(int& direction){
    static bool left = false, right = false, up = false;
    Imagine::Event e;
    do {
        Imagine::getEvent(0, e);
        if (e.type == Imagine::EVT_KEY_ON || e.type == Imagine::EVT_KEY_OFF) {
            bool push = (e.type == Imagine::EVT_KEY_ON);
            switch (e.key) {
            case Imagine::KEY_LEFT :
                left = push;
                break;
            case Imagine::KEY_RIGHT :
                right = push;
                break;
            case Imagine::KEY_UP :
                up = push;
                break;
            }
        }
    } while (e.type!=Imagine::EVT_NONE);
    direction = (up ? 2 : (left ? -1 : (right ? 1 : 0)));
}

void isRemovingBullet(Bullet& bullet){
    int x = bullet.getPositionX(), y = bullet.getPositionY();
    if (x < 0 || x > windowWidth || y < 0){
        bullet.setRemoveMe(true);
    }
}

void handleBullets(){
    for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it){
        (*it).updatePosition();

        isRemovingBullet(*it);

    }

    for (std::vector<Bullet>::iterator it = bullets.end()-1; it != bullets.begin()-1; --it){
        if ((*it).getRemoveMe()){
            bullets.erase(it);
        }
    }
}


int main(){
    std::cout << "Hello World !" << std::endl;

    Canvas canvas;

    Cannon cannon;

    int countdown = 0;
    int direction = 0;
    while (countdown != 300){
        countdown++;
        keyboard(direction);
        if (direction!=2){
            cannon.updatePosition(direction);
        }
        else{
            bullets.push_back(Bullet(cannon.getAngle()));
        }
        handleBullets();
        std::cout << bullets.size() << std::endl;
        Imagine::milliSleep(50);
    }

    canvas.closeCanvas();

    return 0;
}
