#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<long long> a;

    if (mode == 0) {
        a.push_back(rnd.next(0, 1) == 0 ? 0LL : rnd.next(1, 1000000000));
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 50));
        }
    } else if (mode == 2) {
        int prefix = rnd.next(1, 12);
        for (int x = 0; x < prefix; ++x) {
            a.push_back(x);
        }

        int extra = rnd.next(0, 12);
        for (int i = 0; i < extra; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.next(0, prefix - 1));
            } else {
                a.push_back(rnd.next(prefix + 1, prefix + 20));
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 25);
        int prefix = rnd.next(1, min(n, 10));
        for (int x = 0; x < prefix; ++x) {
            a.push_back(x);
        }
        while ((int)a.size() < n) {
            a.push_back(rnd.next(0, 1000000000));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 20);
        int gap = rnd.next(1, min(n, 12));
        for (int x = 0; x <= gap; ++x) {
            if (x != gap) {
                a.push_back(x);
            }
        }
        while ((int)a.size() < n) {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                a.push_back(rnd.next(0, max(0, gap - 1)));
            } else if (choice == 1) {
                a.push_back(rnd.next(gap + 1, gap + 30));
            } else {
                a.push_back(1000000000LL);
            }
        }
    } else {
        int n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(1000000000LL);
            } else {
                a.push_back(rnd.next(0, 8));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
