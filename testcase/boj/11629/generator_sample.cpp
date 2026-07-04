#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int n;
    int x1;
    int y1;
    int x2;
    int y2;
};

static Case makeCase(int n, int mode) {
    Case c{n, 1, 1, 1, 2};

    if (mode == 0) {
        c.x1 = rnd.next(1, n);
        c.y1 = rnd.next(1, n);
        c.x2 = rnd.next(1, n);
        c.y2 = rnd.next(1, n);
    } else if (mode == 1) {
        c.x1 = rnd.any(vector<int>{1, n});
        c.y1 = rnd.any(vector<int>{1, n});
        c.x2 = rnd.any(vector<int>{1, n});
        c.y2 = rnd.any(vector<int>{1, n});
    } else if (mode == 2) {
        c.x1 = rnd.next(1, n);
        c.y1 = rnd.next(1, n);
        c.x2 = c.x1;
        c.y2 = rnd.next(1, n);
    } else if (mode == 3) {
        c.x1 = rnd.next(1, n);
        c.y1 = rnd.next(1, n);
        c.x2 = rnd.next(1, n);
        c.y2 = c.y1;
    } else {
        int len = rnd.next(1, n - 1);
        c.x1 = rnd.next(1, n - len);
        c.y1 = rnd.next(1, n - len);
        c.x2 = c.x1 + len;
        c.y2 = c.y1 + len;
        if (rnd.next(2)) swap(c.x1, c.x2);
        if (rnd.next(2)) swap(c.y1, c.y2);
    }

    while (c.x1 == c.x2 && c.y1 == c.y2) {
        c.x2 = rnd.next(1, n);
        c.y2 = rnd.next(1, n);
    }

    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 16);
    vector<Case> cases;
    cases.reserve(t);

    vector<int> fixedN = {2, 3, 8, 5000};
    for (int n : fixedN) {
        if ((int)cases.size() < t) {
            cases.push_back(makeCase(n, rnd.next(0, 4)));
        }
    }

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 4);
        int n;
        if (rnd.next(100) < 75) {
            n = rnd.next(2, 30);
        } else {
            n = rnd.next(100, 5000);
        }
        cases.push_back(makeCase(n, mode));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& c : cases) {
        println(c.n);
        println(c.x1, c.y1, c.x2, c.y2);
    }

    return 0;
}
