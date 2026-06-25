#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(int n) {
    return max(2, min(100000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c;
    vector<int> values;

    if (mode == 0) {
        c = rnd.next(1, 12);
        for (int i = 0; i < c; ++i) {
            values.push_back(rnd.next(2, 30));
        }
    } else if (mode == 1) {
        c = rnd.next(4, 16);
        vector<int> anchors = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 25, 27, 32, 49, 64};
        for (int i = 0; i < c; ++i) {
            int base = rnd.any(anchors);
            values.push_back(clampN(base + rnd.next(-1, 2)));
        }
    } else if (mode == 2) {
        c = rnd.next(6, 20);
        vector<int> primeAreas = {
            97, 101, 499, 503, 997, 1009, 9973, 10007, 99991, 100000
        };
        for (int i = 0; i < c; ++i) {
            int base = rnd.any(primeAreas);
            values.push_back(clampN(base + rnd.next(-3, 3)));
        }
    } else if (mode == 3) {
        c = rnd.next(8, 24);
        for (int i = 0; i < c; ++i) {
            int a = rnd.next(2, 320);
            int b = rnd.next(2, 320);
            values.push_back(clampN(a * b + rnd.next(-2, 2)));
        }
    } else if (mode == 4) {
        c = rnd.next(10, 30);
        int start = rnd.next(2, 100000 - c + 1);
        for (int i = 0; i < c; ++i) {
            values.push_back(start + i);
        }
    } else {
        c = rnd.next(20, 50);
        for (int i = 0; i < c; ++i) {
            if (i % 5 == 0) {
                values.push_back(rnd.any(vector<int>{2, 3, 99991, 99999, 100000}));
            } else if (rnd.next(0, 2) == 0) {
                values.push_back(rnd.next(2, 200));
            } else {
                values.push_back(rnd.next(2, 100000));
            }
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int n : values) {
        println(n);
    }

    return 0;
}
