#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int,int>> tests;

    int scenario = rnd.next(0, 4);

    if (scenario == 0) {
        // Small t, small magnitude numbers, many zeros
        int t = rnd.next(1, 5);
        for (int i = 0; i < t; i++) {
            int x = rnd.next(-20, 20);
            int y = rnd.next(-20, 20);
            if (rnd.next(0, 4) == 0) x = 0;
            if (rnd.next(0, 4) == 0) y = 0;
            tests.emplace_back(x, y);
        }
    } else if (scenario == 1) {
        // Boundary-focused
        const int L = -1000000000;
        const int R =  1000000000;

        tests.emplace_back(L, R);
        tests.emplace_back(R, L);
        tests.emplace_back(L, L);
        tests.emplace_back(R, R);
        tests.emplace_back(0, L);
        tests.emplace_back(0, R);

        int targetT = rnd.next(6, 10);
        while ((int)tests.size() < targetT) {
            if (rnd.next(0, 1) == 0) {
                int x = rnd.next(L, L + 20);
                int y = rnd.next(L, R);
                tests.emplace_back(x, y);
            } else {
                int x = rnd.next(R - 20, R);
                int y = rnd.next(L, R);
                tests.emplace_back(x, y);
            }
        }
    } else if (scenario == 2) {
        // Medium/large t, fully random in full range
        const int L = -1000000000;
        const int R =  1000000000;

        int t = rnd.next(10, 18);
        for (int i = 0; i < t; i++) {
            int x = rnd.next(L, R);
            int y = rnd.next(L, R);
            tests.emplace_back(x, y);
        }
        // Ensure at least one zero appears
        if (!tests.empty()) {
            int idx = rnd.next(0, (int)tests.size() - 1);
            if (rnd.next(0, 1) == 0)
                tests[idx].first = 0;
            else
                tests[idx].second = 0;
        }
    } else if (scenario == 3) {
        // Pattern-based: sums 0, positive, negative
        const int R = 1000000000;
        int t = rnd.next(8, 15);
        for (int i = 0; i < t; i++) {
            int k = rnd.next(1, R);
            int type = i % 3;
            if (type == 0) {
                // k, -k => sum 0
                tests.emplace_back(k, -k);
            } else if (type == 1) {
                // k, k => positive sum
                tests.emplace_back(k, k);
            } else {
                // -k, -k => negative sum
                tests.emplace_back(-k, -k);
            }
        }
    } else {
        // Single test case, potentially extreme
        const int L = -1000000000;
        const int R =  1000000000;
        vector<pair<int,int>> opts = {
            {0, 0},
            {L, R},
            {R, L},
            {L, L},
            {R, R},
            {123456789, -987654321},
            {rnd.next(L, R), rnd.next(L, R)}
        };
        tests.push_back(rnd.any(opts));
    }

    int t = (int)tests.size();
    if (t == 0) {
        // Fallback safety, should not happen
        tests.emplace_back(0, 0);
        t = 1;
    }

    println(t);
    for (auto &p : tests) {
        println(p.first, p.second);
    }

    return 0;
}
