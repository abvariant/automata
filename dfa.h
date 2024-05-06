#ifndef DFA_H
#define DFA_H

#include "common.h"

using namespace std;

class DFA
{
public:
	typedef pair<state, input> transition;

	// transition table, set of final states and the start state

	map<transition, state> trans_table;
	state start;
	set<state> final;

	// All the inputs this dfa responds to. Inherited from nfa.
	set<input> inputs;

	DFA();
	void simulate(string in);

	void show(void);
};

#endif  //DFA_H


