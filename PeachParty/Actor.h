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
    Player(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, startX, startY, 0){};
    //virtual ~Player();
    virtual void doSomething();
    int getWalkDirection() {return walkDir;}
    void setWalkDirection(int d) {walkDir = d;}
private:
    bool goTo(int m_x, int m_y);
    int numCoins;
    int numStars;
    int playerNum;
    bool state = true; //waiting = true, walking = false
    int ticks_to_move;
    int walkDir = 0;
};

class Peach : public Player {
public:
    Peach(StudentWorld* world, int startX, int startY) : Player(world, IID_PEACH, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, 0) {};
    //virtual ~Peach();
    //virtual void doSomething();
private:
    int numPlayer = 1;
};

//class Yoshi : public Player {
//public:
//    Yoshi(StudentWorld* world, int startX, int startY) : Player(world, IID_YOSHI, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY, 0) {};
//    virtual void doSomething();
//private:
//    int numPlayer = 2;
//};
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
    Square(StudentWorld* world, int imageID, int startX, int startY, int spriteDir): Actor(world, imageID, startX, startY, 1){};
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
    BlueCoinSquare(StudentWorld* world, int startX, int startY) : CoinSquare(world, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH*startX, SPRITE_HEIGHT*startY){};
    virtual void doSomething();
private:
    bool living;
};


//
//class RedCoinSquare : public CoinSquare {
//public:
//
//private:
//
//};
//
//class StarSquare : public Square {
//public:
//
//private:
//
//};
//
//class DirectionalSquare : public Square {
//public:
//
//private:
//
//};
//
//class BankSquare : public Square {
//public:
//
//private:
//
//};
//
//class EventSquare : public Square {
//public:
//
//private:
//
//};
//
//class DroppingSquare : public Square {
//public:
//
//private:
//
//};
//
//class Vortex : public Actor {
//public:
//
//private:
//
//};


#endif // ACTOR_H_
