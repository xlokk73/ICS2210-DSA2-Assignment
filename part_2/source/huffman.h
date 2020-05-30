#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <vector>
#include <map>

struct Node {
    char value;
    int weight;
    Node* left;
    Node* right;
};

extern std::map<char, int> data;
extern std::vector<Node*> trees;

Node* make_node(char value, char wieght, Node* left, Node* right);

void destroy(Node* tree);

void huffman(std::string content);

void show_table(Node* root, std::string history);

#endif
