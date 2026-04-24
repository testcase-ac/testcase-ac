#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N
    int N;
    double p = rnd.next();
    if (p < 0.2) {
        N = 1;
    } else {
        N = rnd.next(2, 10);
    }

    // Choose rectangle dimensions H x W so that M = H * W
    int H = rnd.next(1, N);
    int W = rnd.next(1, N);
    int M = H * W;

    // Hyper-parameter for number of occupied cells (stacks)
    int S;
    double q = rnd.next();
    if (q < 0.3) {
        // favor small S
        S = rnd.wnext(M, -1) + 1;
    } else if (q < 0.6) {
        // favor large S
        S = rnd.wnext(M, 1) + 1;
    } else {
        // uniform
        S = rnd.next(1, M);
    }
    if (S > M) S = M;

    // Generate all possible cells and pick S distinct ones
    vector<pair<int,int>> all;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            all.emplace_back(i, j);
        }
    }
    shuffle(all.begin(), all.end());
    vector<pair<int,int>> cells(all.begin(), all.begin() + S);

    // Distribute M blocks among these S cells (each at least one)
    vector<int> height(S, 1);
    int rem = M - S;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, S - 1);
        height[idx]++;
    }

    // Build the list of block positions
    vector<pair<int,int>> blocks;
    blocks.reserve(M);
    for (int i = 0; i < S; i++) {
        for (int k = 0; k < height[i]; k++) {
            blocks.push_back(cells[i]);
        }
    }
    shuffle(blocks.begin(), blocks.end());

    // Output
    println(N, M);
    for (auto &b : blocks) {
        println(b.first, b.second);
    }
    return 0;
}
