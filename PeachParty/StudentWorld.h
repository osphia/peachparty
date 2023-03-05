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
    Actor* getPlayer(int pNum);
    int getBankBalance() {return bankBalance;}
    void changeBankBalance(int num) {bankBalance += num;}
    void clearBankBalance() {bankBalance = 0;}
    void replace(int x, int y);
    bool yoshiWon();
    double distance(int x1, int x2, int y1, int y2);
    bool overlap(int x, int y);
    void spawnVortex(int x, int y, int dir);

private:
    int m_lives;
    int bankBalance = 0;
    int m_boardNumber;
    Actor* peach;
    Actor* yoshi;
    std::list<Actor*> actors;
};

#endif // STUDENTWORLD_H_
