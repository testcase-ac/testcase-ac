#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);

    // Keep overall input small and readable
    const int MAX_TOTAL_STUDENTS = 20;
    int remainingStudents = MAX_TOTAL_STUDENTS;

    vector<int> N(T);
    vector<long long> maxVal(T);

    for (int t = 0; t < T; ++t) {
        int remainingTests = T - t;
        int maxAllowedN = remainingStudents - (remainingTests - 1); // at least 1 for each future test
        if (maxAllowedN < 1) maxAllowedN = 1;

        int scalePick = rnd.next(0, 99);
        int capN;
        if (scalePick < 50) {               // small values
            capN = 20;
        } else if (scalePick < 80) {        // medium values
            capN = 12;
        } else {                            // fewer but large values
            capN = 5;
        }
        capN = min(capN, maxAllowedN);
        if (capN < 1) capN = 1;

        int n = rnd.next(1, capN);
        N[t] = n;
        remainingStudents -= n;

        // Assign maxVal based on scale
        if (scalePick < 50) {
            maxVal[t] = rnd.next(10LL, 10000LL);
        } else if (scalePick < 80) {
            maxVal[t] = rnd.next(1000000LL, 100000000000LL); // 1e6 .. 1e11
        } else {
            maxVal[t] = rnd.next(1000000000000000LL, 1000000000000000000LL); // 1e15 .. 1e18
        }
    }

    // Decide which testcases should be YES / NO
    vector<bool> isYes(T);
    vector<int> gt1Indices;
    for (int i = 0; i < T; ++i) {
        if (N[i] > 1) gt1Indices.push_back(i);
    }

    if (T == 1 || gt1Indices.empty()) {
        // Only YES is logically possible (if all N == 1 and we want to be safe)
        for (int i = 0; i < T; ++i) isYes[i] = true;
    } else {
        // Ensure at least one YES and one NO, with NO having N > 1
        int idxNo = rnd.any(gt1Indices);
        int idxYes;
        do {
            idxYes = rnd.next(0, T - 1);
        } while (idxYes == idxNo);

        for (int i = 0; i < T; ++i) {
            isYes[i] = (rnd.next(0, 1) == 1);
        }
        isYes[idxNo] = false;
        isYes[idxYes] = true;
    }

    // Output
    println(T);
    println(""); // blank line before first test

    for (int t = 0; t < T; ++t) {
        int n = N[t];
        long long MV = maxVal[t];
        vector<long long> a(n, 0);

        bool makeYes = isYes[t] || (n == 1); // N==1 must be YES logically

        if (makeYes) {
            int pattern = rnd.next(0, 2); // 0,1,2

            if (pattern == 0) {
                // All equal
                long long k = rnd.next(0LL, MV);
                for (int i = 0; i < n; ++i) a[i] = k;
            } else if (pattern == 1) {
                // Random numbers, adjust last to make sum % n == 0
                __int128 sum = 0;
                for (int i = 0; i < n - 1; ++i) {
                    a[i] = rnd.next(0LL, MV / 2 + 1);
                    sum += a[i];
                }
                long long r = (long long)(sum % n);
                int need = (int)((n - r) % n); // 0..n-1
                long long base = need;
                long long maxK = (MV >= base) ? (MV - base) / n : -1;
                if (maxK < 0) {
                    // Fallback: all equal
                    long long k = rnd.next(0LL, MV);
                    for (int i = 0; i < n; ++i) a[i] = k;
                } else {
                    long long k = rnd.next(0LL, maxK);
                    a[n - 1] = base + k * n;
                }
            } else {
                // Mostly zeros, one multiple of n
                for (int i = 0; i < n; ++i) a[i] = 0;
                long long qMax = (n > 0) ? (MV / n) : 0;
                long long q = 0;
                if (qMax > 0) q = rnd.next(0LL, qMax);
                int idx = rnd.next(0, n - 1);
                a[idx] = q * n;
            }
        } else {
            // Make NO case: sum % n != 0 (n >= 2 here)
            int pattern = rnd.next(0, 1);

            if (pattern == 0) {
                // Start from a YES pattern and tweak one value
                __int128 sum = 0;
                for (int i = 0; i < n - 1; ++i) {
                    a[i] = rnd.next(0LL, MV / 2 + 1);
                    sum += a[i];
                }
                long long r = (long long)(sum % n);
                int need = (int)((n - r) % n);
                long long base = need;
                long long maxK = (MV >= base) ? (MV - base) / n : -1;
                if (maxK < 0) {
                    // Fallback to random
                    sum = 0;
                    for (int i = 0; i < n; ++i) {
                        a[i] = rnd.next(0LL, MV);
                        sum += a[i];
                    }
                } else {
                    long long k = rnd.next(0LL, maxK);
                    a[n - 1] = base + k * n;
                    sum += a[n - 1];
                }

                // Now sum % n == 0 (or close), tweak one element to break divisibility
                int idx = rnd.next(0, n - 1);
                if (a[idx] < MV) {
                    a[idx] += 1;
                } else if (a[idx] > 0) {
                    a[idx] -= 1;
                } else {
                    a[idx] = 1;
                }
            } else {
                // Pure random then adjust last if needed
                __int128 sum = 0;
                for (int i = 0; i < n; ++i) {
                    a[i] = rnd.next(0LL, MV);
                    sum += a[i];
                }
                if ((long long)(sum % n) == 0) {
                    int idx = rnd.next(0, n - 1);
                    if (a[idx] < MV) {
                        a[idx] += 1;
                    } else if (a[idx] > 0) {
                        a[idx] -= 1;
                    } else {
                        a[idx] = 1;
                    }
                }
            }
        }

        println(n);
        for (int i = 0; i < n; ++i) {
            println(a[i]);
        }
        if (t + 1 < T) println(""); // blank line between testcases
    }

    return 0;
}
