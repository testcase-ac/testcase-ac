#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(1, 10);

    // Decide between a DAG structure or a clustered general graph
    bool isDAG = rnd.next() < 0.3;

    // Initialize adjacency matrix with zeros
    vector<vector<int>> mat(N, vector<int>(N, 0));

    if (isDAG) {
        // DAG: only edges i -> j for i < j
        double density = rnd.next();  // uniform in [0,1)
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (rnd.next() < density) {
                    mat[i][j] = 1;
                }
            }
        }
    } else {
        // General graph with cluster-based probabilities
        int maxClusters = N < 3 ? N : 3;
        int C = rnd.next(1, maxClusters);
        vector<int> cluster(N);
        for (int i = 0; i < N; i++) {
            cluster[i] = rnd.next(0, C - 1);
        }
        double p_in  = rnd.next();         // probability for intra-cluster edges
        double p_out = rnd.next() * p_in;  // smaller probability for inter-cluster

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (cluster[i] == cluster[j]) {
                    if (rnd.next() < p_in) mat[i][j] = 1;
                } else {
                    if (rnd.next() < p_out) mat[i][j] = 1;
                }
            }
        }
    }

    // Output the test case
    println(N);
    for (int i = 0; i < N; i++) {
        println(mat[i]);
    }

    return 0;
}
