#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size N
    int N = rnd.next(3, 10);

    // Decide how many guaranteed collinear triples to insert (0,1,2)
    int maxTriples = min(2, N >= 3 ? 2 : 0);
    int tripleCount = rnd.next(0, maxTriples);

    // Determine total letters k, must be at least 3*tripleCount
    int maxLetters = min(26, N * N);
    int minLetters = 3 * tripleCount;
    if (minLetters > maxLetters) minLetters = 0; // no requirement
    int k = rnd.next(minLetters, maxLetters);

    // Prepare set of used positions
    set<int> used;
    vector<pair<int,int>> positions;

    // Directions for collinear triples
    vector<pair<int,int>> dirs = {{1,0},{0,1},{1,1},{1,-1}};

    // Insert guaranteed triples
    for (int t = 0; t < tripleCount; t++) {
        bool placed = false;
        for (int it = 0; it < 100 && !placed; it++) {
            auto d = rnd.any(dirs);
            int dx = d.first, dy = d.second;
            int x0_lo = 0, x0_hi = N-1, y0_lo = 0, y0_hi = N-1;
            if (dx == 1 && dy == 0) { x0_hi = N-3; }
            if (dx == 0 && dy == 1) { y0_hi = N-3; }
            if (dx == 1 && dy == 1) { x0_hi = N-3; y0_hi = N-3; }
            if (dx == 1 && dy == -1) { x0_hi = N-3; y0_lo = 2; }
            if (x0_lo > x0_hi || y0_lo > y0_hi) continue;
            int x0 = rnd.next(x0_lo, x0_hi);
            int y0 = rnd.next(y0_lo, y0_hi);
            vector<pair<int,int>> cand;
            bool ok = true;
            for (int i = 0; i < 3; i++) {
                int x = x0 + dx * i;
                int y = y0 + dy * i;
                int code = x * N + y;
                if (used.count(code)) { ok = false; break; }
                cand.emplace_back(x, y);
            }
            if (!ok) continue;
            // commit
            for (auto &p : cand) {
                used.insert(p.first * N + p.second);
                positions.push_back(p);
            }
            placed = true;
        }
    }

    // Fill remaining positions randomly
    while ((int)positions.size() < k) {
        int x = rnd.next(0, N-1);
        int y = rnd.next(0, N-1);
        int code = x * N + y;
        if (used.count(code)) continue;
        used.insert(code);
        positions.emplace_back(x, y);
    }

    // Prepare letters pool
    vector<char> letters;
    for (char c = 'A'; c <= 'Z'; c++) letters.push_back(c);
    shuffle(letters.begin(), letters.end());
    letters.resize(k);

    // Build grid
    vector<string> grid(N, string(N, '.'));
    for (int i = 0; i < k; i++) {
        int x = positions[i].first;
        int y = positions[i].second;
        grid[x][y] = letters[i];
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }

    return 0;
}
