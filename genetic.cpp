#include "genetic.h"



bitset<30> get_result_binary_bset(int p){
	bitset<30> binary_bset(p);
	return binary_bset;
}

bitset<30> concat(bitset<15> &b1, bitset<15> &b2){
	string s1 = b1.to_string();
	string s2 = b2.to_string();
	return bitset<30>(s1+s2);
}

vector<bitset<30>> get_multi_2_bset(vector<bitset<15>> b_p_pool){
	vector<bitset<30>> result_pool;
	for(unsigned int i=0; i< b_p_pool.size(); i++){
		for (unsigned int j = i+1; j < b_p_pool.size(); j++) {
			// cout<<"i: "<<i<< " j: "<<j<<endl;
			result_pool.push_back(concat(b_p_pool[i], b_p_pool[j]));
		}
	}
	return result_pool;
}

vector<bitset<30>> get_2_multi_result_bset(vector<int> p_pool){
	vector<bitset<30>> result_pool;
	for(unsigned int i=0; i< p_pool.size(); i++){
		for (unsigned int j = i+1; j < p_pool.size(); j++) {
			result_pool.push_back(get_result_binary_bset(p_pool[i]*p_pool[j]));
		}
	}
	return result_pool;
}

bitset<30> xor_all(vector<bitset<30>> m_2, vector<bitset<30>> m_result){
	bitset<30> b_r;
	for(unsigned int i=0; i<m_result.size(); i++){
		b_r = b_r |= (m_2[i] ^= m_result[i]);
	}
	// cout<<b_r<<endl;
	return b_r;
}

vector<int> positions_of_one(bitset<30>& target){
	vector<int> positions;
	for(int i=0; i < 30; i++){
		if(target[i] == 1){
			positions.push_back(i);
		}
	}
	return positions;
}

void print_v(vector<int>& v){
	cout<<"( ";
	for(unsigned int i = 0; i<v.size();i++){
		cout<<v[i]<<", ";
	}
	cout<<")"<<endl;
	return;
}

void print_ciruit(vector<vector<int>> c){
	for(unsigned int i=0; i<c.size(); i++){
		cout<<"###########################################\n";
		print_v(c[i]);
		cout<<"###########################################\n";
	}
}


void print_population(vector<vector<vector<int>>>& p){
	for(unsigned int i=0; i<p.size(); i++){
		cout<<"******************************************\n";
		for(unsigned int j=0; j<p[i].size(); j++){
			print_v(p[i][j]);
		}
		cout<<"******************************************\n";
	}
}


vector<vector<vector<int>>> initial_population(){

	int pop_num = 1000;
	srand(time(NULL));
	vector<vector<vector<int>>> population;

	for(int i=0; i<pop_num; i++){
		vector<vector<int>> c;
		population.push_back(c);
		for(int j=0; j< (rand()%30)*2+8; j++){  // uncertain if this is enough for the depth of circuit
			vector<int> v;
			population[i].push_back(v);
			for(int n=0; n<rand()%30; n++){
				population[i][j].push_back(rand()%30);
			}
		}
	}
	return population;
}


int fittness_score(vector<bitset<30>> p_2_pool, vector<bitset<30>>& r_pool, vector<vector<int>>& circuit, vector<int>& position){
	// cout<<"*****************************************************\n";
	int score = 0;
	for(unsigned int i=0; i<p_2_pool.size(); i++){
			for(unsigned int n=0; n<circuit.size(); n++){
				int size_c = circuit[n].size()/2;
				int size_ic = circuit[n].size() - size_c;
				vector<int> c_p(circuit[n].begin(), circuit[n].begin()+size_c);
				vector<int> i_c_p(circuit[n].begin()+size_c, circuit[n].end());
				int temp = n % position.size();
				generalized_toffoli_gate(p_2_pool[i], c_p, i_c_p, size_c, size_ic, position[temp]);
			}
			if(p_2_pool[i] == r_pool[i]) {
				score++;
			}
	}
	return score;
}

//
vector<vector<vector<int>>> generate_children(vector<vector<vector<int>>>& p){
	vector<vector<vector<int>>> children;
	vector<vector<int>> c1, c2;
	if(p.size() > 1){
		if(p.size()%2 !=0 ){
			children.push_back(p.back());
			p.pop_back();
		}
		for(unsigned int i=0; i<p.size(); i+=2){
			c1.clear();
			c2.clear();
			for(unsigned int j=0; j<(p[i].size()/2); j++){
				c1.push_back(p[i][j]);
			}
			for(unsigned int j=0; j<(p[i+1].size()/2); j++){
				c2.push_back(p[i+1][j]);
			}
			for(unsigned int j=(p[i].size()/2); j<p[i].size(); j++){
				c2.push_back(p[i][j]);
			}
			for(unsigned int j= (p[i+1].size()/2); j<p[i+1].size(); j++){
				c1.push_back(p[i+1][j]);
			}
			children.push_back(c1);
			children.push_back(c2);
		}
	}else{
		children = p;
	}
	return children;
}

vector<vector<int>> get_new_circuit(){
	vector<vector<int>> new_circuit;
	for(int j=0; j< (rand()%30)*2+8; j++){  // uncertain if this is enough for the depth of circuit
		vector<int> v;
		new_circuit.push_back(v);
		for(int n=0; n<rand()%30; n++){
			new_circuit[j].push_back(rand()%30);
		}
	}
	return new_circuit;
}

//
vector<vector<vector<int>>> next_generation(vector<vector<vector<int>>> initial_pop, vector<bitset<30>> p_2_pool, vector<bitset<30>>& r_pool, vector<int>& position, int& fitness){
	cout<<"next_generation\n";
	vector<vector<vector<int>>> new_generation;
	vector<vector<vector<int>>> high_score_parents, children;
	srand(time(NULL));
	for(unsigned int i=0; i<initial_pop.size(); i++){                       //  loop through population to calculate fittness_score
		int score = fittness_score(p_2_pool, r_pool, initial_pop[i], position);
		if(score > 0 ){
			if(score > fitness) {fitness = score;}
			high_score_parents.push_back(initial_pop[i]);
		}else{
			vector<vector<int>> new_circuit = get_new_circuit();
			new_generation.push_back(new_circuit);
		}
	}
	children = generate_children(high_score_parents);
	for(unsigned int j=0; j<children.size(); j++){
		new_generation.push_back(children[j]);
	}
	initial_pop.clear();
	children.clear();
	high_score_parents.clear();
	return new_generation;
}


void genetic_multiplication_circuit(vector<int> p_pool, vector<bitset<15>> b_p_pool, int& d) {
	cout<<"***genetic_multiplication_circuit***\n";
	vector<bitset<30>> p_2_pool = get_multi_2_bset(b_p_pool);
	vector<bitset<30>> r_pool = get_2_multi_result_bset(p_pool);
	bitset<30> b_xor = xor_all(p_2_pool, r_pool);
	vector<int> positions = positions_of_one(b_xor);
	int fitness = 0;
	vector<vector<vector<int>>> initial_pop = initial_population();
	vector<vector<vector<int>>> new_generation = next_generation(initial_pop, p_2_pool, r_pool, positions, fitness);
	while(d > 0){
		d--;
		new_generation = next_generation(new_generation, p_2_pool, r_pool, positions, fitness);
		cout<<"fitness score is "<<fitness<<endl;
	}
	return;
}
