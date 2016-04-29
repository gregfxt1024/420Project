#include "toffoli_gate.h"


void generalized_toffoli_gate(bitset<30> &bset, vector<int>& ctr, vector<int>& inv_ctr, int& ctr_size, int& ictr_size, int flip_p){
  for(int i=0; i<ctr_size; i++){
    if(bset[ctr[i]] == 1){
      bset[flip_p] = !bset[flip_p];
    }
  }
  for(int i=0; i<ictr_size; i++){
    if(bset[inv_ctr[i]] == 0){
      bset[flip_p] = !bset[flip_p];
    }
  }
  if(ctr_size == 0 && ictr_size == 0)bset[flip_p] = !bset[flip_p];
  return;
}
