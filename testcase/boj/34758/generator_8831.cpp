#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Helper for large / edge coordinates
    vector<long long> special = {
        -1000000000LL, -999999999LL, -100000000LL, -10LL, -1LL, 0LL,
         1LL, 10LL, 100000000LL, 999999999LL, 1000000000LL
    };

    // Generate target (X, Y)
    long long X, Y;
    int ttype = rnd.next(0, 9);
    if (ttype <= 5) {
        // Both small
        X = rnd.next(-10, 10);
        Y = rnd.next(-10, 10);
    } else if (ttype <= 7) {
        // One or both zero-ish
        if (rnd.next(0, 1) == 0) {
            X = 0;
            Y = rnd.next(-10, 10);
        } else {
            X = rnd.next(-10, 10);
            Y = 0;
        }
    } else {
        // From special large set
        X = rnd.any(special);
        Y = rnd.any(special);
    }

    // Scenario type to control shape of test
    int scenario = rnd.next(0, 4);

    int N;
    switch (scenario) {
        case 0: N = rnd.next(1, 3); break;   // tiny
        case 1: N = rnd.next(3, 7); break;   // small
        case 2: N = rnd.next(7, 12); break;  // medium
        case 3: N = rnd.next(5, 12); break;  // many collinear
        case 4: N = rnd.next(5, 12); break;  // all non-collinear
        default: N = rnd.next(3, 7); break;
    }

    // Decide how many should have answer 0 (share X or Y with target)
    int kZero;
    if (scenario == 0) {
        if (N == 1) kZero = rnd.next(0, 1);
        else kZero = rnd.next(1, N - 1); // ensure both 0 and 1 exist
    } else if (scenario == 3) {
        kZero = max(1, (2 * N) / 3);      // mostly 0s
        kZero = min(kZero, N);
    } else if (scenario == 4) {
        kZero = 0;                        // all 1s
    } else {
        kZero = rnd.next(0, N);           // arbitrary mix
    }

    set<pair<long long, long long>> used;
    used.insert({X, Y});

    auto randSmall = [&]() -> long long {
        return rnd.next(-10, 10);
    };
    auto randMixed = [&]() -> long long {
        if (rnd.next(0, 9) < 7) return randSmall();
        else return rnd.any(special);
    };

    vector<pair<long long, long long>> students;
    students.reserve(N);

    // Generate kZero students collinear with target (answer 0)
    for (int i = 0; i < kZero; ++i) {
        while (true) {
            bool shareX = (rnd.next(0, 1) == 0);
            long long xi, yi;
            if (shareX) {
                xi = X;
                yi = randMixed();
                if (yi == Y) continue;
            } else {
                yi = Y;
                xi = randMixed();
                if (xi == X) continue;
            }
            pair<long long, long long> p = {xi, yi};
            if (!used.count(p)) {
                used.insert(p);
                students.push_back(p);
                break;
            }
        }
    }

    // Generate remaining students non-collinear with target (answer 1)
    for (int i = kZero; i < N; ++i) {
        while (true) {
            long long xi = randMixed();
            long long yi = randMixed();
            if (xi == X || yi == Y) continue; // ensure non-collinear
            pair<long long, long long> p = {xi, yi};
            if (!used.count(p)) {
                used.insert(p);
                students.push_back(p);
                break;
            }
        }
    }

    // Output
    println(X, Y);
    println(N);
    for (auto &p : students) {
        println(p.first, p.second);
    }

    return 0;
}
