#ifndef NFA_H
#define NFA_H
#include <vector>

using namespace std;
// Convenience types and constants
typedef unsigned state;
typedef char input;
enum {EPS = -1, NONE = 0};
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
		trans_table(other.trans_table)
	{}
	NFA& operator=(const NFA& other);
	// Adds a transition between two states
	void add_trans(state from, state to, input in);
	// Adds empty state to end of matrix
	void append_empty_state(void);
	// Create space at front of transition matrix
	void shift_states(unsigned shift);
	void fill_states(const NFA& other);
	// Prints out the NFA
	void show(void);

	bool is_legal_state(state s);
	state initial;
	state final;
	unsigned size;
	vector < vector <input> > trans_table;
};

// NFA building function

NFA build_nfa_basic(input in);
NFA build_nfa_alter(NFA nfa1, NFA nfa2);
NFA build_nfa_concat(NFA nfa1, NFA nfa2);
NFA build_nfa_star(NFA nfa);

#endif // NFA_H
