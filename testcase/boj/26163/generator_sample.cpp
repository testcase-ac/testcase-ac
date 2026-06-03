#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> b;

    if (mode == 0) {
        int start = rnd.next(1, 26);
        for (int i = 0; i < 5; ++i) {
            b.push_back(start + i);
        }
    } else if (mode == 1) {
        int last = rnd.next(5, 30);
        for (int i = 4; i >= 0; --i) {
            b.push_back(last - i);
        }
    } else if (mode == 2) {
        b = {1, 2, 3, 4, 30};
        b[rnd.next(1, 3)] = rnd.next(5, 29);
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        for (int x = 1; (int)b.size() < 5 && x <= 30; ++x) {
            if (!binary_search(b.begin(), b.end(), x)) {
                b.push_back(x);
                sort(b.begin(), b.end());
            }
        }
    } else if (mode == 3) {
        int cap = rnd.next(5, 15);
        for (int i = 1; i <= cap; ++i) {
            b.push_back(i);
        }
        shuffle(b.begin(), b.end());
        b.resize(5);
        sort(b.begin(), b.end());
    } else if (mode == 4) {
        int base = rnd.next(1, 10);
        vector<int> gaps;
        int remaining = 30 - base;
        for (int i = 0; i < 4; ++i) {
            int maxGap = remaining - (3 - i);
            int gap = rnd.next(1, maxGap);
            gaps.push_back(gap);
            remaining -= gap;
        }
        b.push_back(base);
        for (int gap : gaps) {
            b.push_back(b.back() + gap);
        }
    } else {
        for (int i = 1; i <= 30; ++i) {
            b.push_back(i);
        }
        shuffle(b.begin(), b.end());
        b.resize(5);
        sort(b.begin(), b.end());
    }

    println(b);
    return 0;
}
