#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void MobileActor::doSomething() {
    if (state) { //still state
//        isValidDirection();
        doAction();
    } else { //walking state
        if (checkFork() && isForce == -1){ //fork
            if (!atFork())
                return;
        }
        isForce = -1;
        turningPoint(); //turn at corners
        spriteDirection();
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
            dropping();
        }
    }
}

void Avatar::doAction() {
    int action = getWorld()->getAction(this->getNumPlayer()); //make sure this line works
    switch (action) {
        case ACTION_NONE: {
            return;
            break;
        }
        case ACTION_ROLL: {
            int die_roll = randInt(1, 10);
            setRoll(die_roll);
            setTicksToMove(die_roll*8);
            setState(false);
            break;
        }
        case ACTION_FIRE: {
            if (hasVortex) {
                getWorld()->spawnVortex(getX(), getY(), getWalkDirection());
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                hasVortex = false;
            }
        }
        default:
            return;
    }
}

bool Avatar::atFork() {
    if (keyPressed())
        return true;
    return false;
}

bool Baddie::atFork() {
    setWalkDirection(randInt(0, 3)*90);
    return true;
}

void Baddie::doAction() {
    //if player and baddie r on same square and avatar is on waiting to roll state then do bad action
    for (int i = 1; i < 3; i++) {
        if (getWorld()->getPlayer(i)->getX() == this->getX() && getWorld()->getPlayer(i)->getY() == this->getY()) {
            if (getWorld()->getPlayer(i)->getState()) {
                if ((i == 1 && newPeach) || (i == 2 && newYoshi)) {
                    if (i == 1)
                        newPeach = false;
                    else
                        newYoshi = false;
                    doBadAction(i);
                }
            }
        }
        else {
            if (i == 1)
                newPeach = true;
            else
                newYoshi = true;
        }
    }
    pauseCounter--;
    if (pauseCounter == 0) {
        squares_to_move = squaresToMove();
        setTicksToMove(squares_to_move*8);
        setWalkDirection(randInt(0, 3)*90);
        spriteDirection();
        setState(false);
    }
}

void Bowser::doBadAction(int pNum) {
    int chance = randInt(1, 2);
    if (chance == 1) {
        getWorld()->getPlayer(pNum)->setCoins(0);
        getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
    }
}

void Boo::doBadAction(int pNum) {
    int chance = randInt(1, 2);
    if (chance == 1) {
        int temp = getWorld()->getPlayer(1)->getCoins();
        getWorld()->getPlayer(1)->setCoins(getWorld()->getPlayer(2)->getCoins());
        getWorld()->getPlayer(2)->setCoins(temp);
    } else {
        int temp = getWorld()->getPlayer(1)->getStars();
        getWorld()->getPlayer(1)->setStars(getWorld()->getPlayer(2)->getStars());
        getWorld()->getPlayer(2)->setStars(temp);
    }
    getWorld()->playSound(SOUND_BOO_ACTIVATE);
}


//SQUARES//
void Square::hasLandedOrPassed(int pNum) {
    if (getWorld()->getPlayer(pNum)->getX() == this->getX() && getWorld()->getPlayer(pNum)->getY() == this->getY()) {
        if (!getWorld()->getPlayer(pNum)->getState()) {
            if (pNum == 1 && passPeach) {
                passPeach = false;
                passAction(pNum);
                return;
            }
            if (pNum == 2 && passYoshi) {
                passYoshi = false;
                passAction(pNum);
                return;
            }
        }
        else {
            if (pNum == 1 && newPeach) {
                newPeach = false;
                passPeach = false;
                squareAction(pNum);
                return;
            }
            if (pNum == 2 && newYoshi) {
                newYoshi = false;
                passYoshi = false;
                squareAction(pNum);
                return;
            }
        }
    }
    else {
        if (pNum == 1) {
            passPeach = true;
            newPeach = true;
            newSwap = true;
        }
        if (pNum == 2){
            passYoshi = true;
            newYoshi = true;
            newSwap = true;
        }
    }
}
    
void BlueCoinSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->addCoins(3);
    getWorld()->playSound(SOUND_GIVE_COIN);
}

void RedCoinSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->addCoins(-3);
    getWorld()->playSound(SOUND_TAKE_COIN);
}

void StarSquare::squareAction(int pNum) {
    if (getWorld()->getPlayer(pNum)->getCoins() < 20)
        return;
    else {
        getWorld()->getPlayer(pNum)->addCoins(-20);
        getWorld()->getPlayer(pNum)->addStar(1);
        getWorld()->playSound(SOUND_GIVE_STAR);
    }
}

void StarSquare::passAction(int pNum) {
    squareAction(pNum);
}

void DirectionalSquare::squareAction(int pNum) {
    getWorld()->getPlayer(pNum)->setWalkDirection(forcingDirection);
    getWorld()->getPlayer(pNum)->setForce(forcingDirection);
}

void DirectionalSquare::passAction(int pNum) {
    squareAction(pNum);
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
}

void EventSquare::squareAction(int pNum) {
    if (getNewSwap()){
        int choose = randInt(1, 3);
        if (choose == 1) {
            getWorld()->getPlayer(pNum)->teleport();
            //make walk direction invalid so u can choose direction
            getWorld()->playSound(SOUND_PLAYER_TELEPORT);
        } else if (choose == 2) {
            //swap player positions, number of ticks left to move, walk direction, sprite direction, roll/walk state
            swapPlayers(); //don't let it retrigger if they've just been swapped
            setNewSwap(false);
            getWorld()->playSound(SOUND_PLAYER_TELEPORT);
        } else {
            //give vortex to player
            getWorld()->getPlayer(pNum)->giveVortex();
            getWorld()->playSound(SOUND_GIVE_VORTEX);
        }
    }
}

void DroppingSquare::squareAction(int pNum) {
    int choose = randInt(1, 2);
    if (choose == 1) {
        int pCoins = getWorld()->getPlayer(pNum)->getCoins();
        if (pCoins <= 10) {
            getWorld()->getPlayer(pNum)->setCoins(0);
        }
        else {
            getWorld()->getPlayer(pNum)->addCoins(-10);
        }
    } else {
        if (getWorld()->getPlayer(pNum)->getStars() > 0)
            getWorld()->getPlayer(pNum)->addStar(-1);
    }
    getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
}

void Square::doSomething() {
    hasLandedOrPassed(1);
    hasLandedOrPassed(2);
}

