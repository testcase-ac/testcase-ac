#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

vector<int> makeFrequencies(int n, int mode) {
    vector<int> frequencies(2 * n + 1, 0);

    if (mode == 0) {
        int hot = rnd.next(0, 2 * n);
        frequencies[hot] = rnd.next(1, 40);
        for (int i = 0; i < (int)frequencies.size(); ++i) {
            if (i != hot && rnd.next(100) < 20) {
                frequencies[i] = rnd.next(0, 3);
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < (int)frequencies.size(); ++i) {
            bool isKey = i % 2 == 1;
            frequencies[i] = isKey ? rnd.next(1, 80) : rnd.next(0, 5);
        }
    } else if (mode == 2) {
        for (int i = 0; i < (int)frequencies.size(); ++i) {
            bool isGap = i % 2 == 0;
            frequencies[i] = isGap ? rnd.next(1, 80) : rnd.next(0, 5);
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 5);
        for (int i = 0; i < (int)frequencies.size(); ++i) {
            frequencies[i] = base + i * rnd.next(0, 3);
        }
    } else if (mode == 4) {
        int peak = rnd.next(0, 2 * n);
        for (int i = 0; i < (int)frequencies.size(); ++i) {
            int distance = abs(i - peak);
            frequencies[i] = max(0, rnd.next(0, 60) - distance * rnd.next(1, 6));
        }
    } else {
        for (int i = 0; i < (int)frequencies.size(); ++i) {
            frequencies[i] = rnd.wnext(100, -2);
        }
    }

    if (accumulate(frequencies.begin(), frequencies.end(), 0) == 0) {
        frequencies[rnd.next(0, 2 * n)] = 1;
    }
    return frequencies;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(2, 6);
    vector<int> sizes;
    sizes.push_back(1);
    sizes.push_back(rnd.next(2, 8));
    if (rnd.next(100) < 35) {
        sizes.push_back(rnd.next(30, 80));
    }
    if (rnd.next(100) < 20) {
        sizes.push_back(200);
    }

    for (int caseIndex = 0; caseIndex < cases; ++caseIndex) {
        int n = rnd.any(sizes);
        if (caseIndex >= (int)sizes.size() || rnd.next(100) < 60) {
            n = rnd.next(1, 18);
        }

        int mode = rnd.next(0, 5);
        vector<int> frequencies = makeFrequencies(n, mode);

        println(n);
        println(frequencies);
    }

    println(0);
    return 0;
}
