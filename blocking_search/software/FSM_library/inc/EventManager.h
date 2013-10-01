#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include <vector>
#include <map>

#include "FSMDataStructures.h"
#include "StateEncoder.h"


enum EventTypeMask
{
  VARIABLE_EVENT = 0x1,
  EXOGENOUS_EVENT = 0x2,
  ALL_EVENTS = 0x3,
  DC_ONLY = 0x4,
  DC_AND_EXOGENOUS = 0x6
};


struct Event
{
	int UniqueFSMcount;
	std::vector<std::pair<int, int> > transitions;
};


class EventManager
{
public:
  EventManager(std::vector<FSM_struct> & FSMArray);
  void AddTransitions(State & state, int fsmIndex, unsigned int restriction);
  void GetNextStates( unsigned int currentState, std::vector<std::pair<unsigned int, std::string> > & nextStates );
  EventTypeMask AssignMask(std::string event);
  
private:
  std::map<std::string, int> EventFrequency;
  std::map<std::string, EventTypeMask> EventTypeMap;
  std::map<std::string, Event> EventsAtCurrentState;
  StateEncoder encoder;
  
  bool GetNextPermutation( std::vector<int> &, const std::vector<int> &, int);
};




#endif
