#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of signals and road length
    int N = rnd.next(1, 10);
    int L = rnd.next(N + 1, 20);

    // Decide position pattern: uniform or clustered
    int pattern = rnd.next(0, 1);
    vector<int> positions;
    if (pattern == 0) {
        // Uniform distinct positions in [1, L-1]
        vector<int> all;
        for (int i = 1; i < L; i++) all.push_back(i);
        shuffle(all.begin(), all.end());
        positions.assign(all.begin(), all.begin() + N);
    } else {
        // Clustered positions within a small window
        int maxWindow = min(L - 2, N - 1 + 5);
        int wLen = rnd.next(N - 1, maxWindow);
        int start = rnd.next(1, L - 1 - wLen);
        vector<int> cluster;
        for (int x = start; x <= start + wLen; x++) cluster.push_back(x);
        shuffle(cluster.begin(), cluster.end());
        positions.assign(cluster.begin(), cluster.begin() + N);
    }
    sort(positions.begin(), positions.end());

    // Hyperparameter for max red/green time
    int maxRG = rnd.next(1, 20);
    // For bias in wnext
    vector<int> biasChoices = {-1, 0, 1};

    // Output header
    println(N, L);
    // Output each signal
    for (int d : positions) {
        int tR = rnd.any(biasChoices);
        int tG = rnd.any(biasChoices);
        int R = rnd.wnext(maxRG, tR) + 1;
        int G = rnd.wnext(maxRG, tG) + 1;
        println(d, R, G);
    }

    return 0;
}
