#include "astar.h"



int heuristic_function(Node* n, vector<bitset<30>> p_2_pool, vector<bitset<30>>& r_pool, vector<int>& position){
  int score = 10000;
  for(unsigned int x=0; x< p_2_pool.size(); x++){
    for(unsigned int i=0; i<n->get_circuit().size(); i++){
      int size_c = n->get_circuit()[i].size()/2;
      int size_ic = n->get_circuit()[i].size() - size_c;
      vector<int> c_p, i_c_p;
      for(int o=0; o<size_c; o++){
        c_p.push_back(n->get_circuit()[i][o]);
      }
      for(unsigned int y=size_c; y<n->get_circuit()[i].size(); y++){
        i_c_p.push_back(n->get_circuit()[i][y]);
      }
      int temp = i % position.size();
      generalized_toffoli_gate(p_2_pool[x], c_p, i_c_p, size_c, size_ic, position[temp]);
    }
    bitset<30> x_or = p_2_pool[x] ^= r_pool[x];
    score -= x_or.count();
  }
  return score;
}

Node* get_the_highest_child(vector<Node*> children){
  vector<vector<int>> temp;
  Node* best_child = new Node(temp);
  int max = 0;
  for(unsigned int i=0; i<children.size(); i++){
    if(children[i]->get_score() > max){
      max = children[i]->get_score();
      best_child = children[i];
    }
  }

  return best_child;
}


void astar_multiplication_circuit(vector<int> p_pool, vector<bitset<15>> b_p_pool, int& d){
  cout<<"***astar_multiplication_circuit***\n";
	vector<bitset<30>> p_2_pool = get_multi_2_bset(b_p_pool);
	vector<bitset<30>> r_pool = get_2_multi_result_bset(p_pool);
	bitset<30> b_xor = xor_all(p_2_pool, r_pool);
	vector<int> positions = positions_of_one(b_xor);
  vector<Node*> travel_history;
  vector<vector<int>> start_circuit;
  Node* root= new Node(start_circuit);
  while(d > 0){
    if(root->get_score() == 10000) break;
    d--;
    travel_history.push_back(root);
    root->expand_node();
    for(unsigned int i=0; i<root->get_children().size(); i++){
      root->get_children()[i]->set_score(heuristic_function(root->get_children()[i],p_2_pool,r_pool,positions ));
    }
    root = get_the_highest_child(root->get_children());
  }
  root->print_node();
  cout<<"root->get_score is "<<root->get_score()<<endl;
}
