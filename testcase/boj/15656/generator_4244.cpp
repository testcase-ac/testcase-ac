#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of input
    int N = rnd.next(1, 7);
    int M = rnd.next(1, N);

    // Three modes for distinct numbers
    int mode = rnd.next(0, 2);
    set<int> S;
    if (mode == 0) {
        // small range [1, N*10]
        int hi = max(N, 1) * 10;
        while ((int)S.size() < N)
            S.insert(rnd.next(1, hi));
    } else if (mode == 1) {
        // large range [1, 10000]
        while ((int)S.size() < N)
            S.insert(rnd.next(1, 10000));
    } else {
        // clustered around a random center
        int center = rnd.next(1, 10000);
        int spread = rnd.next(N, 100);
        while ((int)S.size() < N) {
            int off = rnd.next(0, 2 * spread) - spread;
            int x = center + off;
            if (x < 1) x = 1;
            if (x > 10000) x = 10000;
            S.insert(x);
        }
    }

    // Prepare and shuffle input order
    vector<int> a(S.begin(), S.end());
    shuffle(a.begin(), a.end());

    // Output
    println(N, M);
    println(a);

    return 0;
}
