#include <ctime>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>

// Substitute RBTree.h or RBTree-BST.h
#include "RBTree-BST.h"

using namespace std;

const int ITERS = 10000;

long diff (const timespec& first, const timespec& second)
{
  return ((second.tv_sec - first.tv_sec) * (1000000000 / ITERS)
       + (second.tv_nsec - first.tv_nsec) / ITERS);
}

int main()
{
  srand(getpid() ^ time(nullptr));

  timespec check[6];

  vector<int> nums;
  RBTree<int> randorder;
  RBTree<int> inorder;
  FILE * fp;

  for (int i = 0; i < ITERS; ++i)
    nums.push_back(rand());

  clock_gettime(CLOCK_MONOTONIC, &check[0]);

  for (int i = 0; i < ITERS; ++i)
    randorder.add(nums[i]);

  clock_gettime(CLOCK_MONOTONIC, &check[1]);

  for (int i = 0; i < ITERS; ++i)
    randorder.contains(rand());

  clock_gettime(CLOCK_MONOTONIC, &check[2]);

  sort (nums.begin(), nums.end());

  clock_gettime(CLOCK_MONOTONIC, &check[3]);

  for (int i = 0; i < ITERS; ++i)
    inorder.add(nums[i]);

  clock_gettime(CLOCK_MONOTONIC, &check[4]);

  for (int i = 0; i < ITERS; ++i)
    inorder.contains(rand());

  clock_gettime(CLOCK_MONOTONIC, &check[5]);
  
  fp = fopen ("speedBSTree.txt", "w+");
  fprintf(fp, "Avg add (random) : ""%ld""ns\n" "Avg search (random): ""%ld""ns\n" "Avg add (order): "" %ld""ns\n" "Avg search (order): "" %ld""ns\n", diff (check[0], check[1]), diff (check[1], check[2]), diff (check[3], check[4]), diff (check[4], check[5]));
 fclose(fp); 
  cout << "Avg add (random): " << diff (check[0], check[1]) << "ns\n";
  cout << "Avg search (random): " << diff (check[1], check[2]) << "ns\n";
  cout << "Avg add (order): " << diff (check[3], check[4]) << "ns\n";
  cout << "Avg search (order): " << diff (check[4], check[5]) << "ns\n";
}
