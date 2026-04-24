#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter t to bias tree size
    int t = rnd.any(vector<int>{-1, 0, 1});
    // Choose k in [1,4] using weighted next to vary tree sizes
    int k = rnd.wnext(4, t) + 1;
    int N = (1 << k) - 1;  // N = 2^k - 1, full binary tree

    // Generate weights
    vector<long long> w(N);
    int mode = rnd.next(0, 2);
    int base;
    for (int i = 0; i < N; i++) {
        if (mode == 0) {
            // uniform in [-10,10]
            w[i] = rnd.next(-10, 10);
        } else if (mode == 1) {
            // biased positive
            base = rnd.next(0, 10);
            w[i] = base + rnd.next(-5, 5);
        } else {
            // biased negative
            base = rnd.next(-10, 0);
            w[i] = base + rnd.next(-5, 5);
        }
    }

    // With 50% chance, add a positive cluster in a random subtree
    if (rnd.next(0, 1) == 0) {
        int root = rnd.next(0, N - 1);
        vector<int> q = {root};
        for (int i = 0; i < (int)q.size(); i++) {
            int x = q[i];
            int l = 2 * x + 1, r = 2 * x + 2;
            if (l < N) q.push_back(l);
            if (r < N) q.push_back(r);
        }
        int boost = rnd.next(5, 10);
        for (int x : q) w[x] += boost;
    }

    // With 50% chance, add a negative cluster in another subtree
    if (rnd.next(0, 1) == 0) {
        int root = rnd.next(0, N - 1);
        vector<int> q = {root};
        for (int i = 0; i < (int)q.size(); i++) {
            int x = q[i];
            int l = 2 * x + 1, r = 2 * x + 2;
            if (l < N) q.push_back(l);
            if (r < N) q.push_back(r);
        }
        int boost = rnd.next(5, 10);
        for (int x : q) w[x] -= boost;
    }

    // Output
    println(N);
    println(w);

    return 0;
}
