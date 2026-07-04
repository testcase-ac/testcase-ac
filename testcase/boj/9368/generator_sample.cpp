#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Henchman {
    int bribe;
    int probability;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        int c;
        int m;
        vector<Henchman> henchmen;

        if (mode == 0) {
            n = rnd.next(1, 5);
            c = rnd.next(1, 16);
            m = rnd.next(1, 20);
            for (int i = 0; i < n; ++i) {
                henchmen.push_back({rnd.next(0, 8), rnd.next(0, 100)});
            }
        } else if (mode == 1) {
            n = rnd.next(2, 8);
            c = rnd.next(1, min(16, n + 3));
            m = rnd.next(1, 50);
            for (int i = 0; i < n; ++i) {
                int bribe = rnd.next(0, 1) ? rnd.next(0, 5) : rnd.next(20, 60);
                int probability = rnd.any(vector<int>{0, 1, 50, 99, 100});
                henchmen.push_back({bribe, probability});
            }
        } else if (mode == 2) {
            n = rnd.next(5, 12);
            c = rnd.next(1, min(16, n));
            m = rnd.next(100, 1000);
            int base = rnd.next(10, 120);
            for (int i = 0; i < n; ++i) {
                henchmen.push_back({min(1000, base + rnd.next(0, 80)), rnd.next(5, 95)});
            }
        } else if (mode == 3) {
            n = 16;
            c = rnd.next(1, 16);
            m = rnd.next(1, 1000);
            for (int i = 0; i < n; ++i) {
                henchmen.push_back({rnd.next(0, 1000), rnd.next(0, 100)});
            }
        } else if (mode == 4) {
            n = rnd.next(3, 10);
            c = rnd.next(1, min(16, n + 2));
            m = rnd.next(1, 15);
            for (int i = 0; i < n; ++i) {
                henchmen.push_back({rnd.next(16, 1000), rnd.next(10, 90)});
            }
        } else {
            n = rnd.next(6, 14);
            c = rnd.next(1, min(16, n));
            m = rnd.next(50, 250);
            for (int i = 0; i < n; ++i) {
                int bribe = (i % 3 == 0) ? 0 : rnd.next(1, 100);
                int probability = (i % 4 == 0) ? 100 : rnd.next(0, 100);
                henchmen.push_back({bribe, probability});
            }
        }

        shuffle(henchmen.begin(), henchmen.end());
        println(n, c, m);
        for (const Henchman& henchman : henchmen) {
            println(henchman.bribe, henchman.probability);
        }
    }

    return 0;
}
