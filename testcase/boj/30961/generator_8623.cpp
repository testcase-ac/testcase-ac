#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 9);
    int N = 0;
    vector<long long> A;

    switch (scenario) {
        case 0: {
            // Hand-crafted tiny edge cases
            int sub = rnd.next(0, 4);
            if (sub == 0) {
                N = 1;
                A = {0};
            } else if (sub == 1) {
                N = 1;
                A = { (long long)rnd.next(0, 10) };
            } else if (sub == 2) {
                N = 2;
                long long x = rnd.next(0, 10);
                long long y = rnd.next(0, 10);
                A = {x, y};
            } else if (sub == 3) {
                N = 3;
                A = {1, 1, 1};
            } else {
                N = 3;
                A = {0, 1, 0};
            }
            break;
        }
        case 1: {
            // All equal values (including all zeros, all ones, random small/big)
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(1, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            int valType = rnd.next(0, 3);
            long long val;
            if (valType == 0) val = 0;
            else if (valType == 1) val = 1;
            else if (valType == 2) val = rnd.next(2, 20);
            else val = (long long)rnd.next((int)1e9 - 1000, (int)1e9);
            A.assign(N, val);
            break;
        }
        case 2: {
            // Strictly increasing sequence
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(2, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            long long start = rnd.next(0, 20);
            long long cur = start;
            for (int i = 0; i < N; i++) {
                A.push_back(cur);
                long long add = rnd.next(1, 5);
                cur += add;
                if (cur > (long long)1e9) cur = (long long)1e9; // clamp
            }
            break;
        }
        case 3: {
            // Strictly decreasing sequence
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(2, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            long long start = rnd.next(0, 20);
            long long cur = start + (long long)5 * N;
            if (cur > (long long)1e9) cur = (long long)1e9;
            for (int i = 0; i < N; i++) {
                A.push_back(cur);
                long long sub = rnd.next(1, 5);
                if (cur > sub) cur -= sub;
                else cur = 0;
            }
            break;
        }
        case 4: {
            // Random small values (0..20) with many duplicates
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(1, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            for (int i = 0; i < N; i++) {
                A.push_back(rnd.next(0, 20));
            }
            break;
        }
        case 5: {
            // Random wide values (0..1e9)
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(1, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            for (int i = 0; i < N; i++) {
                A.push_back((long long)rnd.next(0, (int)1e9));
            }
            break;
        }
        case 6: {
            // Mixture of many zeros and some very large numbers
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(2, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            int zeros = rnd.next(N / 2, N); // at least half zeros
            int bigs = N - zeros;
            for (int i = 0; i < zeros; i++) A.push_back(0);
            for (int i = 0; i < bigs; i++) {
                long long v = (long long)rnd.next((int)1e9 - 1000, (int)1e9);
                A.push_back(v);
            }
            shuffle(A.begin(), A.end());
            break;
        }
        case 7: {
            // Repeating pattern with small values
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(2, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            int k = rnd.next(2, min(5, N));
            vector<long long> base;
            for (int i = 0; i < k; i++) {
                base.push_back(rnd.next(0, 10));
            }
            for (int i = 0; i < N; i++) {
                A.push_back(base[i % k]);
            }
            break;
        }
        case 8: {
            // Valley / peak shape
            int maxNType = rnd.next(0, 2);
            if (maxNType == 0) N = rnd.next(3, 7);
            else if (maxNType == 1) N = rnd.next(8, 15);
            else N = rnd.next(16, 25);

            bool valley = rnd.next(0, 1);
            long long center = rnd.next(0, 5);
            long long height = rnd.next(6, 20);
            int mid = N / 2;

            A.assign(N, 0);
            if (valley) {
                // high at ends, low in middle
                for (int i = 0; i < N; i++) {
                    int dist = abs(i - mid);
                    long long val = center + dist;
                    if (val > height) val = height;
                    A[i] = val;
                }
                A[0] = height;
                A[N - 1] = height;
            } else {
                // low at ends, high in middle (peak)
                for (int i = 0; i < N; i++) {
                    int dist = abs(i - mid);
                    long long val = height - dist;
                    if (val < center) val = center;
                    A[i] = val;
                }
            }
            break;
        }
        case 9: {
            // Binary {0,1} with some structure
            int maxNType = rnd.next(0, 3);
            if (maxNType == 0) N = rnd.next(1, 5);
            else if (maxNType == 1) N = rnd.next(6, 10);
            else if (maxNType == 2) N = rnd.next(11, 20);
            else N = rnd.next(21, 40);

            int blocks = rnd.next(1, min(5, N));
            int remaining = N;
            for (int b = 0; b < blocks; b++) {
                int len;
                if (b == blocks - 1) len = remaining;
                else len = rnd.next(1, remaining - (blocks - 1 - b));
                remaining -= len;
                int bit = (b % 2 == 0 ? 0 : 1);
                for (int i = 0; i < len; i++) A.push_back(bit);
            }
            // maybe shuffle a bit with small probability to break perfect blocks
            if (rnd.next(0, 1)) {
                int swaps = rnd.next(0, N / 3);
                for (int i = 0; i < swaps; i++) {
                    int x = rnd.next(0, N - 1);
                    int y = rnd.next(0, N - 1);
                    swap(A[x], A[y]);
                }
            }
            break;
        }
    }

    println(N);
    println(A);

    return 0;
}
