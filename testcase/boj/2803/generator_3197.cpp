#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int M = rnd.next(1, 7);          // number of toy types
    int N = rnd.next(1, 10);         // number of boxes
    bool fullCover = rnd.next(0, 4) > 0; // 80% chance to cover all types
    int missingType = -1;
    if (!fullCover) {
        missingType = rnd.next(1, M);
    }
    // densities for adding extra types
    double densFull = rnd.next(0.0, 1.0);
    double densPartial = rnd.next(0.0, 1.0);

    // Initialize boxes
    vector<vector<int>> boxes(N);

    // If forcing full coverage, assign each type to at least one box
    if (fullCover) {
        for (int t = 1; t <= M; t++) {
            int b = rnd.next(0, N - 1);
            boxes[b].push_back(t);
        }
    }

    // Fill boxes with additional types
    for (int i = 0; i < N; i++) {
        vector<bool> has(M+1, false);
        for (int t : boxes[i]) has[t] = true;
        for (int t = 1; t <= M; t++) {
            if (!has[t] && (fullCover || t != missingType)) {
                double p = fullCover ? densFull : densPartial;
                if (rnd.next() < p) {
                    boxes[i].push_back(t);
                    has[t] = true;
                }
            }
        }
        shuffle(boxes[i].begin(), boxes[i].end());
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        printf("%d", (int)boxes[i].size());
        for (int t : boxes[i]) {
            printf(" %d", t);
        }
        printf("\n");
    }
    return 0;
}
