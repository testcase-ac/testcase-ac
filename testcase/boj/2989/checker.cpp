#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N, K;
vector<int> X, Y, F;
unordered_map<long long, int> coord2idx;

// Read and validate an answer (jury or participant), return the reported final energy.
int readAns(InStream &stream) {
    // Read reported final energy
    int reportedE = stream.readInt(0, 1000000000, "final energy");
    // Read path length L
    int L = stream.readInt(2, N, "L");
    vector<bool> used(N+1, false);

    // Will store the sequence of indices
    vector<int> path(L);
    int curE = 0;
    int prevX = -1, prevY = -1;

    for (int i = 0; i < L; i++) {
        // Read coordinates
        int x = stream.readInt(0, 100000, format("x[%d]", i+1).c_str());
        int y = stream.readInt(0, 100000, format("y[%d]", i+1).c_str());
        long long key = ( (long long)x << 32 ) | (unsigned long long)y;
        if (!coord2idx.count(key)) {
            stream.quitf(_wa, "leaf at (%d,%d) does not exist", x, y);
        }
        int idx = coord2idx[key];
        path[i] = idx;

        // First leaf must be 1
        if (i == 0 && idx != 1) {
            stream.quitf(_wa, "path does not start at leaf 1");
        }
        // Last leaf must be N
        if (i == L-1 && idx != N) {
            stream.quitf(_wa, "path does not end at leaf %d", N);
        }
        // No revisits
        if (used[idx]) {
            stream.quitf(_wa, "leaf %d visited more than once", idx);
        }
        used[idx] = true;

        // On first leaf, eat flies
        if (i == 0) {
            curE += F[idx];
        } else {
            // Check jump validity
            int dx = x - prevX;
            int dy = y - prevY;
            if (!((dx > 0 && dy == 0) || (dy > 0 && dx == 0))) {
                stream.quitf(_wa,
                    "invalid jump from (%d,%d) to (%d,%d)", prevX, prevY, x, y);
            }
            // Check enough energy to jump
            if (curE < K) {
                stream.quitf(_wa,
                    "not enough energy to jump: have %d, need %d", curE, K);
            }
            curE -= K;
            // Eat flies on arrival
            curE += F[idx];
        }
        prevX = x;
        prevY = y;
    }

    // Check reportedE matches computed
    if (curE != reportedE) {
        stream.quitf(_wa,
            "reported energy %d does not match computed energy %d",
            reportedE, curE);
    }
    return reportedE;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    N = inf.readInt(2, 300000);
    K = inf.readInt(1, 1000);
    X.resize(N+1);
    Y.resize(N+1);
    F.resize(N+1);
    coord2idx.reserve(N * 2);

    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(0, 100000);
        int y = inf.readInt(0, 100000);
        int f = inf.readInt(0, 1000);
        X[i] = x; Y[i] = y; F[i] = f;
        long long key = ( (long long)x << 32 ) | (unsigned long long)y;
        coord2idx[key] = i;
    }

    // Read jury and participant answers
    int juryE = readAns(ans);
    int partE = readAns(ouf);

    // Compare
    if (juryE != partE) {
        quitf(_wa, "wrong final energy: expected %d, found %d", juryE, partE);
    } else {
        quitf(_ok, "final energy = %d", partE);
    }
    return 0;
}
