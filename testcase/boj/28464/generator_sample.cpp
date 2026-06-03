#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int value = rnd.next(1, 10000);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int lo = rnd.next(1, 9990);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 10)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back((i % 2 == 0) ? rnd.next(1, 6) : rnd.next(9995, 10000));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 21);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) {
                a.push_back(rnd.next(1, 30));
            } else if (bucket == 1) {
                a.push_back(rnd.next(300, 700));
            } else {
                a.push_back(rnd.next(9000, 10000));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 24);
        int start = rnd.next(1, 10000 - n + 1);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i);
        }
        if (rnd.next(0, 1) == 0) {
            reverse(a.begin(), a.end());
        }
    } else {
        n = rnd.next(1, 30);
        int distinct = rnd.next(1, min(n, 5));
        vector<int> choices;
        for (int i = 0; i < distinct; ++i) {
            choices.push_back(rnd.next(1, 10000));
        }
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(choices));
        }
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
