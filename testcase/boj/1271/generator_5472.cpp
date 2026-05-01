#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose n's digit count small or large
    int ndigits = rnd.next() < 0.5 ? rnd.next(1, 3) : rnd.next(10, 20);
    // Build n as a random positive integer with no leading zeros
    string n;
    n += char('1' + rnd.next(0, 8));  // first digit 1-9
    for (int i = 1; i < ndigits; i++)
        n += char('0' + rnd.next(0, 9));

    // Build m with special cases or general
    string m;
    double p = rnd.next();
    if (p < 0.1) {
        // trivial case: 1
        m = "1";
    } else if (p < 0.2) {
        // edge case: equal to n
        m = n;
    } else {
        // general: pick digit count for m
        int md;
        // with small chance make m very small
        if (rnd.next() < 0.2)
            md = 1;
        else
            md = rnd.next(1, ndigits);
        if (md < ndigits) {
            // any number with fewer digits is <= n
            m += char('1' + rnd.next(0, 8));
            for (int i = 1; i < md; i++)
                m += char('0' + rnd.next(0, 9));
        } else {
            // same length: generate digit by digit ensuring m <= n
            bool prefix_equal = true;
            for (int i = 0; i < ndigits; i++) {
                int ub = prefix_equal ? n[i] - '0' : 9;
                int lb = (i == 0 ? 1 : 0);
                if (ub < lb) ub = lb; // fallback
                int d = rnd.next(lb, ub);
                m += char('0' + d);
                if (prefix_equal && d < (n[i] - '0')) prefix_equal = false;
            }
        }
    }

    // Output as per problem: n m on first line
    println(n, m);
    return 0;
}
