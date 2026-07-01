#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

const int ALPHABET = 26;

string fromCycles(vector<vector<int>> cycles) {
    vector<int> p(ALPHABET);
    for (const auto& cycle : cycles) {
        int len = (int)cycle.size();
        for (int i = 0; i < len; ++i) {
            p[cycle[i]] = cycle[(i + 1) % len];
        }
    }

    string s;
    for (int x : p) {
        s.push_back(char('A' + x));
    }
    return s;
}

vector<vector<int>> randomPartitionCycles(vector<int> letters, const vector<int>& sizes) {
    shuffle(letters.begin(), letters.end());

    vector<vector<int>> cycles;
    int at = 0;
    for (int size : sizes) {
        vector<int> cycle;
        for (int i = 0; i < size; ++i) {
            cycle.push_back(letters[at++]);
        }
        if (size > 1) {
            shuffle(cycle.begin(), cycle.end());
        }
        cycles.push_back(cycle);
    }
    return cycles;
}

vector<int> randomCycleSizes() {
    vector<int> sizes;
    int remaining = ALPHABET;
    while (remaining > 0) {
        int size;
        if (remaining == 1) {
            size = 1;
        } else if (rnd.next(0, 3) == 0) {
            size = rnd.next(1, min(remaining, 4));
        } else {
            size = rnd.next(1, remaining);
        }
        sizes.push_back(size);
        remaining -= size;
    }
    return sizes;
}

string squareOfRandomPermutation() {
    vector<int> p(ALPHABET), q(ALPHABET);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end());

    for (int i = 0; i < ALPHABET; ++i) {
        q[i] = p[p[i]];
    }

    string s;
    for (int x : q) {
        s.push_back(char('A' + x));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    println(t);

    vector<int> letters(ALPHABET);
    iota(letters.begin(), letters.end(), 0);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 7);
        string s;

        if (mode == 0) {
            s = fromCycles(randomPartitionCycles(letters, vector<int>(ALPHABET, 1)));
        } else if (mode == 1) {
            s = squareOfRandomPermutation();
        } else if (mode == 2) {
            s = fromCycles(randomPartitionCycles(letters, {2, 2, 22}));
        } else if (mode == 3) {
            int evenLen = rnd.any(vector<int>{2, 4, 6, 8, 10, 12});
            vector<int> sizes = {evenLen};
            int remaining = ALPHABET - evenLen;
            while (remaining > 0) {
                int size = min(remaining, rnd.any(vector<int>{1, 3, 5, 7, 9}));
                sizes.push_back(size);
                remaining -= size;
            }
            s = fromCycles(randomPartitionCycles(letters, sizes));
        } else if (mode == 4) {
            int evenLen = rnd.any(vector<int>{2, 4, 6, 8});
            vector<int> sizes = {evenLen, evenLen};
            int remaining = ALPHABET - 2 * evenLen;
            while (remaining > 0) {
                int size = rnd.next(1, min(remaining, 6));
                sizes.push_back(size);
                remaining -= size;
            }
            s = fromCycles(randomPartitionCycles(letters, sizes));
        } else if (mode == 5) {
            s = fromCycles(randomPartitionCycles(letters, {26}));
        } else if (mode == 6) {
            vector<int> sizes = randomCycleSizes();
            s = fromCycles(randomPartitionCycles(letters, sizes));
        } else {
            vector<int> shuffled = letters;
            shuffle(shuffled.begin(), shuffled.end());
            s.clear();
            for (int x : shuffled) {
                s.push_back(char('A' + x));
            }
        }

        println(s);
    }

    return 0;
}
