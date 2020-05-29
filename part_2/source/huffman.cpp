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

    return node;
}

void destroy(Node* tree) {
  if ( tree != nullptr ) {
      destroy(tree->left);
      destroy(tree->right);
      free(tree);
  }
}

void find_least(std::vector<Node*> vec, int* least) {
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
        if(least[0] > vec[i]->weight) {
            least[0] = vec[i]->weight;
            least[1] = i;
        }
    }

    // find least 2;
    for (int i = 0; i < vec.size(); ++i) {
        if(least[2] > vec[i]->weight && i != least[1]) {
            least[2] = vec[i]->weight;
            least[3] = i;
        }
    }
}

void print_tree(Node* node) {
    if (node==nullptr) {
        return;
    }

    if (node->left == nullptr && node->right == nullptr) {
        std::cout << "Value: " << node->value << " Weight: " << node->weight << std::endl;
        return;
    }

    if ( node->left != nullptr) {
        print_tree(node->left);
    }

    if ( node->right != nullptr) {
        print_tree(node->right);
    }
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

    //Huffman 
    while(trees.size() != 1) {
        std::cout << "hello" << std::endl;
        //find least 1 and least 2
        int least[4];
        find_least(trees, least);

        // merge trees
        Node* new_node = make_node('_', least[0] + least[2], trees[least[1]], trees[least[3]]);
        
        //  remove old nodes
        trees.erase(trees.begin() + least[1]);
        if ( least[3] < least[1] ) {
            trees.erase(trees.begin() + least[3]);
        }

        else {
            trees.erase(trees.begin() + least[3] - 1);
        }

        // add new node
        trees.push_back(new_node);
    }

    std::cout << "SIZE OF VECTOR: " << trees.size() << std::endl;


    std::cout << "Printing tree: " << std::endl;
    print_tree(trees[0]);
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
