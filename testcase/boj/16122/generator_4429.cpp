#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N in [0,10], biased by rnd.wnext
    vector<int> bias = {-2, -1, 0, 1, 2};
    int t = rnd.any(bias);
    int N = rnd.wnext(11, t); // generates 0..10

    // Compute reachable values from 0 in exactly i operations
    vector<vector<int>> reachable(N+1);
    set<int> prev;
    prev.insert(0);
    reachable[0] = vector<int>(prev.begin(), prev.end());
    for (int i = 1; i <= N; i++) {
        set<int> curr;
        for (int x : prev) {
            curr.insert(-x);
            curr.insert(~x); // ~x = -x-1
        }
        reachable[i] = vector<int>(curr.begin(), curr.end());
        prev = move(curr);
    }

    // Pick M randomly from reachable[N]
    int M = rnd.any(reachable[N]);

    // Output
    println(N, M);
    return 0;
}
