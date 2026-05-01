#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<int> random_partition(int S, int k) {
    // partition integer S into k positive parts
    vector<int> parts;
    if (k == 1) {
        parts.push_back(S);
        return parts;
    }
    // we need k-1 cut points from [1..S-1], S >= k
    vector<int> pool;
    for (int i = 1; i < S; i++)
        pool.push_back(i);
    shuffle(pool.begin(), pool.end());
    vector<int> cuts(pool.begin(), pool.begin() + (k - 1));
    sort(cuts.begin(), cuts.end());
    int prev = 0;
    for (int x : cuts) {
        parts.push_back(x - prev);
        prev = x;
    }
    parts.push_back(S - prev);
    return parts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // grid size
    int L = rnd.next(3, 10);
    println(L);

    // decide if valid tiling: only possible for L >= 5
    bool makeValid = (L >= 5) && (rnd.next(100) >= 20);
    if (!makeValid) {
        // invalid case: random pieces with border '#'
        for (int i = 0; i < 5; i++) {
            int N = rnd.next(1, L);
            int M = rnd.next(1, L);
            println(N, M);
            vector<string> s(N, string(M, '.'));
            for (int r = 0; r < N; r++)
                for (int c = 0; c < M; c++)
                    if (rnd.next(2)) s[r][c] = '#';
            // ensure each border has at least one '#'
            bool ok;
            ok = false;
            for (int c = 0; c < M; c++) if (s[0][c] == '#') ok = true;
            if (!ok) s[0][rnd.next(0, M-1)] = '#';
            ok = false;
            for (int c = 0; c < M; c++) if (s[N-1][c] == '#') ok = true;
            if (!ok) s[N-1][rnd.next(0, M-1)] = '#';
            ok = false;
            for (int r = 0; r < N; r++) if (s[r][0] == '#') ok = true;
            if (!ok) s[rnd.next(0, N-1)][0] = '#';
            ok = false;
            for (int r = 0; r < N; r++) if (s[r][M-1] == '#') ok = true;
            if (!ok) s[rnd.next(0, N-1)][M-1] = '#';
            for (auto &row : s) println(row);
        }
        return 0;
    }

    // valid tiling case
    vector<vector<int>> grid(L, vector<int>(L, 0));
    // choose a pattern for diversity
    vector<int> patterns = {0, 1};
    if (L >= 5) {
        patterns.push_back(2);
        patterns.push_back(3);
        patterns.push_back(4);
    }
    int pat = rnd.any(patterns);

    if (pat == 0) {
        // horizontal stripes: 5 parts
        auto hs = random_partition(L, 5);
        int r = 0;
        for (int i = 0; i < 5; i++) {
            for (int dr = 0; dr < hs[i]; dr++)
                for (int c = 0; c < L; c++)
                    grid[r+dr][c] = i+1;
            r += hs[i];
        }
    } else if (pat == 1) {
        // vertical stripes: 5 parts
        auto ws = random_partition(L, 5);
        int c = 0;
        for (int i = 0; i < 5; i++) {
            for (int dc = 0; dc < ws[i]; dc++)
                for (int r = 0; r < L; r++)
                    grid[r][c+dc] = i+1;
            c += ws[i];
        }
    } else if (pat == 2) {
        // top stripe (id=1) + 4 bottom vertical stripes (ids 2-5)
        // ensure bottom height >=4
        int h0 = rnd.next(1, L-4);
        for (int r = 0; r < h0; r++)
            for (int c = 0; c < L; c++)
                grid[r][c] = 1;
        int S = L - h0;
        auto ws = random_partition(S, 4);
        int c = 0;
        for (int i = 0; i < 4; i++) {
            for (int dc = 0; dc < ws[i]; dc++)
                for (int r = h0; r < L; r++)
                    grid[r][c+dc] = i+2;
            c += ws[i];
        }
    } else if (pat == 3) {
        // left stripe (id=1) + 4 right horizontal stripes (ids 2-5)
        int w0 = rnd.next(1, L-4);
        for (int c = 0; c < w0; c++)
            for (int r = 0; r < L; r++)
                grid[r][c] = 1;
        int S = L - w0;
        auto hs = random_partition(S, 4);
        int r = 0;
        for (int i = 0; i < 4; i++) {
            for (int dr = 0; dr < hs[i]; dr++)
                for (int c = w0; c < L; c++)
                    grid[r+dr][c] = i+2;
            r += hs[i];
        }
    } else {
        // ring (id=1) + 4 inner quadrants (ids 2-5)
        for (int i = 0; i < L; i++) {
            grid[i][0] = grid[i][L-1] = 1;
            grid[0][i] = grid[L-1][i] = 1;
        }
        int S = L - 2;
        auto hs2 = random_partition(S, 2);
        auto ws2 = random_partition(S, 2);
        int r0 = 1, c0 = 1;
        // quadrant 2
        for (int dr = 0; dr < hs2[0]; dr++)
            for (int dc = 0; dc < ws2[0]; dc++)
                grid[r0+dr][c0+dc] = 2;
        // quadrant 3
        for (int dr = 0; dr < hs2[0]; dr++)
            for (int dc = ws2[0]; dc < S; dc++)
                grid[r0+dr][c0+dc] = 3;
        // quadrant 4
        for (int dr = hs2[0]; dr < S; dr++)
            for (int dc = 0; dc < ws2[0]; dc++)
                grid[r0+dr][c0+dc] = 4;
        // quadrant 5
        for (int dr = hs2[0]; dr < S; dr++)
            for (int dc = ws2[0]; dc < S; dc++)
                grid[r0+dr][c0+dc] = 5;
    }

    // extract and print the 5 pieces
    for (int id = 1; id <= 5; id++) {
        int rmin = L, rmax = -1, cmin = L, cmax = -1;
        for (int r = 0; r < L; r++)
            for (int c = 0; c < L; c++)
                if (grid[r][c] == id) {
                    rmin = min(rmin, r);
                    rmax = max(rmax, r);
                    cmin = min(cmin, c);
                    cmax = max(cmax, c);
                }
        int N = rmax - rmin + 1;
        int M = cmax - cmin + 1;
        println(N, M);
        for (int dr = 0; dr < N; dr++) {
            string row;
            for (int dc = 0; dc < M; dc++)
                row.push_back(grid[rmin+dr][cmin+dc] == id ? '#' : '.');
            println(row);
        }
    }

    return 0;
}
