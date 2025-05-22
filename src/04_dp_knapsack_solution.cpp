#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapsackRec(int W, std::vector<int> &val, std::vector<int> &wt, int n, 
                                        std::vector<std::vector<int>> &memo) {
    // Base Case
    if (n == 0 || W == 0)
        return 0;
    // Check if we have previously calculated the same subproblem
    if(memo[n][W] != -1)
        return memo[n][W];
    int pick = 0;
    // Pick nth item if it does not exceed the capacity of knapsack
    if (wt[n - 1] <= W)
        pick = val[n - 1] + knapsackRec(W - wt[n - 1], val, wt, n - 1, memo);
    // Don't pick the nth item
    int notPick = knapsackRec(W, val, wt, n - 1, memo);
    // Store the result in memo[n][W] and return it
    return memo[n][W] = std::max(pick, notPick);
}

int knapsack(int W, std::vector<int> &val, std::vector<int> &wt, std::vector<std::vector<int>> &memo) {
    int n = val.size();
    // Memoization table to store the results
    memo.assign(n + 1, std::vector<int>(W + 1, -1));
    return knapsackRec(W, val, wt, n, memo);
}

std::vector<int> extractItems(int W, const std::vector<int>& wt, const std::vector<std::vector<int>>& memo) {
    std::vector<int> selected;
    int n = wt.size();
    int w = W;
    for (int i = n; i > 0 && w > 0; --i) {
        if (memo[i][w] != memo[i-1][w]) {
            selected.push_back(i-1); // item i-1 was included
            w -= wt[i-1];
        }
    }
    return selected;
}

int main() {
    // https://developers.google.com/optimization/pack/knapsack?hl=es-419#c++
    std::vector<int> values = {
      360, 83, 59,  130, 431, 67, 230, 52,  93,  125, 670, 892, 600,
      38,  48, 147, 78,  256, 63, 17,  120, 164, 432, 35,  92,  110,
      22,  42, 50,  323, 514, 28, 87,  73,  78,  15,  26,  78,  210,
      36,  85, 189, 274, 43,  33, 10,  19,  389, 276, 312};

    std::vector<int> weights = {7,  0,  30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0,  36, 3,  8,  15,
       42, 9,  0,  42, 47, 52, 32, 26, 48, 55, 6,  29, 84, 2,  4,  18, 56,
       7,  29, 93, 44, 71, 3,  86, 66, 31, 65, 0,  79, 20, 65, 52, 13};

    int capacity = 850;
    std::vector<std::vector<int>> memo;
    int maxValue = knapsack(capacity, values, weights, memo);
    std::cout << "Total value: " << maxValue << std::endl;

    std::vector<int> selected = extractItems(capacity, weights, memo);
    std::sort(selected.begin(), selected.end());
    std::cout << "Packed items: ";
    for (int idx : selected) std::cout << idx << " ";
    std::cout <<std::endl;

    return 0;
  
}
