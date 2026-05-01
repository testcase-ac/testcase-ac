#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern = rnd.next(0, 4);
    int N;
    vector<long long> h;

    if (pattern == 0) {
        // Very small, random
        N = rnd.next(1, 4);
        h.assign(N, 0);
        for (int i = 0; i < N; ++i)
            h[i] = rnd.next(1, 5);
    } else if (pattern == 1) {
        // Medium random
        N = rnd.next(5, 12);
        h.assign(N, 0);
        for (int i = 0; i < N; ++i)
            h[i] = rnd.next(1, 20);
    } else if (pattern == 2) {
        // W-like with valleys and peaks
        N = rnd.next(7, 12);
        long long base = rnd.next(5, 20);
        h.assign(N, base);
        int mid = N / 2;

        // One higher central peak
        h[mid] = base + rnd.next(1, 10);

        // One or two valleys
        int valley1 = rnd.next(1, N - 2);
        int valley2 = rnd.next(valley1, N - 2);
        long long low1 = rnd.next(1LL, base - 1);
        long long low2 = rnd.next(1LL, base - 1);
        h[valley1] = low1;
        h[valley2] = low2;
    } else if (pattern == 3) {
        // Plateau ends, mixed inside
        N = rnd.next(5, 10);
        long long H = rnd.next(2, 10);
        h.assign(N, H);
        for (int i = 1; i < N - 1; ++i) {
            if (rnd.next(0, 3) == 0) {
                h[i] = H; // keep plateau
            } else {
                h[i] = rnd.next(1LL, H);
            }
        }
    } else {
        // Large-height extremes
        N = rnd.next(5, 10);
        h.assign(N, 0);
        long long big = (long long)1000000000 - rnd.next(0, 1000);
        long long smallMax = rnd.next(2, 50);

        h[0] = big;
        h[N - 1] = big - rnd.next(0, 100);
        for (int i = 1; i < N - 1; ++i)
            h[i] = rnd.next(1LL, smallMax);

        int mid = N / 2;
        h[mid] = big; // another tall pillar in the middle
    }

    // Apply a global modification for extra variety
    int modType = rnd.next(0, 3); // 0: none, 1: sort asc, 2: sort desc, 3: rotate
    if (modType == 1) {
        sort(h.begin(), h.end());
    } else if (modType == 2) {
        sort(h.rbegin(), h.rend());
    } else if (modType == 3 && N > 1) {
        int k = rnd.next(0, N - 1);
        rotate(h.begin(), h.begin() + k, h.end());
    }

    // Decide Q
    int Q;
    if (rnd.next(0, 2) == 0) Q = N;
    else Q = rnd.next(1, N);

    // Prepare positions 1..N
    vector<int> all(N);
    for (int i = 0; i < N; ++i) all[i] = i + 1;

    // Find local minima and maxima for biased query choices
    vector<int> lows, highs;
    if (N >= 3) {
        for (int i = 1; i < N - 1; ++i) {
            if (h[i] < h[i - 1] && h[i] < h[i + 1]) lows.push_back(i + 1);
            if (h[i] > h[i - 1] && h[i] > h[i + 1]) highs.push_back(i + 1);
        }
    }

    shuffle(all.begin(), all.end());
    int style = rnd.next(0, 2); // 0: random, 1: lows first, 2: highs first

    vector<int> queries;
    queries.reserve(Q);
    vector<bool> used(N + 1, false);

    auto fill_from_all = [&](void) {
        for (int x : all) {
            if ((int)queries.size() >= Q) break;
            if (!used[x]) {
                used[x] = true;
                queries.push_back(x);
            }
        }
    };

    if (style == 1 && !lows.empty()) {
        shuffle(lows.begin(), lows.end());
        for (int x : lows) {
            if ((int)queries.size() >= Q) break;
            if (!used[x]) {
                used[x] = true;
                queries.push_back(x);
            }
        }
        fill_from_all();
    } else if (style == 2 && !highs.empty()) {
        shuffle(highs.begin(), highs.end());
        for (int x : highs) {
            if ((int)queries.size() >= Q) break;
            if (!used[x]) {
                used[x] = true;
                queries.push_back(x);
            }
        }
        fill_from_all();
    } else {
        // Pure random distinct positions
        for (int x : all) {
            if ((int)queries.size() >= Q) break;
            queries.push_back(x);
        }
    }

    // Maybe sort queries (to mix ordered and unordered cases)
    if (rnd.next(0, 1) == 0)
        sort(queries.begin(), queries.end());

    // Output
    println(N);
    println(h);
    println(Q);
    for (int x : queries)
        println(x);

    return 0;
}
