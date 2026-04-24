#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Read a and b
        int a = inf.readInt(1, 10000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 10000, "b");
        inf.readEoln();

        // Validate basic constraints
        ensuref(a < b,
                "In test case %d: a (%d) must be less than b (%d)",
                tc + 1, a, b);
        ensuref(std::gcd(a, b) == 1,
                "In test case %d: a (%d) and b (%d) must be coprime",
                tc + 1, a, b);

        // Simulate the greedy Egyptian‐fraction algorithm
        long long rem_num = a;
        long long rem_den = b;
        vector<long long> xs;
        while (rem_num != 0) {
            // x = ceil(rem_den / rem_num)
            long long x = (rem_den + rem_num - 1) / rem_num;
            xs.push_back(x);

            // compute new remainder: rem_num/rem_den - 1/x = (rem_num*x - rem_den)/(rem_den*x)
            long long new_num = rem_num * x - rem_den;
            if (new_num == 0) {
                break;  // exact representation reached
            }
            long long new_den = rem_den * x;
            // must stay positive
            ensuref(new_num > 0 && new_den > 0,
                    "In test case %d: invalid remainder (%lld/%lld) after subtracting 1/%lld",
                    tc + 1, new_num, new_den, x);

            rem_num = new_num;
            rem_den = new_den;
        }
        ensuref(!xs.empty(),
                "In test case %d: failed to compute any unit fraction", tc + 1);

        // Validate the global bound: b * x1 * x2 * ... * x_{m-1} < 2^31
        const long long LIMIT = (1LL << 31);
        __int128 prod = b;
        for (size_t i = 0; i + 1 < xs.size(); ++i) {
            prod *= xs[i];
            ensuref(prod < LIMIT,
                    "In test case %d: product of b and x1..x_%zu is %lld which is >= 2^31",
                    tc + 1, i + 1, (long long)prod);
        }
    }

    inf.readEof();
    return 0;
}
