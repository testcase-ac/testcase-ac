#include "testlib.h"
#include <set>
#include <utility>
#include <vector>

using namespace std;

int randomEvenSteps() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        vector<int> small = {2, 4, 6, 8, 10, 12};
        return rnd.any(small);
    }
    if (mode == 1) {
        return 2 * rnd.next(20, 50);
    }
    if (mode == 2) {
        return 2 * rnd.next(1, 50);
    }

    int around = rnd.next(35, 50);
    return 2 * rnd.next(max(1, around - 8), min(50, around + 8));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasetCount = rnd.next(4, 18);
    vector<pair<int, int>> cases;
    cases.reserve(datasetCount);

    if (rnd.next(2) == 0) cases.emplace_back(0, 2);
    if (rnd.next(2) == 0) cases.emplace_back(1000000000, 100);
    if (rnd.next(2) == 0) cases.emplace_back(rnd.next(1, 1000000000), rnd.any(vector<int>{6, 8, 10, 12, 60}));

    set<pair<int, int>> used(cases.begin(), cases.end());
    while ((int)cases.size() < datasetCount) {
        int k;
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            k = (int)cases.size() + 1;
        } else if (mode == 1) {
            k = rnd.next(0, 20);
        } else if (mode == 2) {
            k = rnd.next(999999900, 1000000000);
        } else {
            k = rnd.next(0, 1000000000);
        }

        int s = randomEvenSteps();
        if (used.insert({k, s}).second) {
            cases.emplace_back(k, s);
        }
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [k, s] : cases) {
        println(k, s);
    }

    return 0;
}
