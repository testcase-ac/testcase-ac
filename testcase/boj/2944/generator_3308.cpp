#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of students
    int N = rnd.next(1, 10);
    // Hyper-parameter for number of periods H: weighted to produce small, medium, or large values
    vector<int> ts = {-2, -1, 0, 1, 2};
    int t = rnd.any(ts);
    int H = rnd.wnext(1000000000, t) + 1;

    // Build adjacency matrix initialized to no edges
    vector<string> adj(N, string(N, '0'));

    // Hyper-parameter for graph shape: star, path, complete, or random density
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // star graph: node 1 connected to all others
        for (int i = 1; i < N; i++) {
            adj[0][i] = adj[i][0] = '1';
        }
    } else if (mode == 1) {
        // path graph: 1-2-3-...-N
        for (int i = 0; i + 1 < N; i++) {
            adj[i][i+1] = adj[i+1][i] = '1';
        }
    } else if (mode == 2) {
        // complete graph
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                adj[i][j] = adj[j][i] = '1';
    } else {
        // random density graph
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (rnd.next() < p) {
                    adj[i][j] = adj[j][i] = '1';
                }
            }
        }
    }

    // Output
    println(N, H);
    for (int i = 0; i < N; i++) {
        println(adj[i]);
    }

    return 0;
}
