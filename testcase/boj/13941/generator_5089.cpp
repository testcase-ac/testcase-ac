#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of glasses
    int N = rnd.next(1, 10);
    // Choose K with bias: small or large
    int tK = rnd.next(-2, 2);
    int K = rnd.wnext(N, tK) + 1; // in [1, N]
    // Symmetry hyper-parameter
    bool symmetric = rnd.next(0, 1);
    // Cost distribution type: 0=small, 1=large, 2=clustered
    int cost_type = rnd.next(0, 2);

    vector<vector<int>> C(N, vector<int>(N, 0));
    vector<int> cluster(N, 0);
    if (cost_type == 2) {
        int num_clusters = rnd.next(1, min(N, 3));
        for (int i = 0; i < N; i++) {
            cluster[i] = rnd.next(0, num_clusters - 1);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                C[i][j] = 0;
            } else if (symmetric && j < i) {
                C[i][j] = C[j][i];
            } else {
                int v;
                if (cost_type == 0) {
                    // small random costs
                    v = rnd.next(0, 5);
                } else if (cost_type == 1) {
                    // large random costs
                    v = rnd.next(0, 100000);
                } else {
                    // clustered costs
                    if (cluster[i] == cluster[j]) {
                        v = rnd.next(1, 10);
                    } else {
                        v = rnd.next(50, 100);
                    }
                }
                C[i][j] = v;
            }
        }
    }

    // Output
    println(N, K);
    for (int i = 0; i < N; i++) {
        println(C[i]);
    }
    return 0;
}
