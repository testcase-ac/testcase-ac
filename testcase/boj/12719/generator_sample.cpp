#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int a;
    int b;
    int p;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                          43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
                          101, 127, 149, 173, 199, 251, 331, 499, 997};

    int c = rnd.next(6, 10);
    vector<Case> cases;

    for (int i = 0; i < c; ++i) {
        int mode = rnd.next(0, 5);
        int a;
        int b;
        int p;

        if (mode == 0) {
            a = rnd.next(1, 40);
            b = min(1000, a + rnd.next(1, 12));
            p = rnd.next(2, b);
        } else if (mode == 1) {
            int prime = rnd.any(primes);
            int loMul = rnd.next(1, max(1, 1000 / prime));
            int left = prime * loMul;
            int maxSteps = min(4, max(1, (1000 - left) / prime));
            int right = min(1000, left + prime * rnd.next(1, maxSteps));
            a = max(1, left - rnd.next(0, min(3, left - 1)));
            b = min(1000, right + rnd.next(0, 3));
            p = prime;
        } else if (mode == 2) {
            b = rnd.next(2, 1000);
            a = rnd.next(max(1, b - 20), b);
            p = b;
        } else if (mode == 3) {
            a = rnd.next(850, 1000);
            b = rnd.next(a, 1000);
            p = rnd.next(2, b);
        } else if (mode == 4) {
            a = rnd.next(1, 950);
            b = rnd.next(a + 20, min(1000, a + 80));
            int span = b - a + 1;
            p = rnd.next(max(2, span / 2), b);
        } else {
            int width = rnd.next(0, 4);
            a = rnd.next(1, 1000 - width);
            b = a + width;
            p = rnd.next(2, b);
        }

        cases.push_back({a, b, p});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& tc : cases) {
        println(tc.a, tc.b, tc.p);
    }

    return 0;
}
