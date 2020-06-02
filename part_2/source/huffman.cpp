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

void show_table(Node* root, std::string history) { 

    // if node is null, return 
    if (root == nullptr) {
        return; 
    }
    
    std::string left_history(history);
    std::string right_history(history);
      
    // if node is leaf node, print its data     
    if (root->left==nullptr && root->right==nullptr) { 
        std::cout << history << " " << root->value << std::endl;  
        return; 
    } 
  
    // if left child exists, check for leaf  
    // recursively 
    if (root->left != nullptr) {
        left_history.push_back('1'); 
        show_table(root->left, left_history); 
    }
          
    // if right child exists, check for leaf  
    // recursively 
    if (root->right != nullptr) {
        right_history.push_back('0');
        show_table(root->right, right_history); 
    }
}  

bool greater_than(Node* node1, Node* node2) {
    return node1->weight > node2->weight;
}

std::vector<Node*> merge_and_remove(std::vector<Node*> trees) {
    int first_index = trees.size() - 1;
    int second_index = first_index - 1;

    Node* first = trees[first_index];
    Node* second = trees[second_index];
    Node* new_node = make_node('_', first->weight + second->weight, first, second);

    trees.erase(trees.begin() + first_index);
    trees.erase(trees.begin() + second_index);

    trees.push_back(new_node);
    
    return trees;
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

    while(trees.size() > 1) {
        std::sort(trees.begin(), trees.end(), greater_than); 
        trees = merge_and_remove(trees);
    }
}

