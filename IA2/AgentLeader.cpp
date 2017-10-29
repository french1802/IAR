#include "AgentLeader.h"
#include "SteeringBehaviors.h"
#include "ParamLoader.h"



AgentLeader::AgentLeader(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale)
	:Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
	m_nJoueur = 0;
	m_icpt = 0;
}


AgentLeader::AgentLeader(AgentPoursuiveur ap)
	: Vehicle(ap.World(), ap.Pos(), RandFloat()*TwoPi, ap.Velocity(), ap.Mass(), ap.MaxForce(), ap.MaxSpeed(), ap.MaxTurnRate(), Prm.VehicleScale)
{
	m_nJoueur = 0;
	m_icpt = 0;
}


void AgentLeader::ActivateLeader(void)
{
	m_nJoueur = 0;
	m_icpt = 0;
	this->Steering()->FlockingOff();
	this->Steering()->WallAvoidanceOn();
	this->SetScale(Vector2D(10, 10));
	this->Steering()->WanderOn();
	this->SetMaxSpeed(70);
	this->FollowingOn();
}

void AgentLeader::ActivatePlayer(void)
{
	m_nJoueur = 1;
	m_icpt = 0;
	this->Steering()->SetFlagsToZero();
	this->SetVelocity(Vector2D(100,0));

}

void AgentLeader::Update(double time_elapsed)
{
	Vehicle::Update(time_elapsed);
	if (m_nJoueur == 1) {
		if (this->m_vVelocity != Vector2D(0, 0)) {
			if (m_icpt == 0) {
				m_icpt = 15;
			}
			else {
				m_icpt--;
				if (m_icpt == 0) {

					this->SetVelocity(Vector2D(0, 0));
				}
			}
		}
	}
}
AgentLeader::~AgentLeader()
{
}
