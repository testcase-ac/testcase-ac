#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Scenario selector for diversity: small, medium, large
    int scenario = rnd.next(1, 3);
    int A, B;
    int Emax, Cmax;

    if (scenario == 1) {
        // Small parameters
        A = rnd.next(1, 20);
        B = rnd.next(1, 20);
        Emax = 100;
        Cmax = 100;
    } else if (scenario == 2) {
        // Medium parameters
        A = rnd.next(1, 1000);
        B = rnd.next(1, 1000);
        Emax = 2000;
        Cmax = 2000;
    } else {
        // Large parameters
        A = rnd.next(1, 10000000);
        B = rnd.next(1, 10000000);
        Emax = 10000000;
        Cmax = 10000000;
    }

    // Build candidate ranges for C to hit different edge‐cases:
    // 1) C in [1, A], 2) C in [A, A+B], 3) C in [A+B, Cmax]
    vector<pair<int,int>> ranges;
    int lo, hi;

    lo = 1;          hi = min(Cmax, A);
    if (lo <= hi) ranges.emplace_back(lo, hi);

    lo = A;          hi = min(Cmax, A + B);
    if (lo <= hi) ranges.emplace_back(lo, hi);

    lo = A + B;      hi = Cmax;
    if (lo <= hi) ranges.emplace_back(lo, hi);

    auto sel = rnd.any(ranges);
    int C = rnd.next(sel.first, sel.second);

    // D and E defining the uniform arrival window [D, E]
    int D = rnd.next(0, Emax);
    int E = rnd.next(D, Emax);

    // Output one test case
    println(A, B, C, D, E);

    return 0;
}
