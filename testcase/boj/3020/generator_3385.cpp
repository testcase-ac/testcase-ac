#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of obstacles (even)
    int Npairs = rnd.next(1, 5);
    int N = 2 * Npairs;
    // Cave height
    int H = rnd.next(2, 10);
    // Skew parameters for stalagmites and stalactites
    int t_low   = rnd.next(-2, 2);
    int t_high  = rnd.next(-2, 2);

    // Generate obstacles: even indices = stalagmites, odd = stalactites
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            // Stalagmite (grows from ground)
            a[i] = rnd.wnext(H - 1, t_low) + 1;
        } else {
            // Stalactite (hangs from ceiling)
            a[i] = rnd.wnext(H - 1, t_high) + 1;
        }
    }

    // Output
    println(N, H);
    for (int x : a) println(x);

    return 0;
}
