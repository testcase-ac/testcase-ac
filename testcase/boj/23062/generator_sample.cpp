#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

struct TestCase {
    int a_mod;
    int b_mod;
    int c_mod;
    int a_rem;
    int b_rem;
    int c_rem;
};

int boundedMod(int value) {
    return max(1, min(1000000, value));
}

TestCase consistentCase(int maxMod) {
    int a = rnd.next(1, maxMod);
    int b = rnd.next(1, maxMod);
    int c = rnd.next(1, maxMod);
    int x = rnd.next(0, 1000000);
    return {a, b, c, x % a, x % b, x % c};
}

TestCase inconsistentPairCase() {
    int g = rnd.next(2, 500);
    int a = g * rnd.next(1, 2000);
    int b = g * rnd.next(1, 2000);
    int c = rnd.next(1, 1000000);
    a = boundedMod(a);
    b = boundedMod(b);

    int base = rnd.next(0, g - 1);
    int aRem = base + g * rnd.next(0, (a - 1 - base) / g);
    int badBase = (base + rnd.next(1, g - 1)) % g;
    int bRem = badBase + g * rnd.next(0, (b - 1 - badBase) / g);
    int cRem = rnd.next(0, c - 1);
    return {a, b, c, aRem, bRem, cRem};
}

TestCase boundaryCase() {
    vector<int> mods = {1, 2, 999983, 999998, 999999, 1000000};
    shuffle(mods.begin(), mods.end());

    array<int, 3> chosen = {mods[0], mods[1], mods[2]};
    array<int, 3> rems;
    for (int i = 0; i < 3; ++i) {
        if (chosen[i] == 1) {
            rems[i] = 0;
        } else if (rnd.next(0, 1) == 0) {
            rems[i] = rnd.next(0, min(chosen[i] - 1, 5));
        } else {
            rems[i] = rnd.next(max(0, chosen[i] - 6), chosen[i] - 1);
        }
    }

    return {chosen[0], chosen[1], chosen[2], rems[0], rems[1], rems[2]};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 30);
    vector<TestCase> tests;

    tests.push_back({1, 1, 1, 0, 0, 0});
    tests.push_back(boundaryCase());
    tests.push_back(inconsistentPairCase());

    while ((int)tests.size() < t) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            tests.push_back(consistentCase(12));
        } else if (mode == 1) {
            tests.push_back(consistentCase(1000));
        } else if (mode == 2) {
            tests.push_back(consistentCase(1000000));
        } else if (mode == 3) {
            tests.push_back(inconsistentPairCase());
        } else {
            tests.push_back(boundaryCase());
        }
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (const TestCase& tc : tests) {
        println(tc.a_mod, tc.b_mod, tc.c_mod, tc.a_rem, tc.b_rem, tc.c_rem);
    }

    return 0;
}
