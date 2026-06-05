#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long valueWithResidue(int residue, int style) {
    const long long maxA = 1000000000LL;
    long long maxQ = (maxA - residue) / 3;

    if (style == 0) return residue;
    if (style == 1) return maxA - ((maxA - residue) % 3);
    if (style == 2) return 3LL * rnd.next(0LL, min(20LL, maxQ)) + residue;
    if (style == 3) return 3LL * rnd.next(max(0LL, maxQ - 20), maxQ) + residue;
    return 3LL * rnd.next(0LL, maxQ) + residue;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 30);
    vector<long long> a;

    if (mode == 0) {
        int residue = rnd.next(0, 2);
        int style = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) a.push_back(valueWithResidue(residue, style));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(0, 2);
            a.push_back(valueWithResidue(residue, rnd.next(0, 2)));
        }
    } else if (mode == 2) {
        vector<long long> pool = {0, 1, 2, 3, 4, 5, 999999996LL, 999999997LL,
                                  999999998LL, 999999999LL, 1000000000LL};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 3) {
        n = 3 * rnd.next(1, 10);
        for (int i = 0; i < n / 3; ++i) {
            int style = rnd.next(0, 4);
            a.push_back(valueWithResidue(0, style));
            a.push_back(valueWithResidue(1, style));
            a.push_back(valueWithResidue(2, style));
        }
    } else if (mode == 4) {
        int dominant = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(4) == 0 ? rnd.next(0, 2) : dominant;
            a.push_back(valueWithResidue(residue, rnd.next(0, 4)));
        }
    } else {
        n = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0LL, 1000000000LL));
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
