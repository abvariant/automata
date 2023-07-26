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
   // Constructed with the NFA size (amount of states), the 
   // initial state and the final state
   NFA(unsigned size_, state initial_, state final_);
    
   // Adds a transition between two states
   void add_trans(state from, state to, input in);

   // Prints out the NFA
   void show(void);

private:
   bool is_legal_state(state s);

   state initial;
   state final;
   unsigned size;
   vector<vector<input> > trans_table;
};

#endif // NFA_H