#include "Node.h"


void Node::add_child(Node* _child){
		children.push_back(_child);
		children[children.size()-1]->set_parent(this);
		children[children.size()-1]->set_depth(get_depth() + 1);
}


void Node::print_node(){
	for(unsigned int i=0; i<circuit.size(); i++){
		print_v(circuit[i]);
	}
}


void Node::expand_node(){
	srand(time(NULL));
	int num_of_child = 40;
	for(int i=0; i<num_of_child; i++){
		int size = rand()%30;
		vector<vector<int>> child_circuit = this->circuit;
		vector<int> gate_paras;
		for(int j=0; j<size; j++){
			gate_paras.push_back(rand()%30);
		}
		child_circuit.push_back(gate_paras);
		Node* new_child = new Node(child_circuit);
		this->add_child(new_child);
	}
}
