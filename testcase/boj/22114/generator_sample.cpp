#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(50000, 100000);
    } else if (mode >= 4) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(2, 18);
    }

    int k = (mode == 0) ? rnd.next(1, 100) : rnd.next(1, 99);
    vector<int> gaps(n - 1);

    if (mode == 0) {
        for (int& gap : gaps) {
            gap = rnd.next(1, k);
        }
    } else if (mode == 1) {
        for (int& gap : gaps) {
            gap = rnd.next(k + 1, 100);
        }
    } else if (mode == 2) {
        int bad = rnd.next(0, n - 2);
        for (int i = 0; i < n - 1; ++i) {
            if (i == bad) {
                gaps[i] = rnd.next(k + 1, 100);
            } else {
                gaps[i] = rnd.next(1, k);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n - 1; ++i) {
            bool bad = (i % 2 == rnd.next(0, 1));
            gaps[i] = bad ? rnd.next(k + 1, 100) : rnd.next(1, k);
        }
    } else {
        int i = 0;
        while (i < n - 1) {
            int goodRun = rnd.next(0, mode == 6 ? 200 : 8);
            for (int j = 0; j < goodRun && i < n - 1; ++j, ++i) {
                if (rnd.next(0, 3) == 0) {
                    gaps[i] = k;
                } else {
                    gaps[i] = rnd.next(1, k);
                }
            }

            int badRun = rnd.next(1, mode == 6 ? 5 : 3);
            for (int j = 0; j < badRun && i < n - 1; ++j, ++i) {
                if (k == 100) {
                    gaps[i] = 100;
                } else if (rnd.next(0, 2) == 0) {
                    gaps[i] = k + 1;
                } else {
                    gaps[i] = rnd.next(k + 1, 100);
                }
            }
        }
    }

    println(n, k);
    println(gaps);
    return 0;
}
