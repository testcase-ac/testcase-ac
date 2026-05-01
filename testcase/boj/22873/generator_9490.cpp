#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with some variability, but keep it small.
    int modeN = rnd.next(0, 4);
    int N;
    if (modeN == 0) N = 1;
    else if (modeN == 1) N = rnd.next(2, 5);
    else if (modeN == 2) N = rnd.next(6, 10);
    else if (modeN == 3) N = rnd.next(11, 15);
    else N = rnd.next(16, 20);

    // Choose Q similarly small.
    int modeQ = rnd.next(0, 3);
    int Q;
    if (modeQ == 0) Q = rnd.next(1, 5);
    else if (modeQ == 1) Q = rnd.next(6, 10);
    else Q = rnd.next(11, 20);

    vector<int> a(N), b(N);

    // Choose pattern type for A and B.
    int pattern = rnd.next(0, 3); // 0: no-carry, 1: many-carry, 2: random, 3: structured
    if (pattern == 0) {
        // No-carry: ensure a[i] + b[i] <= 8
        for (int i = 0; i < N; i++) {
            int s = rnd.next(0, 8);
            int ai = rnd.next(0, s);
            int bi = s - ai;
            a[i] = ai;
            b[i] = bi;
        }
    } else if (pattern == 1) {
        // Many carries: a[i] + b[i] >= 10
        for (int i = 0; i < N; i++) {
            int s = rnd.next(10, 18);
            int lo = max(0, s - 9);
            int hi = min(9, s);
            int ai = rnd.next(lo, hi);
            int bi = s - ai;
            a[i] = ai;
            b[i] = bi;
        }
    } else if (pattern == 2) {
        // Completely random digits
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(0, 9);
            b[i] = rnd.next(0, 9);
        }
    } else {
        // Structured patterns
        int sub = rnd.next(0, 2);
        if (sub == 0) {
            // A all 9s, B mostly zeros
            for (int i = 0; i < N; i++) {
                a[i] = 9;
                if (rnd.next(0, 3) == 0) b[i] = rnd.next(0, 9);
                else b[i] = 0;
            }
        } else if (sub == 1) {
            // A all 0s, B random
            for (int i = 0; i < N; i++) {
                a[i] = 0;
                b[i] = rnd.next(0, 9);
            }
        } else {
            // A and B equal
            for (int i = 0; i < N; i++) {
                int d = rnd.next(0, 9);
                a[i] = b[i] = d;
            }
        }
    }

    // Optionally add leading zeros.
    if (rnd.next(0, 2) == 0) {
        int maxZero = min(N, 3);
        int k = rnd.next(1, maxZero);
        for (int i = 0; i < k; i++) {
            a[i] = 0;
        }
    }
    if (rnd.next(0, 2) == 0) {
        int maxZero = min(N, 3);
        int k = rnd.next(1, maxZero);
        for (int i = 0; i < k; i++) {
            b[i] = 0;
        }
    }

    string A, B;
    A.reserve(N);
    B.reserve(N);
    for (int i = 0; i < N; i++) {
        A.push_back(char('0' + a[i]));
        B.push_back(char('0' + b[i]));
    }

    // Prepare queries.
    vector<char> type(Q);
    vector<int> idx(Q);
    vector<int> digit(Q);

    vector<int> aCurr = a, bCurr = b;

    // Ensure at least one query that doesn't change anything.
    {
        char t = (rnd.next(0, 1) == 0 ? 'A' : 'B');
        int iPos = rnd.next(1, N);
        int pos = N - iPos;
        int cur = (t == 'A' ? aCurr[pos] : bCurr[pos]);
        type[0] = t;
        idx[0] = iPos;
        digit[0] = cur; // no change
    }

    int qPattern = rnd.next(0, 3);

    for (int qi = 1; qi < Q; qi++) {
        char t;
        int iPos;
        int d;

        if (qPattern == 0) {
            // Pure random queries.
            t = (rnd.next(0, 1) == 0 ? 'A' : 'B');
            iPos = rnd.next(1, N);
            d = rnd.next(0, 9);
        } else if (qPattern == 1) {
            // Focus on one hot position.
            static char mainType = (rnd.next(0, 1) == 0 ? 'A' : 'B');
            static int mainIdx = rnd.next(1, N);
            if (rnd.next(0, 2) != 0) {
                t = mainType;
                iPos = mainIdx;
            } else {
                t = (rnd.next(0, 1) == 0 ? 'A' : 'B');
                iPos = rnd.next(1, N);
            }
            d = rnd.next(0, 9);
        } else if (qPattern == 2) {
            // Sweep positions sequentially.
            t = (rnd.next(0, 1) == 0 ? 'A' : 'B');
            iPos = (qi % N) + 1;
            d = rnd.next(0, 9);
        } else {
            // Toggle between two digits on a fixed position, with some random noise.
            static bool init = false;
            static char mainType;
            static int mainIdx;
            static int d1, d2;
            static int toggleState;
            if (!init) {
                mainType = (rnd.next(0, 1) == 0 ? 'A' : 'B');
                mainIdx = rnd.next(1, N);
                d1 = rnd.next(0, 9);
                do {
                    d2 = rnd.next(0, 9);
                } while (d2 == d1);
                toggleState = 0;
                init = true;
            }
            if (rnd.next(0, 3) != 0) {
                t = mainType;
                iPos = mainIdx;
                d = (toggleState ? d1 : d2);
                toggleState ^= 1;
            } else {
                t = (rnd.next(0, 1) == 0 ? 'A' : 'B');
                iPos = rnd.next(1, N);
                d = rnd.next(0, 9);
            }
        }

        type[qi] = t;
        idx[qi] = iPos;
        digit[qi] = d;

        int pos = N - iPos;
        if (t == 'A') aCurr[pos] = d;
        else bCurr[pos] = d;
    }

    // Output the generated test case.
    println(N, Q);
    println(A);
    println(B);
    for (int i = 0; i < Q; i++) {
        printf("%c %d %d\n", type[i], idx[i], digit[i]);
    }

    return 0;
}
