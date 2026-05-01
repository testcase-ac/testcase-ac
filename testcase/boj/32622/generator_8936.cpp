#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6);
    int N;
    vector<int> a;

    switch (scenario) {
        // All equal (all 0 or all 1), size small
        case 0: {
            N = rnd.next(1, 20);
            int v = rnd.next(0, 1);
            a.assign(N, v);
            break;
        }
        // Alternating pattern, starting with 0 or 1
        case 1: {
            N = rnd.next(2, 25);
            int start = rnd.next(0, 1);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = (start ^ (i & 1));
            break;
        }
        // Single change: block of 0s then 1s, or 1s then 0s
        case 2: {
            N = rnd.next(2, 40);
            int split = rnd.next(1, N - 1);
            int first = rnd.next(0, 1);
            int second = 1 - first;
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = (i < split ? first : second);
            break;
        }
        // Random short runs
        case 3: {
            N = rnd.next(5, 40);
            a.clear();
            int cur = rnd.next(0, 1);
            while ((int)a.size() < N) {
                int rem = N - (int)a.size();
                int len = rnd.next(1, min(5, rem));
                for (int i = 0; i < len; ++i)
                    a.push_back(cur);
                // Sometimes keep same color, sometimes toggle
                if (rnd.next(0, 1))
                    cur ^= 1;
            }
            break;
        }
        // Mostly one color with a few isolated or small runs of the other
        case 4: {
            N = rnd.next(10, 40);
            int base = rnd.next(0, 1);
            int other = 1 - base;
            a.assign(N, base);
            int k = rnd.next(1, min(5, N));
            // choose distinct starting positions for "other" runs
            vector<int> pos(N);
            for (int i = 0; i < N; ++i)
                pos[i] = i;
            shuffle(pos.begin(), pos.end());
            pos.resize(k);
            for (int idx : pos) {
                int runLen = rnd.next(1, min(3, N - idx));
                for (int j = idx; j < idx + runLen; ++j)
                    a[j] = other;
            }
            break;
        }
        // One long run inside, random noisy edges
        case 5: {
            N = rnd.next(7, 20);
            a.assign(N, 0);
            int longLen = rnd.next(3, max(3, N / 2));
            if (longLen >= N) longLen = N - 1;
            int start = rnd.next(0, N - longLen);
            int val = rnd.next(0, 1);
            for (int i = start; i < start + longLen; ++i)
                a[i] = val;
            // Fill left and right with somewhat random bits
            for (int i = 0; i < start; ++i) {
                if (rnd.next(0, 3) == 0)
                    a[i] = val;       // sometimes extend run-like patterns
                else
                    a[i] = rnd.next(0, 1);
            }
            for (int i = start + longLen; i < N; ++i) {
                if (rnd.next(0, 3) == 0)
                    a[i] = val;
                else
                    a[i] = rnd.next(0, 1);
            }
            break;
        }
        // Tricky prefix-merge case: designed pattern
        case 6: {
            // fixed size to keep very readable
            vector<vector<int>> patterns = {
                {1,1,0,0,0,1,1,1,0,0},
                {0,0,1,1,1,0,0,0,1},
                {1,0,0,1,1,1,0,1,0,0,0},
                {0,1,1,0,0,0,1,1,1,0},
            };
            auto v = rnd.any(patterns);
            a = v;
            N = (int)a.size();
            break;
        }
    }

    println(N);
    println(a);

    return 0;
}
