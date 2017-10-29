#ifndef LEADER_H
#define LEADER_H



#pragma once
#include "Vehicle.h"
#include "AgentPoursuiveur.h"

class AgentPoursuiveur;

class AgentLeader :
	public Vehicle
{
private:
	int m_nJoueur;
	int m_icpt;
public:
	AgentLeader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);

	AgentLeader(AgentPoursuiveur);
	void Update(double time_elapsed);
	void ActivatePlayer(void);
	void ActivateLeader(void);
	~AgentLeader();
};


#endif

