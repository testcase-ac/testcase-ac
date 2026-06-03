#include "testlib.h"

#include <vector>

using namespace std;

int valueWithResidue(int residue, bool large = false) {
    residue %= 7;
    if (residue < 0) residue += 7;

    if (residue == 0) {
        int lo = large ? 12000 : 1;
        int hi = 100000 / 7;
        return 7 * rnd.next(lo, hi);
    }

    int maxK = (100000 - residue) / 7;
    int lo = large ? 12000 : 0;
    return residue + 7 * rnd.next(lo, maxK);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> residues;

    if (mode == 0) {
        n = rnd.next(1, 6);
        residues.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        residues.assign(n, 0);
        residues[rnd.next(n)] = 4;
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        int a = rnd.next(1, 6);
        int b = (4 - a + 7) % 7;
        residues.push_back(a);
        residues.push_back(b);
        while ((int)residues.size() < n) residues.push_back(rnd.any(vector<int>{0, a, b}));
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        int a = rnd.next(1, 6);
        int b = rnd.next(1, 6);
        int c = (4 - a - b + 14) % 7;
        residues.push_back(a);
        residues.push_back(b);
        residues.push_back(c);
        while ((int)residues.size() < n) residues.push_back(rnd.next(0, 6));
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        int r = rnd.next(1, 6);
        residues.assign(n, r);
    } else if (mode == 5) {
        n = rnd.next(40, 120);
        for (int i = 0; i < n; ++i) residues.push_back(rnd.next(0, 6));
    } else {
        n = rnd.next(800, 1000);
        for (int i = 0; i < n; ++i) residues.push_back(rnd.next(0, 6));
    }

    shuffle(residues.begin(), residues.end());

    vector<int> a;
    bool large = mode >= 5;
    for (int residue : residues) a.push_back(valueWithResidue(residue, large));

    println(n);
    println(a);
    return 0;
}
