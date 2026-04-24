#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checkable cases
    int N = rnd.next(1, 10);

    // Decide generation type for diversity
    double t = rnd.next(0.0, 1.0);
    vector<int> p(N);
    for (int i = 0; i < N; i++) p[i] = i + 1;

    if (t < 0.2) {
        // identity: 1,2,3,...
    } else if (t < 0.4) {
        // reverse
        reverse(p.begin(), p.end());
    } else if (t < 0.6) {
        // nearly sorted: a few random swaps
        int swaps = rnd.next(1, max(1, N/2));
        for (int i = 0; i < swaps; i++) {
            int x = rnd.next(0, N-1);
            int y = rnd.next(0, N-1);
            swap(p[x], p[y]);
        }
    } else {
        // fully random
        shuffle(p.begin(), p.end());
    }

    // Compute A[i]: for each value i (1..N), count larger before it
    vector<int> pos(N+1);
    for (int idx = 0; idx < N; idx++) {
        pos[p[idx]] = idx;
    }
    vector<int> A(N+1, 0);
    for (int i = 1; i <= N; i++) {
        int idx = pos[i];
        int cnt = 0;
        for (int j = 0; j < idx; j++) {
            if (p[j] > i) cnt++;
        }
        A[i] = cnt;
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        println(A[i]);
    }
    return 0;
}
