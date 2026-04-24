#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of closets
    int n = rnd.next(4, 20);
    // Choose two distinct open closets
    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 1);
    shuffle(ids.begin(), ids.end());
    int a = ids[0], b = ids[1];
    if (a > b) swap(a, b);
    // Sequence length with bias: small, medium, or large
    int weightT = rnd.any(vector<int>{-1, 0, 1});
    int k = rnd.wnext(20, weightT) + 1;  // in [1,20]
    // Clustering probability for locality in sequence
    double clusterProb = rnd.next(0.0, 1.0);
    // Build usage sequence
    vector<int> seq;
    int prev = rnd.next(1, n);
    seq.push_back(prev);
    for (int i = 1; i < k; i++) {
        int x;
        if (rnd.next() < clusterProb) {
            int d = rnd.next(1, max(1, n - 1));
            int lo = max(1, prev - d);
            int hi = min(n, prev + d);
            x = rnd.next(lo, hi);
        } else {
            x = rnd.next(1, n);
        }
        seq.push_back(x);
        prev = x;
    }
    // Output
    println(n);
    println(a, b);
    println(k);
    for (int x : seq) println(x);
    return 0;
}
