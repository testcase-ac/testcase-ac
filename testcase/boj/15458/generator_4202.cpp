#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(2, 10);
    // Hyper-parameters to bias tree shape and number of pre-colored nodes
    int shapeBias = rnd.next(-3, 3);
    int colorBias = rnd.next(-3, 3);

    // Generate a random tree with bias: parent[i] in [1..i-1]
    vector<pair<int,int>> edges;
    for (int i = 2; i <= N; i++) {
        // rnd.wnext(i-1, shapeBias) gives [0..i-2] biased
        int p = rnd.wnext(i-1, shapeBias) + 1;
        edges.emplace_back(i, p);
    }
    // Shuffle edge order for randomness
    shuffle(edges.begin(), edges.end());

    // Number of already painted barns K, biased
    int K = rnd.wnext(N+1, colorBias); // gives [0..N]
    // Select K distinct barns to pre-color
    vector<int> barns(N);
    for (int i = 0; i < N; i++) barns[i] = i+1;
    shuffle(barns.begin(), barns.end());
    barns.resize(K);

    // Assign random colors 1..3
    vector<pair<int,int>> colored;
    for (int b : barns) {
        int c = rnd.next(1, 3);
        colored.emplace_back(b, c);
    }
    // Shuffle color assignment order
    shuffle(colored.begin(), colored.end());

    // Output
    println(N, K);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    for (auto &bc : colored) {
        println(bc.first, bc.second);
    }
    return 0;
}
