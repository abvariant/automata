#include "nfa.h"

int main()
{
   NFA n(11, 0, 10);

   n.add_trans(0, 1, EPS);
   n.add_trans(0, 7, EPS);
   n.add_trans(1, 2, EPS);
   n.add_trans(1, 4, EPS);
   n.add_trans(2, 3, 'a');
   n.add_trans(4, 5, 'b');
   n.add_trans(3, 6, EPS);
   n.add_trans(5, 6, EPS);
   n.add_trans(6, 1, EPS);
   n.add_trans(6, 7, EPS);
   n.add_trans(7, 8, 'a');
   n.add_trans(8, 9, 'b');
   n.add_trans(9, 10, 'b');

   n.show();

   return 0;
}