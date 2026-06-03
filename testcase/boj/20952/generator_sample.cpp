#include "testlib.h"

#include <vector>

using namespace std;

long long valueWithResidue(int residue, long long low, long long high) {
    long long first = low + ((residue - low % 7 + 7) % 7);
    if (first > high) return low;
    long long count = (high - first) / 7 + 1;
    return first + 7LL * rnd.next(0LL, count - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 3 ? 40 : 25);
    int m = rnd.next(1, mode == 3 ? 40 : 25);
    vector<long long> a(n), b(m);

    if (mode == 0) {
        for (long long& x : a) x = rnd.next(1LL, 200LL);
        for (long long& x : b) x = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        int residue = rnd.next(0, 6);
        for (long long& x : a) x = valueWithResidue(residue, 1, 500);
        for (long long& x : b) {
            int bResidue = rnd.next(0, 6);
            x = valueWithResidue(bResidue, 1, 500);
        }
    } else if (mode == 2) {
        int missingResidue = rnd.next(0, 6);
        for (long long& x : a) {
            int residue = rnd.next(0, 5);
            if (residue >= missingResidue) ++residue;
            x = valueWithResidue(residue, 1, 700);
        }
        for (long long& x : b) x = valueWithResidue(rnd.next(0, 6), 1, 700);
    } else if (mode == 3) {
        for (long long& x : a) {
            int residue = rnd.next(0, 6);
            x = valueWithResidue(residue, 1000000000LL - 500, 1000000000LL);
        }
        for (long long& x : b) {
            int residue = rnd.next(0, 6);
            x = valueWithResidue(residue, 1000000000LL - 500, 1000000000LL);
        }
    } else {
        int currentShift = 0;
        for (long long& x : a) x = valueWithResidue(rnd.next(0, 6), 1, 1000);
        for (long long& x : b) {
            int target = rnd.next(0, 6);
            int residue = (7 - currentShift + target) % 7;
            x = valueWithResidue(residue, 1, 1000);
            if (rnd.next(0, 1)) currentShift = (currentShift + residue) % 7;
        }
    }

    shuffle(a.begin(), a.end());
    shuffle(b.begin(), b.end());

    println(n, m);
    println(a);
    println(b);

    return 0;
}
