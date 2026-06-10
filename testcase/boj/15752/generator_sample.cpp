#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? 1 : rnd.next(2, 30);
    vector<int> x;

    if (mode == 0) {
        x.push_back(rnd.next(1, 1000));
    } else if (mode == 1) {
        int step = rnd.next(1, 3);
        int start = rnd.next(1, 1000 - (n - 1) * step);
        for (int i = 0; i < n; ++i) {
            x.push_back(start + i * step);
        }
    } else if (mode == 2) {
        int start = rnd.next(1, 700);
        int cur = start;
        for (int i = 0; i < n; ++i) {
            x.push_back(cur);
            cur += (i % 2 == 0 ? rnd.next(1, 3) : rnd.next(5, 20));
            if (cur > 1000) {
                n = i + 1;
                break;
            }
        }
    } else if (mode == 3) {
        int start = rnd.next(1, 850);
        int cur = start;
        for (int i = 0; i < n; ++i) {
            x.push_back(cur);
            cur += rnd.next(1, 12);
            if (i % 4 == 1) {
                cur += rnd.next(10, 40);
            }
            if (cur > 1000) {
                n = i + 1;
                break;
            }
        }
    } else {
        set<int> used;
        if (rnd.next(0, 1)) {
            used.insert(1);
            used.insert(1000);
        }
        while ((int)used.size() < n) {
            used.insert(rnd.next(1, 1000));
        }
        x.assign(used.begin(), used.end());
    }

    shuffle(x.begin(), x.end());

    println((int)x.size());
    println(x);

    return 0;
}
