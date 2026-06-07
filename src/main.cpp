// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>

int main() {
   std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  std::vector<std::vector<char>> perms = getAllPerms(tree);

  std::vector<char> result1 = getPerm1(tree, 1);
  std::vector<char> result2 = getPerm2(tree, 2);

  return 0;
}
