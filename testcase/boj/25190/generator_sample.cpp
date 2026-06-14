#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> hikers;

    if (mode == 0) {
        int n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            int p = rnd.any(vector<int>{1, 2, 99, 100});
            int c = rnd.any(vector<int>{1, 2, p, 3000});
            hikers.push_back({p, max(1, min(3000, c))});
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 12);
        int p = rnd.next(1, 12);
        int c = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) hikers.push_back({p, c});
    } else if (mode == 2) {
        int n = rnd.next(6, 18);
        int pollution = 0;
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 20);
            int slack = rnd.next(-2, 8);
            int c = max(1, min(3000, pollution + slack));
            hikers.push_back({p, c});
            pollution += rnd.next(0, p);
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 24);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(70, 100);
            int c = rnd.next(1, 220);
            hikers.push_back({p, c});
        }
    } else if (mode == 4) {
        int n = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 100);
            int c;
            if (rnd.next(0, 2) == 0) c = rnd.next(1, 40);
            else if (rnd.next(0, 1) == 0) c = rnd.next(2950, 3000);
            else c = rnd.next(500, 1600);
            hikers.push_back({p, c});
        }
    } else {
        int n = rnd.next(12, 35);
        int base = rnd.next(20, 140);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 15);
            int c = max(1, min(3000, base + i * rnd.next(1, 8) + rnd.next(-10, 10)));
            hikers.push_back({p, c});
        }
    }

    shuffle(hikers.begin(), hikers.end());

    println(static_cast<int>(hikers.size()));
    for (auto [p, c] : hikers) println(p, c);

    return 0;
}
