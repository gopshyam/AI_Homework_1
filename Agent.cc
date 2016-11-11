// Agent.cc

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Agent.h"
#include "Orientation.h"

#define UNEXPLORED 0
#define VISITED 1
#define SAFE 2
#define UNSAFE 3

using namespace std;

Agent::Agent ()
{
    agentHasArrow = true;
    agentHasGold = false;
    X = 0;
    Y = 0;
    agentOrientation = RIGHT;
    shotOutcome = false;
    forwardMove = false;
    wumpusKilled = false;

    //initialize location values
    for (int i = 0; i < WORLD_SIZE; i++){
        for (int j = 0; j < WORLD_SIZE; j++) {
            location_info[i][j] = UNEXPLORED;
        }
    }
}

Agent::~Agent ()
{
    
}

void Agent::Initialize ()
{

}

void Agent::updateLocation(Action action) {
    if (forwardMove){
        switch(agentOrientation){
            case UP:
                Y++;
                break;
            case DOWN:
                Y--;
                break;
            case RIGHT:
                X++;
                break;
            case LEFT:
                X--;
                break;
        }
        return;
    }

    if (action == TURNRIGHT) {
        switch(agentOrientation){
            case UP:
                agentOrientation = RIGHT;
                break;
            case DOWN:
                agentOrientation = LEFT;
                break;
            case RIGHT:
                agentOrientation = DOWN;
                break;
            case LEFT:
                agentOrientation = UP;
                break;
        }
        return;
    }

    if (action == TURNLEFT) {
        switch(agentOrientation){
            case UP:
                agentOrientation = LEFT;
                break;
            case DOWN:
                agentOrientation = RIGHT;
                break;
            case RIGHT:
                agentOrientation = UP;
                break;
            case LEFT:
                agentOrientation = DOWN;
                break;
        }
        return;
    }
}

                

void Agent::markDangerous(){
    int x = X, y = Y;

    if (x-1 >= 0) {
        if (location_info[x-1][Y] != VISITED && location_info[x-1][Y] != SAFE) {
            location_info[x-1][Y] = UNSAFE;
        }
    }
    if (y-1 >= 0) {
        if (location_info[X][y-1] != VISITED && location_info[X][y-1] != SAFE) {
            location_info[X][y-1] = UNSAFE;
        }
    }

    if (location_info[x+1][Y] != VISITED && location_info[x+1][Y] != SAFE) {
        location_info[x+1][Y] = UNSAFE;
    }

    if (location_info[X][y+1] != VISITED && location_info[X][y+1] != SAFE) {
        location_info[X][y+1] = UNSAFE;
    }
}

void Agent::markSafe(){
    int x = X, y = Y;

    if (x-1 >=0 ) {
        if (location_info[x-1][Y] != VISITED){
            location_info[x-1][Y] = SAFE;
        }
    }

    if (x-1 >=0 ) {
        if (location_info[X][y-1] != VISITED){
            location_info[X][y-1] = SAFE;
        }
    }

    if (location_info[x+1][Y] != VISITED){
            location_info[x+1][Y] = SAFE;
        }

    if (location_info[X][y+1] != VISITED){
            location_info[X][y+1] = SAFE;
        }

}


Action Agent::Process (Percept& percept)
{
	char c;
	Action action;
	bool validAction = false;

    if (forwardMove && !percept.Bump){
        updateLocation(GOFORWARD);
    }
    forwardMove = false;
    location_info[X][Y] = VISITED;

    if (percept.Stench && !wumpusKilled) {
        markDangerous();
    } else {
        markSafe();
    }
    
    
    if (shotOutcome == true) {
        if (percept.Scream) {
            //Mark the wumpus killeda
            wumpusKilled = true;
        } else {
            //Mark adjacent squares as safe as the arrow missed
            switch(agentOrientation) {
                case UP:
                    location_info[X][Y+1] = SAFE;
                    break;
                case DOWN:
                    location_info[X][Y-1] = SAFE;
                    break;
                case LEFT:
                    location_info[X-1][Y] = SAFE;
                    break;
                case RIGHT:
                    location_info[X+1][Y] = SAFE;
                    break;
            }
            
            correctiveAction = true;
            action = TURNRIGHT;
            validAction = true;
        }
        shotOutcome = false;
    }

    if (agentHasGold && X == 0 && Y == 0) {
        action = CLIMB;
        validAction = true;
    }
    if (!validAction && percept.Bump) {
        action = TURNLEFT;
        if (correctiveAction) {
            action = TURNRIGHT;
        }
        validAction = true;
    }
    if (!validAction && percept.Glitter) {
        action = GRAB;
        validAction = true;
        agentHasGold = true;
    }
    if (!validAction && percept.Stench && agentHasArrow) {
        action = SHOOT;
        shotOutcome = true;
        validAction = true;
        agentHasArrow = false;
    }
    if (!validAction) {
        action = GOFORWARD;
        forwardMove = true;
        validAction = true;
    }
    



	while (! validAction)
	{
		validAction = true;
		cout << "Action? ";
		cin >> c;
		if (c == 'f') {
			action = GOFORWARD;
		} else if (c == 'l') {
			action = TURNLEFT;
		} else if (c == 'r') {
			action = TURNRIGHT;
		} else if (c == 'g') {
			action = GRAB;
		} else if (c == 's') {
			action = SHOOT;
		} else if (c == 'c') {
			action = CLIMB;
		} else {
			cout << "Huh?" << endl;
			validAction = false;
		}
	}

    updateLocation(action);
	return action;
}

void Agent::GameOver (int score)
{

}

