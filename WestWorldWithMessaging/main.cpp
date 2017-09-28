#include <fstream>
#include <time.h>
#include <thread>
#include <mutex>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include "Ivrogne.h"


std::ofstream os;
std::mutex ent_manager,ent_update;


void Handle_bot(BaseGameEntity* Bge)
{
	for (int i = 0; i<30; ++i)
	{
		ent_manager.lock();
		Bge->Update();
		ent_manager.unlock();
		Sleep(800);
	}
}

void Update_msg()
{
	for (int i = 0; i < 30; i++)
	{
		//dispatch any delayed messages
		Dispatch->DispatchDelayedMessages();

	}
}

int main()
{
	//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
	os.open("output.txt");
#endif

	//seed random number generator
	srand((unsigned)time(NULL));

	//create a miner
	Miner* Bob = new Miner(ent_Miner_Bob);

	//create his wife
	MinersWife* Elsa = new MinersWife(ent_Elsa);

	//create the ivrogne
	Ivrogne* Franck = new Ivrogne(ent_Franck);

	EntityMgr->RegisterEntity(Bob);
	EntityMgr->RegisterEntity(Elsa);
	EntityMgr->RegisterEntity(Franck);

	std::thread tBob(Handle_bot, Bob);
	std::thread tElsa(Handle_bot, Elsa);
	std::thread tFranck(Handle_bot, Franck);
//	std::thread tMsg(Update_msg);
    
    

  
  //wait for a keypress before exiting
  tBob.join();
  tFranck.join();
  tElsa.join();
  //tidy up
  delete Bob;
  delete Elsa;
  delete Franck;

  PressAnyKeyToContinue();


  return 0;
}