//helper functions
void MobileActor::turningPoint() {
    int dir = getWalkDirection();
    if (ticks_to_move % 8 == 0) {
        int newX = 0;
        int newY = 0;
        switch(dir) {
            case (right):
                getPositionInThisDirection(right, 16, newX, newY);
                if (!getWorld()->validPos(newX, newY)) {
                    getPositionInThisDirection(up, 16, newX, newY);
                    if (getWorld()->validPos(newX, newY)){
                        setWalkDirection(up);
                    }
                    getPositionInThisDirection(down, 16, newX, newY);
                    if (getWorld()->validPos(newX, newY))
                        setWalkDirection(down);
                }
                break;
            case(up):
                getPositionInThisDirection(up, 16, newX, newY);
                if (!getWorld()->validPos(newX, newY)) {
                    getPositionInThisDirection(right, 16, newX, newY);
                    if (getWorld()->validPos(newX, newY))
                        setWalkDirection(right);
                    else
                        setWalkDirection(left);
                }
                break;
            case(left):
                getPositionInThisDirection(left, 16, newX, newY);
                if (!getWorld()->validPos(newX, newY)) {
                    getPositionInThisDirection(up, 16, newX, newY);
                    if (getWorld()->validPos(newX, newY))
                        setWalkDirection(up);
                    else
                        setWalkDirection(down);
                }
                break;
            case(down):
                getPositionInThisDirection(down, 16, newX, newY);
                if (!getWorld()->validPos(newX, newY)) {
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
    spriteDirection();
}

void MobileActor::spriteDirection() {
    if (getWalkDirection() == left)
        setDirection(left);
    else
        setDirection(right);
}

void MobileActor::teleport() {
    int randX;
    int randY;
    do {
        randX = randInt(0, SPRITE_WIDTH*BOARD_WIDTH-1);
        randY = randInt(0, SPRITE_HEIGHT*BOARD_HEIGHT-1);
    } while(!getWorld()->validPos(randX, randY));
    moveTo(randX, randY);
}

void Avatar::teleport() {
    MobileActor::teleport();
    
    int newX;
    int newY;
    int randDir;
    do {
        randDir = randInt(0, 3)*90;
        getPositionInThisDirection(randDir, 16, newX, newY);
    } while(!getWorld()->validPos(newX, newY));
    setWalkDirection(randDir);
    spriteDirection();
}

bool MobileActor::checkFork() {
    int newX;
    int newY;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        getPositionInThisDirection(i*90, 16, newX, newY);
        if (getWorld()->validPos(newX, newY))
            count ++;
    }
    if (count >= 3)
        return true;
    return false;
}

void Avatar::giveVortex() {
    hasVortex = true;
}

bool Avatar::keyPressed() {
    int action = getWorld()->getAction(this->getNumPlayer()); //make sure this line works
    int newX;
    int newY;
    switch (action) {
        case ACTION_NONE: {
            return false;
            break;
        }
        case ACTION_UP: { //change direction cases to be more concise
            getPositionInThisDirection(up, 16, newX, newY);
            if (getWorld()->validPos(newX, newY) && getWalkDirection() != down) {
                setWalkDirection(up);
                return true;
            }
            return false;
        }
        case ACTION_DOWN: {
            getPositionInThisDirection(down, 16, newX, newY);
            if (getWorld()->validPos(newX, newY) && getWalkDirection() != up) {
                setWalkDirection(down);
                return true;
            }
            return false;
        }
        case ACTION_RIGHT: {    
            getPositionInThisDirection(right, 16, newX, newY);
            if (getWorld()->validPos(newX, newY) && getWalkDirection() != left) {
                setWalkDirection(right);
                return true;
            }
            return false;
        }
        case ACTION_LEFT: {
            getPositionInThisDirection(left, 16, newX, newY);
            if (getWorld()->validPos(newX, newY) && getWalkDirection() != right) {
                setWalkDirection(left);
                return true;
            }
            return false;
        }
        default:
            return false;
    }
}

void Baddie::whenHit() {
    teleport();
    setWalkDirection(right);
    spriteDirection();
    setState(true);
    setPauseCounter();
}

void Bowser::dropping() {
    int chance = randInt(1, 4);
    if (chance == 3) {
        getWorld()->replace(getX(), getY());
        getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
    }
}

void Vortex::doSomething() {
    if (!isAlive())
        return;
    moveAtAngle(getDirection(), 2); //figure out direction
    
    if (getX() < 0 || getX() >= VIEW_WIDTH || getY() < 0 || getY() >= VIEW_HEIGHT)
        kill();
    
    if (getWorld()->overlap(getX(), getY())) {
        kill();
        getWorld()->playSound(SOUND_HIT_BY_VORTEX);
    }
}

void EventSquare::swapPlayers() {
    int tempX = getWorld()->getPlayer(1)->getX();
    int tempY = getWorld()->getPlayer(1)->getY();
    getWorld()->getPlayer(1)->moveTo(getWorld()->getPlayer(2)->getX(), getWorld()->getPlayer(2)->getY());
    getWorld()->getPlayer(2)->moveTo(tempX, tempY);
    
    int tempPlayer = getWorld()->getPlayer(1)->getTicksToMove();
    getWorld()->getPlayer(1)->setTicksToMove(getWorld()->getPlayer(2)->getTicksToMove());
    getWorld()->getPlayer(1)->setTicksToMove(tempPlayer);
    
    int tempDir = getWorld()->getPlayer(1)->getWalkDirection();
    getWorld()->getPlayer(1)->setWalkDirection(getWorld()->getPlayer(2)->getWalkDirection());
    getWorld()->getPlayer(1)->setWalkDirection(tempDir); //works
    
    getWorld()->getPlayer(1)->spriteDirection();
    getWorld()->getPlayer(2)->spriteDirection();
    
    bool tempState = getWorld()->getPlayer(1)->getState();
    getWorld()->getPlayer(1)->setState(getWorld()->getPlayer(2)->getState());
    getWorld()->getPlayer(1)->setState(tempState);
}
