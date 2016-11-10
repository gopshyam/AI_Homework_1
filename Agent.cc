// Agent.cc

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Agent.h"
#include "Location.h"
#include "WumpusWorld.h"

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
    num_unsafe_locations = 0;
}

void Agent::add_to_unsafe_locations(Location location)
{
    unsafe_locations[num_unsafe_locations] = location;
    num_unsafe_locations++;
}

bool action_is_valid(WumpusWorld wumpusWorld, int Action, Location unsafe_locations[]) {
    return true;
}

Action Agent::Process (Percept& percept, WumpusWorld& wumpusWorld)
{
	char c;
	Action action;
	bool validAction = false;

    add_to_unsafe_locations(wumpusWorld.currentState.agentLocation);

    srand((unsigned)time(0)); 
    int action_index = (rand()%3);

    switch (action_index) {
        case 0:
            action = GOFORWARD;
        case 1:
            action = TURNLEFT;
        case 2:
            action = TURNRIGHT;
    }

    if (action_is_valid(wumpusWorld, action, unsafe_locations)) {
        return action;
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
	return action;
}

void Agent::GameOver (int score)
{

}

