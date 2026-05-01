#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of fields
    int N = rnd.next(2, 10);
    // Hyper-parameters: choose well and pipe cost scales
    vector<int> scales = {10, 100, 1000};
    int wellScale = rnd.any(scales);
    int pipeScale = rnd.any(scales);
    double heavyProb = rnd.next(0.0, 1.0);

    // Generate well-digging costs
    vector<int> W(N);
    for (int i = 0; i < N; i++) {
        W[i] = rnd.next(1, wellScale);
    }

    // Generate pipe-connection costs symmetrically
    vector<vector<int>> P(N, vector<int>(N, 0));
    int heavyMin = pipeScale * 2;
    int heavyMax = pipeScale * 5;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int cost;
            if (rnd.next() < heavyProb)
                cost = rnd.next(heavyMin, heavyMax);
            else
                cost = rnd.next(1, pipeScale);
            P[i][j] = P[j][i] = cost;
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(W[i]);
    }
    for (int i = 0; i < N; i++) {
        println(P[i]);
    }
    return 0;
}
