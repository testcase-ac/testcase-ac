#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    int total = N * M;

    // Hyper-parameter for number of jewels
    int maxJewels = min(5, total);
    double p = rnd.next();
    int jewels;
    if (p < 0.3) {
        jewels = 1;
    } else if (p < 0.6) {
        jewels = maxJewels;
    } else {
        jewels = rnd.next(1, maxJewels);
    }

    // Hyper-parameter for number of trackers
    int maxTrackers = total - jewels;
    if (maxTrackers < 0) maxTrackers = 0;
    maxTrackers = min(maxTrackers, 5);
    double q = rnd.next();
    int trackers;
    if (q < 0.3) {
        trackers = 0;
    } else if (q < 0.6) {
        trackers = maxTrackers;
    } else {
        trackers = rnd.next(0, maxTrackers);
    }

    // Choose distinct cells
    vector<int> cells(total);
    for (int i = 0; i < total; i++) cells[i] = i;
    shuffle(cells.begin(), cells.end());

    vector<string> grid(N, string(M, '.'));
    // Place jewels
    for (int i = 0; i < jewels; i++) {
        int id = cells[i];
        int r = id / M, c = id % M;
        grid[r][c] = '*';
    }
    // Place trackers
    for (int i = jewels; i < jewels + trackers; i++) {
        int id = cells[i];
        int r = id / M, c = id % M;
        grid[r][c] = '#';
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
