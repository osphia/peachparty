#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void MobileActor::doSomething() {
    if (state) { //still state
        doAction();
    } else { //walking state
        attemptWalk();
        switch (getWalkDirection()) { //walk two steps
            case (right):
                moveAtAngle(right, 2);
                break;
            case (up):
                moveAtAngle(up, 2);
                break;
            case (left):
                moveAtAngle(left, 2);
                break;
            case (down):
                moveAtAngle(down, 2);
                break;
            default:
                break;
        }
        ticks_to_move--;
        if (ticks_to_move == 0) {
            state = true;
            setPauseCounter();
        }
    }
}

void MobileActor::turningPoint() {
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
}

void Avatar::doAction() {
    int action = getWorld()->getAction(this->getNumPlayer()); //make sure this line works
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
}

void Avatar::attemptWalk() {
    //if avatar on top of directional square...
    //else if avatar is directly on top of square at a fork...
    turningPoint();
}

void Baddie::attemptWalk() {
    //if directly on top of square and at a fork
        //pick new random legal direction
        //update sprite facing direction
    turningPoint();
}

void Baddie::doAction() {
    //if player and baddie r on same square and avatar is on waiting to roll state then do bad action
    doBadAction();
    pauseCounter--;
    if (pauseCounter == 0) {
        squares_to_move = randInt(1, 3);
        ticks_to_move = squares_to_move*8;
        setWalkDirection(randInt(0, 3)*90);
        if (getWalkDirection() == left)
            setDirection(left);
        else
            setDirection(right);
        state = false;
    }
}

void Bowser::doBadAction() {
    int chance = randInt(1, 2);
    if (chance == 1)
        getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
        //make player lose coins!
}

void Boo::doBadAction() {
    int chance = randInt(1, 2);
    if (chance == 1)
        getWorld()->playSound(SOUND_BOO_ACTIVATE);
}

void Square::hasLanded(int pNum) {
    if (getWorld()->getPlayer(pNum)->getX() == this->getX() && getWorld()->getPlayer(pNum)->getY() == this->getY() && getWorld()->getPlayer(pNum)->getState()) {
        if (pNum == 1 && newPeach) {
            newPeach = false;
            squareAction(pNum);
        }
        if (pNum == 2 && newYoshi) {
            newYoshi = false;
            squareAction(pNum);
        }
    }
    if (!getWorld()->getPlayer(pNum)->getState()) {
        if (pNum == 1)
            newPeach = true;
        else
            newYoshi = true;
    }
}

void Square::hasPassed(int pNum) {
    if (getWorld()->getPlayer(pNum)->getX() == this->getX() && getWorld()->getPlayer(pNum)->getY() == this->getY() && !getWorld()->getPlayer(pNum)->getState()) {
        if (pNum == 1 && passPeach) {
            passPeach = false;
            passAction(pNum);
        }
        if (pNum == 2 && passYoshi) {
            passYoshi = false;
            passAction(pNum);
        }
    }
    else {
        if (pNum == 1)
            passPeach = true;
        else
            passYoshi = true;
    }
}
    
void BlueCoinSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->addCoins(3);
    //std::cerr << getWorld()->getPlayer(pNum)->getCoins() << std::endl;
    getWorld()->playSound(SOUND_GIVE_COIN);
}

void RedCoinSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->addCoins(-3);
    //std::cerr << getWorld()->getPlayer(pNum)->getCoins() << std::endl;
    getWorld()->playSound(SOUND_TAKE_COIN);
}

void StarSquare::squareAction(int pNum) {
    if (getWorld()->getPlayer(pNum)->getCoins() < 20)
        return;
    else {
        getWorld()->getPlayer(pNum)->addCoins(-20);
        getWorld()->getPlayer(pNum)->addStar();
        getWorld()->playSound(SOUND_GIVE_STAR);
        std::cerr<< "got star" << std::endl;
    }
}

void DirectionalSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->setWalkDirection(forcingDirection);
}

void BankSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->addCoins(getWorld()->getBankBalance());
    getWorld()->clearBankBalance();
    getWorld()->playSound(SOUND_WITHDRAW_BANK);
}
    
void BankSquare::passAction(int pNum) {
    int pCoins = getWorld()->getPlayer(pNum)->getCoins();
    if (pCoins < 5) {
        getWorld()->getPlayer(pNum)->addCoins(-pCoins);
        getWorld()->changeBankBalance(pCoins);
    }
    else {
        getWorld()->getPlayer(pNum)->addCoins(-5);
        getWorld()->changeBankBalance(5);
    }
    getWorld()->playSound(SOUND_DEPOSIT_BANK);
    std::cout << "bank balance: " << getWorld()->getBankBalance() << std::endl;
}

void Square::doSomething() {
    hasLanded(1); //when player lands it does both landed and passed
    hasPassed(1);
    hasLanded(2);
    hasPassed(2);
}
void CoinSquare::doSomething() {
    if (!living) {
        return;
    }
    hasLanded(1);
    hasLanded(2);
}

void EventSquare::doSomething() {
    return;
}

void DroppingSquare::doSomething() {
    return;
}
