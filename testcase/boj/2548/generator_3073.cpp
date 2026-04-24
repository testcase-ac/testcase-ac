#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of elements
    int N = rnd.next(1, 10);
    // Maximum value for elements
    int maxv = rnd.next(1, 20);
    // Choose distribution type
    int type = rnd.next(0, 3);
    vector<int> a(N);

    if (type == 0) {
        // Uniform distribution
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, maxv);
        }
    } else if (type == 1) {
        // Clustered around random centers
        int c = (N >= 2 ? rnd.next(2, min(3, N)) : 1);
        vector<int> centers(c);
        for (int i = 0; i < c; i++) {
            centers[i] = rnd.next(1, maxv);
        }
        int d = rnd.next(0, max(1, maxv / 4));
        for (int i = 0; i < N; i++) {
            int cen = centers[rnd.next(0, c - 1)];
            int jitter = rnd.next(0, 2 * d) - d;
            int v = cen + jitter;
            if (v < 1) v = 1;
            if (v > maxv) v = maxv;
            a[i] = v;
        }
    } else if (type == 2) {
        // Already sorted values
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, maxv);
        }
        sort(a.begin(), a.end());
    } else {
        // Few distinct values with duplicates
        int ds = rnd.next(1, min(N, maxv));
        vector<int> cand(maxv);
        for (int i = 0; i < maxv; i++) cand[i] = i + 1;
        shuffle(cand.begin(), cand.end());
        vector<int> centers(cand.begin(), cand.begin() + ds);
        for (int i = 0; i < N; i++) {
            a[i] = rnd.any(centers);
        }
    }

    // For all but sorted case, shuffle to randomize order
    if (type != 2) {
        shuffle(a.begin(), a.end());
    }

    // Output
    println(N);
    println(a);
    return 0;
}
