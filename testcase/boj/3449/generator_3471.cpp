#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small, but at least 2 to include fixed ones
    int T = rnd.next(2, 8);

    // We'll always include two fixed corner cases if T>=2
    int fixedCount = min(T, 2);
    int rndCount = T - fixedCount;

    vector<pair<string, string>> cases;

    // Fixed corner cases
    if (fixedCount >= 1) cases.emplace_back("0", "1");
    if (fixedCount >= 2) cases.emplace_back("111", "000");

    // Hyper-parameters for random cases
    vector<int> tvals = { -2, -1, 0, 1, 2 };
    vector<double> pvals = { 0.0, 0.1, 0.5, 0.9, 1.0 };

    for (int i = 0; i < rndCount; i++) {
        // Length biased towards small or large
        int t = rnd.any(tvals);
        int len = rnd.wnext(10, t) + 1;  // length in [1,10]

        // Probability of bit flip for Hamming distance
        double p = rnd.any(pvals);

        string a(len, '0'), b(len, '0');
        for (int j = 0; j < len; j++) {
            char bit = rnd.next(0, 1) ? '1' : '0';
            a[j] = bit;
            // flip with probability p
            if (rnd.next() < p) {
                b[j] = (bit == '1' ? '0' : '1');
            } else {
                b[j] = bit;
            }
        }
        cases.emplace_back(a, b);
    }

    // Output
    println(T);
    for (auto &pr : cases) {
        println(pr.first);
        println(pr.second);
    }

    return 0;
}
