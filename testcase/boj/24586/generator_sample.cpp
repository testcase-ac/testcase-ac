#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool hasValidBobCards(int p, int q, const string& positions) {
    for (int x = 1; x <= 9; ++x) {
        if (x == p || x == q) {
            continue;
        }
        for (int y = x + 1; y <= 9; ++y) {
            if (y == p || y == q) {
                continue;
            }

            int aliceIndex = 0;
            int bobIndex = 0;
            int aliceCards[2] = {p, q};
            int bobCards[2] = {x, y};
            int table[4];

            for (int i = 0; i < 4; ++i) {
                if (positions[i] == 'A') {
                    table[i] = aliceCards[aliceIndex++];
                } else {
                    table[i] = bobCards[bobIndex++];
                }
            }

            if (is_sorted(table, table + 4) &&
                adjacent_find(table, table + 4) == table + 4) {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> patterns = {"AABB", "ABAB", "ABBA", "BAAB", "BABA", "BBAA"};
    string positions = rnd.any(patterns);

    vector<pair<int, int>> candidates;
    for (int p = 1; p <= 9; ++p) {
        for (int q = p + 1; q <= 9; ++q) {
            if (hasValidBobCards(p, q, positions)) {
                candidates.emplace_back(p, q);
            }
        }
    }

    int mode = rnd.next(0, 2);
    if (mode == 0) {
        vector<pair<int, int>> edgeCandidates;
        for (auto candidate : candidates) {
            if (candidate.first == 1 || candidate.second == 9) {
                edgeCandidates.push_back(candidate);
            }
        }
        if (!edgeCandidates.empty()) {
            candidates = edgeCandidates;
        }
    } else if (mode == 1) {
        vector<pair<int, int>> middleCandidates;
        for (auto candidate : candidates) {
            if (candidate.first > 1 && candidate.second < 9) {
                middleCandidates.push_back(candidate);
            }
        }
        if (!middleCandidates.empty()) {
            candidates = middleCandidates;
        }
    }

    auto [p, q] = rnd.any(candidates);
    println(p, q);
    println(positions);

    return 0;
}
