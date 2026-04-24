#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checking
    int N = rnd.next(1, 10);

    // Base sorted sequence 1..N
    vector<int> base(N);
    iota(base.begin(), base.end(), 1);

    // Choose generation pattern
    int type = rnd.next(0, 3);
    vector<int> p;

    if (type == 0) {
        // Completely random permutation
        p = base;
        shuffle(p.begin(), p.end());
    } else if (type == 1) {
        // Fully reversed
        p = base;
        reverse(p.begin(), p.end());
    } else if (type == 2) {
        // Nearly sorted: start sorted, then perform a few random swaps
        p = base;
        int num_swaps = rnd.next(1, max(1, N/2));
        for (int i = 0; i < num_swaps; i++) {
            int a = rnd.next(0, N - 1);
            int b = rnd.next(0, N - 1);
            swap(p[a], p[b]);
        }
    } else {
        // Random prefix + sorted suffix
        int s = rnd.next(0, N);  // suffix length
        vector<int> temp = base;
        shuffle(temp.begin(), temp.end());
        vector<int> B(temp.begin(), temp.begin() + s);
        vector<int> A(temp.begin() + s, temp.end());
        sort(B.begin(), B.end());
        shuffle(A.begin(), A.end());
        p = A;
        p.insert(p.end(), B.begin(), B.end());
    }

    // Output
    println(N);
    println(p);

    return 0;
}
