#include "Ivrogne.h"



bool Ivrogne::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Ivrogne::Update()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);


	m_pStateMachine->Update();
}




