#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: grid size
    int N = rnd.next(3, 8);
    int M = rnd.next(3, 8);

    int NM = N * M;
    // Number of viruses V: between 2 and min(10, NM-3)
    int V = rnd.next(2, min(10, NM - 3));

    // Pre-existing walls W0: leave at least 3 empty for new walls
    int maxWalls = NM - V - 3;
    // Weighted bias parameter for walls
    vector<int> tvals = {-2, -1, 0, 1, 2};
    int t = rnd.any(tvals);
    int W0 = rnd.wnext(maxWalls + 1, t);  // in [0..maxWalls], biased

    // Mark used cells
    vector<bool> used(NM, false);
    vector<int> virusPos;

    // Decide whether to cluster viruses
    bool cluster = rnd.next(2) == 1;
    if (cluster) {
        // Place first virus randomly
        int first = rnd.next(NM - 1);
        virusPos.push_back(first);
        used[first] = true;
        // Place the rest
        for (int i = 1; i < V; i++) {
            if (rnd.next() < 0.7) {
                // attempt neighbor
                int base = rnd.any(virusPos);
                int r = base / M, c = base % M;
                vector<int> nei;
                if (r > 0) nei.push_back((r - 1) * M + c);
                if (r + 1 < N) nei.push_back((r + 1) * M + c);
                if (c > 0) nei.push_back(r * M + (c - 1));
                if (c + 1 < M) nei.push_back(r * M + (c + 1));
                if (!nei.empty()) {
                    int pick = rnd.any(nei);
                    if (!used[pick]) {
                        virusPos.push_back(pick);
                        used[pick] = true;
                        continue;
                    }
                }
            }
            // fallback: random unused
            int x;
            do {
                x = rnd.next(NM - 1);
            } while (used[x]);
            virusPos.push_back(x);
            used[x] = true;
        }
    } else {
        // Place V random distinct viruses
        while ((int)virusPos.size() < V) {
            int x = rnd.next(NM - 1);
            if (!used[x]) {
                used[x] = true;
                virusPos.push_back(x);
            }
        }
    }

    // Place pre-existing walls
    vector<int> wallPos;
    while ((int)wallPos.size() < W0) {
        int x = rnd.next(NM - 1);
        if (!used[x]) {
            used[x] = true;
            wallPos.push_back(x);
        }
    }

    // Build grid
    vector<vector<int>> grid(N, vector<int>(M, 0));
    for (int id : virusPos) {
        int r = id / M, c = id % M;
        grid[r][c] = 2;
    }
    for (int id : wallPos) {
        int r = id / M, c = id % M;
        grid[r][c] = 1;
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }

    return 0;
}
