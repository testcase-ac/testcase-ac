#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 30);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 5);
        int r = 1;
        int c = 1;

        if (mode == 0) {
            r = rnd.next(1, 3);
            c = rnd.next(1, 3);
        } else if (mode == 1) {
            r = 1;
            c = rnd.next(1, 10);
        } else if (mode == 2) {
            r = rnd.next(1, 10);
            c = 1;
        } else if (mode == 3) {
            r = rnd.next(2, 10);
            c = rnd.next(2, 10);
        } else if (mode == 4) {
            r = rnd.next(7, 10);
            c = rnd.next(7, 10);
        } else {
            r = rnd.next(2, 10);
            c = rnd.next(2, 10);
            if (rnd.next(0, 1) == 1) {
                swap(r, c);
            }
        }

        cases.push_back({r, c});
    }

    println((int)cases.size());
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
