#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small to medium N for manual verification
    int N = rnd.next(4, 12);
    vector<pair<int,int>> edges;
    // Hyper-parameter: choose tree shape
    int t = rnd.next(1,5);
    if (t == 1) {
        // Path
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i+1);
    } else if (t == 2) {
        // Star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++)
            if (i != center)
                edges.emplace_back(center, i);
    } else if (t == 3) {
        // Random tree by linking to a random previous node
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    } else if (t == 4) {
        // Complete binary tree structure
        for (int i = 2; i <= N; i++)
            edges.emplace_back(i/2, i);
    } else {
        // Caterpillar: a path with leaves hanging off
        int spine = rnd.next(2, N-2);
        // Build spine
        for (int i = 1; i < spine; i++)
            edges.emplace_back(i, i+1);
        // Attach remaining leaves
        for (int v = spine+1; v <= N; v++) {
            int attach = rnd.next(1, spine);
            edges.emplace_back(attach, v);
        }
    }
    // Shuffle edges for randomness
    shuffle(edges.begin(), edges.end());
    // Select distinct A, B
    int A = rnd.next(1, N);
    int B = rnd.next(1, N);
    while (B == A) B = rnd.next(1, N);
    // Output
    println(N, A, B);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
