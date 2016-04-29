#ifndef GENETIC_H
#define GENETIC_H


#include "toffoli_gate.h"

void print_population(vector<vector<vector<int>>>& p);
void print_v(vector<int>& v);
void print_ciruit(vector<vector<int>> c);

// convert multiply result to 30 bits binary
bitset<30> get_result_binary_bset(int p);

// conbine two 15 bits number to one 30 bits pattern
bitset<30> concat(bitset<15> &b1, bitset<15> &b2);

// get all p1, p2 combination set which p1 > p2, and combine then together
vector<bitset<30>> get_multi_2_bset(vector<bitset<15>> b_p_pool);

// get all result from multiply 2 odd primes in 30 bitset format
vector<bitset<30>> get_2_multi_result_bset(vector<int> p_pool);

//xor all m_2_result and 2_m_combine to a bitset with all necssary flip bit one
bitset<30> xor_all(vector<bitset<30>> m_2, vector<bitset<30>> result);

// utility function return the position of 1 in the bitset
vector<int> positions_of_one(bitset<30>& target);

//generate initial population
vector<vector<vector<int>>> initial_population();

// get fittness_score
int fittness_score(vector<bitset<30>> p_2_pool, vector<bitset<30>>& r_pool, vector<vector<int>>& circuit, vector<int>& position);

// keep generate next generation by crossing high fittness_score parent to get children until get the high enough score children
vector<vector<int>> next_generation(vector<vector<int>> initial_pop, vector<bitset<30>> p_2_pool, vector<bitset<30>>& r_pool, vector<int>& position, int& fitness);

//cross parent to generate childrens
vector<vector<vector<int>>> generate_children(vector<vector<vector<int>>>& p);

// new circuit
vector<vector<int>> get_new_circuit();

// genetic algorithm to find the most fittness_score circuit tree that do prime multiply
void genetic_multiplication_circuit(vector<int> p_pool, vector<bitset<15>> b_p_pool, int& d);





#endif
