#ifndef SUBSET_CONSTRUCT_H
#define SUBSET_CONSTRUCT_H

#include "nfa.h"
#include "dfa.h"

std::set<state> build_eps_closure(NFA nfa, std::set<state> states);
DFA subset_construct(NFA nfa);

#endif // SUBSET_CONSTRUCT_H
