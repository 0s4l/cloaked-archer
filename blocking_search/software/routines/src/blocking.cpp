
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <stack>
#include <bitset>
#include <cmath>

#include "FSMDataStructures.h"
#include "MemoryManager.h"
#include "EventManager.h"
#include "StateEncoder.h"
#include "Utilities.h"

using namespace std;

void MapCommonEvents(vector<FSM_struct> & FSMArray)
{
  vector< vector<int> > sharedEvents;
  
  cout << "Index" << endl;
  for(int i=0; i<FSMArray.size(); i++)
  {
    cout << i << "\t" << FSMArray[i].fsmName << "\t" << FSMArray[i].alphabet.size() <<  endl;
  }
  cout << endl<<"   ";
  for(int i=0; i<FSMArray.size(); i++)
  {
    if(i<10)
      cout << i << "  ";
    else
      cout << i << " ";
  }
  cout<<endl;
  
  for(int i=0; i<FSMArray.size(); i++)
  {
    if(i<10)
      cout << i << "  ";
    else
      cout << i << " ";
      
    vector<int> row;
    for(int j=0; j<=i; j++)
    {
      cout << "...";
      row.push_back(0);
    }
    for(int j=i+1; j<FSMArray.size(); j++)
    {
      sort(FSMArray[i].alphabet.begin(), FSMArray[i].alphabet.end());
      sort(FSMArray[j].alphabet.begin(), FSMArray[j].alphabet.end());
      
      vector<string> intersection(FSMArray[i].alphabet.size() + FSMArray[j].alphabet.size());
      vector<string>::iterator it = set_intersection(FSMArray[i].alphabet.begin(), FSMArray[i].alphabet.end(), FSMArray[j].alphabet.begin(), FSMArray[j].alphabet.end(), intersection.begin());
      intersection.resize(it-intersection.begin());
      
      if(intersection.size() == 0)
      {
        cout << "-  ";
      }
      else
      {
        if(intersection.size() >= 10 )
          cout <<  intersection.size()<< " ";
        else
          cout << intersection.size() << "  ";
      }
      row.push_back(intersection.size()); 
    }
    cout << endl;
    sharedEvents.push_back(row);
  }
  cout << endl;

}

void WriteStateToFile( unsigned int currentState, vector<pair<unsigned int, string> > & nextStates, bool marked, ofstream & outfile, StateEncoder & encoder)
{
  outfile << encoder.GenerateStateName( currentState ) << "\t";
  if(marked)
  {
    outfile << 1 << "\t";
  }
  else
  {
    outfile << 0 << "\t";
  }
  outfile << nextStates.size() << "\t" << endl;
  
  for(int i=0; i<nextStates.size(); i++)
  {
    outfile << nextStates[i].second << "\t";
    outfile << encoder.GenerateStateName( nextStates[i].first ) << "\t";
    outfile << "c\to" << endl;
  }
  
  outfile << endl;
  outfile.flush();
}


