#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 8), M = rnd.next(1, min(N*(N-1), N*3));
    vector<double> weights(3);
    for(int i = 0; i < 3; i++) weights[i] = rnd.next();
    vector<tuple<int, int, int>> edges;
    sort(weights.begin(), weights.end());
    for(int i = 0; i < M; i++) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        while(u == v) {
            u = rnd.next(1, N);
            v = rnd.next(1, N);
        }
        double w = rnd.next();

        if(w < weights[0]) {
            edges.push_back({u, v, rnd.next(-5, -1)});
        } else if(w < weights[1]) {
            edges.push_back({u, v, 0});
        } else {
            edges.push_back({u, v, rnd.next(1, 5)});
        }
    }
    println(N, M);
    for(auto [u, v, w] : edges) {
        println(u, v, w);
    }
}
