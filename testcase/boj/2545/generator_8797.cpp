#include "testlib.h"
using namespace std;

struct Test {
    long long A, B, C, D;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Test> tests;

    // Include sample tests from the statement
    tests.push_back({4, 5, 6, 0});
    tests.push_back({4, 5, 6, 3});
    tests.push_back({1, 1, 10, 9});

    // Decide how many additional random tests to generate
    int extra = rnd.next(2, 7); // so total T will be between 5 and 10

    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(0, 3);
        long long A, B, C;

        if (type == 0) {
            // Small dimensions, fully random
            A = rnd.next(1, 10);
            B = rnd.next(1, 10);
            C = rnd.next(1, 10);
        } else if (type == 1) {
            // Degenerate: one dimension is 1
            int pos = rnd.next(0, 2);
            long long dims[3];
            for (int j = 0; j < 3; ++j) {
                if (j == pos) dims[j] = 1;
                else dims[j] = rnd.next(1, 20);
            }
            A = dims[0];
            B = dims[1];
            C = dims[2];
        } else if (type == 2) {
            // Medium-sized box
            A = rnd.next(1, 100);
            B = rnd.next(1, 100);
            C = rnd.next(1, 100);
        } else {
            // Larger box, still within 64-bit volume safety
            A = rnd.next(1, 1000000);
            B = rnd.next(1, 1000000);
            C = rnd.next(1, 1000000);
        }

        long long maxCuts = A + B + C - 3;
        long long D;

        if (maxCuts <= 0) {
            D = 0;
        } else {
            int dt = rnd.next(0, 4);
            if (dt == 0) {
                D = 0;
            } else if (dt == 1) {
                D = maxCuts;
            } else if (dt == 2) {
                D = 1;
            } else if (dt == 3) {
                D = (maxCuts > 1 ? maxCuts - 1 : maxCuts);
            } else {
                D = rnd.next(0LL, maxCuts);
            }
        }

        tests.push_back({A, B, C, D});
    }

    int T = (int)tests.size();
    println(T);
    printf("\n");
    for (int i = 0; i < T; ++i) {
        println(tests[i].A, tests[i].B, tests[i].C, tests[i].D);
        if (i + 1 < T) printf("\n");
    }

    return 0;
}
