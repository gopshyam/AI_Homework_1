// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"
#include "Location.h"
#include "WumpusWorld.h"

class Agent
{
private:
    Location unsafe_locations[1000];
    int num_unsafe_locations;
    void add_to_unsafe_locations(Location location);
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept, WumpusWorld& wumpusWorld);
	void GameOver (int score);
};

#endif // AGENT_H
