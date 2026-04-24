#include "testlib.h"
#include <vector>
using namespace std;

int skew_t;
vector<pair<int,int>> child;

// Build a random binary tree on IDs [l..r], where each bar has two endpoints.
// We choose how many bars go to the left subtree (K) via weighted randomness.
void build(int l, int r) {
    int total = r - l + 1;     // number of bars in this subtree
    int subs = total - 1;      // bars to distribute to children
    if (subs == 0) {
        // Leaf bar: both endpoints are toys
        child[l] = {-1, -1};
        return;
    }
    // K = number of bars in the left subtree, in [0..subs], biased by skew_t
    int hi = subs + 1;  // for rnd.wnext: range [0..hi-1] = [0..subs]
    int K = rnd.wnext(hi, skew_t);
    int leftBars = K;
    int rightBars = subs - K;
    // assign child IDs or -1 for toy
    int leftChild  = leftBars  > 0 ? l + 1       : -1;
    int rightChild = rightBars > 0 ? l + K + 1   : -1;
    child[l] = {leftChild, rightChild};
    // recurse on subranges if there are bars
    if (leftBars  > 0) build(l + 1,     l + K);
    if (rightBars > 0) build(l + K + 1, r);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of bars small and hand-checkable
    int N = rnd.next(1, 10);

    // Hyper-parameter to bias tree shapes: positive => left-heavy, negative => right-heavy
    vector<int> tvals = {-2, -1, 0, 1, 2};
    skew_t = rnd.any(tvals);

    child.assign(N + 1, {0, 0});
    build(1, N);

    // Output
    println(N);
    for (int i = 1; i <= N; ++i) {
        println(child[i].first, child[i].second);
    }
    return 0;
}
