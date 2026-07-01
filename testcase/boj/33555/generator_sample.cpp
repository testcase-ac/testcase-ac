#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int pickValue(int lo, int hi) {
    vector<int> candidates;
    for (int value : {lo, lo + 1, lo + 2, 2, 3, 4, 5, 12, 100, 22999, 23000, hi - 2, hi - 1, hi}) {
        if (lo <= value && value <= hi) {
            candidates.push_back(value);
        }
    }

    if (!candidates.empty() && rnd.next(0, 3) == 0) {
        return rnd.any(candidates);
    }
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int unknown = rnd.next(0, 2);
    vector<string> parts(3);

    if (unknown == 2) {
        int a = pickValue(1, 23000);
        int b = pickValue(1, 23000);
        parts[0] = to_string(a);
        parts[1] = to_string(b);
        parts[2] = "?";
    } else {
        int c = pickValue(2, 23000);
        int knownLeg = pickValue(1, c - 1);

        parts[unknown] = "?";
        parts[1 - unknown] = to_string(knownLeg);
        parts[2] = to_string(c);
    }

    println(parts);
    return 0;
}
