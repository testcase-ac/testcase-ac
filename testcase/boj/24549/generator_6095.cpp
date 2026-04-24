#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N
    double pN = rnd.next();
    int N;
    if (pN < 0.2) N = rnd.next(1, 3);
    else if (pN < 0.6) N = rnd.next(4, 6);
    else N = rnd.next(7, 9);

    // Hyper-parameter for M
    double pM = rnd.next();
    int M;
    if (pM < 0.2) M = rnd.next(1, 3);
    else if (pM < 0.6) M = rnd.next(4, 6);
    else M = rnd.next(7, 9);

    int S = N * M;

    // Hyper-parameter for K
    double q = rnd.next();
    int K;
    if (q < 0.1) {
        K = 0;                       // no soldiers
    } else if (q < 0.2) {
        K = S;                       // full of soldiers
    } else if (q < 0.5) {
        // bias to small K
        K = rnd.wnext(S + 1, -1);
    } else if (q < 0.8) {
        // bias to large K
        K = rnd.wnext(S + 1, 1);
    } else {
        // uniform
        K = rnd.next(0, S);
    }
    if (K > S) K = S;

    // Generate all cells and pick K for soldiers
    vector<pair<int,int>> cells;
    cells.reserve(S);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cells.emplace_back(i, j);
        }
    }
    shuffle(cells.begin(), cells.end());
    vector<pair<int,int>> soldiers(cells.begin(), cells.begin() + K);

    // Output
    println(N, M, K);
    for (auto &pr : soldiers) {
        println(pr.first, pr.second);
    }

    return 0;
}
