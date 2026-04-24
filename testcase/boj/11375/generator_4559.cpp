#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable cases
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Probability for random edge inclusion
    double p = rnd.next();

    // Prepare containers
    vector<vector<int>> can(N);

    // Hyper-parameter: number of workers with full skillset
    int full_cnt = rnd.next(0, N);
    vector<int> ids(N);
    for (int i = 0; i < N; i++) ids[i] = i;
    shuffle(ids.begin(), ids.end());

    // Assign full lists
    for (int t = 0; t < full_cnt; t++) {
        int i = ids[t];
        can[i].reserve(M);
        for (int j = 1; j <= M; j++)
            can[i].push_back(j);
    }

    // Assign random edges for the rest
    for (int i = 0; i < N; i++) {
        if ((int)can[i].size() == M) continue; // already full
        for (int j = 1; j <= M; j++) {
            if (rnd.next() < p) {
                can[i].push_back(j);
            }
        }
    }

    // Ensure there's at least one edge
    int total = 0;
    for (auto &v : can) total += v.size();
    if (total == 0) {
        int i = rnd.next(0, N-1);
        int j = rnd.next(1, M);
        can[i].push_back(j);
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        int k = can[i].size();
        // Remove duplicates, just in case
        sort(can[i].begin(), can[i].end());
        can[i].erase(unique(can[i].begin(), can[i].end()), can[i].end());
        k = can[i].size();
        printf("%d", k);
        for (int x : can[i]) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}
