#include <iostream>
#include <vector>
#include <queue>

int dp_coin_change(int W, const std::vector<int> &coins) {
    std::vector<int> dp(W + 1, W + 1);
    dp[0] = 0;

    for (int i = 1; i <= W; ++i) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return (dp[W] == W + 1) ? -1 : dp[W]; // -1 si no se puede dar el cambio exacto
}

int greedy_coin_change(int W, const std::vector<int> &coins) {
    std::priority_queue<int> max_heap(coins.begin(), coins.end());
    int total_coins = 0;

    while (W > 0 && !max_heap.empty()) {
        int coin = max_heap.top();
        max_heap.pop();
        while (W >= coin) {
            W -= coin;
            total_coins++;
        }
    }

    return (W == 0) ? total_coins : -1; // -1 si no se puede dar el cambio exacto
}

int main() {
    std::vector<int> coins = {1, 5, 10, 50, 100};
    int W = 1250;

    int result = dp_coin_change(W, coins);
    if (result != -1) {
        std::cout << "Número mínimo de monedas para dar el cambio: " << result << std::endl;
    } else {
        std::cout << "No es posible dar el cambio exacto." << std::endl;
    }
    return 0;
}