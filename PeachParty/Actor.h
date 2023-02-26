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
class Player : public Actor {
public:
    Player(StudentWorld* world, int imageID, int startX, int startY, int spriteDir, int numPlayer): Actor(world, imageID, startX, startY, 0), playerNum(numPlayer){};
    //virtual ~Player();
    virtual void doSomething();
    int getWalkDirection() {return walkDir;}
    void setWalkDirection(int d) {walkDir = d;}
    int getNumPlayer() {return playerNum;}
private:
    bool goTo(int m_x, int m_y);
    int numCoins = 0;
    int numStars = 0;
    bool hasVortex = false;
    int playerNum;
    bool state = true; //waiting = true, walking = false
    int ticks_to_move = 0;
    int walkDir = 0;
};

class Peach : public Player {
public:
    Peach(StudentWorld* world, int startX, int startY) : Player(world, IID_PEACH, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right, 1) {};
    //virtual ~Peach();
    //virtual void doSomething();
private:
};

class Yoshi : public Player {
public:
    Yoshi(StudentWorld* world, int startX, int startY) : Player(world, IID_YOSHI, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, right, 2) {};
    //virtual void doSomething();
private:
};
//
////baddies
//class Baddie : public Actor {
//public:
//
//private:
//
//};
//
//class Boo : public Baddie {
//public:
//
//private:
//
//};
//
//class Bowser : public Baddie {
//public:
//
//private:
//
//};
//
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
