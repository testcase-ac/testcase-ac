#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAX_TIME = 2000000;

void addValue(set<int>& values, int x) {
    if (0 <= x && x <= MAX_TIME) {
        values.insert(x);
    }
}

void fillRandom(set<int>& values, int target) {
    while ((int)values.size() < target) {
        addValue(values, rnd.next(0, MAX_TIME));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    set<int> values;

    if (mode == 0) {
        int step = rnd.next(2, 5000);
        int start = rnd.next(0, MAX_TIME - step * (n - 1));
        for (int i = 0; i < n; ++i) {
            addValue(values, start + step * i);
        }
    } else if (mode == 1) {
        int k = rnd.next(2, 200);
        int residue = rnd.next(0, k - 1);
        int maxC = (MAX_TIME - residue) / k;
        n = min(n, maxC + 1);
        vector<int> coeffs;
        for (int c = 0; c <= maxC; ++c) {
            coeffs.push_back(c);
        }
        shuffle(coeffs.begin(), coeffs.end());
        for (int i = 0; i < n; ++i) {
            addValue(values, coeffs[i] * k + residue);
        }
    } else if (mode == 2) {
        int start = rnd.next(0, MAX_TIME - n + 1);
        for (int i = 0; i < n; ++i) {
            addValue(values, start + i);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 24);
        int k = rnd.next(2, 80);
        int residue = rnd.next(0, k - 1);
        int startC = rnd.next(0, max(0, (MAX_TIME - residue) / k - n));
        for (int i = 0; i < n / 2; ++i) {
            addValue(values, (startC + i) * k + residue);
        }
        fillRandom(values, n);
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        addValue(values, 0);
        addValue(values, MAX_TIME);
        while ((int)values.size() < n) {
            if (rnd.next(0, 1) == 0) {
                addValue(values, rnd.next(0, 2000));
            } else {
                addValue(values, rnd.next(MAX_TIME - 2000, MAX_TIME));
            }
        }
    } else {
        fillRandom(values, n);
    }

    vector<int> times(values.begin(), values.end());
    println((int)times.size());
    println(times);

    return 0;
}
