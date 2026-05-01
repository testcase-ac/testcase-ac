#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias toward small/medium
    int nType = rnd.next(0, 2);
    int N;
    if (nType == 0) N = rnd.next(1, 3);
    else if (nType == 1) N = rnd.next(4, 10);
    else N = rnd.next(11, 15);

    // Choose M with bias toward having some queries but keeping input compact
    int mType = rnd.next(0, 2);
    int M;
    if (mType == 0) M = rnd.next(1, 5);
    else if (mType == 1) M = rnd.next(6, 15);
    else M = rnd.next(16, 20);

    vector<long long> A(N);

    // Choose pattern for initial array
    int pattern = rnd.next(0, 5);
    if (pattern == 0) {
        // Random small values
        for (int i = 0; i < N; ++i)
            A[i] = rnd.next(1, 20);
    } else if (pattern == 1) {
        // All equal
        int choice = rnd.next(0, 2);
        long long val;
        if (choice == 0) val = 1;
        else if (choice == 1) val = rnd.next(2, 20);
        else val = 1000000000LL;
        for (int i = 0; i < N; ++i)
            A[i] = val;
    } else if (pattern == 2) {
        // Strictly increasing
        long long base = rnd.next(1, 20);
        long long step = rnd.next(1, 5);
        for (int i = 0; i < N; ++i)
            A[i] = base + step * i;
    } else if (pattern == 3) {
        // Strictly decreasing
        long long base = rnd.next(30, 60);
        long long step = rnd.next(1, 5);
        for (int i = 0; i < N; ++i)
            A[i] = base - step * i;
        for (int i = 0; i < N; ++i)
            if (A[i] < 1) A[i] = 1;
    } else if (pattern == 4) {
        // Unique minimum at random position
        long long minVal = rnd.next(1, 10);
        int pos = rnd.next(0, N - 1);
        for (int i = 0; i < N; ++i) {
            if (i == pos) A[i] = minVal;
            else A[i] = minVal + rnd.next(1, 15);
        }
    } else {
        // Many duplicates with multiple minima
        vector<long long> pool;
        pool.push_back(1);
        pool.push_back(2);
        pool.push_back(3);
        for (int i = 0; i < N; ++i)
            A[i] = rnd.any(pool);
        // Ensure at least two minima
        if (N >= 2) {
            A[0] = 1;
            A[N - 1] = 1;
        } else {
            A[0] = 1;
        }
    }

    // Output N and initial array
    println(N);
    println(A);

    // Prepare query types
    vector<int> qtype(M, 1);
    int cntType2 = 0;
    for (int i = 0; i < M; ++i) {
        // 40% chance to be type 2
        if (rnd.next(0, 99) < 40) {
            qtype[i] = 2;
            cntType2++;
        } else {
            qtype[i] = 1;
        }
    }
    // Ensure at least one type 2 query
    if (cntType2 == 0) {
        int pos = rnd.next(0, M - 1);
        qtype[pos] = 2;
        cntType2 = 1;
    }
    // Sometimes force first query to be type 2 to test initial state
    if (rnd.next(0, 1) == 0)
        qtype[0] = 2;

    println(M);

    // Generate and output queries, updating A for realism
    for (int qi = 0; qi < M; ++qi) {
        if (qtype[qi] == 2) {
            println(2);
        } else {
            int idx = rnd.next(1, N); // 1-based index
            long long v;
            int mode = rnd.next(0, 4);
            if (mode == 0) {
                v = 1; // smallest possible
            } else if (mode == 1) {
                v = 1000000000LL; // largest possible
            } else if (mode == 2) {
                v = rnd.next(1, 20); // small range
            } else if (mode == 3) {
                v = rnd.next(1, 1000000000); // full range
            } else {
                // Near current value at idx
                long long cur = A[idx - 1];
                int delta = rnd.next(-5, 5);
                long long cand = cur + delta;
                if (cand < 1) cand = 1;
                if (cand > 1000000000LL) cand = 1000000000LL;
                v = cand;
            }
            A[idx - 1] = v;
            println(1, idx, v);
        }
    }

    return 0;
}
