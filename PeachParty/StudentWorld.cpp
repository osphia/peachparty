#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <list>

using namespace std;

GameWorld* createStudentWorld(string assetPath) {
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath) {
}

//adding actors
void StudentWorld::addActor(Actor* act) {
    actors.push_back(act);
}

//destructor
StudentWorld::~StudentWorld() {
    cleanUp();
}


int StudentWorld::init()
{
    m_boardNumber = getBoardNumber();
    
    Board bd;
    string bdNum = "0" + to_string(m_boardNumber);
    string board_file = assetPath() + "board" + bdNum + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found || result == Board::load_fail_bad_format)
        return GWSTATUS_BOARD_ERROR;
    else if (result == Board::load_success) {
        //cerr << "Successfully loaded board\n";
        for (int i = 0; i < SPRITE_WIDTH; i ++) {
            for (int j = 0; j < SPRITE_HEIGHT; j++) {
                Board::GridEntry ge = bd.getContentsOf(i, j);
                switch (ge) {
                    case Board::empty:
                        break;
                    case Board::boo:
                        addActor(new Boo(this, i, j));
                        addActor(new BlueCoinSquare(this, i, j));
                        break;
                    case Board::bowser:
                        addActor(new Bowser(this, i, j));
                        addActor(new BlueCoinSquare(this, i, j));
                        break;
                    case Board::player:
                        peach = new Peach(this, i, j);
                        yoshi = new Yoshi(this, i,j);
                        addActor(new BlueCoinSquare(this, i, j));
                        break;
                    case Board::red_coin_square:
                        addActor(new RedCoinSquare(this, i, j));
                        break;
                    case Board::blue_coin_square:
                        addActor(new BlueCoinSquare(this, i, j));
                        break;
                    case Board::up_dir_square:
                        addActor(new DirectionalSquare(this, i, j, 90));
                        break;
                    case Board::down_dir_square:
                        addActor(new DirectionalSquare(this, i, j, 270));
                        break;
                    case Board::left_dir_square:
                        addActor(new DirectionalSquare(this, i, j, 180));
                        break;
                    case Board::right_dir_square:
                        addActor(new DirectionalSquare(this, i, j, 0));
                        break;
                    case Board::event_square:
                        addActor(new EventSquare(this, i, j));
                        break;
                    case Board::bank_square:
                        addActor(new BankSquare(this, i, j));
                        break;
                    case Board::star_square:
                        addActor(new StarSquare(this, i, j));
                        break;
                }
            }
        }
    }
        startCountdownTimer(99);  // this placeholder causes timeout after 5 seconds
        return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //all actors do something
    if (peach->isAlive())
        peach->doSomething();
    if (yoshi->isAlive())
        yoshi->doSomething();
    for (list<Actor*>::iterator itr = actors.begin(); itr != actors.end(); itr++) {
        if ((*itr)->isAlive()) {
            (*itr)->doSomething();
        } else {
            delete *itr;
            itr = actors.erase(itr);
        }
    }
    
    //update status text
    string p1Vortex = "";
    string p2Vortex = "";
    if (getPlayer(1)->hasVortx()) {
        p1Vortex = " VOR";
    }
    if (getPlayer(1)->hasVortx()) {
        p2Vortex = " VOR";
    }
    string stats = "P1 Roll: " + to_string(this->getPlayer(1)->getTicksToMove()/8) + " Stars: " + to_string(this->getPlayer(1)->getStars()) + " $$: " + to_string(this->getPlayer(1)->getCoins()) + p1Vortex + " | Time: " + to_string(timeRemaining()) + " | Bank: " + to_string(this->getBankBalance()) + " | P2 Roll: " + to_string(this->getPlayer(2)->getTicksToMove()/8) + " Stars: " + to_string(this->getPlayer(2)->getStars()) + " $$: " +  to_string(this->getPlayer(2)->getCoins()) + p2Vortex;
    setGameStatText(stats);
    
    //check if game is over
    if (timeRemaining() <= 0) {
        playSound(SOUND_GAME_FINISHED);
        if (yoshiWon()) {
            setFinalScore(getPlayer(2)->getStars(), getPlayer(2)->getCoins());
            return GWSTATUS_YOSHI_WON;
        } else {
            setFinalScore(getPlayer(1)->getStars(), getPlayer(1)->getCoins());
            return GWSTATUS_PEACH_WON;
        }
    }
    
    //continue
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    it = actors.begin();
    
    while (it != actors.end()) {
        delete *it;
        it = actors.erase(it);
    }
    
    delete peach;
    peach = nullptr;
    delete yoshi;
    yoshi = nullptr;
}


//helper functions

bool StudentWorld::validPos(int x, int y) { //change later
    m_boardNumber = getBoardNumber();

    Board bd;
    string bdNum = "0" + to_string(m_boardNumber);
    string board_file = assetPath() + "board" + bdNum + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found || result == Board::load_fail_bad_format)
        return GWSTATUS_BOARD_ERROR;
    else if (result == Board::load_success) {
        //cerr << "Successfully loaded board\n";
    }

    Board::GridEntry ge = bd.getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT);
    //cerr << x << " " << y << endl;
    //cerr << x/SPRITE_WIDTH << " " << y/SPRITE_HEIGHT << endl;
    if (ge != Board::empty && x%16 == 0 && y%16 == 0) {
        return true;
    }
    return false;
}

Actor* StudentWorld::getPlayer(int pNum) {
    if (pNum == 1)
        return peach;
    return yoshi;
}

void StudentWorld::replace(int x, int y) {
    for (list<Actor*>::iterator it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->getX() == x && (*it)->getY() == y && (*it)->getIsSquare()) {
            delete *it;
            it = actors.erase(it);
        }
    }
    addActor(new DroppingSquare(this, x/SPRITE_WIDTH, y/SPRITE_HEIGHT));
}

bool StudentWorld::yoshiWon() {
    if (getPlayer(2)->getStars() > getPlayer(1)->getStars())
        return true;
    else if (getPlayer(2)->getStars() < getPlayer(1)->getStars())
        return false;
    else {
        if (getPlayer(2)->getCoins() > getPlayer(1)->getCoins())
            return true;
        else if (getPlayer(2)->getCoins() < getPlayer(1)->getCoins())
            return false;
    }
    
    int chance = randInt(1, 2);
    if (chance == 1)
        return false;
    else
        return true;
}

double StudentWorld::distance(int x1, int x2, int y1, int y2){
    return pow(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0), 0.5);
}

bool StudentWorld::overlap(int x, int y) {
    for (list<Actor*>::iterator itr = actors.begin(); itr != actors.end(); itr++) {
        if ((*itr)->impacted()) {
            int actX = (*itr)->getX();
            int actY = (*itr)->getY();
            if (distance(actX, x, actY, y) <= 16) {//idk bro?
                (*itr)->whenHit(); //will only kill first one in list
                return true;
            }
        }
    }
    return false;
}

void StudentWorld::spawnVortex(int x, int y, int dir) {
    addActor(new Vortex(this, IID_VORTEX, x, y, 0, dir));
}
