#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    vector<int> values;

    int mode = rnd.next(0, 5);
    int targetT = rnd.next(8, 80);

    if (mode == 0) {
        targetT = rnd.next(8, 30);
        for (int i = 0; i < targetT; ++i) {
            values.push_back(rnd.next(1, 80));
        }
    } else if (mode == 1) {
        targetT = rnd.next(10, 45);
        for (int i = 0; i < targetT; ++i) {
            int r = rnd.next(1, 1000);
            int square = r * r;
            int delta = rnd.next(-3, 3);
            int n = square + delta;
            values.push_back(max(1, min(maxN, n)));
        }
    } else if (mode == 2) {
        targetT = rnd.next(15, 60);
        int lo = rnd.next(1, 900000);
        int hi = min(maxN, lo + rnd.next(20, 5000));
        for (int i = 0; i < targetT; ++i) {
            values.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        targetT = rnd.next(20, 70);
        int limit = rnd.next(200, 5000);
        vector<bool> winning(limit + 1, false);
        for (int n = 1; n <= limit; ++n) {
            for (int r = 1; r * r <= n; ++r) {
                if (!winning[n - r * r]) {
                    winning[n] = true;
                    break;
                }
            }
        }

        vector<int> losing;
        vector<int> win;
        for (int n = 1; n <= limit; ++n) {
            (winning[n] ? win : losing).push_back(n);
        }

        for (int i = 0; i < targetT; ++i) {
            bool wantLosing = !losing.empty() && rnd.next(0, 99) < 45;
            values.push_back(wantLosing ? rnd.any(losing) : rnd.any(win));
        }
    } else if (mode == 4) {
        targetT = rnd.next(20, 80);
        for (int i = 0; i < targetT; ++i) {
            if (rnd.next(0, 99) < 70) {
                values.push_back(rnd.next(900000, maxN));
            } else {
                values.push_back(rnd.next(1, maxN));
            }
        }
    } else {
        targetT = rnd.next(12, 50);
        int base = rnd.next(1, 999900);
        for (int i = 0; i < targetT; ++i) {
            int step = rnd.next(0, 25);
            values.push_back(min(maxN, base + i * step));
        }
    }

    if (rnd.next(0, 99) < 70) values.push_back(1);
    if (rnd.next(0, 99) < 50) values.push_back(2);
    if (rnd.next(0, 99) < 50) values.push_back(3);
    if (rnd.next(0, 99) < 50) values.push_back(maxN);

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int n : values) {
        println(n);
    }

    return 0;
}
