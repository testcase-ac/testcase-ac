#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int a;
    int b;
    vector<pair<int, int>> semesters(10);

    if (mode == 0) {
        n = rnd.next(1, 3);
        a = rnd.next(1, 20);
        b = rnd.next(a, min(35, a + rnd.next(0, 15)));
        for (auto& semester : semesters) {
            semester = {rnd.next(1, 2), rnd.next(1, 2)};
        }
    } else if (mode == 1) {
        n = rnd.next(6, 7);
        a = rnd.next(55, 70);
        b = rnd.next(max(a, 118), 132);
        for (auto& semester : semesters) {
            int x = rnd.next(1, 6);
            int y = rnd.next(1, 6);
            semester = {x, y};
        }
    } else if (mode == 2) {
        n = rnd.next(3, 6);
        a = rnd.next(40, 65);
        b = rnd.next(max(a, 105), 129);
        int rich = rnd.next(0, max(0, 8 - n - 1));
        for (int i = 0; i < 10; ++i) {
            if (i == rich) {
                semesters[i] = {rnd.next(5, 6), rnd.next(1, 6)};
            } else {
                semesters[i] = {rnd.next(1, 4), rnd.next(1, 6)};
            }
        }
    } else if (mode == 3) {
        n = rnd.next(1, 7);
        a = rnd.next(60, 150);
        b = rnd.next(max(a, 125), 150);
        for (auto& semester : semesters) {
            int x = rnd.next(1, 6);
            int y = rnd.next(max(1, 6 - x), 6);
            semester = {x, y};
        }
    } else if (mode == 4) {
        n = rnd.next(4, 7);
        a = rnd.next(1, 65);
        b = rnd.next(max(a, 115), 150);
        for (auto& semester : semesters) {
            semester = {rnd.next(1, 2), rnd.next(4, 6)};
        }
    } else {
        n = rnd.next(1, 7);
        a = rnd.next(1, 150);
        b = rnd.next(a, 150);
        for (auto& semester : semesters) {
            int x = rnd.next(1, 6);
            int y = rnd.next(1, 6);
            if (rnd.next(0, 3) == 0) {
                x = rnd.any(vector<int>{1, 6});
            }
            if (rnd.next(0, 3) == 0) {
                y = rnd.any(vector<int>{1, 6});
            }
            semester = {x, y};
        }
    }

    println(n, a, b);
    for (auto [x, y] : semesters) {
        println(x, y);
    }

    return 0;
}
