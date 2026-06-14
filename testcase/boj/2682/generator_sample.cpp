#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    while ((int)cases.size() < t) {
        int mode = rnd.next(6);
        int n;
        int k;

        if (mode == 0) {
            n = rnd.next(1, 4);
            k = rnd.next(1, n);
        } else if (mode == 1) {
            n = rnd.next(16, 20);
            k = rnd.next(1, n);
        } else if (mode == 2) {
            n = rnd.next(2, 20);
            k = 1;
        } else if (mode == 3) {
            n = rnd.next(2, 20);
            k = n;
        } else if (mode == 4) {
            n = rnd.next(3, 20);
            k = rnd.next(max(1, n / 2), n);
        } else {
            n = rnd.next(3, 20);
            k = rnd.next(2, min(n, 6));
        }

        cases.emplace_back(n, k);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }

    return 0;
}
