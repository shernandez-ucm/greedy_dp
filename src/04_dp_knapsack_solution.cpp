#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::vector;

// Devuelve el valor máximo y la tabla dp
int knapsack(int W, const vector<int> &val, const vector<int> &wt, vector<vector<int>> &dp) {
    int n = wt.size();
    dp.assign(n + 1, vector<int>(W + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else {
                int pick = 0;
                if (wt[i - 1] <= j)
                    pick = val[i - 1] + dp[i - 1][j - wt[i - 1]];
                int notPick = dp[i - 1][j];
                dp[i][j] = std::max(pick, notPick);
            }
        }
    }
    return dp[n][W];
}

// Extrae los ítems seleccionados usando la tabla dp
vector<int> extractItems(int W, const vector<int>& wt, const vector<vector<int>>& dp) {
    vector<int> selected;
    int n = wt.size();
    int w = W;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i-1][w]) {
            selected.push_back(i-1);
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
