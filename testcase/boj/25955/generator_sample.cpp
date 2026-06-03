#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string difficulty(int tier, int stage) {
    const string tiers = "BSGPD";
    return string(1, tiers[tier]) + toString(stage);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> all;
    for (int tier = 0; tier < 5; ++tier) {
        for (int stage = 1000; stage >= 1; --stage) {
            all.push_back(difficulty(tier, stage));
        }
    }

    int mode = rnd.next(0, 5);
    int n = 0;
    vector<int> indices;

    if (mode == 0) {
        n = rnd.next(2, 8);
        int tier = rnd.next(0, 4);
        int firstStage = rnd.next(n, 1000);
        for (int i = 0; i < n; ++i) {
            indices.push_back(tier * 1000 + (1000 - (firstStage - i)));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int start = rnd.next(0, static_cast<int>(all.size()) - n);
        for (int i = 0; i < n; ++i) {
            indices.push_back(start + i);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        int step = rnd.next(1, 7);
        int start = rnd.next(0, static_cast<int>(all.size()) - 1 - step * (n - 1));
        for (int i = 0; i < n; ++i) {
            indices.push_back(start + i * step);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 15);
        indices.push_back(0);
        indices.push_back(999);
        indices.push_back(1000);
        indices.push_back(1999);
        indices.push_back(2000);
        indices.push_back(2999);
        indices.push_back(3000);
        indices.push_back(3999);
        indices.push_back(4000);
        indices.push_back(4999);
        shuffle(indices.begin(), indices.end());
        indices.resize(min(n, static_cast<int>(indices.size())));
        while (static_cast<int>(indices.size()) < n) {
            int candidate = rnd.next(0, static_cast<int>(all.size()) - 1);
            if (find(indices.begin(), indices.end(), candidate) == indices.end()) {
                indices.push_back(candidate);
            }
        }
        sort(indices.begin(), indices.end());
    } else {
        n = rnd.next(2, 25);
        while (static_cast<int>(indices.size()) < n) {
            int candidate = rnd.next(0, static_cast<int>(all.size()) - 1);
            if (find(indices.begin(), indices.end(), candidate) == indices.end()) {
                indices.push_back(candidate);
            }
        }
        sort(indices.begin(), indices.end());
    }

    vector<string> output;
    for (int index : indices) {
        output.push_back(all[index]);
    }

    bool makeSwap = rnd.next(0, 99) < 75;
    if (makeSwap) {
        int left = rnd.next(0, static_cast<int>(output.size()) - 2);
        int right;
        if (rnd.next(0, 1) == 0) {
            right = left + 1;
        } else {
            right = rnd.next(left + 1, static_cast<int>(output.size()) - 1);
        }
        swap(output[left], output[right]);
    }

    println(static_cast<int>(output.size()));
    println(output);

    return 0;
}
