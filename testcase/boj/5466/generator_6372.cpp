#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of markets
    int N = rnd.next(1, 10);
    // Fuel costs
    int U = rnd.next(1, 10);
    int D = rnd.next(1, U);
    // Home position
    int S = rnd.next(2, 50);
    // Maximum possible position for markets
    int maxPos = S + N + 5;

    // Determine how many markets upstream (L < S) and downstream (L > S)
    int upCount, downCount;
    if (N > 1) {
        upCount = rnd.next(1, min(N - 1, S - 1));
    } else {
        upCount = rnd.next(0, 1);
    }
    downCount = N - upCount;

    // Generate unique positions
    vector<int> upCands;
    for (int x = 1; x < S; ++x) upCands.push_back(x);
    shuffle(upCands.begin(), upCands.end());
    vector<int> positions;
    for (int i = 0; i < upCount; ++i) positions.push_back(upCands[i]);

    vector<int> downCands;
    for (int x = S + 1; x <= maxPos; ++x) downCands.push_back(x);
    shuffle(downCands.begin(), downCands.end());
    for (int i = 0; i < downCount; ++i) positions.push_back(downCands[i]);

    // Hyperparameters for days and profits
    int maxDay = max(1, N * 3);
    vector<int> tOptions = { -2, -1, 1, 2 };
    vector<int> mOptions = { -1, 1 };

    // Build market list
    vector<tuple<int,int,int>> markets;
    for (int i = 0; i < N; ++i) {
        int tBias = rnd.any(tOptions);
        int T = rnd.wnext(maxDay, tBias) + 1;
        int L = positions[i];
        int pBias = rnd.any(mOptions);
        int M = rnd.wnext(1000, pBias) + 1;
        markets.emplace_back(T, L, M);
    }
    shuffle(markets.begin(), markets.end());

    // Output
    println(N, U, D, S);
    for (auto &mk : markets) {
        int T, L, M;
        tie(T, L, M) = mk;
        println(T, L, M);
    }

    return 0;
}
