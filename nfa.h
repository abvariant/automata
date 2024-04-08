#ifndef NFA_H
#define NFA_H
#include "common.h"

using namespace std;

// Convenience types and constants
class NFA
{
public:
	// Constructed with the NFA size (amount of
	// states), the initial state and the final state
	NFA(unsigned size_, state initial_, state final_);
	// Copy!
	NFA(const NFA& other) :
		initial(other.initial),
		final(other.final),
		size(other.size),
		trans_table(other.trans_table),
		inputs(other.inputs)
	{}
	NFA& operator=(const NFA& other);
	// Adds a transition between two states
	void add_trans(state from, state to, input in);
	// Adds empty state to end of matrix
	void append_empty_state(void);
	// Create space at front of transition matrix
	void shift_states(unsigned shift);
	void fill_states(const NFA& other);
	
	// Append given set of inputs to current set
	void append_input_states(set<input> newInputs);
	
	// Prints out the NFA
	void show(void);
	// Returns a set of NFA states from which there is a transition on 
	// input symbol inp from some state s in states
	set<state> move(set<state> states, input inp);

	bool is_legal_state(state s);
	state initial;
	state final;
	unsigned size;
	vector < vector <input> > trans_table;
	// All the inputs this nfa responds to
	set<input> inputs;
};

// NFA building function

// creates a 2-state nfa. State '0' and state '1'.
NFA build_nfa_basic(input in);

// alternation. ie: nfa1 or nfa2
// Creates new nfa from "nfa2"
NFA build_nfa_alter(NFA nfa1, NFA nfa2);

// concatenation. ie: 
NFA build_nfa_concat(NFA nfa1, NFA nfa2);

// re-impliments nfa as "zero or more" nfa.
NFA build_nfa_star(NFA nfa);

#endif // NFA_H
