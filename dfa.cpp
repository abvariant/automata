#include <assert.h>
#include <iostream>
#include <string>
#include "dfa.h"

using namespace std;
DFA::DFA()
{
}
void DFA::simulate(string in)
{
	// "start" is nfa.initial, set in nfa constructor.
	state cur_state = start;

	// string buffer for containing successful candidate sub-string.
	string buf = "";

	for (string::const_iterator i = in.begin(); i != in.end(); ++i)
	{
		// if the current character is not in the input set,
		if(inputs.find(*i) == inputs.end())
		{
			// reset current state to start state
			// and empty buffer
			cur_state = start;
			buf = "";
		}
		else
		{
			// example transition: (eg: "state 0, given input 'a'")
			transition trans = make_pair(cur_state, *i);

			// If transition isn't found,
			if (trans_table.find(trans) == trans_table.end())
			{
				// At this point, input char exists, but there is no
				// transition from the current state to that character.

				// So hop back to beginning of DFA, blank sub-string,
				// and keep going.
				cur_state = start;
				buf = "";

				// this continue should only be necessary if the
				// start-state is the same as the final state, which is
				// nonsense, but it does mean the final state check never
				// happens.
				continue;
			}
			else
			{
				// Input char exists, and there is a transition from the
				// current state. Update current state, and append char
				// to buffer.
				cur_state = trans_table[trans];
				buf += *i;
			}

			if (final.find(cur_state) != final.end())
			{
				// accept substring, print out.
				cout << "Found matching string: " << buf << endl << endl;
				//reset to start state
				cur_state = start;
				// reset buffer
				buf = "";
			}
		}
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


