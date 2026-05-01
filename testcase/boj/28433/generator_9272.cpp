#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: mostly small, sometimes just 1
    int T;
    if (rnd.next(0, 4) == 0) T = 1;
    else T = rnd.next(4, 8);

    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int type = rnd.next(0, 9);
        int N;
        vector<long long> A;

        switch (type) {
            case 0: { // Single element: various extremes
                N = 1;
                int c = rnd.next(0, 4);
                long long val;
                if (c == 0) val = 0;
                else if (c == 1) val = 1;
                else if (c == 2) val = -1;
                else if (c == 3) val = 1000000000LL;
                else val = -1000000000LL;
                A.push_back(val);
                break;
            }
            case 1: { // Small random array with small values, occasionally big
                N = rnd.next(2, 8);
                A.resize(N);
                for (int i = 0; i < N; ++i) {
                    if (rnd.next(0, 9) == 0) {
                        int c = rnd.next(0, 3);
                        if (c == 0) A[i] = 0;
                        else if (c == 1) A[i] = 1000000000LL;
                        else A[i] = -1000000000LL;
                    } else {
                        A[i] = rnd.next(-5, 5);
                    }
                }
                break;
            }
            case 2: { // All positive
                N = rnd.next(1, 10);
                A.resize(N);
                for (int i = 0; i < N; ++i)
                    A[i] = rnd.next(1, 5);
                break;
            }
            case 3: { // All negative
                N = rnd.next(1, 10);
                A.resize(N);
                for (int i = 0; i < N; ++i)
                    A[i] = -rnd.next(1, 5);
                break;
            }
            case 4: { // Alternating starting positive
                N = rnd.next(2, 12);
                A.resize(N);
                for (int i = 0; i < N; ++i) {
                    if (i % 2 == 0) A[i] = rnd.next(1, 5);
                    else A[i] = -rnd.next(1, 5);
                }
                break;
            }
            case 5: { // Alternating starting negative
                N = rnd.next(2, 12);
                A.resize(N);
                for (int i = 0; i < N; ++i) {
                    if (i % 2 == 0) A[i] = -rnd.next(1, 5);
                    else A[i] = rnd.next(1, 5);
                }
                break;
            }
            case 6: { // Many zeros mixed with positives and negatives
                N = rnd.next(3, 12);
                A.resize(N);
                for (int i = 0; i < N; ++i) {
                    int c = rnd.next(0, 2);
                    if (c == 0) A[i] = 0;
                    else if (c == 1) A[i] = rnd.next(1, 5);
                    else A[i] = -rnd.next(1, 5);
                }
                break;
            }
            case 7: { // Balanced pairs x, -x, with possible zeros
                vector<long long> tmp;
                while ((int)tmp.size() < 4) {
                    int pairs = rnd.next(1, 3);
                    for (int p = 0; p < pairs; ++p) {
                        long long x = rnd.next(1, 5);
                        tmp.push_back(x);
                        tmp.push_back(-x);
                        if ((int)tmp.size() >= 10) break;
                    }
                    if ((int)tmp.size() >= 10) break;
                }
                // Insert some zeros randomly
                for (int i = 0; i < (int)tmp.size(); ++i) {
                    if (rnd.next(0, 6) == 0) {
                        // insert zero before tmp[i]
                        A.push_back(0);
                    }
                    A.push_back(tmp[i]);
                    if ((int)A.size() >= 12) break;
                }
                if ((int)A.size() < 3) {
                    // Fallback in very rare case
                    A = tmp;
                }
                if ((int)A.size() > 12) A.resize(12);
                N = (int)A.size();
                break;
            }
            case 8: { // Large magnitude values and zeros
                N = rnd.next(2, 7);
                A.resize(N);
                for (int i = 0; i < N; ++i) {
                    int c = rnd.next(0, 4);
                    if (c == 0) A[i] = 1000000000LL;
                    else if (c == 1) A[i] = -1000000000LL;
                    else if (c == 2) A[i] = 999999999LL;
                    else if (c == 3) A[i] = -999999999LL;
                    else A[i] = 0;
                }
                break;
            }
            case 9: { // Repetitive simple patterns
                int patternType = rnd.next(0, 2);
                if (patternType == 0) {
                    // [1, -1, 1, -1, ...]
                    N = rnd.next(2, 12);
                    A.resize(N);
                    for (int i = 0; i < N; ++i)
                        A[i] = (i % 2 == 0 ? 1 : -1);
                } else if (patternType == 1) {
                    // [2, -2, -2, 2] repeated
                    vector<long long> base = {2, -2, -2, 2};
                    int reps = rnd.next(1, 3);
                    for (int r = 0; r < reps; ++r) {
                        for (long long v : base)
                            A.push_back(v);
                    }
                    if ((int)A.size() > 12) A.resize(12);
                    N = (int)A.size();
                } else {
                    // mix of [3, -1, -2] pattern
                    vector<long long> base = {3, -1, -2};
                    int reps = rnd.next(1, 4);
                    for (int r = 0; r < reps; ++r) {
                        for (long long v : base)
                            A.push_back(v);
                    }
                    if ((int)A.size() > 12) A.resize(12);
                    N = (int)A.size();
                }
                break;
            }
        }

        // Safety: ensure 1 <= N
        if (N <= 0) {
            N = 1;
            A.assign(1, 0);
        }

        println(N);
        println(A);
    }

    return 0;
}
