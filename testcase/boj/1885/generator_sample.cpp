#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = 1;
    vector<int> s;

    if (mode == 0) {
        k = rnd.next(1, 6);
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(1, k));
        }
    } else if (mode == 1) {
        k = rnd.next(2, 12);
        int n = rnd.next(1, 30);
        int missing = rnd.next(1, k);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, k - 1);
            if (x >= missing) ++x;
            s.push_back(x);
        }
    } else if (mode == 2) {
        k = rnd.next(1, 10);
        int blocks = rnd.next(1, 6);
        for (int b = 0; b < blocks; ++b) {
            for (int x = 1; x <= k; ++x) {
                s.push_back(x);
            }
        }
        int tail = rnd.next(0, k - 1);
        for (int x = 1; x <= tail; ++x) {
            s.push_back(x);
        }
    } else if (mode == 3) {
        k = rnd.next(2, 14);
        int blocks = rnd.next(1, 5);
        vector<int> values;
        for (int x = 1; x <= k; ++x) {
            values.push_back(x);
        }
        for (int b = 0; b < blocks; ++b) {
            shuffle(values.begin(), values.end());
            for (int x : values) {
                s.push_back(x);
                if (rnd.next(0, 3) == 0) {
                    s.push_back(x);
                }
            }
        }
    } else if (mode == 4) {
        k = rnd.next(3, 18);
        int blocks = rnd.next(1, 4);
        for (int b = 0; b < blocks; ++b) {
            vector<int> values;
            for (int x = 1; x <= k; ++x) {
                values.push_back(x);
            }
            shuffle(values.begin(), values.end());
            int heldBack = values.back();
            values.pop_back();
            for (int x : values) {
                s.push_back(x);
            }
            s.push_back(rnd.next(1, k));
            s.push_back(heldBack);
        }
    } else {
        k = rnd.next(50, 200);
        int n = rnd.next(k, min(500, k * 3));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                s.push_back(rnd.next(1, min(k, 5)));
            } else {
                s.push_back(rnd.next(1, k));
            }
        }
    }

    println((int)s.size(), k);
    for (int x : s) {
        println(x);
    }

    return 0;
}
