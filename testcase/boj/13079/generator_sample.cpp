#include "testlib.h"
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int m;
    int k;
};

static TestCase randomCase() {
    int k = rnd.next(1, 29);
    int m = rnd.next(0, k - 1);
    int n = rnd.next(1, 30);
    return {n, m, k};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<TestCase> cases;

    cases.push_back({1, 0, 1});
    cases.push_back({1, 0, 29});
    cases.push_back({30, 0, 1});
    cases.push_back({30, 28, 29});
    cases.push_back({30, 0, 2});
    cases.push_back({30, 1, 2});

    int extraCases = rnd.next(4, 24);
    for (int i = 0; i < extraCases; ++i) {
        int mode = rnd.next(0, 5);

        if (mode == 0) {
            int k = rnd.next(1, 29);
            cases.push_back({rnd.next(1, 5), rnd.next(0, k - 1), k});
        } else if (mode == 1) {
            int k = rnd.next(1, 29);
            cases.push_back({rnd.next(25, 30), rnd.next(0, k - 1), k});
        } else if (mode == 2) {
            int k = rnd.next(1, 29);
            cases.push_back({rnd.next(1, 30), 0, k});
        } else if (mode == 3) {
            int k = rnd.next(2, 29);
            cases.push_back({rnd.next(1, 30), k - 1, k});
        } else if (mode == 4) {
            int k = rnd.next(1, 6);
            cases.push_back({rnd.next(1, 30), rnd.next(0, k - 1), k});
        } else {
            cases.push_back(randomCase());
        }
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const TestCase& testCase : cases) {
        println(testCase.n, testCase.m, testCase.k);
    }

    return 0;
}
