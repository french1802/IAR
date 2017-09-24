#include "IvrogneOwnedState.h"
#include "Ivrogne.h"
#include "EntityNames.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "misc\utils.h"
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
	if (pIvrogne->GetFSM()->CurrentState() == Altercation::Instance())
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": "
			<< "I sure will win, you moron!";
	}
	else
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": "
			<< "Ah'm leavin' the saloon i can't drink anymore";
	}
}

bool SeSaouleAuBar::OnMessage(Ivrogne* pIvrogne, const Telegram& msg)
{
	SetTextColor(BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
		case Msg_InTheBar:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pIvrogne->ID()) <<
				" at time: " << Clock->GetCurrentTime();
			if (pIvrogne->isDrunkEnough() == true)
			{
				SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": You my nemesis bob, you stole my drink! Come Fight Me!";

				//Begin the fight
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
					pIvrogne->ID(),
					ent_Miner_Bob,
					Msg_WantToFight,
					NO_ADDITIONAL_INFO);

				pIvrogne->GetFSM()->SetCurrentState(Altercation::Instance());
			}
			else
			{
				SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": Hi Bob, let's have a drink together!";

			}
			
		}
		return true;
	}
	return false;
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

	if (pIvrogne->isRestedEnough() == true)
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
	
}


void Altercation::Execute(Ivrogne* pIvrogne)
{
	int combat_value = RandInt(0,10);
	if(combat_value <4) //Perdu pour l'ivrogne
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": " << "Your fist is steady for sure! I apologize.";

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pIvrogne->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_YouWon,   //the message
			NO_ADDITIONAL_INFO);
		pIvrogne->setEbrietyMax();
	}
	else
	{
		cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": " << "Such a loser! You owe me a drink !";

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pIvrogne->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_YouLose,   //the message
			NO_ADDITIONAL_INFO);
	}
	pIvrogne->GetFSM()->SetState(SeSaouleAuBar::Instance());
}

void Altercation::Exit(Ivrogne* pIvrogne)
{
	cout << "\n" << GetNameOfEntity(pIvrogne->ID()) << ": "
		<< "Every Man needs to have a fight once in a while!";
}

bool Altercation::OnMessage(Ivrogne* pIvrogne, const Telegram& msg)
{
	return false;
}