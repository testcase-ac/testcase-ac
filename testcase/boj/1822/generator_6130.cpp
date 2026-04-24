#include "testlib.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose sizes: small or medium
    int nA, nB;
    if (rnd.next(0, 1) == 0) {
        nA = rnd.next(1, 10);
        nB = rnd.next(1, 10);
    } else {
        nA = rnd.next(10, 30);
        nB = rnd.next(10, 30);
    }

    // Overlap pattern: 1=no overlap, 2=A subset of B, 3=controlled partial, 4=random independent
    int overlapType = rnd.next(1, 4);
    // ensure type 2 only when B can contain all of A
    if (overlapType == 2 && nB < nA) {
        do {
            overlapType = rnd.next(1, 4);
        } while (overlapType == 2);
    }

    unordered_set<int> Aset, Bset;
    int maxVal = max(nA, nB) * 20 + 50;

    if (overlapType == 1) {
        // no overlap
        while ((int)Aset.size() < nA) Aset.insert(rnd.next(1, maxVal));
        while ((int)Bset.size() < nB) Bset.insert(rnd.next(maxVal + 1, maxVal * 2));
    } else if (overlapType == 2) {
        // A subset of B
        while ((int)Aset.size() < nA) Aset.insert(rnd.next(1, maxVal));
        Bset = Aset;
        while ((int)Bset.size() < nB) Bset.insert(rnd.next(1, maxVal * 2));
    } else if (overlapType == 3) {
        // controlled partial overlap
        int k = rnd.next(0, min(nA, nB));
        unordered_set<int> common;
        while ((int)common.size() < k) common.insert(rnd.next(1, maxVal));
        Aset = common;
        Bset = common;
        while ((int)Aset.size() < nA) {
            int x = rnd.next(1, maxVal * 2);
            if (!common.count(x)) Aset.insert(x);
        }
        while ((int)Bset.size() < nB) {
            int x = rnd.next(1, maxVal * 2);
            if (!common.count(x)) Bset.insert(x);
        }
    } else {
        // random independent with possible accidental overlap
        while ((int)Aset.size() < nA) Aset.insert(rnd.next(1, maxVal * 2));
        while ((int)Bset.size() < nB) Bset.insert(rnd.next(1, maxVal * 2));
    }

    // Convert to vectors
    vector<int> A(Aset.begin(), Aset.end()), B(Bset.begin(), Bset.end());
    shuffle(A.begin(), A.end());
    shuffle(B.begin(), B.end());

    // Output input format
    println(nA, nB);
    println(A);
    println(B);

    return 0;
}
