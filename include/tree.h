// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTree {
private:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        Node(char val) : value(val) {}
    };
    
    std::shared_ptr<Node> root;
    int factorial(int n) const;
    void buildTree(std::shared_ptr<Node> node, std::vector<char> remaining);
    void getAllPermsRecursive(std::shared_ptr<Node> node, 
                             std::vector<char>& current,
                             std::vector<std::vector<char>>& result) const;
    
public:
    PMTree(const std::vector<char>& elements);
    
    friend std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
    friend std::vector<char> getPerm1(const PMTree& tree, int num);
    friend std::vector<char> getPerm2(const PMTree& tree, int num);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
