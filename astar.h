#ifndef ASTAR_H
#define ASTAR_H

#include "Node.h"

// heuristic_function to determine heuristic_score of children
// the maximun heuristic_score is 100000. which is the perfect solutions
//
int heuristic_function(Node* n, vector<bitset<30>> p_2_pool, vector<bitset<30>>& r_pool, vector<int>& position);

//loop through children to find the highest heuristic_score child
Node* get_the_highest_child(vector<Node*> children);

//use astar algorithm to find the best circuit that can solve multiplication of two prime odd numbers
void astar_multiplication_circuit(vector<int> p_pool, vector<bitset<15>> b_p_pool, int& depth);


#endif
