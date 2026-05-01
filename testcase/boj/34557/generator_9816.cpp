#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose scenario type for variability
    int scenario = rnd.next(0, 4); // 0..4

    int N, M;
    if (scenario == 0) {
        // Very small grid, short sequence
        N = rnd.next(1, 3);
        M = rnd.next(1, 8);
    } else if (scenario == 1) {
        // Small grid, medium sequence
        N = rnd.next(4, 8);
        M = rnd.next(10, 30);
    } else if (scenario == 2) {
        // Medium grid, medium-long sequence
        N = rnd.next(5, 10);
        M = rnd.next(15, 40);
    } else if (scenario == 3) {
        // Edge case: 1x1 grid
        N = 1;
        M = rnd.next(1, 20);
    } else {
        // Narrow grids, various lengths
        N = rnd.next(2, 6);
        M = rnd.next(5, 30);
    }

    // Generate map
    vector<vector<int>> grid(N, vector<int>(N, 0));

    // Choose start position
    int sr = rnd.next(0, N - 1);
    int sc = rnd.next(0, N - 1);
    grid[sr][sc] = 2;

    // Obstacle density by scenario
    double p;
    if (scenario == 0) p = 0.2;
    else if (scenario == 1) p = 0.35;
    else if (scenario == 2) p = 0.5;
    else if (scenario == 3) p = 0.0; // no obstacles on 1x1
    else p = 0.4;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == sr && j == sc) continue;
            if (rnd.next() < p) grid[i][j] = 1;
        }
    }

    // Assign events to W, A, S, D
    vector<string> events = {"Down", "Stay", "Up"};
    vector<string> mapping(4);

    int assignType = rnd.next(0, 1); // 0 or 1
    if (assignType == 0) {
        // Each key independently random event
        for (int i = 0; i < 4; i++) {
            mapping[i] = events[rnd.next(0, 2)];
        }
    } else {
        // Ensure all three event types appear at least once
        vector<int> idx = {0, 1, 2, 3};
        shuffle(idx.begin(), idx.end());
        mapping[idx[0]] = "Down";
        mapping[idx[1]] = "Stay";
        mapping[idx[2]] = "Up";
        mapping[idx[3]] = events[rnd.next(0, 2)];
    }

    // Generate key sequence of length M
    string keys = "WASD";
    string seq;
    seq.reserve(M);

    int patternType = rnd.next(0, 3); // 0..3
    if (patternType == 0) {
        // Fully random keys
        for (int i = 0; i < M; i++) {
            seq.push_back(rnd.any(keys));
        }
    } else if (patternType == 1) {
        // Long runs of the same key (many Stay events)
        char cur = rnd.any(keys);
        while ((int)seq.size() < M) {
            int rem = M - (int)seq.size();
            int lenSeg = rnd.next(1, min(5, rem));
            for (int k = 0; k < lenSeg; k++) seq.push_back(cur);
            // pick next key (possibly same, but often different)
            char nxt = rnd.any(keys);
            if (rnd.next(0, 1) == 1) {
                // ensure change sometimes
                while (nxt == cur) nxt = rnd.any(keys);
            }
            cur = nxt;
        }
    } else if (patternType == 2) {
        // Alternating between two keys (many Up events, no Stay)
        char a = rnd.any(keys);
        char b;
        do { b = rnd.any(keys); } while (b == a);
        for (int i = 0; i < M; i++) {
            seq.push_back((i % 2 == 0) ? a : b);
        }
    } else {
        // Cycle through W, A, S, D
        for (int i = 0; i < M; i++) {
            seq.push_back(keys[i % 4]);
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    // W, A, S, D mapping
    println(mapping[0]);
    println(mapping[1]);
    println(mapping[2]);
    println(mapping[3]);
    println(seq);

    return 0;
}
