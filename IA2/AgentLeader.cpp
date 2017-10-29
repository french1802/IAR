#include "AgentLeader.h"
#include "SteeringBehaviors.h"




AgentLeader::AgentLeader(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale)
	:Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
}


void AgentLeader::ActivateLeader(void)
{
	this->Steering()->FlockingOff();
	this->SetScale(Vector2D(10, 10));
	this->Steering()->WanderOn();
	this->SetMaxSpeed(70);
	this->FollowingOn();
}



AgentLeader::~AgentLeader()
{
}
