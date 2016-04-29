//420 project

//Xuetao Fan
#include "genetic.h"
#include "astar.h"

// global number of primes
unsigned int num_of_primes = 0;

const int max_value = 32767;  // 15 bit max binary
// get number of bits map to decimal number
unordered_map<string, int> get_map(){
	unordered_map<string, int> result;
	result["3"] = 7;
	result["4"] = 15;
	result["5"] = 31;
	result["6"] = 63;
	result["7"] = 127;
	result["8"] = 255;
	result["9"] = 511;
	result["10"] = 1023;
	result["11"] = 2047;
	result["12"] = 4095;
	result["13"] = 8191;
	result["14"] = 16383;
	result["15"] = 32767;

	return result;
}

// generate all positive odd prime number from 3 to n
int* find_all_prime(int n){
	static int prime_num_pool[32767];
	int count = 0;
	for(int i=2; i<= n; i++){
		bool is_prime = true;
		for(int j=2; j*j<=i; j++){
			if(i % j == 0){
				is_prime = false;
				break;
			}
		}
		if(is_prime && i != 2){
			prime_num_pool[count] = i;
			count++;
		}
	}
	num_of_primes = count;
	return prime_num_pool;
}

// convert decimal number p to binary
bitset<15> get_binary_bset(int p){
	bitset<15> binary_bset(p);
	return binary_bset;
}

int main(){
	unordered_map<string, int> num_bits =  get_map();
	string num;
	int depth = 0, algorithm = 0;
	cout<<"420 toffoli_gate multiplication with A algorithm\n";
	cout<<"number of bits(3-15): ";
	cin>>num;
	cout<<"Please choose from two algorithms( 1 for genetic, 2 for astar): ";
	cin>>algorithm;
	cout<<"Please input a number for generation for genetic or for depth of A*: ";
	cin>>depth;
	vector<int> prime_pool;
	vector<bitset<15>> b_prime_pool;   // all primes in binary to get fittness
	int* p;
	p = find_all_prime(num_bits[num]);
	for(unsigned int i=0; i< num_of_primes; i++){
		prime_pool.push_back(*(p+i));
	}
	for(unsigned int i=0; i<prime_pool.size();i++){
		b_prime_pool.push_back(get_binary_bset(prime_pool[i]));
	}
	switch (algorithm) {
		case 1:
			genetic_multiplication_circuit(prime_pool, b_prime_pool, depth);
			break;
		case 2:
			astar_multiplication_circuit(prime_pool, b_prime_pool, depth);
			break;
		default:
			cout<<"Invalid Input for algorithm choose, good bye!!!";
	}
	return 0;
}
