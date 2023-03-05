#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int depth) : GraphObject(imageID, startX, startY, right, 0), m_game(world) {};
    //virtual ~Actor();
    virtual void doSomething() = 0;
    StudentWorld* getWorld() {return m_game;}
    virtual bool isAlive() { return alive;}
    virtual void kill() {alive = false;}
    virtual int getWalkDirection() {return -1;}
    virtual void setWalkDirection(int d) {return;}
    virtual bool getState() {return false;}
    virtual void setState(bool b) {return;}
    virtual int getTicksToMove() {return -1;} //change all of these bruh
    virtual void setTicksToMove(int t) {return;}
    virtual void addCoins(int num) {return;}
    virtual void setCoins(int num) {return;} //change
    virtual int getCoins() {return 1;} //delete later
    virtual int getStars() {return 1;} //change later
    virtual void addStar(int n) {return;}
    virtual void setStars(int n) {return;}
    virtual int getRoll() {return 1;}
    virtual bool impacted() {return false;}
    virtual void teleport() {return;}
    virtual int getForce() {return -2;}
    virtual void setForce(int num) {return;}
    virtual void whenHit() {return;}
    virtual void giveVortex(){return;}
    virtual bool hasVortx() {return false;}
    virtual void setIsSquare(bool val) {isSquare = val;}
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
    //virtual ~Player();
    virtual void doSomething();
    virtual void doAction() = 0;
    virtual void attemptWalk() = 0;
    virtual int getWalkDirection() {return walkDir;}
    virtual void setWalkDirection(int d) {walkDir = d;}
    virtual bool getState() {return state;}
    virtual void setState(bool b) {state = b;}
    virtual int getTicksToMove() {return ticks_to_move;}
    virtual void setTicksToMove(int t) {ticks_to_move = t;}
    virtual void turningPoint();
    void spriteDirection();
    virtual void teleport();
    bool checkFork();
    int getOppDirection(int dir);
    virtual void setPauseCounter() = 0;
    virtual bool atFork() = 0;
    virtual int getForce() {return isForce;}
    virtual void setForce(int num) {isForce = num;}
    virtual void dropping(){return;}
private: //CHANGE, not allowed protected
    bool state = true; //waiting = true, walking = false
    int ticks_to_move = 0;
    int walkDir = 0;
    int isForce = -1;
};

class Avatar : public MobileActor {
public:
    Avatar(StudentWorld* world, int imageID, int startX, int startY, int spriteDir, int numPlayer): MobileActor(world, imageID, startX, startY, 0), playerNum(numPlayer){}
    //virtual void doSomething();
    virtual void doAction();
    virtual void attemptWalk();
    void setPauseCounter() {return;}
    int getNumPlayer() {return playerNum;}
    void addCoins(int num) {numCoins += num;}
    int getCoins() {return numCoins;}
    void setCoins(int num) {numCoins = num;}
    int getStars() {return numStars;}
    void addStar(int n) {numStars+= n;}
    void setStars(int n) {numStars = n;}
    int getRoll() {return m_roll;}
    void setRoll(int roll) {m_roll = roll;}
    bool keyPressed();
    virtual bool atFork();
    virtual void giveVortex();
    virtual bool hasVortx() {return hasVortex;}
    
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
    //virtual ~Peach();
    //virtual void doSomething();
private:
};

class Yoshi : public Avatar {
public:
    Yoshi(StudentWorld* world, int startX, int startY) : Avatar(world, IID_YOSHI, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right, 2) {};
    //virtual void doSomething();
private:
};

//baddies
class Baddie : public MobileActor {
public:
    Baddie(StudentWorld* world, int imageID, int startX, int startY) : MobileActor(world, imageID, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right) {};
    virtual void doAction();
    virtual void doBadAction(int pNum) = 0;
    virtual void attemptWalk();
    virtual void setPauseCounter();
    virtual bool impacted() {return true;}
    virtual void whenHit();
    virtual bool atFork();
protected: //no protected, CHANGE
    bool newPeach = true;
    bool newYoshi = true;
    int pauseCounter = 180;
    int squares_to_move;
};

class Boo : public Baddie {
public:
    Boo(StudentWorld* world, int startX, int startY) : Baddie(world, IID_BOO, startX, startY) {};
    virtual void doBadAction(int pNum);
private:

};

class Bowser : public Baddie {
public:
    Bowser(StudentWorld* world, int startX, int startY) : Baddie(world, IID_BOWSER, startX, startY) {};
    virtual void doBadAction(int pNum);
    virtual void dropping();
private:
};

//square
class Square : public Actor {
public:
    Square(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, 1){setIsSquare(true);}
    virtual void doSomething();
    virtual void hasLandedOrPassed(int pNum);
    virtual void squareAction(int pNum){} //change to pure virtual
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
    virtual void doSomething();
private:
    bool living = true;
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
