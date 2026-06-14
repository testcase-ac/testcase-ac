#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(6, 24);
    vector<pair<int, int>> cases;

    cases.push_back({1, rnd.next(0, 1)});
    cases.push_back({17, rnd.next(0, 17)});
    cases.push_back({17, 17});

    while ((int)cases.size() < p) {
        int mode = rnd.next(0, 5);
        int n;
        int k;

        if (mode == 0) {
            n = rnd.next(1, 4);
            k = rnd.next(0, n);
        } else if (mode == 1) {
            n = rnd.next(10, 17);
            k = 0;
        } else if (mode == 2) {
            n = rnd.next(10, 17);
            k = n;
        } else if (mode == 3) {
            n = rnd.next(8, 17);
            k = rnd.next(max(0, n - 3), n);
        } else if (mode == 4) {
            n = rnd.next(8, 17);
            k = rnd.next(0, min(n, 3));
        } else {
            n = rnd.next(1, 17);
            k = rnd.next(0, n);
        }

        cases.push_back({n, k});
    }

    println(p);
    int dataSetNumber = rnd.next(0, 100);
    for (const auto& [n, k] : cases) {
        if (rnd.next(0, 4) == 0) {
            dataSetNumber = rnd.next(0, 1000000000);
        } else {
            dataSetNumber += rnd.next(1, 7);
        }
        println(dataSetNumber, n, k);
    }

    return 0;
}
