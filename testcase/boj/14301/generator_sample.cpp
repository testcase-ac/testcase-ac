#include "testlib.h"

#include <utility>
#include <vector>
using namespace std;

pair<int, int> nearMultipleOfThree() {
    int base = rnd.next(1, 33) * 3;
    int r = max(1, min(100, base + rnd.next(-2, 2)));
    int c = max(1, min(100, rnd.next(1, 33) * 3 + rnd.next(-2, 2)));
    return {r, c};
}

pair<int, int> randomCase() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        return {1, rnd.next(1, 100)};
    }
    if (mode == 1) {
        return {rnd.next(1, 100), 1};
    }
    if (mode == 2) {
        return nearMultipleOfThree();
    }
    if (mode == 3) {
        int r = rnd.next(2, 12);
        int c = rnd.next(2, 12);
        return {r, c};
    }
    if (mode == 4) {
        int r = rnd.next(80, 100);
        int c = rnd.next(80, 100);
        return {r, c};
    }

    int r = rnd.next(1, 100);
    int c = rnd.next(1, 100);
    return {r, c};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases = {
        {1, 1},
        {1, 100},
        {100, 1},
        {2, 3},
        {3, 2},
        {3, 3},
        {100, 100},
    };

    int targetT = rnd.next(12, 30);
    while ((int)cases.size() < targetT) {
        cases.push_back(randomCase());
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [r, c] : cases) {
        println(r, c);
    }

    return 0;
}
