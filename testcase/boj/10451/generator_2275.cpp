#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases between 1 and 5
    int T = rnd.next(1, 5);
    printf("%d\n", T);
    for (int tc = 0; tc < T; tc++) {
        // Size of permutation N between 2 and 10 for easy verification
        int N = rnd.next(2, 10);
        printf("%d\n", N);

        vector<int> perm(N + 1);
        // mode = 0: fully random permutation
        // mode = 1: generate exactly k cycles
        int mode = rnd.next(0, 1);
        if (mode == 0) {
            vector<int> a(N);
            iota(a.begin(), a.end(), 1);
            shuffle(a.begin(), a.end());
            for (int i = 1; i <= N; i++) {
                perm[i] = a[i - 1];
            }
        } else {
            // choose target cycle count k
            int k = rnd.next(1, N);
            // Generate k cycles by cutting a shuffled list
            vector<int> cuts = {0, N};
            vector<int> pts(N - 1);
            iota(pts.begin(), pts.end(), 1);
            shuffle(pts.begin(), pts.end());
            for (int i = 0; i < k - 1; i++) {
                cuts.push_back(pts[i]);
            }
            sort(cuts.begin(), cuts.end());
            // shuffle labels
            vector<int> labels(N);
            iota(labels.begin(), labels.end(), 1);
            shuffle(labels.begin(), labels.end());
            // build each cycle
            for (int ci = 0; ci < k; ci++) {
                int l = cuts[ci], r = cuts[ci + 1];
                int len = r - l;
                for (int j = 0; j < len; j++) {
                    int u = labels[l + j];
                    int v = labels[l + (j + 1) % len];
                    perm[u] = v;
                }
            }
        }

        // Print the permutation
        for (int i = 1; i <= N; i++) {
            printf("%d%c", perm[i], i == N ? '\n' : ' ');
        }
    }
    return 0;
}
