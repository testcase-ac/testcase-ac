#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate small N and H for easy verification
    int N = rnd.next(2, 5);
    int H = rnd.next(1, 5);

    // Generate all possible positions for horizontal lines
    vector<pair<int, int>> positions;
    for (int a = 1; a <= H; ++a) {
        for (int b = 1; b <= N - 1; ++b) {
            positions.emplace_back(a, b);
        }
    }

    // Shuffle positions to randomize selection
    shuffle(positions.begin(), positions.end());

    // Filter positions to avoid conflicts
    set<pair<int, int>> used;
    vector<pair<int, int>> valid_positions;

    for (auto& pos : positions) {
        int a = pos.first;
        int b = pos.second;
        // Ensure no two horizontal lines are adjacent or overlap
        if (used.count({a, b})) continue;
        if (used.count({a, b - 1})) continue;
        if (used.count({a, b + 1})) continue;
        used.insert({a, b});
        valid_positions.push_back(pos);
    }

    // The maximum number of horizontal lines we can place without conflicts
    int maxM = valid_positions.size();

    // Randomly choose M between 0 and maxM
    int M = rnd.next(0, maxM);

    println(N, M, H);

    // Shuffle valid_positions again to randomize the output
    shuffle(valid_positions.begin(), valid_positions.end());

    // Output M horizontal lines
    for (int i = 0; i < M; ++i) {
        println(valid_positions[i].first, valid_positions[i].second);
    }

    return 0;
}
