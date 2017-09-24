#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_WantToFight,
  Msg_YouLose,
  Msg_YouWon,
  Msg_InTheBar
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_WantToFight:

	  return "Fight";

  case Msg_YouLose:

	 return "You Lose";
	 
  case Msg_YouWon:

	  return "You Won";

  case Msg_InTheBar:

	  return "I am in the bar";

  default:

    return "Not recognized!";
  }
}

#endif