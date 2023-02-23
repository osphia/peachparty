#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Player::doSomething() {
    if (state) { //still state
        int action = getWorld()->getAction(1);
        if (action != ACTION_NONE) { //change later
            if (action == ACTION_ROLL) {
                int die_roll = randInt(1, 10);
                ticks_to_move = die_roll*8;
                state = false;
            }
        }
        else {
            return;
        }
    } else { //walking state
        int dir = getDirection();
        switch(dir) {
            case (0): //right
                if (!getWorld()->validPos(getX()+2, getY())) { //what if neither are valid??
                    if (getWorld()->validPos(getX(), getY() + 2))
                        setDirection(90);
                    else
                        setDirection(270);
                }
                break;
            case(90): //up
                if (!getWorld()->validPos(getX(), getY()+2)) { //what if neither are valid??
                    if (getWorld()->validPos(getX()+2, getY()))
                        setDirection(0);
                    else
                        setDirection(180);
                }
                break;
            case(180): //left
                if (!getWorld()->validPos(getX()-2, getY())) { //what if neither are valid??
                    if (getWorld()->validPos(getX(), getY() + 2))
                        setDirection(90);
                    else
                        setDirection(270);
                }
                break;
            case(270): //down
                if (!getWorld()->validPos(getX(), getY()-2)) { //what if neither are valid??
                    if (getWorld()->validPos(getX()+2, getY()))
                        setDirection(0);
                    else
                        setDirection(180);
                }
                break;
            default:
                break; //non valid direction
        }
        if (dir == 180) //sprite facing direction
            spriteDir = 180;
        else
            spriteDir = 0;
        
        switch (dir) { //walk two steps
            case (0):
                moveTo(getX()+2, getY());
                break;
            case (90):
                moveTo(getX(), getY()+2);
                break;
            case (180):
                moveTo(getX()-2, getY());
                break;
            case (270):
                moveTo(getX(), getY()-2);
                break;
            default:
                break;
        }
        ticks_to_move--;
        if (ticks_to_move == 0)
            state = true;
    }
}

bool Player::goTo(int m_x, int m_y) { //change later
    if (getWorld()->validPos(m_x, m_y)) {
        moveTo(m_x, m_y);
        return true;
    }
    return false;
}

void BlueCoinSquare::doSomething() {
    std::cerr << "test";
    return;
}
//void Yoshi::doSomething() {
//    std::cerr << "what";
//    return;
//}
