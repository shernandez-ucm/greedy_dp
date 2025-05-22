#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <random>

// ...existing code...

int main() {
    int n;
    std::cout << "Enter number of items: ";
    std::cin >> n;

    // Random number generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> value_dist(10, 1000);   // values between 10 and 1000
    std::uniform_int_distribution<> weight_dist(1, 100);    // weights between 1 and 100

    std::vector<int> values(n), weights(n);
    int total_weight = 0;
    for (int i = 0; i < n; ++i) {
        values[i] = value_dist(gen);
        weights[i] = weight_dist(gen);
        total_weight += weights[i];
    }

    // Set capacity to about half the total weight (typical for knapsack tests)
    int capacity = total_weight / 2;
    std::cout << "Knapsack capacity: " << capacity << std::endl;

    // Print generated values and weights

    return 0;
}