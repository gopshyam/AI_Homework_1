// Agent.h

#ifndef AGENT_H
#define AGENT_H
#define WORLD_SIZE 1000

#include "Action.h"
#include "Percept.h"
#include "Orientation.h"

class Agent
{
private:
    bool agentHasArrow;
    bool agentHasGold;
    int X;
    int Y;
    Orientation agentOrientation;
    void updateLocation(Action action);
    int location_info[WORLD_SIZE][WORLD_SIZE];
    bool shotOutcome;
    bool correctiveAction;
    bool forwardMove;
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);
};

#endif // AGENT_H
