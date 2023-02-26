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
    virtual bool isAlive() { return alive; }
private:
    StudentWorld* m_game;
    bool alive = true;
};

//players
class MobileActor : public Actor {
public:
    MobileActor(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, startX, startY, 0) {};
    //virtual ~Player();
    virtual void doSomething();
    virtual void doAction() = 0;
    virtual void attemptWalk() = 0;
    int getWalkDirection() {return walkDir;}
    void setWalkDirection(int d) {walkDir = d;}
    virtual void turningPoint();
    virtual void setPauseCounter() = 0;
protected:
    bool state = true; //waiting = true, walking = false
    int ticks_to_move = 0;
    int walkDir = 0;
};

class Avatar : public MobileActor {
public:
    Avatar(StudentWorld* world, int imageID, int startX, int startY, int spriteDir, int numPlayer): MobileActor(world, imageID, startX, startY, 0), playerNum(numPlayer){};
    //virtual void doSomething();
    virtual void doAction();
    virtual void attemptWalk();
    void setPauseCounter() {return;}
    int getNumPlayer() {return playerNum;}
private:
    int playerNum;
    int numCoins = 0;
    int numStars = 0;
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
    virtual void doBadAction() = 0;
    virtual void attemptWalk();
    void setPauseCounter() {pauseCounter = 180;}
protected:
    int pauseCounter = 180;
    int squares_to_move;
};

class Boo : public Baddie {
public:
    Boo(StudentWorld* world, int startX, int startY) : Baddie(world, IID_BOO, startX, startY) {};
    virtual void doBadAction();
private:

};

class Bowser : public Baddie {
public:
    Bowser(StudentWorld* world, int startX, int startY) : Baddie(world, IID_BOWSER, startX, startY) {};
    virtual void doBadAction();
private:

};

////square
class Square : public Actor {
public:
    Square(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, 1){};
private:
    bool isAlive;
};

class CoinSquare : public Square {
public:
    CoinSquare(StudentWorld* world, int imageID, int startX, int startY) : Square(world, imageID, startX, startY, 0){};
private:

};

class BlueCoinSquare : public CoinSquare {
public:
    BlueCoinSquare(StudentWorld* world, int startX, int startY) : CoinSquare(world, IID_BLUE_COIN_SQUARE, startX, startY){};
    virtual void doSomething();
private:
    bool living;
};

class RedCoinSquare : public CoinSquare {
public:
    RedCoinSquare(StudentWorld* world, int startX, int startY) : CoinSquare(world, IID_RED_COIN_SQUARE, startX, startY){};
    virtual void doSomething();
private:
    bool living;
};

class StarSquare : public Square {
public:
    StarSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_STAR_SQUARE, startX, startY, 0){};
    virtual void doSomething();
private:
};

class DirectionalSquare : public Square {
public:
    DirectionalSquare(StudentWorld* world, int startX, int startY, int squareDir) : Square(world, IID_DIR_SQUARE, startX, startY, squareDir){setDirection(squareDir);};
    virtual void doSomething();
private:
};

class BankSquare : public Square {
public:
    BankSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_BANK_SQUARE, startX, startY, 0){};
    virtual void doSomething();
private:
};

class EventSquare : public Square {
public:
    EventSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_EVENT_SQUARE, startX, startY, 0){};
    virtual void doSomething();
private:
};

class DroppingSquare : public Square {
public:
    DroppingSquare(StudentWorld* world, int startX, int startY) : Square(world, IID_DROPPING_SQUARE, startX, startY, 0){};
    virtual void doSomething();
private:
};

//
//class Vortex : public Actor {
//public:
//
//private:
//
//};


#endif // ACTOR_H_
