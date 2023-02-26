#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Player::doSomething() {
    if (state) { //still state
        int action;
        if (this->getNumPlayer() == 1)
            action = getWorld()->getAction(1); //only for peach, change later
        else
            action = getWorld()->getAction(2);
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
        int dir = getWalkDirection();
        if (ticks_to_move % 8 == 0) {
            int newX = 0;
            int newY = 0;
            switch(dir) {
                case (right):
                    getPositionInThisDirection(right, 16, newX, newY);
                    if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                        getPositionInThisDirection(up, 16, newX, newY);
                        if (getWorld()->validPos(newX, newY)){
                            setWalkDirection(up);
                        }
                        getPositionInThisDirection(down, 16, newX, newY);
                        if (getWorld()->validPos(newX, newY)) //always returns false
                            setWalkDirection(down);
                    }
                    break;
                case(up):
                    getPositionInThisDirection(up, 16, newX, newY);
                    if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                        getPositionInThisDirection(right, 16, newX, newY);
                        if (getWorld()->validPos(newX, newY))
                            setWalkDirection(right);
                        else
                            setWalkDirection(left);
                    }
                    break;
                case(left):
                    getPositionInThisDirection(left, 16, newX, newY);
                    if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                        getPositionInThisDirection(up, 16, newX, newY);
                        if (getWorld()->validPos(newX, newY))
                            setWalkDirection(up);
                        else
                            setWalkDirection(down);
                    }
                    break;
                case(down):
                    getPositionInThisDirection(down, 16, newX, newY);
                    if (!getWorld()->validPos(newX, newY)) { //what if neither are valid??
                        getPositionInThisDirection(right, 16, newX, newY);
                        if (getWorld()->validPos(newX, newY))
                            setWalkDirection(right);
                        else
                            setWalkDirection(left);
                    }
                    break;
                default:
                    break; //non valid direction
            }
        }
        
        if (getWalkDirection() == left)
            setDirection(left);
        else
            setDirection(right);
        
        switch (getWalkDirection()) { //walk two steps
            case (right):
                moveTo(getX()+2, getY()); //goto or moveto???
                break;
            case (up):
                moveTo(getX(), getY()+2);
                break;
            case (left):
                moveTo(getX()-2, getY());
                break;
            case (down):
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

void BlueCoinSquare::doSomething() {
    if (living) {
        //increase coins by 3
        return;
    }
    return;
}

void RedCoinSquare::doSomething() {
    if (living) {
        //decrease coins by 3
        return;
    }
    return;
}

void StarSquare::doSomething() {
    return;
}

void DirectionalSquare::doSomething() {
    return;
}

void BankSquare::doSomething() {
    return;
}

void EventSquare::doSomething() {
    return;
}

void DroppingSquare::doSomething() {
    return;
}
