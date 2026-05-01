#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 6); // choose scenario type
    int N;
    vector<int> swifts, sems;

    if (type == 6) {
        // Special small case: N = 1, sometimes equal, sometimes not
        N = 1;
        swifts.resize(1);
        sems.resize(1);
        bool equal = rnd.next(0, 1);
        if (equal) {
            int val = rnd.next(0, 20);
            swifts[0] = val;
            sems[0] = val;
        } else {
            swifts[0] = rnd.next(0, 20);
            do {
                sems[0] = rnd.next(0, 20);
            } while (sems[0] == swifts[0]);
        }
    } else if (type == 0) {
        // Completely random arrays
        int bucket = rnd.next(0, 9);
        if (bucket < 4)
            N = rnd.next(1, 5);
        else if (bucket < 8)
            N = rnd.next(6, 15);
        else
            N = rnd.next(16, 25);

        swifts.resize(N);
        sems.resize(N);
        for (int i = 0; i < N; i++) {
            swifts[i] = rnd.next(0, 20);
            sems[i] = rnd.next(0, 20);
        }
    } else {
        // Use difference pattern e[i] = swifts[i] - sems[i]
        vector<int> e;

        if (type == 1) {
            // Always equal after every day
            int bucket = rnd.next(0, 9);
            if (bucket < 4)
                N = rnd.next(1, 5);
            else if (bucket < 8)
                N = rnd.next(6, 15);
            else
                N = rnd.next(16, 25);
            e.assign(N, 0);
        } else if (type == 2) {
            // Never equal after any day: diff strictly positive and growing
            int bucket = rnd.next(0, 9);
            if (bucket < 4)
                N = rnd.next(1, 5);
            else if (bucket < 8)
                N = rnd.next(6, 15);
            else
                N = rnd.next(16, 25);
            e.assign(N, 1); // prefix diffs: 1, 2, 3, ...
        } else if (type == 3) {
            // Equal only at the end (K = N), not before
            N = rnd.next(2, 21); // ensure last step magnitude <= 20
            e.assign(N, 1);
            e[N - 1] = -(N - 1); // prefix diffs: 1..N-1, then 0
        } else if (type == 4) {
            // Equal at some middle K0 < N but not at N
            int bucket = rnd.next(0, 9);
            if (bucket < 4)
                N = rnd.next(3, 5);
            else if (bucket < 8)
                N = rnd.next(6, 15);
            else
                N = rnd.next(16, 25);
            e.assign(N, 0);
            int upperK0 = min(N - 1, 21);
            int k0 = rnd.next(2, upperK0);
            for (int i = 0; i < k0 - 1; i++)
                e[i] = 1;
            e[k0 - 1] = -(k0 - 1); // makes prefix diff 0 at k0
            for (int i = k0; i < N; i++)
                e[i] = 1; // diff moves away from 0 afterwards
        } else if (type == 5) {
            // Many equal prefixes: pattern +1, -1, +1, -1, ... then tail of +1
            int bucket = rnd.next(0, 9);
            if (bucket < 4)
                N = rnd.next(4, 6);
            else if (bucket < 8)
                N = rnd.next(7, 15);
            else
                N = rnd.next(16, 25);
            e.assign(N, 0);
            int maxK = (N - 1) / 2; // ensure 2k <= N-1 so tail has length >= 1
            int k;
            if (rnd.next(0, 1) == 0)
                k = maxK;
            else
                k = rnd.next(1, maxK);
            for (int j = 0; j < k; j++) {
                e[2 * j] = 1;
                e[2 * j + 1] = -1; // diff hits 0 at days 2,4,...,2k
            }
            for (int i = 2 * k; i < N; i++)
                e[i] = 1; // final diff > 0, no more equalities
        }

        // Convert difference pattern e[i] to valid scores 0..20
        swifts.resize(N);
        sems.resize(N);
        for (int i = 0; i < N; i++) {
            int diff = e[i]; // swifts[i] - sems[i]
            // sems[i] in [max(0, -diff), min(20, 20 - diff)]
            int low = max(0, -diff);
            int high = min(20, 20 - diff);
            int s2 = rnd.next(low, high);
            int s1 = s2 + diff;
            sems[i] = s2;
            swifts[i] = s1;
        }
    }

    println(N);
    println(swifts);
    println(sems);

    return 0;
}
