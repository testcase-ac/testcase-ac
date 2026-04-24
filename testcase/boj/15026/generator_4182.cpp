#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total participants (even, between 2 and 20)
    int T = rnd.next(1, 10) * 2;

    // Divide into beginners (b), normal (n), experienced (e)
    int b = rnd.next(0, T);
    int n = rnd.next(0, T - b);
    int e = T - b - n;

    // Strengths sb < sn < se
    int sb = rnd.next(1, 900);
    int sn = rnd.next(sb + 1, 950);
    int se = rnd.next(sn + 1, 1000);

    int m = T / 2;

    // Hyper-parameters for speed factors: mix of small and large clusters
    int hiSmall = rnd.next(1, 1000);
    int loLarge = rnd.next(hiSmall + 1, 100000);
    double pSmall = rnd.next();

    vector<int> c(m);
    for (int i = 0; i < m; i++) {
        if (rnd.next() < pSmall) {
            c[i] = rnd.next(1, hiSmall);
        } else {
            c[i] = rnd.next(loLarge, 100000);
        }
    }

    // Output
    println(b, n, e);
    println(sb, sn, se);
    println(c);

    return 0;
}
