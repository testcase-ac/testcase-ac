#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int length;
    vector<int> positions;

    if (mode == 0) {
        length = rnd.next(10, 25);
        for (int x = 0; x <= length; ++x) {
            positions.push_back(x);
        }
        shuffle(positions.begin(), positions.end());
        positions.resize(6);
    } else if (mode == 1) {
        length = rnd.any(vector<int>{10, 11, 20, 100, 999, 1000});
        set<int> chosen{0, length};
        while ((int)chosen.size() < 6) {
            chosen.insert(rnd.next(0, length));
        }
        positions.assign(chosen.begin(), chosen.end());
        shuffle(positions.begin(), positions.end());
    } else if (mode == 2) {
        length = rnd.next(12, 80);
        set<int> chosen;
        while ((int)chosen.size() < 6) {
            int x = rnd.next(0, length);
            int y = length - x;
            if (x != y) {
                chosen.insert(x);
                chosen.insert(y);
            }
        }
        positions.assign(chosen.begin(), chosen.end());
        shuffle(positions.begin(), positions.end());
        positions.resize(6);
    } else if (mode == 3) {
        length = rnd.next(50, 1000);
        int lo = rnd.next(0, length - 10);
        int hi = rnd.next(lo + 5, length);
        set<int> chosen{lo, hi};
        while ((int)chosen.size() < 6) {
            chosen.insert(rnd.next(lo, hi));
        }
        positions.assign(chosen.begin(), chosen.end());
        shuffle(positions.begin(), positions.end());
    } else {
        length = rnd.next(10, 1000);
        set<int> chosen;
        while ((int)chosen.size() < 6) {
            int bias = rnd.next(0, 3);
            if (bias == 0) {
                chosen.insert(rnd.next(0, min(length, 20)));
            } else if (bias == 1) {
                chosen.insert(rnd.next(max(0, length - 20), length));
            } else {
                chosen.insert(rnd.next(0, length));
            }
        }
        positions.assign(chosen.begin(), chosen.end());
        shuffle(positions.begin(), positions.end());
    }

    vector<pair<int, int>> pairs;
    for (int i = 0; i < 6; i += 2) {
        pairs.push_back({positions[i], positions[i + 1]});
    }
    shuffle(pairs.begin(), pairs.end());

    println(length);
    for (const auto& p : pairs) {
        println(p.first, p.second);
    }

    return 0;
}
