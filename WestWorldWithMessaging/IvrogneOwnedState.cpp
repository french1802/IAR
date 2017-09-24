#include "IvrogneOwnedState.h"
#include "Ivrogne.h"
#include "EntityNames.h"


#include <iostream>
using namespace std;


SeSaouleAuBar* SeSaouleAuBar::Instance()
{
	static SeSaouleAuBar instance;

	return &instance;
}

void SeSaouleAuBar::Enter(Ivrogne* pIvrogne)
{
	//if the Ivrogne isnt in the bar, he must go to the bar 
	if (pIvrogne->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": " << "Going to get wasted at the saloon";
	
		pIvrogne->ChangeLocation(saloon);
	}
}


void SeSaouleAuBar::Execute(Ivrogne* pIvrogne)
{
	//if the Ivrogne isnt in the bar, he must go to the bar 
	pIvrogne->increaseEbriety();

	if (pIvrogne->isWastedEnough())
	{
		pIvrogne->GetFSM()->ChangeState(DorsChezLui::Instance());
	}
}

void SeSaouleAuBar::Exit(Ivrogne* pIvrogne)
{
	cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": "
		<< "Ah'm leavin' the saloon i can't drink anymore";
}

bool SeSaouleAuBar::OnMessage(Ivrogne* pIvrogne, const Telegram& msg)
{
	//TODO Message reçu par bob
}

DorsChezLui* DorsChezLui::Instance()
{
	static DorsChezLui instance;

	return &instance;
}

void DorsChezLui::Enter(Ivrogne* pIvrogne)
{
	//if the Ivrogne isnt in at home yet, he must go there 
	if (pIvrogne->Location() != home_I)
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": " << "I'm Wasted, I should go to bed!";

		pIvrogne->ChangeLocation(home_I);
	}
}


void DorsChezLui::Execute(Ivrogne* pIvrogne)
{
	pIvrogne->decreaseEbriety();

	if (pIvrogne->isRestedEnough == true)
	{
		pIvrogne->GetFSM()->ChangeState(SeSaouleAuBar::Instance());
	}
}

void DorsChezLui::Exit(Ivrogne* pIvrogne)
{
	cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": "
		<< "Ah'm leavin' my house, another bad day... What COuld I do?";
}

bool DorsChezLui::OnMessage(Ivrogne* pIvrogne, const Telegram& msg)
{
	return false;
}


Altercation* Altercation::Instance()
{
	static Altercation instance;

	return &instance;
}

void Altercation::Enter(Ivrogne* pIvrogne)
{
	//if the Ivrogne isnt in at home yet, he must go there 
	if (pIvrogne->Location() != home_I)
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": " << "I'm Wasted, I should go to bed!";

		pIvrogne->ChangeLocation(home_I);
	}
}


void Altercation::Execute(Ivrogne* pIvrogne)
{
	pIvrogne->decreaseEbriety();

	if (pIvrogne->isRestedEnough == true)
	{
		pIvrogne->GetFSM()->ChangeState(SeSaouleAuBar::Instance());
	}
}

void Altercation::Exit(Ivrogne* pIvrogne)
{
	cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": "
		<< "Ah'm leavin' my house, another bad day... What Could I do?";
}

bool Altercation::OnMessage(Ivrogne* pIvrogne, const Telegram& msg)
{
	return false;
}