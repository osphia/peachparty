#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0);
    virtual ~Actor();
    virtual void doSomething();
    virtual void moveTo(int x, int y)
    {
    }
private:
    StudentWorld* m_game;
    int m_imageID;
    int m_x;
    int m_y;
};

//players
class Player : public Actor {
public:
    Player(int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0);
    virtual void doSomething();
private:
    int playerNum;
};

class Peach : public Player {
public:
    Peach(int startX, int startY) : Player(IID_PEACH, startX, startY) {};
    virtual void doSomething();
private:
    
};

class Yoshi : public Player {
public:
    Yoshi(int startX, int startY) : Player(IID_YOSHI, startX, startY) {};
    virtual void doSomething();
private:
};

//baddies
class Baddie : public Actor {
public:
    
private:
    
};

class Boo : public Baddie {
public:
    
private:
    
};

class Bowser : public Baddie {
public:
    
private:
    
};

//square
class Square : public Actor {
public:
    
private:
    
};

class CoinSquare : public Square {
public:
    
private:
    
};

class BlueCoinSquare : public CoinSquare {
public:
    
private:
    
};

class RedCoinSquare : public CoinSquare {
public:
    
private:
    
};

class StarSquare : public Square {
public:
    
private:
    
};

class DirectionalSquare : public Square {
public:
    
private:
    
};

class BankSquare : public Square {
public:
    
private:
    
};

class EventSquare : public Square {
public:

private:
    
};

class DroppingSquare : public Square {
public:
    
private:
    
};

class Vortex : public Actor {
public:
    
private:
    
};
#endif // ACTOR_H_
