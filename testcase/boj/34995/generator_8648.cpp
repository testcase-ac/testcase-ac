#include "testlib.h"
using namespace std;

string randomA(int len) {
    // General A: first digit 1..9, others 0..9
    string a(len, '0');
    a[0] = char('1' + rnd.next(0, 8)); // 1..9
    for (int i = 1; i < len; ++i)
        a[i] = char('0' + rnd.next(0, 9)); // 0..9
    return a;
}

string randomA_nozero(int len) {
    // A with all digits 1..9 (used when we copy digits into coupon string)
    string a(len, '1');
    for (int i = 0; i < len; ++i)
        a[i] = char('1' + rnd.next(0, 8)); // 1..9
    return a;
}

string randomPattern(int n) {
    string s(n, '?');
    for (int i = 0; i < n; ++i) {
        // roughly 1/3 '?' and 2/3 digits
        if (rnd.next(0, 2) == 0) {
            s[i] = '?';
        } else {
            s[i] = char('1' + rnd.next(0, 8)); // 1..9
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);
    int N, lenA;
    string S, A;

    switch (scenario) {
        // 0: all '?' with equal length, always satisfiable
        case 0: {
            N = rnd.next(1, 30);
            lenA = N;
            S.assign(N, '?');
            A = randomA(lenA);
            break;
        }
        // 1: N < len(A), always unsatisfiable
        case 1: {
            N = rnd.next(1, 20);
            lenA = rnd.next(N + 1, min(N + 10, 80));
            S = randomPattern(N);
            A = randomA(lenA);
            break;
        }
        // 2: N > len(A), always satisfiable
        case 2: {
            lenA = rnd.next(1, 20);
            int maxN = min(lenA + 10, 80);
            N = rnd.next(lenA + 1, maxN);
            S = randomPattern(N);
            A = randomA(lenA);
            break;
        }
        // 3: N == len(A), craft equal-length unsatisfiable (first mismatch smaller)
        case 3: {
            N = rnd.next(1, 60);
            lenA = N;

            // Use only digits 1..9 here so copying into S never creates '0'
            A = randomA_nozero(N);

            // ensure there is at least one position with A[i] >= '2'
            bool hasPos = false;
            for (int i = 0; i < N; ++i)
                if (A[i] > '1')
                    hasPos = true;
            if (!hasPos) {
                int i = rnd.next(0, N - 1);
                A[i] = '2';
            }

            vector<int> cand;
            for (int i = 0; i < N; ++i)
                if (A[i] > '1')
                    cand.push_back(i);
            int p = rnd.any(cand); // position where we will make coupon digit smaller

            S.assign(N, '?');
            for (int i = 0; i < p; ++i)
                S[i] = A[i]; // equal prefix, all in '1'..'9'

            int hiDigit = (A[p] - '0') - 1; // at least 1, since A[p] >= '2'
            int newDigit = rnd.next(1, hiDigit); // 1..A[p]-1
            S[p] = char('0' + newDigit);

            for (int i = p + 1; i < N; ++i) {
                if (rnd.next(0, 1) == 0)
                    S[i] = '?';
                else
                    S[i] = char('1' + rnd.next(0, 8)); // 1..9
            }
            break;
        }
        // 4: N == len(A), satisfiable with mixed '?' and fixed digits
        case 4: {
            N = rnd.next(1, 60);
            lenA = N;

            string C(N, '1');
            for (int i = 0; i < N; ++i)
                C[i] = char('1' + rnd.next(0, 8)); // coupon witness digits (1..9)

            S.assign(N, '?');
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 2) == 0)
                    S[i] = '?';
                else
                    S[i] = C[i]; // always 1..9
            }

            A = C; // start with A == C

            // With some probability, make A strictly smaller while keeping same length
            if (rnd.next(0, 1) == 0) {
                vector<int> cand;
                if (C[0] > '1') cand.push_back(0); // can decrease but keep first digit non-zero
                for (int i = 1; i < N; ++i)
                    cand.push_back(i); // any non-first position ok

                if (!cand.empty()) {
                    int q = rnd.any(cand);
                    int hi = (C[q] - '0') - 1;
                    int lo = (q == 0 ? 1 : 0);
                    if (hi >= lo) {
                        int newd = rnd.next(lo, hi);
                        A[q] = char('0' + newd);
                        for (int i = q + 1; i < N; ++i)
                            A[i] = char('0' + rnd.next(0, 9));
                    }
                }
            }
            break;
        }
        // 5: N == len(A), no '?' (fully fixed coupon), sat or unsat
        case 5: {
            N = rnd.next(1, 60);
            lenA = N;
            bool sat = rnd.next(0, 1) == 0;

            string B(N, '1');
            for (int i = 0; i < N; ++i)
                B[i] = char('1' + rnd.next(0, 8)); // digits 1..9
            S = B;

            if (sat) {
                // Make A <= B
                A = B;
                if (rnd.next(0, 1) == 0) {
                    vector<int> cand;
                    if (B[0] > '1') cand.push_back(0);
                    for (int i = 1; i < N; ++i)
                        cand.push_back(i);

                    if (!cand.empty()) {
                        int q = rnd.any(cand);
                        int hi = (B[q] - '0') - 1;
                        int lo = (q == 0 ? 1 : 0);
                        if (hi >= lo) {
                            int newd = rnd.next(lo, hi);
                            A[q] = char('0' + newd);
                            for (int i = q + 1; i < N; ++i)
                                A[i] = char('0' + rnd.next(0, 9));
                        }
                    }
                }
            } else {
                // Make A > B with same length
                // Ensure B is not all '9'
                bool all9 = true;
                for (int i = 0; i < N; ++i)
                    if (B[i] != '9') { all9 = false; break; }
                if (all9) {
                    int pos = rnd.next(0, N - 1);
                    B[pos] = '8';
                    S = B;
                }

                vector<int> cand;
                for (int i = 0; i < N; ++i)
                    if (B[i] < '9') cand.push_back(i);

                int p = rnd.any(cand);
                A.assign(N, '0');
                for (int i = 0; i < p; ++i)
                    A[i] = B[i];
                int newd = rnd.next(B[p] - '0' + 1, 9);
                A[p] = char('0' + newd);
                for (int i = p + 1; i < N; ++i)
                    A[i] = char('0' + rnd.next(0, 9));
            }
            break;
        }
    }

    println(N, S);
    println(A);
    return 0;
}
