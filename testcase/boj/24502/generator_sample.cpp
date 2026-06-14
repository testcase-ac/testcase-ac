#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;

int valueWithResidue(int residue, int k) {
    if (k == 1) {
        return rnd.next(1, 100);
    }

    if (residue == 0) {
        int maxMult = min(5, MAX_A / k);
        return rnd.next(1, maxMult) * k;
    }

    int maxMult = min(5, (MAX_A - residue) / k);
    return rnd.next(0, maxMult) * k + residue;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k;

    if (mode == 0) {
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        k = rnd.next(2, 20);
    } else if (mode == 2) {
        k = rnd.next(900000000, 1000000000);
        n = rnd.next(1, 12);
    } else {
        k = rnd.next(2, 1000);
    }

    vector<int> residues(n, 0);

    if (k == 1) {
        for (int i = 0; i < n; ++i) {
            residues[i] = 0;
        }
    } else if (mode == 0) {
        int residue = rnd.next(1, k - 1);
        fill(residues.begin(), residues.end(), residue);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            residues[i] = (i % 2 == 0) ? rnd.next(0, k - 1) : rnd.next(1, k - 1);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            residues[i] = rnd.next(0, min(k - 1, 20));
        }
    } else {
        for (int i = 0; i + 1 < n; ++i) {
            residues[i] = rnd.next(0, k - 1);
        }

        long long sum = 0;
        for (int i = 0; i + 1 < n; ++i) {
            sum += residues[i];
        }

        bool makeSolvable = rnd.next(0, 1) == 0;
        residues[n - 1] = (k - sum % k) % k;
        if (!makeSolvable) {
            residues[n - 1] = (residues[n - 1] + rnd.next(1, k - 1)) % k;
        }
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = valueWithResidue(residues[i], k);
    }

    println(n, k);
    println(a);
    return 0;
}
