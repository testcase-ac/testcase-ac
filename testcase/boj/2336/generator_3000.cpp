#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand-checkable cases
    int N = rnd.next(1, 10);
    // Base ordering 1..N
    vector<int> base(N);
    iota(base.begin(), base.end(), 1);

    // perm1: either identity, reversed, or fully random
    int t1 = rnd.next(0, 2);
    vector<int> perm1 = base;
    if (t1 == 1) {
        reverse(perm1.begin(), perm1.end());
    } else if (t1 == 2) {
        shuffle(perm1.begin(), perm1.end());
    }

    // perm2: derived from perm1 by small swaps, or reverse, or random
    vector<int> perm2 = perm1;
    int t2 = rnd.next(0, 2);
    if (t2 == 0 && N >= 2) {
        int K = rnd.next(0, N / 2);
        for (int i = 0; i < K; i++) {
            int pos = rnd.next(0, N - 2);
            swap(perm2[pos], perm2[pos + 1]);
        }
    } else if (t2 == 1) {
        reverse(perm2.begin(), perm2.end());
    } else {
        shuffle(perm2.begin(), perm2.end());
    }

    // perm3: derived from base or perm2, mixing patterns
    vector<int> perm3 = base;
    int t3 = rnd.next(0, 2);
    if (t3 == 0 && N >= 2) {
        int w = rnd.next(-2, 2);
        int K = rnd.wnext(N, w);
        for (int i = 0; i < K; i++) {
            int pos = rnd.next(0, N - 2);
            swap(perm3[pos], perm3[pos + 1]);
        }
    } else if (t3 == 1) {
        perm3 = perm2;
        int K = rnd.next(0, N / 3);
        for (int i = 0; i < K; i++) {
            int x = rnd.next(0, N - 1);
            int y = rnd.next(0, N - 1);
            swap(perm3[x], perm3[y]);
        }
    } else {
        shuffle(perm3.begin(), perm3.end());
    }

    // Output
    println(N);
    println(perm1);
    println(perm2);
    println(perm3);
    return 0;
}
