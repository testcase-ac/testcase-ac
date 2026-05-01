#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(1, 8);
    int N = 0;
    vector<int> A;

    auto clamp100 = [](int x) {
        if (x < 1) return 1;
        if (x > 100) return 100;
        return x;
    };

    switch (type) {
        case 1: {
            // Very small, monotone increasing or decreasing
            N = rnd.next(2, 5);
            A.resize(N);
            int start = rnd.next(1, 50);
            int step = rnd.next(0, 10);
            bool inc = rnd.next(0, 1);
            for (int i = 0; i < N; ++i) {
                int v = inc ? start + step * i : start - step * i;
                A[i] = clamp100(v);
            }
            break;
        }
        case 2: {
            // All equal values
            N = rnd.next(2, 10);
            A.resize(N);
            int v = rnd.next(1, 100);
            for (int i = 0; i < N; ++i) A[i] = v;
            break;
        }
        case 3: {
            // Alternating between two extreme or random distinct values
            N = rnd.next(2, 20);
            A.resize(N);
            int x, y;
            if (rnd.next(0, 1) == 0) {
                x = 1;
                y = 100;
            } else {
                x = rnd.next(1, 100);
                do { y = rnd.next(1, 100); } while (y == x);
            }
            for (int i = 0; i < N; ++i) {
                A[i] = (i % 2 == 0 ? x : y);
            }
            break;
        }
        case 4: {
            // Small value range, random
            N = rnd.next(5, 20);
            A.resize(N);
            int mx = rnd.next(2, 5);
            for (int i = 0; i < N; ++i) {
                A[i] = rnd.next(1, mx);
            }
            break;
        }
        case 5: {
            // Medium size, fully random in [1,100]
            // Prefer small, but sometimes up to 80
            if (rnd.next(0, 3) == 0)
                N = rnd.next(20, 80);
            else
                N = rnd.next(10, 20);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                A[i] = rnd.next(1, 100);
            }
            break;
        }
        case 6: {
            // Mostly same with a few spikes
            N = rnd.next(5, 25);
            A.resize(N);
            int base = rnd.next(1, 100);
            for (int i = 0; i < N; ++i) A[i] = base;
            int k = rnd.next(1, min(5, N));
            vector<int> idx(N);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            idx.resize(k);
            for (int id : idx) {
                int v;
                do { v = rnd.next(1, 100); } while (v == base);
                A[id] = v;
            }
            break;
        }
        case 7: {
            // Nearly sorted sequence
            N = rnd.next(5, 20);
            A.resize(N);
            int cur = rnd.next(1, 20);
            for (int i = 0; i < N; ++i) {
                cur += rnd.next(0, 5);
                A[i] = clamp100(cur);
            }
            // Slight random adjacent swaps
            int swaps = rnd.next(1, max(1, N / 3));
            for (int s = 0; s < swaps; ++s) {
                int i = rnd.next(0, N - 2);
                if (rnd.next(0, 1))
                    swap(A[i], A[i + 1]);
            }
            break;
        }
        case 8: {
            // Zigzag high-low pattern
            N = rnd.next(4, 20);
            A.resize(N);
            vector<int> vals;
            int k = (N + 1) / 2;
            int base = rnd.next(1, 50);
            for (int i = 0; i < k; ++i) {
                int v = clamp100(base + rnd.next(-20, 20));
                vals.push_back(v);
            }
            sort(vals.begin(), vals.end());
            vector<int> zig;
            int l = 0, r = (int)vals.size() - 1;
            while ((int)zig.size() < N && l <= r) {
                zig.push_back(vals[r--]);
                if ((int)zig.size() < N && l <= r) zig.push_back(vals[l++]);
            }
            // If still need more, pad with extremes
            while ((int)zig.size() < N) zig.push_back(rnd.next(1, 100));
            for (int i = 0; i < N; ++i) A[i] = zig[i];
            break;
        }
        default: {
            // Fallback: simple random
            N = rnd.next(2, 10);
            A.resize(N);
            for (int i = 0; i < N; ++i) A[i] = rnd.next(1, 100);
            break;
        }
    }

    println(N);
    println(A);

    return 0;
}
