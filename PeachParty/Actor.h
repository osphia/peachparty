#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int depth) : GraphObject(imageID, startX, startY, right, 0), m_game(world) {};
    virtual void doSomething() = 0;
    virtual bool impacted() {return false;}
    virtual void whenHit() {return;}
    virtual void setIsSquare(bool val) {isSquare = val;}
    
    StudentWorld* getWorld() {return m_game;}
    bool isAlive() { return alive;}
    void kill() {alive = false;}
    bool getIsSquare() {return isSquare;}
private:
    StudentWorld* m_game;
    bool alive = true;
    bool isSquare = false;
    
};

//players
class MobileActor : public Actor {
public:
    MobileActor(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, startX, startY, 0) {}
    virtual void doSomething();
    virtual void doAction() = 0;
    virtual void setPauseCounter() {return;}
    virtual void dropping() {return;}
    virtual bool atFork() = 0;
    //virtual void isValidDirection(){return;}
    
    int getWalkDirection() {return walkDir;}
    void setWalkDirection(int d) {walkDir = d;}
    bool getState() {return state;}
    void setState(bool b) {state = b;}
    int getTicksToMove() {return ticks_to_move;}
    void setTicksToMove(int t) {ticks_to_move = t;}
    void turningPoint();
    void spriteDirection();
    virtual void teleport();
    bool checkFork();
    int getOppDirection(int dir);
    void setForce(int num) {isForce = num;}

private:
    bool state = true; //waiting = true, walking = false
    int ticks_to_move = 0;
    int walkDir = 0;
    int isForce = -1;
};

class Avatar : public MobileActor {
public:
    Avatar(StudentWorld* world, int imageID, int startX, int startY, int spriteDir, int numPlayer): MobileActor(world, imageID, startX, startY, 0), playerNum(numPlayer){}
    virtual void doAction();
    virtual bool atFork();
    //virtual void isValidDirection();
    
    int getNumPlayer() {return playerNum;}
    void addCoins(int num) {numCoins += num;}
    int getCoins() {return numCoins;}
    void setCoins(int num) {numCoins = num;}
    void addStar(int n) {numStars+= n;}
    int getStars() {return numStars;}
    void setStars(int n) {numStars = n;}
    int getRoll() {return m_roll;}
    void setRoll(int roll) {m_roll = roll;}
    bool keyPressed();
    void giveVortex();
    bool hasVortx() {return hasVortex;}
    virtual void teleport();
    
private:
    int playerNum;
    int numCoins = 0;
    int numStars = 0;
    int m_roll = 0;
    bool hasVortex = false;
};

class Peach : public Avatar {
public:
    Peach(StudentWorld* world, int startX, int startY) : Avatar(world, IID_PEACH, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right, 1) {};
private:
};

class Yoshi : public Avatar {
public:
    Yoshi(StudentWorld* world, int startX, int startY) : Avatar(world, IID_YOSHI, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right, 2) {};
private:
};

//baddies
class Baddie : public MobileActor {
public:
    Baddie(StudentWorld* world, int imageID, int startX, int startY) : MobileActor(world, imageID, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right) {};
    virtual void doAction();
    virtual void doBadAction(int pNum) = 0;
    virtual void setPauseCounter(){pauseCounter = 180;}
    virtual bool impacted() {return true;}
    virtual void whenHit();
    virtual bool atFork();
    virtual int squaresToMove() = 0;
private:
    bool newPeach = true;
    bool newYoshi = true;
    int pauseCounter = 180;
    int squares_to_move;
};

class Boo : public Baddie {
public:
    Boo(StudentWorld* world, int startX, int startY) : Baddie(world, IID_BOO, startX, startY) {};
    virtual void doBadAction(int pNum);
    virtual int squaresToMove() {return randInt(1, 3);}
private:

};

class Bowser : public Baddie {
public:
    Bowser(StudentWorld* world, int startX, int startY) : Baddie(world, IID_BOWSER, startX, startY) {};
    virtual void doBadAction(int pNum);
    virtual int squaresToMove() {return randInt(1,10);}
    virtual void dropping();
private:
};

//square
class Square : public Actor {
public:
    Square(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, 1){setIsSquare(true);}
    virtual void doSomething();
    virtual void hasLandedOrPassed(int pNum);
    virtual void squareAction(int pNum) = 0;
    virtual void passAction(int pNum){return;}
    virtual void setNewSwap(bool swap) {newSwap = swap;}
    virtual bool getNewSwap() {return newSwap;}
private:
    bool isAlive;
    bool newPeach = true;
    bool newYoshi = true;
    bool passPeach = true;
    bool passYoshi = true;
    bool newSwap = true;
};

class CoinSquare : public Square {
public:
    CoinSquare(StudentWorld* world, int imageID, int startX, int startY) : Square(world, imageID, startX, startY, 0){};
private:
};

class BlueCoinSquare : public CoinSquare {
public:
    BlueCoinSquare(StudentWorld* world, int startX, int startY) : CoinSquare(world, IID_BLUE_COIN_SQUARE, startX, startY){};
    virtual void squareAction(int pNum);
private:
};

class RedCoinSquare : public CoinSquare {
public:
    RedCoinSquare(StudentWorld* world, int startX, int startY) : CoinSquare(world, IID_RED_COIN_SQUARE, startX, startY){};
    virtual void squareAction(int pNum);
private:
};

class StarSquare : public Square {
public:
    StarSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_STAR_SQUARE, startX, startY, 0){};
    virtual void squareAction(int pNum);
    virtual void passAction(int pNum);
private:
};

class DirectionalSquare : public Square {
public:
    DirectionalSquare(StudentWorld* world, int startX, int startY, int squareDir) : Square(world, IID_DIR_SQUARE, startX, startY, squareDir){setDirection(squareDir); forcingDirection = squareDir;};
    virtual void squareAction(int pNum);
    virtual void passAction(int pNum);
private:
    int forcingDirection;
};

class BankSquare : public Square {
public:
    BankSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_BANK_SQUARE, startX, startY, 0){};
    virtual void squareAction(int pNum);
    virtual void passAction(int pNum);
private:
};

class EventSquare : public Square {
public:
    EventSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_EVENT_SQUARE, startX, startY, 0){};
    virtual void squareAction(int pNum);
    void swapPlayers();
private:
};

class DroppingSquare : public Square {
public:
    DroppingSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_DROPPING_SQUARE, startX, startY, 0){};
    virtual void squareAction(int pNum);
private:
};

class Vortex : public Actor {
public:
    Vortex(StudentWorld* world, int imageID, int startX, int startY, int spriteDir, int dir): Actor(world, IID_VORTEX, startX, startY, 0) {setDirection(dir);}
    virtual void doSomething();
private:
};


#endif // ACTOR_H_
