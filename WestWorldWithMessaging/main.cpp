#include <fstream>
#include <time.h>
#include <thread>


#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include "Ivrogne.h"


std::ofstream os;

void Update_bot(BaseGameEntity* Bge)
{
	for (int i = 0; i<30; ++i)
	{
		Bge->Update();
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
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create the ivrogne
  Ivrogne* Franck = new Ivrogne(ent_Franck);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Franck);

  //run Bob and Elsa through a few Update calls
 
	std::thread tBob(Update_bot, Bob);
	std::thread tElsa(Update_bot, Elsa);
	std::thread tFranck(Update_bot, Franck);
	std::thread tMsg(Update_msg);
    
    

  //tidy up
  delete Bob;
  delete Elsa;
  delete Franck;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();
  tBob.join();
  tFranck.join();
  tElsa.join();

  return 0;
}