unsigned int DepthFirstSearch(vector<FSM_struct>& FSMArr, MemoryManager & memory, EventManager & event, StateEncoder & encoder, unsigned int worstcase, string outputDirectory)
{
  ofstream outfile;
  if(!outputDirectory.empty())
  {
    string filename;
    for(int i=0; i<FSMArr.size(); i++)
    {
      filename += (FSMArr[i].fsmName + ",");
    }
    filename.erase(filename.end()-1);
    
    string filepath = outputDirectory + filename + ".fsm";
    outfile.open(filepath.c_str());
    if(!outfile.is_open())
    {
      cerr << "File "<<filepath <<" failed to open!"<<endl;
    }
    outfile << setw(8) << "CORRUPT" << endl << endl;
  }
	//Initialize search stack for depth-first search, add initial state
	//Note that this assumes the 0th state in each file is the marked state
	unsigned currentState = 0;
	unsigned int counter = 0;
	unsigned int maxStackSize = 0;
	
	memory.PushOnStack( currentState );	
	
	while( !memory.IsStackEmpty() )
	{	
		//Get current state off top of stack
		currentState = memory.PopOffStack();
		
		// Loop through each FSM, examining the current state's transitions
		// case 1:
		//    If ALL states are marked (indicating real or "proper" states),
		//    consider all events from all states. 
		// case 2: 
		//    If at least one state is unmarked, consider only variable events
		//    That is, lowercase events in unmarked states
		 
		bool unmarkedStates = encoder.CheckForUnmarkedStates(currentState);
		
    for(int i=0; i<FSMArr.size(); i++)
    {
	    //Extract state index from encoded composite state
	    int stateIndex = encoder.FindStateIndex(currentState, i);
	    
	    if( unmarkedStates )
	    {
	      //Add only variable events
	      event.AddTransitions(FSMArr[i].states[stateIndex], i, VARIABLE_EVENT);
      }
      else
      {
        //Add both variable and exogenous events
        event.AddTransitions(FSMArr[i].states[stateIndex], i, ALL_EVENTS);
      }
    }
        
		//Get next states
		vector<pair<unsigned int, string> > nextStates;
    event.GetNextStates( currentState, nextStates );
    
    
    //Write current state to .FSM file
    if( outfile.is_open() )
    {
      WriteStateToFile( currentState, nextStates, !unmarkedStates, outfile, encoder );
    }
    
 
    //Push next states onto stack
    for( int i=0; i<nextStates.size(); i++)
    {
      memory.PushOnStack(nextStates[i].first);
    }

		//Update counter 
		counter++;
		if(!(counter % 10000))
		{
		  if(memory.GetSizeOfStack() > maxStackSize )
		  {
		    maxStackSize = memory.GetSizeOfStack();
		  }
			cout << counter << " states accessed. ["<< (counter*100)/worstcase << "%]";
			cout << " Stack size: " << memory.GetSizeOfStack() << "         \r";
			cout.flush();
		}
	}
	
	//Print summary statistics
	cout << endl;
	cout << "Total states accessed: " << counter << endl;
	cout << "Max size of stack: "<< maxStackSize << endl;
	
	if(outfile.is_open())
  {
    outfile.seekp(0, ios::beg);
    outfile << setw(8) << counter;
    outfile.close();
  }  
  
	return counter;
}

int main(int argc, char * argv[])
{
	//Declare vector of FSM_structs
	vector<FSM_struct> FSMArr;
	
	//Read in .fsm files
	//Change second parameter to "0" to not print update
	int worstcase = readFSM(FSMArr, 1, argc, argv);
	MapCommonEvents(FSMArr);
	//Populate number of states in each FSM
	vector<int> numStates;
	for(int i=0; i<FSMArr.size(); i++)
	{
	  numStates.push_back(FSMArr[i].numStates);
	}
	MemoryManager memory(numStates);
	EventManager event(FSMArr);
	StateEncoder encoder(FSMArr);
	
	unsigned int totalStatesAccessed;
	//totalStatesAccessed = DepthFirstSearch(FSMArr, memory, event, encoder, worstcase, "../FSM_files/");
	
	cout << (int)PARAM_IN << endl;
	//GenerateOptimalSubgroups(FSMArr);
	
	cout << "Hello World" << endl;
	return 0;
}


