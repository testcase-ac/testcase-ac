#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

struct Case {
    int j;
    int p;
    int H;
    int L;
};

int nearValue(int base, int spread) {
    return max(1, min(500, base + rnd.next(-spread, spread)));
}

Case randomCase(int mode) {
    if (mode == 0) {
        int base = rnd.next(1, 8);
        return {nearValue(base, 2), nearValue(base, 2), nearValue(base, 2), nearValue(base, 2)};
    }

    if (mode == 1) {
        int base = rnd.next(420, 500);
        return {nearValue(base, 30), nearValue(base, 30), nearValue(base, 30), nearValue(base, 30)};
    }

    if (mode == 2) {
        return {rnd.next(1, 500), rnd.next(1, 500), rnd.next(1, 20), rnd.next(300, 500)};
    }

    if (mode == 3) {
        return {rnd.next(1, 500), rnd.next(1, 500), rnd.next(300, 500), rnd.next(1, 25)};
    }

    if (mode == 4) {
        return {rnd.next(1, 25), rnd.next(350, 500), rnd.next(1, 500), rnd.next(1, 500)};
    }

    if (mode == 5) {
        return {rnd.next(350, 500), rnd.next(1, 25), rnd.next(1, 500), rnd.next(1, 500)};
    }

    if (mode == 6) {
        vector<int> edge = {1, 2, 499, 500};
        return {rnd.any(edge), rnd.any(edge), rnd.any(edge), rnd.any(edge)};
    }

    int H = rnd.next(1, 500);
    int L = rnd.next(1, 500);
    int j = nearValue(H, rnd.next(0, 80));
    int p = nearValue(L, rnd.next(0, 80));
    return {j, p, H, L};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    vector<Case> cases;
    cases.reserve(t);

    for (int mode = 0; mode < 8 && (int)cases.size() < t; ++mode) {
        cases.push_back(randomCase(mode));
    }
    while ((int)cases.size() < t) {
        cases.push_back(randomCase(rnd.next(0, 7)));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& tc : cases) {
        println(tc.j, tc.p, tc.H, tc.L);
    }

    return 0;
}
