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
#include "IvrogneOwnedState.h"
#include "misc/ConsoleUtils.h"
#include "misc/utils.h"
#include <Time.h>
#include <string>
#include <cassert>
#include <iostream>


template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//The amount the ivrogne can drink before he has to go to sleep
const int EbrietyMaxLevel = 40;
//The amount of drink the ivrogne need to drink before he'll fight Bob
const int EbrietyAgressiveLevel = 10;
//The minimum the ivrogne has to be sober up before wake up
const int sleepTimeMin = 4;




class Ivrogne :
	public BaseGameEntity
{
private: 
	StateMachine<Ivrogne>* m_pStateMachine;

	location_type m_Location;

	// How many drinks the Ivrogne already has in him
	int m_iEbriety;

public:
	Ivrogne(int id) :m_Location(home_I),
		m_iEbriety(0),
		BaseGameEntity(id)
	{
	
		m_pStateMachine = new StateMachine<Ivrogne>(this);

		m_pStateMachine->SetCurrentState(SeSaouleAuBar::Instance());
	}

	~Ivrogne() { delete m_pStateMachine; }

	void Update();

	virtual bool HandleMessage(const Telegram& msg);

	StateMachine<Ivrogne>* GetFSM()const { return m_pStateMachine; }


	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	void		  increaseEbriety() { m_iEbriety++; }
	void		  decreaseEbriety() { m_iEbriety--; }
	void		  setEbrietyMax() { m_iEbriety = EbrietyMaxLevel; }

	bool		  isRestedEnough() { return m_iEbriety <= RandInt(0,sleepTimeMin+1); }
	bool		  isDrunkEnough()  { return m_iEbriety >= EbrietyAgressiveLevel; }
	bool		  isWastedEnough() { return m_iEbriety >= EbrietyMaxLevel; }
};




#endif