#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int N = rnd.next(1, 8);
    // Number of trees, weighted for diversity
    int wM = rnd.any(vector<int>{-1, 0, 1});
    int M = rnd.wnext(N * N, wM) + 1;
    // Years to simulate, weighted to get small or larger K
    int wK = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int K = rnd.wnext(20, wK) + 1;
    // Nutrient addition per cell: choose a max for diversity
    bool bigA = rnd.next() < 0.5;
    int maxA = bigA ? rnd.next(10, 20) : rnd.next(1, 10);
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rnd.next(1, maxA);
        }
    }
    // Prepare distinct positions for trees
    vector<pair<int,int>> cells;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());
    // Plant M trees with varied age distributions
    vector<tuple<int,int,int>> trees;
    for (int i = 0; i < M; i++) {
        int x = cells[i].first;
        int y = cells[i].second;
        double p = rnd.next();
        int age;
        if (p < 0.3) age = rnd.next(6, 10);
        else if (p < 0.6) age = rnd.next(1, 5);
        else age = rnd.next(1, 10);
        trees.emplace_back(x, y, age);
    }
    // Output
    println(N, M, K);
    for (int i = 0; i < N; i++)
        println(A[i]);
    for (auto &t : trees) {
        int x, y, age;
        tie(x, y, age) = t;
        println(x, y, age);
    }
    return 0;
}
