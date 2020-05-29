#include <iostream>
#include "huffman.h"

std::map<char, int> data;
std::vector<Node*> trees;



Node* make_node(char value, char weight, Node* left, Node* right) {
    Node* node = new Node;
    node->value = value;
    node->weight = weight;
    node->left = left;
    node->right = right;

    if ( left == nullptr && right == nullptr )  { node->is_leaf = true; }
    else                                        { node->is_leaf = false; }

    return node;
}

void destroy(Node* tree) {
  if ( tree != nullptr ) {
      destroy(tree->left);
      destroy(tree->right);
      free(tree);
  }
}

int* find_least(std::vector<Node*> vec, int* least) {
    // find max
    int max = -1;
    int max_index = -1;
    for(int i = 0; i < vec.size(); ++i) {
        if(max < vec[i]->weight) {
            max = vec[i]->weight;
            max_index = i;
        }
    }

    // find least 1;
    least[0] = least[2] = max;
    least[1] = least[3] = max_index;

    for(int i = 0; i < vec.size(); ++i) {
        if(least[0] > vec[i]->weight && vec[i]->value != '_') {
            least[0] = vec[i]->weight;
            least[1] = i;
        }
    }

    // find least 2;
    for (int i = 0; i < vec.size(); ++i) {
        if(least[2] > vec[i]->weight && i != least[1] && vec[i]->value != '_') {
            least[2] = vec[i]->weight;
            least[3] = i;
        }
    }

    return least;
}


void huffman(std::string content) {
    std::cout << "Compressing: " << content << std::endl;
    
    for (char const &c: content) {
	    if (data.find(c) != data.end()) {
            data[c]++;
        }

        else {
            data[c] = 1;
        }
    }

    // Make trees from data
    std::cout << "COLLECTED DATA:" << std::endl;
    for(std::map<char, int>::iterator i = data.begin(); i != data.end(); ++i) {
        std::cout << i->first << " " << i->second << " ";
        Node* node = make_node(i->first, i->second, nullptr, nullptr);
        trees.push_back(node);
    }
    std::cout << std::endl;

    while(trees.size() != 1) {
        int array[4];
        int* least = find_least(trees, array);
        int first = least[0];
        int index1 = least[1];
        int second = least[2];
        int index2 = least[3];

    
        std::cout << "LEAST1: " << trees[index1]->weight << " LEAST2: " << trees[index2]->weight << std::endl;
        

        // Create node with new values and add it to tree list
        std::cout << "Making new node with weight: " << first + second << std::endl; 
        Node* new_node = make_node('_', first + second, trees[index2], trees[index1]);
        trees.push_back(new_node);
        
        // Remove old nodes from tree list
        std::cout << "removing nodes with value: " << trees[index1]->value << " " << trees[index2]->value << std::endl;
        trees.erase(trees.begin() + index1);
        trees.erase(trees.begin() + index2 - 1);

        std::cout << "Current vector: " << std::endl;
        for(int i = 0; i < trees.size(); ++i) {
            std::cout << trees[i]->value << " ";
        }
    }
}

void printLeafNodes(Node* root) { 

    // if node is null, return 
    if (root == nullptr) {
        return; 
    }
      
    // if node is leaf node, print its data     
    if (root->left==nullptr && root->right==nullptr) 
    { 
        std::cout << root->value << " " << root->weight << " ";  
        return; 
    } 
  
    // if left child exists, check for leaf  
    // recursively 
    if (root->left) 
       printLeafNodes(root->left); 
          
    // if right child exists, check for leaf  
    // recursively 
    if (root->right) 
       printLeafNodes(root->right); 
}  

void show_table() {
    // printLeafNodes(trees[0]);
}
