#include "testlib.h"
#include <vector>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose N from a small set for hand-checkability
    vector<int> possibleN = {2, 3, 5, 8, 13, 20};
    int N = rnd.any(possibleN);

    // Choose a cost-pattern type for variability
    // 0: full uniform [1,1000]
    // 1: small uniform [1,10]
    // 2: skewed one color cheap per house
    // 3: linear trend + noise
    // 4: periodic cheapest-color pattern
    int type = rnd.next(0, 4);

    vector<vector<int>> cost(N, vector<int>(3));

    switch (type) {
        case 0:
            // full range
            for (int i = 0; i < N; i++)
                for (int j = 0; j < 3; j++)
                    cost[i][j] = rnd.next(1, 1000);
            break;
        case 1:
            // small range
            for (int i = 0; i < N; i++)
                for (int j = 0; j < 3; j++)
                    cost[i][j] = rnd.next(1, 10);
            break;
        case 2:
            // skewed: one color cheap per house
            for (int i = 0; i < N; i++) {
                int fav = rnd.next(0, 2);
                for (int j = 0; j < 3; j++) {
                    if (j == fav) cost[i][j] = rnd.next(1, 20);
                    else          cost[i][j] = rnd.next(100, 1000);
                }
            }
            break;
        case 3:
            {
                // linear trend + small noise
                int base[3], delta[3];
                for (int j = 0; j < 3; j++) {
                    base[j] = rnd.next(1, 50);
                    delta[j] = rnd.next(0, 20);
                }
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < 3; j++) {
                        cost[i][j] = base[j] + i * delta[j] + rnd.next(0, 10);
                        if (cost[i][j] > 1000) cost[i][j] = 1000;
                    }
                }
            }
            break;
        case 4:
            {
                // periodic cheapest-color pattern
                vector<array<int,3>> patterns = {
                    array<int,3>{1, 100, 100},
                    array<int,3>{100, 1, 100},
                    array<int,3>{100, 100, 1}
                };
                for (int i = 0; i < N; i++) {
                    auto p = patterns[i % 3];
                    for (int j = 0; j < 3; j++) {
                        cost[i][j] = p[j] + rnd.next(0, 10);
                    }
                }
            }
            break;
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++)
        println(cost[i]);

    return 0;
}
