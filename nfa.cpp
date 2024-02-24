#include <assert.h>
#include <iostream>
#include <string>
//#include
#include "nfa.h"
using namespace std;
NFA::NFA(unsigned size_, state initial_, state final_)
{
	size = size_;
	initial = initial_;
	final = final_;
	assert(is_legal_state(initial));
	assert(is_legal_state(final));
	// Initialize trans_table with an "empty graph",
	// no transitions between its states
	for (unsigned i = 0; i < size; ++i)
	{
		vector <input> v;
		for (unsigned j = 0; j < size; ++j)
		{
			v.push_back(NONE);
		}
		trans_table.push_back(v);
	}
}
bool NFA::is_legal_state(state s)
{
	// We have 'size' states, numbered 0 to size-1
	//if (s < 0 || s >= size)
	if ( s >= size)
		return false;
	return true;
}
NFA& NFA::operator=(const NFA& other)
{
	if (this == &other)
		return *this;

	initial = other.initial;
	final = other.final;
	size = other.size;
	trans_table = other.trans_table;

	return *this;
}
void NFA::add_trans(state from, state to, input in)
{
	assert(is_legal_state(from));
	assert(is_legal_state(to));
	// shows question mark chars
	//std::cout << from << " " << to << " " << (int)in << std::endl;
	trans_table[from][to] = in;
}
void NFA::append_empty_state(void)
{
	// Append new row with increased size
	vector<input> empty_row(size+1, NONE);
	trans_table.push_back(empty_row);

	// Not sure why this loop is needed when the
	// matrix has already been appended to...
	for (state i=0; i<size; ++i)
		trans_table[i].push_back(NONE);

	size += 1;
}
void NFA::shift_states(unsigned shift)
{
	unsigned new_size = size + shift;

	if (shift < 1)
		return;

	vector <input> empty_row(new_size, NONE);
	vector < vector <input> > new_trans_table(new_size, empty_row);

	for (state i=0; i<size ; ++i)
	{
		for (state j=0; j<size ; ++j)
		{
			new_trans_table[i+shift][j+shift] = trans_table[i][j];
		}
	}

	size = new_size;
	initial += shift;
	final += shift;
	trans_table = new_trans_table;
}
void NFA::fill_states(const NFA& other)
{

	for (state i=0; i<other.size ; ++i)
	{
		for (state j=0; j<other.size ; ++j)
		{
			trans_table[i][j] = other.trans_table[i][j];
		}
	}

}
void NFA::show(void)
{
	std::cout << "This NFA has " << size << " states: 0 - " << size - 1 << std::endl;
	std::cout << "The initial state is " << initial << std::endl;
	std::cout << "The final state is " << final << std::endl << std::endl;
	for (unsigned from = 0; from < size; ++from)
	{
		for (unsigned to = 0; to < size; ++to)
		{
			input in = trans_table[from][to];
			if (in != NONE)
			{
				std::cout << "Transition from " << from << " to " << to << " on input ";
				if (in == EPS)
				{
					std::cout << "EPS" << std::endl;
				}
				else
				{
					std::cout << in << std::endl;
				}
			}
		}
	}
}
NFA build_nfa_basic(input in)
{
	NFA basic(2, 0, 1);
	//std::cout << in << std::endl;
	basic.add_trans(0, 1, in);
	return basic;
}
NFA build_nfa_alter(NFA nfa1, NFA nfa2)
{
	// Shift to make room for initial state
	nfa1.shift_states(1);

	// Shift to make room for nfa1
	nfa2.shift_states(nfa1.size);

	// Created new nfa from new larger nfa2
	NFA new_nfa(nfa2);

	// All nfa1 states copied to new_nfa
	new_nfa.fill_states(nfa1);

	// Set initial states in new nfa from each of old
	new_nfa.add_trans(0, nfa1.initial, EPS);
	new_nfa.add_trans(0, nfa2.initial, EPS);
	new_nfa.initial = 0;

	// Make space for final state(s)
	new_nfa.append_empty_state();

	// Set new final state
	new_nfa.final = new_nfa.size - 1;
	new_nfa.add_trans(nfa1.final, new_nfa.final, EPS);
	new_nfa.add_trans(nfa2.final, new_nfa.final, EPS);

	return new_nfa;
}
NFA build_nfa_concat(NFA nfa1, NFA nfa2)
{
	// Size is -1 so the nfa1 final overlaps the nfa2 initial,
	// overwriting it.
	nfa2.shift_states(nfa1.size-1);

	NFA new_nfa(nfa2);

	// Overwriting nfa2/new_nfa's inital state with nfa1's final.
	new_nfa.fill_states(nfa1);

	// Setting the proper initial
	new_nfa.initial = nfa1.initial;

	return new_nfa;
}
NFA build_nfa_star(NFA nfa)
{
	nfa.shift_states(1);
	nfa.append_empty_state();

	nfa.add_trans(nfa.final, nfa.initial, EPS);
	nfa.add_trans(0, nfa.initial, EPS);
	nfa.add_trans(nfa.final, nfa.size-1, EPS);
	nfa.add_trans(0, nfa.size-1, EPS);

	nfa.initial=0;
	nfa.final = nfa.size-1;

	return nfa;
}
