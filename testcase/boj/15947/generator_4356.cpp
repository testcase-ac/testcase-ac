#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAXN = 1000000;
    // Hyper-parameter to choose type of test
    int t = rnd.next(0, 4);
    int N;
    if (t == 0) {
        // minimal
        N = 1;
    } else if (t == 1) {
        // maximal
        N = MAXN;
    } else if (t == 2) {
        // near cycle boundaries: multiples of 14 ± 1
        int kmax = MAXN / 14;
        if (kmax < 1) kmax = 1;
        int k = rnd.next(1, kmax);
        int base = k * 14;
        vector<int> delta = { -1, 0, 1 };
        int d = rnd.any(delta);
        N = base + d;
        if (N < 1) N = 1;
        if (N > MAXN) N = MAXN;
    } else if (t == 3) {
        // pick a word that is "tururu..." or "turu..." in iteration >=4
        int imax = (MAXN - 15) / 14;
        if (imax < 4) imax = 4;
        int i = rnd.next(4, imax);
        vector<int> poss = {2,3,6,7,10,11};
        int p = rnd.any(poss);
        N = i * 14 + p + 1;
        if (N > MAXN) N = MAXN;
    } else {
        // completely random
        N = rnd.next(1, MAXN);
    }
    println(N);
    return 0;
}
