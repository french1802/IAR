#ifndef IVROGNE_H
#define IVROGNE_H
//-----------------------
//
// Name : Ivrogne
//
// Desc : A class defining an Ivrogne
// Author : Frnaçois Duport
//
//------------------------

#include "BaseGameEntity.h"
#include "fsm/StateMachine.h"
#include "Locations.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//The amount the ivrogne can drink before he has to go to sleep
const int EbrietyMaxLevel = 20;
//The amount of drink the ivrogne need to drink before he'll fight Bob
const int EbrietyAgressiveLevel = 15;
//The minimum the ivrogne has to sleep before he sober up
const int sleepTimeMin = 3;
//The maximum the ivrogne has to sleep before he sober up
const int sleepTimeMax = 8;



class Ivrogne :
	public BaseGameEntity
{
private: 
	StateMachine<Ivrogne>* m_pStateMAchine;


public:
	Ivrogne();
	~Ivrogne();
};




#endif