#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int blocks = rnd.next(1, min(6, n));
        vector<int> cuts;
        for (int i = 1; i < n; ++i) {
            cuts.push_back(i);
        }
        shuffle(cuts.begin(), cuts.end());
        cuts.resize(blocks - 1);
        sort(cuts.begin(), cuts.end());
        cuts.push_back(n);

        int start = 0;
        for (int cut : cuts) {
            if (rnd.next(2)) {
                reverse(a.begin() + start, a.begin() + cut);
            }
            start = cut;
        }
    } else if (mode == 3) {
        vector<vector<int>> stacks(4);
        for (int x = 1; x <= n; ++x) {
            stacks[rnd.next(4)].push_back(x);
        }
        a.clear();
        int remaining = n;
        while (remaining > 0) {
            vector<int> order = {0, 1, 2, 3};
            shuffle(order.begin(), order.end());
            for (int id : order) {
                if (!stacks[id].empty() && rnd.next(3) > 0) {
                    a.push_back(stacks[id].front());
                    stacks[id].erase(stacks[id].begin());
                    --remaining;
                }
            }
        }
    } else if (mode == 4) {
        int len = min(n, rnd.next(5, min(10, max(5, n))));
        reverse(a.begin(), a.begin() + len);
        if (len < n) {
            shuffle(a.begin() + len, a.end());
        }
    } else {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int l = rnd.next(n);
            int r = rnd.next(n);
            if (l > r) {
                swap(l, r);
            }
            reverse(a.begin() + l, a.begin() + r + 1);
        }
    }

    println(n);
    println(a);
    return 0;
}
