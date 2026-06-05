#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> makeCase(int mode) {
    int l = 0;
    int u = 0;

    if (mode == 0) {
        l = rnd.next(-30, 30);
        u = l + rnd.next(0, 40);
    } else if (mode == 1) {
        l = rnd.next(-999999, -1);
        u = rnd.next(0, 200);
    } else if (mode == 2) {
        l = rnd.next(1, 200);
        u = l + rnd.next(0, 300);
    } else if (mode == 3) {
        l = rnd.next(900000, 999999);
        u = rnd.next(l, 999999);
    } else if (mode == 4) {
        u = rnd.next(-999999, -900000);
        l = rnd.next(-999999, u);
    } else if (mode == 5) {
        l = rnd.next(-999999, 999999);
        u = l;
    } else {
        int center = rnd.next(-1000, 1000);
        int radius = rnd.next(0, 2500);
        l = max(-999999, center - radius);
        u = min(999999, center + radius);
    }

    if (l == -1 && u == -1) u = 0;
    return {l, u};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 12);
    vector<pair<int, int>> cases;
    cases.reserve(caseCount);

    for (int i = 0; i < caseCount; ++i) {
        cases.push_back(makeCase(rnd.next(0, 6)));
    }

    shuffle(cases.begin(), cases.end());
    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }
    println(-1, -1);

    return 0;
}
