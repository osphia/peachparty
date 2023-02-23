#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Player::doSomething() {
    if (state) { //still state
        int action = getWorld()->getAction(1); //only for peach, change later
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
        int newX = 0;
        int newY = 0;
        switch(dir) {
            case (right):
                getPositionInThisDirection(right, 2, newX, newY);
                if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                    getPositionInThisDirection(up, 2, newX, newY);
                    if (getWorld()->validPos(newX, newY)){
                        setDirection(up);
                    }
                    getPositionInThisDirection(down, 2, newX, newY);
                    if (getWorld()->validPos(newX, newY)) //always returns false
                        setDirection(down);
                }
                break;
            case(up):
                getPositionInThisDirection(up, 2, newX, newY);
                if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                    getPositionInThisDirection(right, 2, newX, newY);
                    if (getWorld()->validPos(newX, newY))
                        setDirection(right);
                    else
                        setDirection(left);
                }
                break;
            case(left):
                getPositionInThisDirection(left, 2, newX, newY);
                if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                    getPositionInThisDirection(up, 2, newX, newY);
                    if (getWorld()->validPos(newX, newY))
                        setDirection(up);
                    else
                        setDirection(down);
                }
                break;
            case(down):
                getPositionInThisDirection(down, 2, newX, newY);
                if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                    getPositionInThisDirection(right, 2, newX, newY);
                    if (getWorld()->validPos(newX, newY))
                        setDirection(right);
                    else
                        setDirection(left);
                }
                break;
            default:
                break; //non valid direction
        }
        
        if (dir == left) //sprite facing direction
            spriteDir = left;
        else
            spriteDir = right;
        
        switch (dir) { //walk two steps
            case (right):
                goTo(getX()+2, getY()); //goto or moveto???
                break;
            case (up):
                goTo(getX(), getY()+2);
                break;
            case (left):
                goTo(getX()-2, getY());
                break;
            case (down):
                goTo(getX(), getY()-2);
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
    return;
}
//void Yoshi::doSomething() {
//    std::cerr << "what";
//    return;
//}
