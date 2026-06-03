#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 5) {
        t = rnd.next(40, 120);
    } else {
        t = rnd.next(1, 18);
    }

    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int a;
        int b;

        if (mode == 0) {
            a = rnd.next(1, 8);
            b = rnd.next(1, 8);
        } else if (mode == 1) {
            int sum = rnd.next(2, 30);
            a = rnd.next(1, sum - 1);
            b = sum - a;
        } else if (mode == 2) {
            a = rnd.next(1, 777);
            b = a;
        } else if (mode == 3) {
            if (rnd.next(0, 1) == 0) {
                a = rnd.next(1, 12);
                b = rnd.next(700, 777);
            } else {
                a = rnd.next(700, 777);
                b = rnd.next(1, 12);
            }
        } else if (mode == 4) {
            vector<pair<int, int>> boundary = {
                {1, 1},
                {1, 777},
                {777, 1},
                {777, 777},
                {776, 777},
                {777, 776},
            };
            pair<int, int> picked = rnd.any(boundary);
            a = picked.first;
            b = picked.second;
        } else {
            a = rnd.next(1, 777);
            b = rnd.next(1, 777);
        }

        cases.emplace_back(a, b);
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
