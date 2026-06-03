#include "testlib.h"
#include <vector>
using namespace std;

int randomYear() {
    int n;
    do {
        n = rnd.next(1000, 9999);
    } while (n % 100 == 0);
    return n;
}

int goodYear() {
    vector<int> candidates;
    int suffix = rnd.next(1, 99);
    for (int n = 1000 + suffix; n <= 9999; n += 100) {
        if ((n + 1) % suffix == 0)
            candidates.push_back(n);
    }
    return candidates.empty() ? randomYear() : rnd.any(candidates);
}

int nearBoundaryYear() {
    vector<int> candidates = {
        1001, 1002, 1098, 1099, 1101, 1199,
        2023, 2024, 2029, 2030,
        9899, 9901, 9998, 9999
    };
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 24);
    vector<int> tests;
    tests.reserve(t);

    while ((int)tests.size() < t) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            tests.push_back(nearBoundaryYear());
        } else if (mode == 1) {
            tests.push_back(goodYear());
        } else if (mode == 2) {
            int suffix = rnd.next(1, 99);
            int century = rnd.next(10, 99);
            tests.push_back(century * 100 + suffix);
        } else {
            tests.push_back(randomYear());
        }
    }

    shuffle(tests.begin(), tests.end());

    println(t);
    for (int n : tests)
        println(n);

    return 0;
}
