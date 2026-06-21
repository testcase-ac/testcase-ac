#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        m = rnd.next(8, 20);
    } else if (mode == 2) {
        n = rnd.next(10, 30);
        m = rnd.next(15, 35);
    } else if (mode == 3) {
        n = rnd.next(20, 80);
        m = rnd.next(20, 60);
    } else if (mode == 4) {
        n = rnd.next(2, 15);
        m = rnd.next(10, 30);
    } else {
        n = rnd.next(80, 200);
        m = rnd.next(30, 80);
    }

    vector<pair<string, vector<int>>> events;
    events.reserve(m);

    int occupiedUntil = 0;
    for (int i = 0; i < m; ++i) {
        bool chooseArrival;
        if (mode == 4) {
            chooseArrival = i % 3 != 2;
        } else if (i == 0) {
            chooseArrival = rnd.next(0, 1) == 0;
        } else {
            chooseArrival = rnd.next(0, 99) < 60;
        }

        if (chooseArrival) {
            int p;
            if (mode == 0) {
                p = rnd.next(1, n);
            } else if (mode == 1) {
                p = rnd.next(1, min(n, 5));
            } else if (mode == 2) {
                p = rnd.next(max(1, n / 3), n);
            } else if (mode == 3) {
                p = rnd.next(1, max(1, n / 2));
            } else if (mode == 4) {
                p = rnd.next(max(1, n - 3), n);
            } else {
                p = rnd.next(1, n);
            }
            events.push_back({"A", {p}});
            occupiedUntil = min(n, occupiedUntil + p);
        } else {
            int a;
            int b;
            if (mode == 3 && rnd.next(0, 99) < 50) {
                int width = rnd.next(1, min(n, 8));
                a = rnd.next(1, n - width + 1);
                b = a + width - 1;
            } else if (mode == 4) {
                a = rnd.next(1, n);
                b = rnd.next(a, n);
            } else if (occupiedUntil > 0 && rnd.next(0, 99) < 70) {
                a = rnd.next(1, occupiedUntil);
                b = rnd.next(a, occupiedUntil);
            } else {
                a = rnd.next(1, n);
                b = rnd.next(a, n);
            }
            events.push_back({"L", {a, b}});
            if (b == occupiedUntil) {
                occupiedUntil = a - 1;
            }
        }
    }

    println(n, m);
    for (const auto& event : events) {
        if (event.first == "A") {
            println(event.first, event.second[0]);
        } else {
            println(event.first, event.second[0], event.second[1]);
        }
    }

    return 0;
}
