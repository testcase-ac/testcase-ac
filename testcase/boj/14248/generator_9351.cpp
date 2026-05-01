#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);

    if (scenario == 0) {
        // Scenario 0: smallest edge case
        int n = 1;
        vector<int> a(1);
        a[0] = rnd.next(1, 5);
        int s = 1;
        println(n);
        println(a);
        println(s);
    } else if (scenario == 1) {
        // Scenario 1: all jumps are 1, full reachability
        int n = rnd.next(2, 25);
        vector<int> a(n, 1);
        int s = rnd.next(1, n);
        println(n);
        println(a);
        println(s);
    } else if (scenario == 2) {
        // Scenario 2: barrier in the middle (one stone with huge A blocks crossing)
        int n = rnd.next(5, 15);
        vector<int> a(n, 1);
        int b = rnd.next(2, n - 1); // barrier index
        a[b - 1] = n + 5;           // A[b] > n, so from b you can't move
        int s = rnd.next(1, b - 1); // start on the left side
        println(n);
        println(a);
        println(s);
    } else if (scenario == 3) {
        // Scenario 3: random small with mixed jumps
        int n = rnd.next(2, 20);
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            // mix of small and moderately larger jumps
            if (rnd.next(0, 3) == 0)
                a[i] = rnd.next(1, n + 5);       // may be > n, creates dead ends
            else
                a[i] = rnd.next(1, min(20, n));  // within range
        }
        int s = rnd.next(1, n);
        println(n);
        println(a);
        println(s);
    } else if (scenario == 4) {
        // Scenario 4: many isolated stones due to large jumps
        int n = rnd.next(3, 12);
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            if (rnd.next(0, 1) == 0)
                a[i] = rnd.next(1, n);                 // normal jump
            else
                a[i] = rnd.next(n + 1, n + 20);        // always jumps out of bridge
        }
        int s = rnd.next(1, n);
        println(n);
        println(a);
        println(s);
    } else if (scenario == 5) {
        // Scenario 5: fixed tricky directed case (requires mixing directions,
        // and undirected-graph assumptions will overcount reachability)
        int n = 10;
        vector<int> a = {2, 3, 1, 1, 2, 4, 2, 1, 3, 1};
        int s = 5;
        println(n);
        println(a);
        println(s);
    }

    return 0;
}
