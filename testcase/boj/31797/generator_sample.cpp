#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    int M = rnd.next(1, 12);
    if (mode == 5) {
        M = rnd.next(20, 40);
    }

    int N;
    if (mode == 0) {
        N = rnd.next(1, 2 * M);
    } else if (mode == 1) {
        N = rnd.next(max(1, 2 * M - 3), 2 * M + 3);
    } else if (mode == 2) {
        N = rnd.next(900, 1000);
    } else {
        N = rnd.next(1, 1000);
    }

    const int totalHands = 2 * M;
    vector<int> heights;
    heights.reserve(totalHands);

    if (mode == 0) {
        int start = rnd.next(1, 10000 - totalHands + 1);
        for (int i = 0; i < totalHands; ++i) {
            heights.push_back(start + i);
        }
    } else if (mode == 1) {
        int start = rnd.next(1, 10000 - totalHands + 1);
        for (int i = 0; i < totalHands; ++i) {
            heights.push_back(start + totalHands - 1 - i);
        }
    } else if (mode == 2) {
        vector<int> pool(10000);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        heights.assign(pool.begin(), pool.begin() + totalHands);
    } else if (mode == 3) {
        int lowCount = rnd.next(1, totalHands - 1);
        for (int i = 0; i < lowCount; ++i) {
            heights.push_back(i + 1);
        }
        for (int i = 0; i < totalHands - lowCount; ++i) {
            heights.push_back(10000 - i);
        }
        shuffle(heights.begin(), heights.end());
    } else {
        int step = rnd.next(2, max(2, 10000 / totalHands));
        int start = rnd.next(1, 10000 - step * (totalHands - 1));
        for (int i = 0; i < totalHands; ++i) {
            heights.push_back(start + i * step);
        }
        if (mode == 5) {
            shuffle(heights.begin(), heights.end());
        }
    }

    vector<pair<int, int>> hands;
    hands.reserve(M);
    for (int i = 0; i < M; ++i) {
        int first = heights[2 * i];
        int second = heights[2 * i + 1];
        if (rnd.next(0, 1)) {
            swap(first, second);
        }
        hands.push_back({first, second});
    }
    if (rnd.next(0, 1)) {
        shuffle(hands.begin(), hands.end());
    }

    println(N, M);
    for (const auto& hand : hands) {
        println(hand.first, hand.second);
    }

    return 0;
}
