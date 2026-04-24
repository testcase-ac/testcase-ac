#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: include small, max, and typical
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        N = 1;
    } else if (p < 0.2) {
        N = 10;
    } else {
        N = rnd.next(2, 9);
    }
    // Build initial ascending permutation
    vector<int> perm(N);
    for (int i = 0; i < N; i++) perm[i] = i + 1;
    // Choose pattern type
    int type = (N == 1 ? 0 : rnd.next(0, 4));
    switch (type) {
        case 0:
            // already ascending
            break;
        case 1:
            // fully descending
            reverse(perm.begin(), perm.end());
            break;
        case 2:
            // random shuffle
            shuffle(perm.begin(), perm.end());
            break;
        case 3:
            // almost ascending: one adjacent swap
            if (N >= 2) {
                int i = rnd.next(1, N - 1) - 1;
                swap(perm[i], perm[i+1]);
            }
            break;
        case 4:
            // almost descending: start descending, then one swap
            reverse(perm.begin(), perm.end());
            if (N >= 2) {
                int i = rnd.next(1, N - 1) - 1;
                swap(perm[i], perm[i+1]);
            }
            break;
    }
    // Output
    println(N);
    println(perm);
    return 0;
}
