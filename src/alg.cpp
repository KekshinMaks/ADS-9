// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

#include <algorithm>
#include <memory>
#include <vector>

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    return;
  }

  root = std::make_shared<Node>('\0');
  std::vector<char> sorted = elements;
  std::sort(sorted.begin(), sorted.end());
  buildTree(root, sorted);
}

int PMTree::factorial(int n) const {
  int result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

void PMTree::buildTree(std::shared_ptr<Node> node,
                       std::vector<char> remaining) {
  if (remaining.empty()) {
    return;
  }

  std::sort(remaining.begin(), remaining.end());

  for (char c : remaining) {
    auto child = std::make_shared<Node>(c);
    node->children.push_back(child);

    std::vector<char> newRemaining;
    for (char rc : remaining) {
      if (rc != c) {
        newRemaining.push_back(rc);
      }
    }

    buildTree(child, newRemaining);
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;

  if (!tree.root || tree.root->children.empty()) {
    return result;
  }

  std::vector<char> current;
  tree.getAllPermsRecursive(tree.root, current, result);

  return result;
}

void PMTree::getAllPermsRecursive(std::shared_ptr<Node> node,
                                  std::vector<char>& current,
                                  std::vector<std::vector<char>>& result)
                                      const {
  if (node->children.empty()) {
    if (!current.empty()) {
      result.push_back(current);
    }
    return;
  }

  for (const auto& child : node->children) {
    current.push_back(child->value);
    getAllPermsRecursive(child, current, result);
    current.pop_back();
  }
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  if (num < 1) {
    return std::vector<char>();
  }

  auto allPerms = getAllPerms(tree);

  if (num > static_cast<int>(allPerms.size())) {
    return std::vector<char>();
  }

  return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1 || !tree.root || tree.root->children.empty()) {
    return std::vector<char>();
  }

  int totalPerms = tree.factorial(tree.root->children.size());
  if (num > totalPerms) {
    return std::vector<char>();
  }

  std::vector<char> result;
  auto currentNode = tree.root;
  int remaining = num;

  while (currentNode && !currentNode->children.empty()) {
    int childCount = currentNode->children.size();
    int permsPerChild = tree.factorial(childCount - 1);

    int childIndex = (remaining - 1) / permsPerChild;

    if (childIndex >= static_cast<int>(currentNode->children.size())) {
      return std::vector<char>();
    }

    auto selectedChild = currentNode->children[childIndex];
    result.push_back(selectedChild->value);

    currentNode = selectedChild;
    remaining = remaining - (childIndex * permsPerChild);
  }

  return result;
}
