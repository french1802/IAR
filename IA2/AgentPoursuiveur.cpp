#include "AgentPoursuiveur.h"
#include "GameWorld.h"
#include "SteeringBehaviors.h"

using std::vector;

AgentPoursuiveur::AgentPoursuiveur(GameWorld* world, Vector2D position,	double rotation, Vector2D velocity,	double mass, double max_force, double max_speed,double max_turn_rate,double scale)
	:Vehicle(world, position, rotation,velocity,mass,max_force, max_speed,max_turn_rate,scale)
{
}

AgentPoursuiveur::AgentPoursuiveur(AgentLeader ap)
	: Vehicle(ap.World(), ap.Pos(), RandFloat()*TwoPi, ap.Velocity(), ap.Mass(), ap.MaxForce(), ap.MaxSpeed(), ap.MaxTurnRate(), Prm.VehicleScale)
{

}

void AgentPoursuiveur::Update(double time_elapsed)
{
	Vehicle::Update(time_elapsed);
	if (!this->isFollowingOn())
	{
		if (this->getIcpt() == 0) {


			vector<Vehicle*> neighbors = this->World()->Agents();

			unsigned int agentVoisin = 0;
			boolean continu = true;
			while ((agentVoisin < neighbors.size()) && continu)
			{
				if ((neighbors[agentVoisin] != this) &&
					(neighbors[agentVoisin]->isFollowingOn()) &&
					(!neighbors[agentVoisin]->isFollowedOn()))
				{
					this->Steering()->OffsetPursuitOn(neighbors[agentVoisin], Vector2D(-30, 0));
					this->Steering()->FlockingOff();
					this->Steering()->SeparationOn();
					neighbors[agentVoisin]->FollowedOn();
					int i = this->getIcpt();
					i++;
					this->setIcpt(i);
					continu = false;
				}
				agentVoisin++;
			}
		}
		else {
			this->FollowingOn();
			this->setIcpt(0);
		}
	}

}

AgentPoursuiveur::~AgentPoursuiveur()
{
}
