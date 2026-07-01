#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int n;
    int a;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    vector<Case> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 7);
        int n = 2;
        int a = 0;
        int b = 0;

        if (mode == 0) {
            n = rnd.next(2, 6);
            a = rnd.next(0, 10);
            b = rnd.next(a, min(1000, a + rnd.next(0, 8)));
        } else if (mode == 1) {
            n = rnd.next(2, 30);
            a = b = rnd.next(0, 1000);
        } else if (mode == 2) {
            n = rnd.next(2, 1000);
            a = 0;
            b = rnd.next(0, 1000);
        } else if (mode == 3) {
            n = rnd.next(2, 1000);
            a = rnd.next(0, 1000);
            b = 1000;
        } else if (mode == 4) {
            n = rnd.next(900, 1000);
            a = rnd.next(0, 1000);
            b = rnd.next(a, 1000);
        } else if (mode == 5) {
            n = rnd.next(2, 20);
            int maxScore = min(1000, (n + 2) * (n - 1) / 2);
            a = rnd.next(0, maxScore);
            b = rnd.next(a, maxScore);
        } else if (mode == 6) {
            n = rnd.next(2, 1000);
            int center = rnd.next(0, 1000);
            int radius = rnd.next(0, 25);
            a = max(0, center - radius);
            b = min(1000, center + radius);
        } else {
            n = rnd.any(vector<int>{2, 3, 4, 999, 1000});
            a = rnd.any(vector<int>{0, 1, 2, 999, 1000});
            b = rnd.next(a, 1000);
        }

        cases.push_back({n, a, b});
    }

    println(static_cast<int>(cases.size()));
    for (const Case& tc : cases) {
        println(tc.n, tc.a, tc.b);
    }

    return 0;
}
