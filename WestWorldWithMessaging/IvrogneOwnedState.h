#ifndef IVROGNE_OWNED_STATES_H
#define IVROGNE_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Ivrogne;
struct Telegram;




//------------------------------------------------------------------------
//
//  In this state the miner will walk to a goldmine and pick up a nugget
//  of gold. If the miner already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class SeSaouleAuBar : public State<Ivrogne>
{
private:

	SeSaouleAuBar() {}

	//copy ctor and assignment should be private
	SeSaouleAuBar(const SeSaouleAuBar&);
	SeSaouleAuBar& operator=(const SeSaouleAuBar&);

public:

	//this is a singleton
	static SeSaouleAuBar* Instance();

	virtual void Enter(Ivrogne* pIvrogne);

	virtual void Execute(Ivrogne* pIvrogne);

	virtual void Exit(Ivrogne* pIvrogne);

	virtual bool OnMessage(Ivrogne* pIvrogne, const Telegram& msg);

};

class DorsChezLui : public State<Ivrogne>
{
private:

	DorsChezLui() {}

	//copy ctor and assignment should be private
	DorsChezLui(const DorsChezLui&);
	DorsChezLui& operator=(const DorsChezLui&);

public:

	//this is a singleton
	static DorsChezLui* Instance();

	virtual void Enter(Ivrogne* ivrogne);

	virtual void Execute(Ivrogne* ivrogne);

	virtual void Exit(Ivrogne* ivrogne);

	virtual bool OnMessage(Ivrogne* agent, const Telegram& msg);

};



class Altercation : public State<Ivrogne>
{
private:

	Altercation() {}

	//copy ctor and assignment should be private
	Altercation(const Altercation&);
	Altercation& operator=(const Altercation&);

public:

	//this is a singleton
	static Altercation* Instance();

	virtual void Enter(Ivrogne* ivrogne);

	virtual void Execute(Ivrogne* ivrogne);

	virtual void Exit(Ivrogne* ivrogne);

	virtual bool OnMessage(Ivrogne* agent, const Telegram& msg);

};

#endif


