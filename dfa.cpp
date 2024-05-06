#include <assert.h>
#include <iostream>
#include <string>
#include "dfa.h"

using namespace std;
DFA::DFA()
{
}
string DFA::simulate(string in)
{
	// "start" is nfa.initial, set in nfa constructor.
	state cur_state = start;

	for (string::const_iterator i = in.begin(); i != in.end(); ++i)
	{
		// if the current character is not in the input set,
		// reset current state to start state
		if(inputs.find(*i) == inputs.end())
		{
			cur_state = start;
		}
		else
		{
			transition trans = make_pair(cur_state, *i);

			// If transition isn't found, it returns trans_table.end()
			// There isn't a transition for any unknown chars so this always rejects.
			if (trans_table.find(trans) == trans_table.end())
			{
				return "REJECT";
			}
			cur_state = trans_table[trans];
		}
	}

	if (final.find(cur_state) != final.end())
	{
		return "ACCEPT";
	}
	else
	{
		return "REJECT";
	}
}
void DFA::show(void)
{
	cout << "DFA start state: " << start << endl;
	cout << "DFA final state(s): ";
	
	for (set<state>::const_iterator i = final.begin(); i != final.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;

	for (map<transition, state>::const_iterator i = trans_table.begin(); i != trans_table.end(); ++i)
	{
		cout << "Trans[" << (i->first).first << ", " << (i->first).second << "] = " << i->second << endl;
	}
}


