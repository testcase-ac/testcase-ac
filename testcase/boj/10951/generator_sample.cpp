#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int testCaseCount;
    vector<pair<int, int>> cases;

    if (mode == 0) {
        testCaseCount = 1;
    } else if (mode == 1) {
        testCaseCount = rnd.next(2, 6);
        vector<pair<int, int>> boundaryCases = {
            {1, 1}, {1, 9}, {9, 1}, {9, 9}, {5, 5}
        };
        shuffle(boundaryCases.begin(), boundaryCases.end());
        for (int i = 0; i < testCaseCount; ++i) {
            cases.push_back(boundaryCases[i % (int)boundaryCases.size()]);
        }
    } else if (mode == 2) {
        testCaseCount = rnd.next(3, 12);
    } else {
        testCaseCount = rnd.next(15, 45);
    }

    while ((int)cases.size() < testCaseCount) {
        int a = rnd.next(1, 9);
        int b = rnd.next(1, 9);

        if (mode == 2 && rnd.next(0, 2) == 0) {
            a = rnd.any(vector<int>{1, 9});
        }
        if (mode == 3 && rnd.next(0, 3) == 0) {
            b = 10 - a;
        }

        cases.emplace_back(a, b);
    }

    shuffle(cases.begin(), cases.end());
    for (const auto& [a, b] : cases) {
        println(a, b);
    }

    return 0;
}
