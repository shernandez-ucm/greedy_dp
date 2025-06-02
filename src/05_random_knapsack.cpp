#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

class Item {
  public:
    int id;
    int value;
    int weight;
    float value_weight{0.0};
    
    Item(int i,int v,int w){
      id=i;
      value=v;
      weight=w;
      if (w!=0){
        value_weight=1.0*v/w;
      }
      else{
        value_weight=v;
      }
    }
    void display() const{
      std::cout << "id: " << id << ",value: " << value << ",weight : "<< weight <<"\n";
    }
   
};

int knapsack(int W, const std::vector<int> &val, const std::vector<int> &wt, std::vector<std::vector<int>> &dp) {
    int n = wt.size();
    dp.assign(n + 1, std::vector<int>(W + 1, 0));

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

int knapsack_greedy(int W, const std::vector<Item> &items) {
    std::vector<Item> sorted_items = items;
    auto compareByValueWeight = [](const Item &a,const Item &b) {
      return a.value_weight < b.value_weight;
    };
    std::make_heap(sorted_items.begin(), sorted_items.end(),compareByValueWeight);
    int total_value = 0;
    int total_weight = 0;

    for (const auto &item : sorted_items) {
        if (total_weight + item.weight <= W) {
            total_weight += item.weight;
            total_value += item.value;
        } else {
            break; // Can't add more items without exceeding capacity
        }
    }
    return total_value;
}

int main(int argc, char* argv[]) {
    int n=atoi(argv[1]);
    //std::cout << "Enter number of items: ";
    //std::cin >> n;

    // Random number generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> value_dist(10, 1000);   // values between 10 and 1000
    std::uniform_int_distribution<> weight_dist(1, 100);    // weights between 1 and 100
    std::vector<Item> items;
    std::vector<int> values(n), weights(n);
    int total_weight = 0;
    for (int i = 0; i < n; ++i) {
        values[i] = value_dist(gen);
        weights[i] = weight_dist(gen);
        total_weight += weights[i];
        Item item(i,values[i],weights[i]);
        items.push_back(item);
    }

    // Set capacity to about half the total weight (typical for knapsack tests)
    int capacity = total_weight / 2;
    std::cout << "Knapsack capacity: " << capacity << std::endl;
    auto start1=std::chrono::high_resolution_clock::now();
    int greedy_value = knapsack_greedy(capacity,items);
    auto end1=std::chrono::high_resolution_clock::now();
    auto greedy_time=std::chrono::duration_cast<std::chrono::milliseconds>(end1-start1).count();
    std::cout << "Greedy knapsack value: " << greedy_value << ", time : " << greedy_time << "[ms]"<< std::endl;
    std::vector<std::vector<int>> memo;
    auto start2=std::chrono::high_resolution_clock::now();
    int dp_value=knapsack(capacity, values, weights, memo);
    auto end2=std::chrono::high_resolution_clock::now();
    auto dp_time=std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2).count();
    std::cout << "DP knapsack value: " << dp_value << ", time : " << dp_time << "[ms]"<< std::endl;
    // Print generated values and weights

    return 0;
}