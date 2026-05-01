#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = -1;
    if (argc > 2) {
        scenario = atoi(argv[2]);
    }
    if (scenario < 1 || scenario > 9) {
        scenario = rnd.next(1, 9);
    }

    int N = 0;
    int K = 1;
    vector<int> a;

    switch (scenario) {
        case 1: {
            // Very small N, edge cases
            N = rnd.next(1, 3);
            K = rnd.next(1, 3);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(1, 5);
            break;
        }
        case 2: {
            // All distinct increasing
            N = rnd.next(5, 20);
            int start = rnd.next(1, 50);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = start + i; // strictly increasing, all distinct
            if (rnd.next(0, 1) == 0)
                K = 1;
            else
                K = rnd.next(1, min(10, N));
            break;
        }
        case 3: {
            // All same value
            N = rnd.next(5, 40);
            int v = rnd.next(1, 3);
            a.assign(N, v);
            int opt = rnd.next(0, 2);
            if (opt == 0)
                K = 1;
            else if (opt == 1)
                K = rnd.next(2, min(10, N));
            else
                K = rnd.next(N, min(100, N + 10));
            break;
        }
        case 4: {
            // Alternating two values
            N = rnd.next(10, 40);
            int x = rnd.next(1, 10);
            int y;
            do {
                y = rnd.next(1, 10);
            } while (y == x);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = (i % 2 == 0 ? x : y);
            K = rnd.next(1, 5);
            break;
        }
        case 5: {
            // Block structure
            int targetMin = 15, targetMax = 45;
            int curN = 0;
            vector<int> tmp;
            int blockCnt = rnd.next(3, 6);
            for (int b = 0; b < blockCnt && curN < targetMax; ++b) {
                int len = rnd.next(1, 8);
                int v = rnd.next(1, 5);
                for (int i = 0; i < len && curN < targetMax; ++i) {
                    tmp.push_back(v);
                    ++curN;
                }
            }
            if (curN < targetMin) {
                // pad with random blocks
                while (curN < targetMin) {
                    int len = rnd.next(1, 5);
                    int v = rnd.next(1, 5);
                    for (int i = 0; i < len && curN < targetMin; ++i) {
                        tmp.push_back(v);
                        ++curN;
                    }
                }
            }
            a = tmp;
            N = (int)a.size();
            K = rnd.next(1, 5);
            break;
        }
        case 6: {
            // Dense repeats, small K
            N = rnd.next(15, 60);
            int valueRange = rnd.next(2, 5);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(1, valueRange);
            K = rnd.next(1, min(3, 100));
            break;
        }
        case 7: {
            // Random with larger K (often no tight restriction)
            N = rnd.next(15, 60);
            int valueRange = rnd.next(2, 7);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(1, valueRange);
            int kLow = min(5, N);
            int kHigh = min(10, max(N, 10));
            K = rnd.next(kLow, min(kHigh, 100));
            break;
        }
        case 8: {
            // Carefully crafted around K boundary for a specific value
            int baseN = rnd.next(12, 30);
            int x = rnd.next(1, 5);
            int otherRange = 6; // others from [6..11]
            K = rnd.next(1, 4);
            a.clear();

            // pattern: [x repeated K] + [others] + [x repeated K+1] + [others] + [x repeated K]
            int len1 = K;
            int len2 = K + 1;
            int len3 = K;
            for (int i = 0; i < len1; ++i) a.push_back(x);
            int midOthers = rnd.next(1, 4);
            for (int i = 0; i < midOthers; ++i)
                a.push_back(rnd.next(6, 6 + otherRange));
            for (int i = 0; i < len2; ++i) a.push_back(x);
            int tailOthers = rnd.next(1, 4);
            for (int i = 0; i < tailOthers; ++i)
                a.push_back(rnd.next(6, 6 + otherRange));
            for (int i = 0; i < len3; ++i) a.push_back(x);

            // maybe pad randomly up to about baseN
            while ((int)a.size() < baseN) {
                if (rnd.next(0, 1) == 0)
                    a.push_back(x);
                else
                    a.push_back(rnd.next(6, 6 + otherRange));
            }
            N = (int)a.size();
            break;
        }
        case 9: {
            // Values near upper limit, moderate N
            N = rnd.next(5, 15);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(99990, 100000);
            K = rnd.next(1, min(10, 100));
            break;
        }
        default:
            // fallback (should not happen)
            N = 5; K = 2;
            a = {1, 2, 2, 3, 3};
            break;
    }

    N = (int)a.size();
    if (K < 1) K = 1;
    if (K > 100) K = 100;

    println(N, K);
    println(a);

    return 0;
}
