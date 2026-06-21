#include "testlib.h"

#include <vector>

using namespace std;

long long valueWithResidue(int residue, bool preferLarge) {
    long long maxK = (1000000000LL - residue) / 3;
    if (preferLarge && maxK > 0) {
        long long low = max(0LL, maxK - 20);
        return 3 * rnd.next(low, maxK) + residue;
    }
    long long k = rnd.next(0LL, min(40LL, maxK));
    return 3 * k + residue;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 3);
        int residue = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            a.push_back(valueWithResidue(residue, rnd.next(0, 1)));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(0, 2);
            a.push_back(valueWithResidue(residue, false));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 15);
        for (int i = 0; i < n; ++i) {
            int residue = (i + rnd.next(0, 1)) % 3;
            a.push_back(valueWithResidue(residue, false));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 16);
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(0, 3) == 0 ? rnd.next(1, 2) : 0;
            a.push_back(valueWithResidue(residue, rnd.next(0, 1)));
        }
    } else if (mode == 4) {
        n = rnd.next(8, 20);
        int block = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            int residue = (i / block) % 3;
            a.push_back(valueWithResidue(residue, rnd.next(0, 3) == 0));
        }
    } else {
        n = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(0, 2);
            bool large = rnd.next(0, 2) == 0;
            a.push_back(valueWithResidue(residue, large));
        }
    }

    println(n);
    println(a);
    return 0;
}
