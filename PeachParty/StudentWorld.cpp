#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
//    1. Initialize the data structures used to keep track of your game’s world.
//    2. Allocate and insert Peach and Yoshi objects into the game world. Every time a
//    game begins, Peach and Yoshi start out initialized in their starting location as
//    specified by the current board data file.
//    3. Allocate and insert all of the other objects (e.g., squares, baddies, etc.) into the
//    game world as described below.
//    4. Start the countdown timer for the 99-second game.
	startCountdownTimer(5);  // this placeholder causes timeout after 5 seconds
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
//    1. Check if the game is over (i.e., the time remaining is no longer positive). If so:
//    a. Play the SOUND_GAME_FINISHED sound using playSound().
//    b. Call setFinalScore() function to report the number of stars and coins of the
//    winning player.
//    c. If Peach won, return GWSTATUS_PEACH_WON. If Yoshi won, return
//    GWSTATUS_YOSHI_WON. If the game was a tie game, pick a winner randomly
//    and return one of the above return values.
//    2. It must ask all of the actors that are currently active in the game world to do
//    something (e.g., ask each Bowser to move itself, ask each Vortex projectile to
//    check if it overlaps with a baddie, and if so, teleport the baddie to a random
//    square, give Peach and Yoshi both a chance to move, roll, or shoot a Vortex, etc.).
//    3. It must then delete any actors that have become inactive/dead during this tick
//    (e.g., a Vortex that flies off the screen and needs to be removed from the game).
//    4. It must update the status text on the top of the screen with the latest information
//    (e.g., each player's stats).
//    5. If the game is not over, then the function must return GWSTATUS_CONTINUE_GAME.
    // PSEUDOCODE ON PG 19
    
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    setGameStatText("Game will end in a few seconds");
    
    if (timeRemaining() <= 0)
		return GWSTATUS_NOT_IMPLEMENTED;
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}
