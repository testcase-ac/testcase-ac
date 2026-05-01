#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern = rnd.next(0, 3); // 0,1,2: hand-made; 3: random

    if (pattern == 0) {
        // Sample-like small triangle
        int N = 3, M = 3;
        println(N, M);
        println(1, 2, 2, 3);
        println(2, 3, 6, 3);
        println(1, 3, 7, 3);
        return 0;
    } else if (pattern == 1) {
        // Need to consider speeding up and slowing down
        int N = 5, M = 6;
        println(N, M);
        // Backbone with medium K
        println(1, 2, 4, 5);
        println(2, 3, 4, 5);
        // Low-speed shortcut requiring deceleration
        println(3, 5, 4, 2);
        // High-speed detour
        println(2, 4, 10, 10);
        println(4, 5, 10, 10);
        // Direct but long
        println(1, 5, 40, 10);
        return 0;
    } else if (pattern == 2) {
        // Cycle to allow speed-up before a long edge
        int N = 5, M = 5;
        println(N, M);
        // Small high-K cycle 1-2-3-1
        println(1, 2, 1, 10);
        println(2, 3, 1, 10);
        println(3, 1, 1, 10);
        // Path to destination
        println(3, 4, 1, 10);
        println(4, 5, 50, 10);
        return 0;
    } else {
        // Random but structured small graph
        auto randLength = [&]() -> int {
            int t = rnd.next(0, 9);
            if (t < 4) return rnd.next(1, 5);       // small
            else if (t < 8) return rnd.next(6, 25); // medium
            else return rnd.next(26, 80);           // large-ish
        };
        auto randK = [&]() -> int {
            int t = rnd.next(0, 9);
            if (t < 3) return rnd.next(1, 3);       // low
            else if (t < 7) return rnd.next(4, 7);  // mid
            else return rnd.next(8, 10);            // high
        };

        int rollN = rnd.next(0, 9);
        int N;
        if (rollN < 3) N = rnd.next(2, 4);  // quite small
        else N = rnd.next(5, 10);           // medium-small

        vector<tuple<int,int,int,int>> edges;
        set<pair<int,int>> used;

        auto addEdge = [&](int a, int b, int L, int K) {
            if (a == b) return;
            if (a > b) swap(a, b);
            pair<int,int> p = {a, b};
            if (used.count(p)) return;
            used.insert(p);
            edges.emplace_back(a, b, L, K);
        };

        // Simple chain ensuring connectivity and 1->N path
        for (int i = 2; i <= N; ++i) {
            int L = randLength();
            int K = randK();
            addEdge(i - 1, i, L, K);
        }

        // Optional direct-ish edge 1-N with special characteristics
        bool addDirect = (N >= 3 && rnd.next(0, 1) == 0);
        if (addDirect) {
            int Ld, Kd;
            int t = rnd.next(0, 2);
            if (t == 0) {              // long, high K
                Ld = rnd.next(20, 80);
                Kd = rnd.next(5, 10);
            } else if (t == 1) {       // relatively short, low K
                Ld = rnd.next(3, 15);
                Kd = rnd.next(1, 3);
            } else {                   // generic
                Ld = randLength();
                Kd = randK();
            }
            addEdge(1, N, Ld, Kd);
        }

        int maxPossible = N * (N - 1) / 2;
        int Mmax = min(20, maxPossible);
        int baseM = (int)edges.size();
        int targetM = rnd.next(baseM, Mmax);

        while ((int)edges.size() < targetM) {
            int kind = rnd.next(0, 4);
            int u, v;
            if (kind == 0) {
                u = 1;
                v = rnd.next(2, N);           // from start
            } else if (kind == 1) {
                u = rnd.next(1, N - 1);
                v = N;                        // to destination
            } else {
                u = rnd.next(1, N);
                v = rnd.next(1, N);
                if (u == v) continue;
            }

            int L, K;
            int ptype = rnd.next(0, 4);
            if (ptype == 0) {
                // Long high-speed edge
                L = rnd.next(25, 80);
                K = rnd.next(7, 10);
            } else if (ptype == 1) {
                // Short low-speed shortcut
                L = rnd.next(1, 10);
                K = rnd.next(1, 3);
            } else {
                // Generic
                L = randLength();
                K = randK();
            }
            addEdge(u, v, L, K);
        }

        int M = (int)edges.size();
        println(N, M);
        for (auto &e : edges) {
            int a, b, L, K;
            tie(a, b, L, K) = e;
            println(a, b, L, K);
        }
    }

    return 0;
}
