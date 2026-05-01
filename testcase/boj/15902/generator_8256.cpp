#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose L with varied size: small, medium, large (up to 20)
    int caseType = rnd.next(0, 2);
    int L;
    if (caseType == 0) L = rnd.next(1, 5);
    else if (caseType == 1) L = rnd.next(6, 10);
    else L = rnd.next(11, 20);

    // Generate initial tiling a
    vector<int> a;
    int rem = L;
    while (rem > 0) {
        if (rem >= 2 && rnd.next(0, 1) == 0) {
            a.push_back(2);
            rem -= 2;
        } else {
            a.push_back(1);
            rem -= 1;
        }
    }

    // Generate target tiling b with various edge cases
    vector<int> b;
    if (rnd.next(0, 9) == 0) {
        // all 1s
        b.assign(L, 1);
    } else if (L % 2 == 0 && rnd.next(0, 9) == 1) {
        // all 2s (only if even L)
        b.assign(L / 2, 2);
    } else if (rnd.next(0, 4) == 0) {
        // identical to initial
        b = a;
    } else {
        // random mix
        rem = L;
        while (rem > 0) {
            if (rem >= 2 && rnd.next(0, 2) == 0) {
                b.push_back(2);
                rem -= 2;
            } else {
                b.push_back(1);
                rem -= 1;
            }
        }
    }

    // Output
    println(L);
    println((int)a.size());
    println(a);
    println((int)b.size());
    println(b);

    return 0;
}
