#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N, M: 4 ≤ N, M ≤ 500
    int N = inf.readInt(4, 500, "N");
    inf.readSpace();
    int M = inf.readInt(4, 500, "M");
    inf.readEoln();

    // Grid values: natural numbers ≤ 1000 (i.e., 1..1000)
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        vector<int> row = inf.readInts(M, 1, 1000, "a_ij");
        inf.readEoln();
        a[i] = row;
    }

    // --- Global property check: answer exists and is within reasonable bounds ---
    // Problem guarantees that we can place two non-overlapping tetrominoes.
    // For N, M ≥ 4 this is always possible, but we additionally verify by explicit search
    // and also ensure the maximum sum is not overflowing 32-bit int.

    // Precompute all 19 tetromino shapes (with rotations/reflections),
    // each as a set of 4 (dr, dc) offsets with (0,0) included.
    // Coordinates listed in a minimal bounding box, anchor at (0,0).
    const vector<vector<pair<int,int>>> shapes = {
        // I tetromino
        {{0,0},{0,1},{0,2},{0,3}},
        {{0,0},{1,0},{2,0},{3,0}},
        // O tetromino
        {{0,0},{0,1},{1,0},{1,1}},
        // T tetromino
        {{0,0},{0,1},{0,2},{1,1}},
        {{0,1},{1,0},{1,1},{2,1}},
        {{1,0},{1,1},{1,2},{0,1}},
        {{0,0},{1,0},{1,1},{2,0}},
        // S/Z tetrominoes
        {{0,0},{0,1},{1,1},{1,2}}, // Z
        {{1,0},{1,1},{0,1},{0,2}}, // S
        {{0,1},{1,0},{1,1},{2,0}}, // Z rotated
        {{0,0},{1,0},{1,1},{2,1}}, // S rotated
        // L tetrominoes and mirrors (8 variants)
        {{0,0},{1,0},{2,0},{2,1}},
        {{0,1},{1,1},{2,1},{2,0}},
        {{0,0},{0,1},{1,0},{2,0}},
        {{0,0},{0,1},{1,1},{2,1}},
        {{0,0},{0,1},{0,2},{1,0}},
        {{0,0},{0,1},{0,2},{1,2}},
        {{0,2},{1,0},{1,1},{1,2}},
        {{0,0},{1,0},{1,1},{1,2}}
    };

    int bestOne = 0;
    // For each cell and each shape, if inside bounds, compute sum.
    // Store all placements for later use in two-tetromino max computation.
    struct Placement {
        int sum;
        // store 4 cells (flattened index r*M + c)
        int c0, c1, c2, c3;
    };
    vector<Placement> placements;
    placements.reserve(N * M * (int)shapes.size());

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            for (const auto &sh : shapes) {
                int cells[4];
                int curSum = 0;
                bool ok = true;
                for (int k = 0; k < 4; ++k) {
                    int nr = r + sh[k].first;
                    int nc = c + sh[k].second;
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
                        ok = false;
                        break;
                    }
                    cells[k] = nr * M + nc;
                    curSum += a[nr][nc];
                }
                if (!ok) continue;
                sort(cells, cells + 4);
                placements.push_back({curSum, cells[0], cells[1], cells[2], cells[3]});
                if (curSum > bestOne) bestOne = curSum;
            }
        }
    }

    // Ensure at least one placement exists (it always should for N,M >= 4)
    ensuref(!placements.empty(), "No valid tetromino placement found, but N,M >= 4.");

    // Sort placements descending by sum for early pruning
    sort(placements.begin(), placements.end(),
         [](const Placement& A, const Placement& B){ return A.sum > B.sum; });

    long long bestTwo = 0;
    int P = (int)placements.size();
    // Simple O(P^2) with pruning by sum; P is at most ~ N*M*19 (≤ 4.75e6),
    // which is large, but this check is only for validator usage and
    // will not be run under tight constraints in production.
    for (int i = 0; i < P; ++i) {
        // Prune if even pairing with same sum can't beat current best
        if ((long long)placements[i].sum * 2 <= bestTwo) break;
        for (int j = i + 1; j < P; ++j) {
            long long cand = (long long)placements[i].sum + placements[j].sum;
            if (cand <= bestTwo) break; // since placements sorted by sum
            // Check non-overlap: no cell index in common
            int ca[4] = {placements[i].c0, placements[i].c1,
                         placements[i].c2, placements[i].c3};
            int cb[4] = {placements[j].c0, placements[j].c1,
                         placements[j].c2, placements[j].c3};
            bool overlap = false;
            int pa = 0, pb = 0;
            while (pa < 4 && pb < 4) {
                if (ca[pa] == cb[pb]) { overlap = true; break; }
                if (ca[pa] < cb[pb]) ++pa;
                else ++pb;
            }
            if (!overlap) {
                if (cand > bestTwo) bestTwo = cand;
                break; // j loop: smaller sums will only reduce cand
            }
        }
    }

    // Ensure we actually found two non-overlapping tetrominoes.
    ensuref(bestTwo > 0, "No pair of non-overlapping tetrominoes found.");

    // Theoretically max is 8 * 1000 = 8000, but we computed explicitly anyway.
    ensuref(bestTwo <= 8000,
            "Maximum possible sum %lld exceeds theoretical bound 8000.",
            bestTwo);

    inf.readEof();
}
