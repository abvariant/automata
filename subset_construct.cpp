#include "subset_construct.h"


// builds epsilon closure of states for the given NFA
set<state> build_eps_closure(NFA nfa, set<state> states)
{
	// push all states on to stack. 
	vector<state> unchecked_stack(states.begin(), states.end());

	// intialise eps_closure(states) to states
	set<state> eps_closure(states.begin(), states.end());

	while(!unchecked_stack.empty())
	{
		// pop state t, the top element, off the stack
		// get reference to last element in unchecked stack
		state t = unchecked_stack.back();
		// remove and destroy last element, resizing unchecked stack
		unchecked_stack.pop_back();
		
		// for each state u with an edge from t to u labled EPS
		for(vector<input>::const_iterator i = nfa.trans_table[t].begin(); i != nfa.trans_table[t].end(); ++i)
		{
			if (*i==EPS)
			{
				state u = i - nfa.trans_table[t].begin();

				// if u is not already in eps_closure, add it and push it onto stack
				if (eps_closure.find(u) == eps_closure.end())
				{
					eps_closure.insert(u);
					unchecked_stack.push_back(u);
				}
			}
		}
	}
	return eps_closure;
}

// Creates unique state numberts for DFA states
static state gen_new_state(void)
{
	static state num = 0;
	return num++;
}

// Subset construction algorithm. Creates DFA that recognises the same
// language as the given NFA.
DFA subset_construct(NFA nfa)
{
	DFA dfa;

	// state_rep is a set of NFA states which is represented by some DFA state
	typedef set<state> state_rep;
	set<state_rep> marked_states;	
	set<state_rep> unmarked_states;	

	// gives a number to each state in the DFA
	map<state_rep, state> dfa_state_num;

	set<state> nfa_initial;
	nfa_initial.insert(nfa.initial);

	// initially, eps-closure(nfa.internal) is the only state in the DFAs
	// states and it's unmarked
	state_rep first(build_eps_closure(nfa, nfa_initial));
	unmarked_states.insert(first);

	// initial dfa state
	state dfa_initial = gen_new_state();
	dfa_state_num[first] = dfa_initial;
	dfa.start = dfa_initial;

	while(!unmarked_states.empty())
	{
		// take out one unmarked state and mark it (remove from the unmarked set,
		// and insert it into the marked set)
		state_rep a_state = *(unmarked_states.begin());
		unmarked_states.erase(unmarked_states.begin());
		marked_states.insert(a_state);

		// if this state contains the NFA's final state, add it to the DFA's
		// set of final states
		if (a_state.find(nfa.final) != a_state.end())
		{
			dfa.final.insert(dfa_state_num[a_state]);
		}

		// for each input symbol the nfa knows
		for (set<input>::const_iterator inp_i = nfa.inputs.begin(); inp_i != nfa.inputs.end(); ++inp_i)
		{
			// next state
			state_rep next = build_eps_closure(nfa, nfa.move(a_state, *inp_i));

			// if we haven't examined this state before, add it to the unmarked states,
			// and make up a new number for it.
			if (unmarked_states.find(next) == unmarked_states.end() && marked_states.find(next) == marked_states.end())
			{
				unmarked_states.insert(next);
				dfa_state_num[next] = gen_new_state();
			}
			dfa.trans_table[make_pair(dfa_state_num[a_state], *inp_i)] = dfa_state_num[next];
		}
		

	}

	return dfa;
}



