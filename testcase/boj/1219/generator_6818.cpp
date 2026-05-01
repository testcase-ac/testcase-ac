#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(1, 10);
    // Max possible edges considering self-loops, capped by problem constraint
    int maxE = min(50, N * N);
    int M = rnd.next(0, maxE);

    // Generate all possible directed edges (including self-loops), then pick M
    vector<pair<int,int>> cand;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cand.emplace_back(i, j);
    shuffle(cand.begin(), cand.end());
    vector<pair<int,int>> edges(cand.begin(), cand.begin() + M);

    // Hyper-parameters for cost and profit scales
    vector<int> costPool = {0, 10, 1000, 1000000};
    vector<int> profitPool = {0, 10, 1000, 1000000};
    int maxCost = rnd.any(costPool);
    int maxProfit = rnd.any(profitPool);

    // Pick start and end cities
    int A = rnd.next(0, N - 1);
    int B = rnd.next(0, N - 1);

    // Output header
    println(N, A, B, M);
    // Output edges with random costs
    for (auto &e : edges) {
        int c = rnd.next(0, maxCost);
        println(e.first, e.second, c);
    }
    // Output profits for each city
    vector<int> profit(N);
    for (int i = 0; i < N; i++)
        profit[i] = rnd.next(0, maxProfit);
    println(profit);

    return 0;
}
