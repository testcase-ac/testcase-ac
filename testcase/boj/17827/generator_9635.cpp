#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose structure type for variability
    int type = rnd.next(0, 4);

    int N, V;
    if (type == 0) {
        // Minimal case
        N = 2;
        V = 2; // self-loop at N
    } else if (type == 1) {
        // Small N, arbitrary cycle
        N = rnd.next(3, 8);
        V = rnd.next(2, N);
    } else if (type == 2) {
        // Medium N, long cycle (V small)
        N = rnd.next(10, 20);
        V = rnd.next(2, 4); // cycle starts early
    } else if (type == 3) {
        // Medium N, short cycle (V near end)
        N = rnd.next(10, 20);
        int low = max(2, N - 3);
        V = rnd.next(low, N);
    } else {
        // Fully random within limits
        N = rnd.next(2, 20);
        V = rnd.next(2, N);
    }

    // Adjust V if it ever became invalid (safety, though above logic keeps it valid)
    if (V < 2) V = 2;
    if (V > N) V = N;

    long long pathLen = N - 1;        // steps from 1 to N
    long long cycleLen = N - V + 1;   // length of the cycle (V..N)

    // Generate node values
    vector<int> C(N + 1);
    int valType = rnd.next(0, 3);
    if (valType == 0) {
        // Sequential
        for (int i = 1; i <= N; i++) C[i] = i;
    } else if (valType == 1) {
        // All equal
        int x = rnd.next(1, 5);
        for (int i = 1; i <= N; i++) C[i] = x;
    } else if (valType == 2) {
        // Small random
        for (int i = 1; i <= N; i++) C[i] = rnd.next(1, 10);
    } else {
        // Mixed: path part small, cycle part large
        for (int i = 1; i <= N; i++) {
            if (i < V) C[i] = rnd.next(1, 20);
            else C[i] = rnd.next(500000, 1000000);
        }
    }

    // Prepare queries
    vector<long long> Q;
    auto addK = [&](long long k) {
        if (k >= 1 && k <= 1000000000LL)
            Q.push_back(k);
    };

    // Targeted queries for common pitfalls
    addK(1);                         // first step
    if (pathLen >= 2) addK(2);       // small K
    if (pathLen >= 1) addK(pathLen); // at node N
    addK(pathLen + 1);               // first node in the cycle (V)
    addK(pathLen + cycleLen);        // full cycle back to N
    addK(pathLen + cycleLen + 1);    // N -> V after one cycle
    addK(1000000000LL);              // maximum K

    if (cycleLen > 0) {
        long long bigMult = (1000000000LL - pathLen) / cycleLen;
        if (bigMult > 1) {
            long long t = rnd.next(1LL, bigMult);
            long long offset = rnd.next(0LL, cycleLen - 1);
            addK(pathLen + t * cycleLen + offset); // huge K aligning with cycle
        }
    }

    // Decide final M
    int minM = (int)max<size_t>(1, Q.size());
    int M = rnd.next(minM, 20);

    // Fill with additional random queries
    while ((int)Q.size() < M) {
        long long k;
        if (rnd.next(0, 1) == 0) {
            // Prefer small-ish K around path and first few cycles
            long long hi = pathLen + 2LL * cycleLen + 5;
            if (hi < 1) hi = 1;
            if (hi > 1000000000LL) hi = 1000000000LL;
            int hiInt = (int)hi;
            k = rnd.next(1, hiInt);
        } else {
            // Arbitrary large K
            k = rnd.next(1, 1000000000);
        }
        addK(k);
    }

    // Trim in case we went slightly over (shouldn't, but safe)
    if ((int)Q.size() > M) Q.resize(M);

    // Shuffle queries to randomize order
    shuffle(Q.begin(), Q.end());

    // Output
    println(N, M, V);

    vector<int> outC(N);
    for (int i = 1; i <= N; i++) outC[i - 1] = C[i];
    println(outC);

    for (int i = 0; i < M; i++)
        println(Q[i]);

    return 0;
}
