#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int caseCount = rnd.next(6, 12);

    for (int i = 0; i < caseCount; ++i) {
        int mode = rnd.next(0, 5);
        int n, d;

        if (mode == 0) {
            n = rnd.next(1, 8);
            d = 1;
        } else if (mode == 1) {
            n = rnd.next(1, 12);
            d = n;
        } else if (mode == 2) {
            n = rnd.next(2, 20);
            d = rnd.next(n + 1, 4 * n + 25);
        } else if (mode == 3) {
            n = rnd.next(20, 200);
            d = rnd.next(1, 999);
        } else if (mode == 4) {
            n = rnd.next(900000, 999999);
            d = rnd.next(1, 30);
        } else {
            n = rnd.next(1, 999999);
            d = rnd.next(900000, 999999);
        }

        cases.push_back({n, d});
    }

    for (auto [n, d] : cases) {
        println(n, d);
    }
    println(0, 0);

    return 0;
}
