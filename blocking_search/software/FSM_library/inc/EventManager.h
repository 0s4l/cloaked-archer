#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include <vector>
#include <map>

#include "FSMDataStructures.h"
#include "StateEncoder.h"

struct Event
{
	int UniqueFSMcount;
	std::vector<std::pair<int, int> > transitions;
};


class EventManager
{
public:
  EventManager(std::vector<FSM_struct> & FSMArray);
  void AddTransitions(State & state, int fsmIndex);
  void GetNextStates( std::vector<unsigned int> & nextStates, unsigned int currentState );
    
private:
  std::map<std::string, int> EventFrequency;
  std::map<std::string, Event> EventsAtCurrentState;
  StateEncoder encoder;
  
  bool GetNextPermutation( std::vector<int> &, const std::vector<int> &, int);
};




#endif