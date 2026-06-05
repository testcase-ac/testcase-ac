#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long valueForResidue(int residue, int k, int offset) {
    if (residue == 0) {
        return 1LL * k * (offset + 1);
    }
    return residue + 1LL * k * offset;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int k;
    if (mode == 4) {
        k = 100000;
    } else if (mode == 5) {
        k = rnd.next(2, 100000);
    } else {
        k = rnd.next(2, 40);
    }

    int n = rnd.next(2, mode == 4 ? 120 : 35);
    vector<int> residues;

    if (mode == 0) {
        int r = rnd.next(1, k - 1);
        int complement = k - r;
        int left = rnd.next(1, n - 1);
        residues.insert(residues.end(), left, r);
        residues.insert(residues.end(), n - left, complement);
    } else if (mode == 1) {
        int zeros = rnd.next(1, n);
        residues.insert(residues.end(), zeros, 0);
        while ((int)residues.size() < n) {
            residues.push_back(rnd.next(1, k - 1));
        }
    } else if (mode == 2 && k % 2 == 0) {
        int half = k / 2;
        int halfCount = rnd.next(1, n);
        residues.insert(residues.end(), halfCount, half);
        while ((int)residues.size() < n) {
            int r = rnd.next(0, k - 1);
            if (r != half) {
                residues.push_back(r);
            }
        }
    } else if (mode == 3) {
        int r = rnd.next(1, k - 1);
        residues.assign(n, r);
    } else if (mode == 4) {
        vector<int> candidates = {0, 1, 2, 49999, 50000, 50001, 99998, 99999};
        while ((int)residues.size() < n) {
            residues.push_back(rnd.any(candidates));
        }
    } else {
        while ((int)residues.size() < n) {
            residues.push_back(rnd.next(0, k - 1));
        }
    }

    vector<int> usedOffset(k, 0);
    vector<long long> a;
    a.reserve(n);
    for (int residue : residues) {
        long long value = valueForResidue(residue, k, usedOffset[residue]++);
        ensure(value >= 1 && value <= 1000000000LL);
        a.push_back(value);
    }

    if (rnd.next(2)) {
        shuffle(a.begin(), a.end());
    }

    println(n, k);
    println(a);

    return 0;
}
