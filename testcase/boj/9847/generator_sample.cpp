#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

long long countZeroSumSelections(const vector<vector<int>>& sets) {
    long long count = 0;
    for (int w : sets[0]) {
        for (int x : sets[1]) {
            for (int y : sets[2]) {
                for (int z : sets[3]) {
                    if (w + x + y + z == 0) {
                        ++count;
                    }
                }
            }
        }
    }
    return count;
}

vector<int> randomUniqueSet(int size, int low, int high) {
    set<int> used;
    while ((int)used.size() < size) {
        used.insert(rnd.next(low, high));
    }
    return vector<int>(used.begin(), used.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    vector<int> sizes(4);
    for (int i = 0; i < 4; ++i) {
        if (mode == 0) {
            sizes[i] = rnd.next(1, 3);
        } else if (mode == 1) {
            sizes[i] = rnd.next(2, 6);
        } else {
            sizes[i] = rnd.next(4, 9);
        }
    }

    int spread = mode == 0 ? 8 : (mode == 1 ? 20 : 45);
    vector<vector<int>> sets(4);

    for (int attempt = 0; attempt < 10000; ++attempt) {
        for (int i = 0; i < 3; ++i) {
            sets[i] = randomUniqueSet(sizes[i], -spread, spread);
        }
        sets[3] = randomUniqueSet(sizes[3], -spread, spread);

        int chosen0 = rnd.any(sets[0]);
        int chosen1 = rnd.any(sets[1]);
        int chosen2 = rnd.any(sets[2]);
        int needed = -(chosen0 + chosen1 + chosen2);
        if (needed < -60000 || needed > 60000) {
            continue;
        }

        int replaceIndex = rnd.next(0, sizes[3] - 1);
        bool duplicate = false;
        for (int i = 0; i < sizes[3]; ++i) {
            if (i != replaceIndex && sets[3][i] == needed) {
                duplicate = true;
            }
        }
        if (duplicate) {
            continue;
        }

        sets[3][replaceIndex] = needed;
        shuffle(sets[0].begin(), sets[0].end());
        shuffle(sets[1].begin(), sets[1].end());
        shuffle(sets[2].begin(), sets[2].end());
        shuffle(sets[3].begin(), sets[3].end());

        if (countZeroSumSelections(sets) == 1) {
            println(sizes[0], sizes[1], sizes[2], sizes[3]);
            for (const vector<int>& values : sets) {
                for (int value : values) {
                    println(value);
                }
            }
            return 0;
        }
    }

    println(1, 1, 1, 1);
    println(-1);
    println(0);
    println(0);
    println(1);
    return 0;
}
