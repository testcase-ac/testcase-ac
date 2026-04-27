#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = (mode == 0 ? 1 : rnd.next(2, 40));
    vector<int> x;

    if (mode == 0) {
        x.push_back(rnd.next(1, 30));
    } else if (mode == 1) {
        int cur = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            x.push_back(cur);
            cur += 1;
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            x.push_back(cur);
            cur += rnd.next(2, 6);
        }
    } else if (mode == 3) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            x.push_back(cur);
            cur += rnd.next(1, 4);
        }
    } else {
        set<int> values;
        while ((int)values.size() < n) {
            values.insert(rnd.next(1, 250000));
        }
        x.assign(values.begin(), values.end());
    }

    println((int)x.size());
    println(x);
    return 0;
}
