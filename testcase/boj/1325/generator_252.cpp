#include "testlib.h"
#include <set>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    int M = rnd.next(1, min(N*(N-1), 20));
    println(N, M);
    set<pair<int, int>> edges;
    while(edges.size() < M) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if(u == v) continue;
        edges.insert({u, v});
    }
    for(auto e : edges) {
        println(e.first, e.second);
    }
}
