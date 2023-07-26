#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "nfa.h"

using namespace std;

NFA::NFA(unsigned size_, state initial_, state final_)
{
   size = size_;
   initial = initial_;
   final = final_;

   assert(is_legal_state(initial));
   assert(is_legal_state(final));

   // Initialize trans_table with an "empty graph", no transitions
   // between its states
   for (unsigned i = 0; i < size; ++i)
   {
      vector<input> v;

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
   if (s < 0 || s >= size)
      return false;

   return true;
}


void NFA::add_trans(state from, state to, input in)
{
   assert(is_legal_state(from));
   assert(is_legal_state(to));

   trans_table[from][to] = in;
}


void NFA::show(void)
{
   cout << "This NFA has " << size << " states: 0 - " << size - 1 << endl;
   cout << "The initial state is " << initial << endl;
   cout << "The final state is " << final << endl << endl;

   for (unsigned from = 0; from < size; ++from)
   {
      for (unsigned to = 0; to < size; ++to)
      {
         input in = trans_table[from][to];

         if (in != NONE)
         {
            cout << "Transition from " << from << " to " << to << " on input ";

            if (in == EPS)
            {
               cout << "EPS" << endl;
            }
            else
            {
               cout << in << endl;
            }
         }
      }
   }
}