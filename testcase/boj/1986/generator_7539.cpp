#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Board size
    int N = rnd.next(1, 15);
    int M = rnd.next(1, 15);
    int C = N * M;

    // Hyper-parameter skew for piece counts
    int maxQ = min(C, 100);
    int t1 = rnd.next(-3, 3);
    int Q = rnd.wnext(maxQ + 1, t1);

    int rem1 = C - Q;
    int maxK = min(rem1, 100);
    int t2 = rnd.next(-3, 3);
    int K = rnd.wnext(maxK + 1, t2);

    int rem2 = rem1 - K;
    int maxP = min(rem2, 100);
    int t3 = rnd.next(-3, 3);
    int P = rnd.wnext(maxP + 1, t3);

    // Generate all cells and shuffle
    vector<pair<int,int>> cells;
    cells.reserve(C);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());

    // Assign pieces
    vector<pair<int,int>> queens(cells.begin(), cells.begin() + Q);
    vector<pair<int,int>> knights(cells.begin() + Q, cells.begin() + Q + K);
    vector<pair<int,int>> pawns(cells.begin() + Q + K, cells.begin() + Q + K + P);

    // Output
    println(N, M);

    vector<int> line;
    line.clear();
    line.push_back(Q);
    for (auto &p : queens) {
        line.push_back(p.first);
        line.push_back(p.second);
    }
    println(line);

    line.clear();
    line.push_back(K);
    for (auto &p : knights) {
        line.push_back(p.first);
        line.push_back(p.second);
    }
    println(line);

    line.clear();
    line.push_back(P);
    for (auto &p : pawns) {
        line.push_back(p.first);
        line.push_back(p.second);
    }
    println(line);

    return 0;
}
