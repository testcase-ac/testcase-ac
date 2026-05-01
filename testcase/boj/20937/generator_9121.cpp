#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type;
    if (argc > 1) {
        type = atoi(argv[1]);
        if (type < 0) type = 0;
    } else {
        type = rnd.next(0, 6);
    }
    type %= 7;

    vector<int> a;

    if (type == 0) {
        // Small random / edge cases
        int sub = rnd.next(0, 3);
        if (sub == 0) {
            // N = 1
            int N = 1;
            a.resize(N);
            a[0] = rnd.next(1, 10);
        } else if (sub == 1) {
            // Very small random
            int N = rnd.next(2, 5);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = rnd.next(1, 10);
        } else if (sub == 2) {
            // Example-like
            a = {4, 2, 3, 1, 2};
        } else {
            int N = rnd.next(3, 7);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = rnd.next(1, 20);
        }
    } else if (type == 1) {
        // All equal
        int N = rnd.next(1, 50);
        int x = rnd.next(1, 50000);
        a.assign(N, x);
    } else if (type == 2) {
        // Strictly increasing sequence
        int N = rnd.next(2, 50);
        int maxStep = max(1, 50000 / max(1, N));
        int step = rnd.next(1, maxStep);
        int maxStart = 50000 - (N - 1) * step;
        int start = rnd.next(1, maxStart);
        a.resize(N);
        for (int i = 0; i < N; ++i) a[i] = start + i * step;
    } else if (type == 3) {
        // Strictly decreasing sequence
        int N = rnd.next(2, 50);
        int maxStep = max(1, 50000 / max(1, N));
        int step = rnd.next(1, maxStep);
        int minStart = 1 + (N - 1) * step;
        int start = rnd.next(minStart, 50000);
        a.resize(N);
        for (int i = 0; i < N; ++i) a[i] = start - i * step;
    } else if (type == 4) {
        // Few distinct values with random multiplicities
        int N = rnd.next(5, 50);
        int k = rnd.next(2, min(5, N));
        vector<int> vals;
        vals.reserve(k);
        // distinct base values
        while ((int)vals.size() < k) {
            int v = rnd.next(1, 50000);
            bool ok = true;
            for (int u : vals) if (u == v) { ok = false; break; }
            if (ok) vals.push_back(v);
        }
        a.clear();
        a.reserve(N);
        // Ensure at least one of each
        for (int i = 0; i < k; ++i) a.push_back(vals[i]);
        // Distribute remaining
        for (int i = k; i < N; ++i) {
            int id = rnd.next(0, k - 1);
            a.push_back(vals[id]);
        }
        shuffle(a.begin(), a.end());
    } else if (type == 5) {
        // Alternating two values to break "respect input order" solutions
        int M = rnd.next(2, 25);
        int N = 2 * M;
        int x = rnd.next(1, 50000);
        int y;
        do {
            y = rnd.next(1, 50000);
        } while (y == x);
        if (x > y) swap(x, y); // ensure x < y for LNDS > max frequency
        a.clear();
        a.reserve(N);
        for (int i = 0; i < M; ++i) {
            a.push_back(x);
            a.push_back(y);
        }
    } else if (type == 6) {
        // Two values with same max frequency + distinct leftovers
        int N = rnd.next(10, 50);
        int freq = rnd.next(3, max(3, N / 3)); // ensures 2*freq <= N approximately
        while (2 * freq > N - 2) { // keep some space for leftovers
            freq--;
        }
        if (freq < 3) freq = 3;
        int v1 = rnd.next(1, 50000);
        int v2;
        do {
            v2 = rnd.next(1, 50000);
        } while (v2 == v1);

        a.clear();
        a.reserve(N);
        for (int i = 0; i < freq; ++i) a.push_back(v1);
        for (int i = 0; i < freq; ++i) a.push_back(v2);

        int remaining = N - 2 * freq;
        // Distinct leftovers
        std::set<int> used;
        used.insert(v1);
        used.insert(v2);
        while (remaining--) {
            int cand;
            do {
                cand = rnd.next(1, 50000);
            } while (used.count(cand));
            used.insert(cand);
            a.push_back(cand);
        }
        shuffle(a.begin(), a.end());
    }

    int N = (int)a.size();
    println(N);
    println(a);

    return 0;
}
