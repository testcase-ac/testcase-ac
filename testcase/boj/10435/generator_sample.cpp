#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int pickN(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(21, 120);
    if (mode == 2) return rnd.next(121, 700);
    if (mode == 3) return rnd.next(701, 2000);

    static const int edgeValues[] = {1, 2, 3, 4, 5, 57, 80, 500, 1000, 1999, 2000};
    return edgeValues[rnd.next(0, int(sizeof(edgeValues) / sizeof(edgeValues[0])) - 1)];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int p;
    if (mode == 5) {
        p = rnd.next(50, 100);
    } else {
        p = rnd.next(1, 25);
    }

    vector<pair<int, int>> cases;
    set<int> usedK;
    for (int i = 0; i < p; ++i) {
        int k;
        if (rnd.next(0, 3) == 0) {
            k = i + 1;
        } else {
            do {
                k = rnd.next(1, 1000000000);
            } while (usedK.count(k));
        }
        usedK.insert(k);

        int n;
        if (i == 0 && rnd.next(0, 1) == 0) {
            n = 1;
        } else if (i == p - 1 && rnd.next(0, 1) == 0) {
            n = 2000;
        } else {
            n = pickN(rnd.next(0, 4));
        }
        cases.push_back({k, n});
    }

    if (rnd.next(0, 1) == 0) {
        shuffle(cases.begin(), cases.end());
    }

    println(p);
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
