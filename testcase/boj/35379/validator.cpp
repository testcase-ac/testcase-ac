#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line: p q
    // p, q are positive integers, coprime, and 2p-1 <= q <= 1000

    // Read p
    int p = inf.readInt(1, 1000, "p");
    inf.readSpace();
    // Upper bound for q is 1000 per statement; lower bound depends on p
    int q = inf.readInt(1, 1000, "q");
    inf.readEoln();

    // Check statement constraints on q
    ensuref(q >= 2 * p - 1, "q must satisfy 2p - 1 <= q, but got p=%d, q=%d", p, q);

    // Ensure p and q are coprime
    int a = p, b = q;
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    ensuref(a == 1, "p and q must be relatively prime, but gcd(%d, %d) = %d", p, q, a);

    // No further global constraints to check from validator's perspective:
    // Existence / bounds of (r, g) are promises to the solution, not input format.

    inf.readEof();
}
