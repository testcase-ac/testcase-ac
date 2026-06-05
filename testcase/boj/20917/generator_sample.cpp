#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> makeDistinct(int n, int lo, int hi) {
    set<int> used;
    while ((int)used.size() < n) {
        used.insert(rnd.next(lo, hi));
    }
    return vector<int>(used.begin(), used.end());
}

vector<int> makeProgression(int n) {
    int start = rnd.next(1, 100);
    int step = rnd.next(1, 20);
    vector<int> x(n);
    for (int i = 0; i < n; ++i) x[i] = start + i * step;
    return x;
}

vector<int> makeClustered(int n) {
    set<int> used;
    int clusters = rnd.next(2, min(5, n));
    for (int c = 0; c < clusters && (int)used.size() < n; ++c) {
        int base = rnd.next(1 + c * 1000, 300 + c * 1000);
        int take = max(1, n / clusters + rnd.next(-1, 1));
        for (int i = 0; i < take && (int)used.size() < n; ++i) {
            used.insert(base + rnd.next(0, 30));
        }
    }
    while ((int)used.size() < n) used.insert(rnd.next(1, 5000));
    return vector<int>(used.begin(), used.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(2, 14);
        int s = rnd.next(2, n);
        vector<int> x;

        if (mode == 0) {
            n = 2;
            s = 2;
            x = {1, 1000000000};
        } else if (mode == 1) {
            n = rnd.next(2, 12);
            s = n;
            x = makeDistinct(n, 1, 200);
        } else if (mode == 2) {
            n = rnd.next(3, 14);
            s = rnd.next(2, n);
            x = makeProgression(n);
        } else if (mode == 3) {
            n = rnd.next(5, 14);
            s = rnd.next(2, n);
            x = makeClustered(n);
        } else if (mode == 4) {
            n = rnd.next(4, 14);
            s = rnd.next(2, n);
            x = makeDistinct(n, 1, 1000);
            x[0] = 1;
            x[1] = 1000000000;
            sort(x.begin(), x.end());
            x.erase(unique(x.begin(), x.end()), x.end());
            while ((int)x.size() < n) {
                int candidate = rnd.next(2, 999999999);
                if (!binary_search(x.begin(), x.end(), candidate)) {
                    x.push_back(candidate);
                    sort(x.begin(), x.end());
                }
            }
        } else {
            n = rnd.next(2, 14);
            s = rnd.next(2, n);
            x = makeDistinct(n, 1, 10000);
        }

        shuffle(x.begin(), x.end());
        println(n, s);
        println(x);
    }

    return 0;
}
