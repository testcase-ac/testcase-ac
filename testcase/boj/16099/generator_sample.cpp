#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    long long lt;
    long long wt;
    long long le;
    long long we;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 24);
    vector<Case> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 4);
        Case cur{};

        if (mode == 0) {
            cur.lt = rnd.next(1, 30);
            cur.wt = rnd.next(1, 30);
            cur.le = rnd.next(1, 30);
            cur.we = rnd.next(1, 30);
        } else if (mode == 1) {
            long long a = rnd.next(1, 1000000000);
            long long b = rnd.next(1, 1000000000);
            cur.lt = a;
            cur.wt = b;
            cur.le = b;
            cur.we = a;
        } else if (mode == 2) {
            cur.lt = 1000000000LL;
            cur.wt = rnd.next(999999900, 1000000000);
            cur.le = rnd.next(999999900, 1000000000);
            cur.we = 1000000000LL;
        } else if (mode == 3) {
            long long base = rnd.next(1, 1000000);
            cur.lt = base;
            cur.wt = rnd.next(1, 1000000);
            cur.le = base + rnd.next(-1, 1);
            cur.we = rnd.next(1, 1000000);
            cur.le = max(1LL, min(1000000000LL, cur.le));
        } else {
            cur.lt = rnd.next(1, 1000000000);
            cur.wt = rnd.next(1, 1000000000);
            cur.le = rnd.next(1, 1000000000);
            cur.we = rnd.next(1, 1000000000);
        }

        cases.push_back(cur);
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const Case& cur : cases) {
        println(cur.lt, cur.wt, cur.le, cur.we);
    }

    return 0;
}
