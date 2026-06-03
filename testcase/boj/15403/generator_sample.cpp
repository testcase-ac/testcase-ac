#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> lisStarts(const vector<int>& p) {
    int n = int(p.size());
    vector<int> a(n, 1);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (p[i] < p[j]) {
                a[i] = max(a[i], a[j] + 1);
            }
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode <= 3) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(8, 25);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 0) {
        shuffle(p.begin(), p.end());
    } else if (mode == 1) {
        // Mostly increasing permutations create large A_i values.
        int swaps = rnd.next(0, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            swap(p[rnd.next(n)], p[rnd.next(n)]);
        }
    } else if (mode == 2) {
        // Mostly decreasing permutations create many A_i = 1 positions.
        reverse(p.begin(), p.end());
        int swaps = rnd.next(0, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            swap(p[rnd.next(n)], p[rnd.next(n)]);
        }
    } else if (mode == 3) {
        vector<int> low;
        vector<int> high;
        for (int x = 1; x <= n; ++x) {
            if (x <= n / 2) {
                low.push_back(x);
            } else {
                high.push_back(x);
            }
        }
        shuffle(low.begin(), low.end());
        shuffle(high.begin(), high.end());
        p.clear();
        while (!low.empty() || !high.empty()) {
            bool takeHigh = low.empty() || (!high.empty() && rnd.next(2) == 0);
            if (takeHigh) {
                p.push_back(high.back());
                high.pop_back();
            } else {
                p.push_back(low.back());
                low.pop_back();
            }
        }
    } else if (mode == 4) {
        int blockSize = rnd.next(2, 5);
        p.clear();
        for (int start = 1; start <= n; start += blockSize) {
            int end = min(n, start + blockSize - 1);
            vector<int> block;
            for (int x = end; x >= start; --x) {
                block.push_back(x);
            }
            p.insert(p.end(), block.begin(), block.end());
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    vector<int> a = lisStarts(p);
    println(n);
    println(a);

    return 0;
}
