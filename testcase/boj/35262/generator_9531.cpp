#include "testlib.h"
using namespace std;

void fill_side(string &s, int l, int r, int K) {
    if (l > r) return;
    int i = l;
    while (i <= r) {
        if (rnd.next(0, 1) == 0) {
            // leave this position as '1'
            i++;
            continue;
        }
        int maxLen = min(K - 1, r - i + 1);
        if (maxLen <= 0) {
            i++;
            continue;
        }
        int len = rnd.next(1, maxLen);
        for (int j = 0; j < len; ++j)
            s[i + j] = '0';
        i += len + 1; // ensure at least one '1' gap
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0, K = 0;
    string s;

    int pattern = rnd.next(0, 7);

    switch (pattern) {
        case 0: {
            // Tiny edge cases
            int sub = rnd.next(0, 2);
            if (sub == 0) {
                N = 1;
                K = 1;
                s = string(1, rnd.next(0, 1) ? '1' : '0');
            } else if (sub == 1) {
                N = 2;
                K = rnd.next(1, 2);
                s.resize(2);
                for (int i = 0; i < 2; ++i)
                    s[i] = rnd.next(0, 1) ? '1' : '0';
            } else {
                N = rnd.next(3, 5);
                K = rnd.next(1, N);
                s.resize(N);
                for (int i = 0; i < N; ++i)
                    s[i] = rnd.next(0, 1) ? '1' : '0';
            }
            break;
        }
        case 1: {
            // All ones (always gets burger)
            bool big = (rnd.next(0, 4) == 0);
            if (big) N = rnd.next(20, 60);
            else N = rnd.next(1, 20);
            K = rnd.next(1, N);
            s = string(N, '1');
            break;
        }
        case 2: {
            // All zeros (never gets burger)
            bool big = (rnd.next(0, 4) == 0);
            if (big) N = rnd.next(20, 60);
            else N = rnd.next(1, 20);
            K = rnd.next(1, N);
            s = string(N, '0');
            break;
        }
        case 3: {
            // Longest zero run exactly K-1 (borderline pass)
            K = rnd.next(2, 10);
            int Nmin = K;
            int Nmax;
            if (rnd.next(0, 3) == 0)
                Nmax = min(100, K + 40);
            else
                Nmax = min(30, K + 20);
            if (Nmax < Nmin) Nmax = Nmin;
            N = rnd.next(Nmin, Nmax);

            s = string(N, '1');
            int runLen = K - 1;
            int stMax = N - runLen;
            int st = rnd.next(0, stMax);
            for (int i = 0; i < runLen; ++i)
                s[st + i] = '0';

            // Fill sides without creating zero runs of length >= K
            if (st - 2 >= 0)
                fill_side(s, 0, st - 2, K);
            if (st + runLen + 1 <= N - 1)
                fill_side(s, st + runLen + 1, N - 1, K);
            break;
        }
        case 4: {
            // Longest zero run exactly K (borderline fail)
            K = rnd.next(1, 10);
            int Nmin = K;
            int Nmax;
            if (rnd.next(0, 3) == 0)
                Nmax = min(100, K + 40);
            else
                Nmax = min(30, K + 20);
            if (Nmax < Nmin) Nmax = Nmin;
            N = rnd.next(Nmin, Nmax);

            s = string(N, '1');
            int runLen = K;
            int stMax = N - runLen;
            int st = rnd.next(0, stMax);
            for (int i = 0; i < runLen; ++i)
                s[st + i] = '0';

            // Fill sides with runs of length at most K-1
            if (st - 2 >= 0)
                fill_side(s, 0, st - 2, K);
            if (st + runLen + 1 <= N - 1)
                fill_side(s, st + runLen + 1, N - 1, K);
            break;
        }
        case 5: {
            // Completely random, with varied zero density
            bool big = (rnd.next(0, 4) == 0);
            if (big) N = rnd.next(31, 120);
            else N = rnd.next(1, 30);
            K = rnd.next(1, N);

            int mode = rnd.next(0, 3);
            s.resize(N);
            for (int i = 0; i < N; ++i) {
                if (mode == 0) {
                    // balanced
                    s[i] = rnd.next(0, 1) ? '1' : '0';
                } else if (mode == 1) {
                    // mostly ones
                    s[i] = (rnd.next(0, 4) == 0) ? '0' : '1';
                } else if (mode == 2) {
                    // mostly zeros
                    s[i] = (rnd.next(0, 4) == 0) ? '1' : '0';
                } else {
                    // alternating-ish
                    s[i] = (i % 2 == 0) ? '1' : '0';
                }
            }
            break;
        }
        case 6: {
            // K = N edge cases
            bool big = (rnd.next(0, 3) == 0);
            if (big) N = rnd.next(10, 40);
            else N = rnd.next(1, 20);
            K = N;

            s.resize(N);
            if (rnd.next(0, 3) == 0) {
                // all zeros: fail
                s = string(N, '0');
            } else {
                // random but not all zeros
                bool allZero = true;
                for (int i = 0; i < N; ++i) {
                    s[i] = rnd.next(0, 1) ? '1' : '0';
                    if (s[i] == '1') allZero = false;
                }
                if (allZero) {
                    int pos = rnd.next(0, N - 1);
                    s[pos] = '1';
                }
            }
            break;
        }
        case 7: {
            // K = 1 edge cases
            N = rnd.next(1, 50);
            K = 1;

            s.resize(N);
            if (rnd.next(0, 3) == 0) {
                // all ones: pass
                s = string(N, '1');
            } else {
                // random but ensure at least one zero
                bool hasZero = false;
                for (int i = 0; i < N; ++i) {
                    s[i] = rnd.next(0, 1) ? '1' : '0';
                    if (s[i] == '0') hasZero = true;
                }
                if (!hasZero) {
                    int pos = rnd.next(0, N - 1);
                    s[pos] = '0';
                }
            }
            break;
        }
    }

    println(N, K);
    println(s);

    return 0;
}
