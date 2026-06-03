#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<pair<int, int>> tires;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int score = rnd.next(1, 20);
            int people = rnd.next(1, 8);
            tires.push_back({score, people});
        }
    } else if (mode == 1) {
        n = rnd.next(8, 18);
        m = rnd.next(1, 35);
        for (int i = 0; i < n; ++i) {
            int score = rnd.next(1, 80);
            int people = rnd.next(1, 12);
            tires.push_back({score, people});
        }
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        int base = rnd.next(1, 100000);
        m = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            int score = rnd.next(max(1, base - 1000), min(100000, base + 1000));
            int people = rnd.next(1, 100000);
            tires.push_back({score, people});
        }
    } else if (mode == 3) {
        n = rnd.next(5, 16);
        int cap = rnd.next(1, 100000);
        m = cap;
        for (int i = 0; i < n; ++i) {
            int score = rnd.next(1, 100000);
            int near = rnd.next(max(1, cap - 5), min(100000, cap + 5));
            tires.push_back({score, near});
        }
    } else if (mode == 4) {
        n = rnd.next(15, 35);
        m = rnd.next(40, 180);
        for (int i = 0; i < n; ++i) {
            int score = (rnd.next(0, 3) == 0) ? rnd.next(50000, 100000) : rnd.next(1, 50);
            int people = rnd.next(1, 15);
            tires.push_back({score, people});
        }
    } else {
        n = rnd.next(40, 100);
        m = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            int score = rnd.next(1, 100000);
            int people = (rnd.next(0, 1) == 0) ? rnd.next(1, 50) : rnd.next(90000, 100000);
            tires.push_back({score, people});
        }
    }

    shuffle(tires.begin(), tires.end());

    println(n, m);
    for (auto tire : tires) {
        println(tire.first, tire.second);
    }

    return 0;
}
