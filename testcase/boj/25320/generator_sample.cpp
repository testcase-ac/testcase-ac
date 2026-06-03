#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(3, 18);
    }

    int maxBlock = 2 * n;
    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 1) {
        m = rnd.next(1, min(maxBlock, 4));
    } else if (mode == 2) {
        m = rnd.next(max(1, maxBlock - 4), maxBlock);
    } else {
        m = rnd.next(2, min(maxBlock, 14));
    }

    vector<int> blocks(maxBlock);
    iota(blocks.begin(), blocks.end(), 1);

    if (mode == 3 && maxBlock > 1) {
        blocks.erase(blocks.begin());
    }
    shuffle(blocks.begin(), blocks.end());
    if ((int)blocks.size() < m) {
        m = blocks.size();
    }

    if (mode == 4) {
        sort(blocks.begin(), blocks.end());
        if (rnd.next(0, 1)) {
            reverse(blocks.begin(), blocks.end());
        }
    }

    blocks.resize(m);

    if (mode == 0) {
        blocks[0] = 1;
    } else if (mode == 5 && maxBlock > 1) {
        auto it = find(blocks.begin(), blocks.end(), 1);
        if (it == blocks.end()) {
            blocks[rnd.next(m)] = 1;
        }
        shuffle(blocks.begin(), blocks.end());
    }

    vector<pair<string, int>> records;
    records.reserve(m);
    for (int i = 0; i < m; ++i) {
        string robot;
        if (i == 0) {
            robot = "A";
        } else if (mode == 1) {
            robot = "A";
        } else if (mode == 2) {
            robot = (i % 2 == 0 ? "A" : "B");
        } else if (mode == 4) {
            robot = rnd.next(0, 3) == 0 ? "B" : "A";
        } else {
            robot = rnd.next(0, 1) == 0 ? "A" : "B";
        }
        records.push_back({robot, blocks[i]});
    }

    println(n, m);
    for (const auto& [robot, block] : records) {
        println(robot, "BLOCK", block);
    }

    return 0;
}
