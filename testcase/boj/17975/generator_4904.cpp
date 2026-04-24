#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int n1 = rnd.next(1, 5);
    int n2 = rnd.next(1, 5);
    int N = n1 + n2;

    // Prepare distinct coordinates in a small range
    vector<int> xs, ys;
    for (int v = -10; v <= 10; ++v) {
        xs.push_back(v);
        ys.push_back(v);
    }
    shuffle(xs.begin(), xs.end());
    shuffle(ys.begin(), ys.end());
    xs.resize(N);
    ys.resize(N);

    // Pair x and y randomly
    // After shuffling both, pairing by index gives a random matching
    vector<pair<int,int>> pts(N);
    for (int i = 0; i < N; ++i) {
        pts[i] = { xs[i], ys[i] };
    }
    // Shuffle the points so P1 and P2 get mixed
    shuffle(pts.begin(), pts.end());

    // Cost parameters
    int c1 = rnd.next(1, 10);
    int c2 = rnd.next(1, 10);

    // Output in required format
    println(n1);
    for (int i = 0; i < n1; ++i) {
        println(pts[i].first, pts[i].second);
    }
    println(n2);
    for (int i = n1; i < N; ++i) {
        println(pts[i].first, pts[i].second);
    }
    println(c1, c2);

    return 0;
}