/*
//Subfunctions	
void printFirstFive(vector<FSM_struct>& FSMArr);
void printEventHashTable(multimap<string, int>& eventHash);
void printAddr(unsigned long int addr, Event_wrapper& Events, vector<FSM_struct>& fsm);
unsigned long int DFS_Acc(vector<FSM_struct>&, vector<bool>&, Event_wrapper&);
unsigned long int DFS_CoAcc(vector<FSM_struct>&, vector<bool>&, vector<bool>&, Event_wrapper&);
void invertTrans(vector<FSM_struct>& FSMArr, vector<FSM_struct>& FSMArr_inv);
void outputFSM(FSM_struct& FSM, string filepath);
bool genPerms(vector<int>& cur, const vector<int>& part, int col);
int readFSM(vector<FSM_struct>& FSMArr, bool print, int argc, char* argv[]);
	
int main(int argc, char* argv[]){

	//Declare vector of FSM_structs
	vector<FSM_struct> FSMArr;
	
	//Read in .fsm files
	//Change second parameter to "0" to not print update
	int worstcase = readFSM(FSMArr, 1, argc, argv);
	
	//Hash events into individual buckets. Store how many automata include them
	map<string, int> eventHash;
	for(int i=0; i<FSMArr.size(); i++){
		for(int j=0; j<FSMArr[i].numEvents; j++){
			auto it = eventHash.find(FSMArr[i].alphabet[j]);
			if (it == eventHash.end())
				eventHash.insert(make_pair(FSMArr[i].alphabet[j], 1));
			else
				it->second++;			
		}
	}
	
	//Initialize addressing object, accessed bitset, coaccessed bitset
	Event_wrapper Events(eventHash, FSMArr);
	unsigned long base = 1;
	unsigned long vecSize = base<<(Events.totalbits);
	vector<bool> accessed(vecSize);
	vector<bool> coaccessed(vecSize);
	
	if(accessed.size() != vecSize || coaccessed.size() != vecSize){
		cerr<< "Memory not allocated properly"<<endl;
		exit(1);
	}

	//Search for accessible
	cout << "Begining depth-first search for accessibility..."<<endl;
	unsigned long int counter = DFS_Acc(FSMArr, accessed, Events);
	cout << "Done with accessibility search. "<<counter<< " states accessed."<<endl;
	
	//Invert transitions in FSM
	vector<FSM_struct> FSMArr_inv;
	invertTrans(FSMArr, FSMArr_inv);
		
	cout<<"FSMs successfully inverted. Initiating coaccessibility DFS.\n";
	
	//Search for coaccesible
	counter = DFS_CoAcc(FSMArr_inv, accessed, coaccessed, Events);
	cout << "Done with coaccessibility search. "<<counter<< " states are coaccessible."<<endl;
	
	//Print blocking states to file
	printBlockingStates(FSMArr, accessed, coaccessed, Events);
	
	cout<<"Program completed."<<endl;				
	
	return 0;
	
}		

unsigned long int DFS_CoAcc(vector<FSM_struct>& FSMArr, vector<bool>& accessed, vector<bool>& coaccessed, Event_wrapper& Events)
{
	//Initialize search stack for depth-first search, add initial state
	//Note that this assumes the 0th state in each file is the marked state
	stack<unsigned long> Stack;
	Stack.push(0); 
	accessed[0] = 1;
	
	//Loop until all states have been visited
	unsigned long int counter = 0;
	unsigned long curState, newState;
	
	while(!Stack.empty()){
		
		//Get current state off top of stack
		curState = Stack.top();
		Stack.pop();
		
		//Loop through each FSM, examining the current state's transitions
		for(int i=0; i<FSMArr.size(); i++){
			//Extract state index from encoded composite state
			int stateIndex = (curState>>Events.offset[i])&((1<<Events.bits[i])-1);
			
			//Loop through transitions at current state of FSM
			//Insert events into Event structs
			for(int j=0; j<FSMArr[i].states[stateIndex].numTrans; j++){
				//Insert each event
				Events.insertTrans(FSMArr[i].states[stateIndex].transitions[j].event, i,
					FSMArr[i].states[stateIndex].transitions[j].dest);
			}
		}

		//Examine all transitions, insert if unvisited
		vector<unsigned long int> nextStates;
		vector<string> nextEvents;
		Events.getNextAddress(nextStates, nextEvents, curState);

		for(auto it=nextStates.begin(); it!=nextStates.end(); it++){	
			if(coaccessed[*it] == 0 && accessed[*it] == 1){
				coaccessed[*it] = 1;
				Stack.push(*it);
			}	
		}

		//Update counter 
		counter++;
		if(!(counter % 10000)){
			cout<<counter<<" states coaccessed.";
			cout<<" Stack size: "<<Stack.size()<<endl;
		}
		
		Events.clear();
	}
	
	return counter;
}


*/


	
		
		
		
		
		
	
	
	
	
	
