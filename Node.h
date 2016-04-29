#ifndef NODE_H
#define NODE_H

#include "genetic.h"

class Node{
private:
  vector<vector<int>> circuit;  // group of toffoli_gate parameters
  vector<Node*> children;
  Node* parent;
  int heuristic_score;
  int depth;

public:
  //constructor
  Node(vector<vector<int>> c):circuit(c), parent(nullptr), heuristic_score(-1), depth(0) {
  }

  //utility functions
  int get_depth() { return depth; }
  void set_depth(int d) { depth = d; }
  int get_score(){ return heuristic_score; }
  void set_score(int score) { heuristic_score = score; }
  void set_parent(Node* _parent) { parent = _parent; }
  void add_child(Node* _child);
  vector<Node*> get_children() { return children; }
  void set_circuit(vector<vector<int>> c){ circuit = c; }
  vector<vector<int>> get_circuit() { return circuit; }
  void print_node();

  // expand the node with the highest heuristic_score and generate a vector of childern
  void expand_node();

};


#endif
