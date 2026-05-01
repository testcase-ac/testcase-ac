#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int N = rnd.next(2, 10);
    // Road density mode: 0=no roads,1=sparse,2=medium,3=dense,4=full
    int mode = rnd.next(0, 4);
    double p;
    if (mode == 0) p = 0.0;
    else if (mode == 1) p = rnd.next() * 0.2 + 0.05;    // ~[0.05,0.25)
    else if (mode == 2) p = rnd.next() * 0.4 + 0.25;    // ~[0.25,0.65)
    else if (mode == 3) p = rnd.next() * 0.3 + 0.65;    // ~[0.65,0.95)
    else p = 1.0;                                      // full roads

    // Generate roads between adjacent cells
    vector<tuple<int,int,int,int>> roads;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i < N && rnd.next() < p) {
                roads.emplace_back(i, j, i+1, j);
            }
            if (j < N && rnd.next() < p) {
                roads.emplace_back(i, j, i, j+1);
            }
        }
    }
    shuffle(roads.begin(), roads.end());

    int R = roads.size();
    // Number of cows K with variety: small, medium, large
    int kind = rnd.next(0, 2);
    int l, h;
    if (kind == 0) {
        l = 1; h = min(3, N*N);
    } else if (kind == 1) {
        l = 4; h = min(N, N*N);
    } else {
        l = max(4, N+1); h = N*N;
    }
    if (l > h) l = h;
    int K = rnd.next(l, h);

    // Generate distinct cow positions
    vector<pair<int,int>> cells;
    cells.reserve(N*N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());
    cells.resize(K);

    // Output
    println(N, K, R);
    for (auto &t : roads) {
        int r1, c1, r2, c2;
        tie(r1, c1, r2, c2) = t;
        println(r1, c1, r2, c2);
    }
    for (auto &c : cells) {
        println(c.first, c.second);
    }
    return 0;
}
