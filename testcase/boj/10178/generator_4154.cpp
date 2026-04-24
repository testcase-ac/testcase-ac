#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand checking
    int T = rnd.next(1, 10);
    vector<pair<int,int>> cases;
    cases.reserve(T);

    for (int i = 0; i < T; i++) {
        // Choose a case type for diversity
        int type = rnd.next(0, 3);
        int c, v;
        if (type == 0) {
            // Fully random
            c = rnd.next(1, 1000);
            v = rnd.next(1, 1000);
        } else if (type == 1) {
            // c < v case
            c = rnd.next(1, 50);
            int maxV = min(1000, c + rnd.next(1, 50));
            v = rnd.next(c + 1, maxV);
        } else if (type == 2) {
            // c == v case
            int k = rnd.next(1, 1000);
            c = k;
            v = k;
        } else {
            // v divides c case
            v = rnd.next(1, 50);
            int maxK = 1000 / v;
            int k = rnd.next(1, maxK);
            c = k * v;
        }
        cases.emplace_back(c, v);
    }

    // Shuffle to avoid patterned order
    shuffle(cases.begin(), cases.end());

    // Output
    println(T);
    for (auto &p : cases) {
        println(p.first, p.second);
    }

    return 0;
}
