#ifndef TOFFOLI_GATE_H
#define TOFFOLI_GATE_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <deque>
#include <functional>

using namespace std;

// take any number of control bits position and inverted control bit position and flip the bit
void generalized_toffoli_gate(bitset<30> &bset, vector<int>& ctr, vector<int>& inv_ctr, int& ctr_size, int& ictr_size, int flip_p);



#endif
