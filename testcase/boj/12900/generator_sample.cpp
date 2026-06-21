#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct TestCase {
    int m;
    int target;
    vector<pair<int, int>> gates;
    vector<int> leaves;
};

TestCase makeCase(int m, int mode) {
    TestCase tc;
    tc.m = m;
    tc.target = rnd.next(0, 1);

    int internalNodes = (m - 1) / 2;
    int leafNodes = (m + 1) / 2;
    tc.gates.reserve(internalNodes);
    tc.leaves.reserve(leafNodes);

    int gateBias = rnd.next(0, 2);
    int changeBias = rnd.next(0, 2);
    for (int i = 0; i < internalNodes; ++i) {
        int gate;
        if (mode == 1) {
            gate = i % 2;
        } else if (gateBias == 0) {
            gate = 0;
        } else if (gateBias == 1) {
            gate = 1;
        } else {
            gate = rnd.next(0, 1);
        }

        int changeable;
        if (mode == 2) {
            changeable = (i == 0 || rnd.next(0, 3) == 0);
        } else if (changeBias == 0) {
            changeable = rnd.next(0, 4) == 0;
        } else if (changeBias == 1) {
            changeable = rnd.next(0, 4) != 0;
        } else {
            changeable = rnd.next(0, 1);
        }

        tc.gates.push_back({gate, changeable});
    }

    int leafBias = rnd.next(0, 3);
    for (int i = 0; i < leafNodes; ++i) {
        int value;
        if (mode == 3) {
            value = i % 2;
        } else if (leafBias == 0) {
            value = 0;
        } else if (leafBias == 1) {
            value = 1;
        } else if (leafBias == 2) {
            value = rnd.next(0, 4) == 0;
        } else {
            value = rnd.next(0, 4) != 0;
        }
        tc.leaves.push_back(value);
    }

    if (rnd.next(0, 1) == 1) {
        reverse(tc.leaves.begin(), tc.leaves.end());
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 10);
    vector<TestCase> tests;
    tests.reserve(t);

    tests.push_back(makeCase(1, 0));
    if (t >= 2) {
        tests.push_back(makeCase(3, 1));
    }

    while ((int)tests.size() < t) {
        int mode = rnd.next(0, 3);
        int level = rnd.next(1, 5);
        int m = (1 << level) - 1;
        if (rnd.next(0, 3) == 0) {
            m = 2 * rnd.next(1, 12) + 1;
        }
        tests.push_back(makeCase(m, mode));
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (const TestCase& tc : tests) {
        println(tc.m, tc.target);
        for (const auto& gate : tc.gates) {
            println(gate.first, gate.second);
        }
        for (int leaf : tc.leaves) {
            println(leaf);
        }
    }

    return 0;
}
