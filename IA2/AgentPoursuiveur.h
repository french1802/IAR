#ifndef POURSUIVEUR_H
#define POURSUIVEUR_H

#pragma once
#include "Vehicle.h"
class AgentPoursuiveur :
	public Vehicle
{
public:
	AgentPoursuiveur(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);

	void Update(double time_elapsed);
	~AgentPoursuiveur();
};

#endif