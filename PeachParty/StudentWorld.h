#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Board.h"
#include <string>
#include <list>

class Actor;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    void addActor(Actor* act);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool validPos(int x, int y);

private:
    int m_lives;
    int m_stars;
    int m_coins;
    int m_boardNumber;
    Actor* peach;
    Actor* yoshi;
    std::list<Actor*> actors;
};

#endif // STUDENTWORLD_H_
