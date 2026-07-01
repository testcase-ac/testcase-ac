#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int n;
    int m;
    int d;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(5, 12);
    vector<Case> cases;

    for (int i = 0; i < caseCount; ++i) {
        int mode = rnd.next(0, 5);
        int n, m, d;

        if (mode == 0) {
            n = rnd.next(1, 20);
            m = n + rnd.next(1, 4);
            d = rnd.next(2, 10);
        } else if (mode == 1) {
            n = rnd.next(1, 30);
            m = n + rnd.next(5, 12);
            d = rnd.next(2, min(10, m - n + 1));
        } else if (mode == 2) {
            n = rnd.next(900, 999);
            m = rnd.next(n + 1, 1000);
            d = rnd.next(2, 10);
        } else if (mode == 3) {
            int len = rnd.next(2, 25);
            n = rnd.next(1, 1001 - len);
            m = n + len - 1;
            d = rnd.next(2, 10);
        } else if (mode == 4) {
            int len = rnd.next(8, 20);
            n = rnd.next(1, 1001 - len);
            m = n + len - 1;
            d = rnd.any(vector<int>{2, 3, 10});
        } else {
            n = rnd.next(1, 980);
            m = rnd.next(n + 1, min(1000, n + 30));
            d = rnd.next(2, 10);
        }

        cases.push_back({n, m, d});
    }

    shuffle(cases.begin(), cases.end());
    for (const Case& tc : cases) {
        println(tc.n, tc.m, tc.d);
    }
    println(0, 0, 0);

    return 0;
}
