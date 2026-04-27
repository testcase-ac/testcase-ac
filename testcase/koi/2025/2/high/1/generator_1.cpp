#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) n = 2;
    else if (sizeMode == 1) n = rnd.next(3, 8);
    else if (sizeMode == 2) n = rnd.next(9, 20);
    else if (sizeMode == 3) n = rnd.next(21, 60);
    else n = rnd.next(61, 120);

    vector<int> middle;
    for (int v = 2; v <= n - 1; ++v) {
        middle.push_back(v);
    }

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // Already in vertex order.
    } else if (mode == 1) {
        reverse(middle.begin(), middle.end());
    } else if (mode == 2) {
        shuffle(middle.begin(), middle.end());
    } else if (mode == 3) {
        vector<int> odd, even;
        for (int v : middle) {
            if (v % 2) odd.push_back(v);
            else even.push_back(v);
        }
        shuffle(odd.begin(), odd.end());
        shuffle(even.begin(), even.end());
        middle.clear();
        middle.insert(middle.end(), odd.begin(), odd.end());
        middle.insert(middle.end(), even.begin(), even.end());
    } else {
        sort(middle.begin(), middle.end(), [](int a, int b) {
            return abs(a - 1) > abs(b - 1);
        });
    }

    vector<int> p;
    p.push_back(1);
    p.insert(p.end(), middle.begin(), middle.end());
    p.push_back(n);

    vector<long long> diff(n + 2, 0), c(n, 0);
    for (int i = 0; i + 1 < (int)p.size(); ++i) {
        int l = min(p[i], p[i + 1]);
        int r = max(p[i], p[i + 1]);
        ++diff[l];
        --diff[r];
    }
    long long cur = 0;
    for (int i = 1; i <= n - 1; ++i) {
        cur += diff[i];
        c[i] = cur;
    }

    println(n);
    for (int i = 1; i <= n - 1; ++i) {
        if (i > 1) cout << ' ';
        cout << c[i];
    }
    cout << '\n';
    return 0;
}
