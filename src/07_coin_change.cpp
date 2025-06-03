#include <iostream>
#include <vector>
#include <queue>

int dp_coin_change_tabular(int W, const std::vector<int> &coins,std::vector<std::vector<int>> &dp) {
    int n = coins.size();
    dp.assign(n + 1, std::vector<int>(W + 1, W + 1)); // Inicializa con un valor grande

    // Caso base: 0 monedas para cambio 0
    for (int i = 0; i <= n; ++i) dp[i][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= W; ++j) {
            // No tomar la moneda i-1
            dp[i][j] = dp[i-1][j];
            // Tomar la moneda i-1 si es posible
            if (j - coins[i-1] >= 0) {
                dp[i][j] = std::min(dp[i][j], dp[i][j - coins[i-1]] + 1);
            }
        }
    }
    return (dp[n][W] > W) ? -1 : dp[n][W]; // -1 si no se puede dar el cambio exactoas para dar el cambio
}

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
    int W = 24;
    std::vector<std::vector<int>> dp;
    int result = dp_coin_change_tabular(W, coins,dp);
    std::cout << "Monto a retornar: " << W << std::endl;
    if (result != -1) {
        std::cout << "Número mínimo de monedas para dar el cambio: " << result << std::endl;
    } else {
        std::cout << "No es posible dar el cambio exacto." << std::endl;
    }
    std::cout << "Tabla DP:" << std::endl;
    for (size_t i = 0; i < dp.size(); ++i) {
        for (size_t j = 0; j < dp[i].size(); ++j) {
            if (dp[i][j] > W)
                std::cout << "∞ ";
            else
                std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}