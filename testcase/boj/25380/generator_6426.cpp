#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for N, M: bias slightly towards larger sizes up to 10
    int N = rnd.wnext(9, 1) + 2; // in [2,10]
    int M = rnd.wnext(9, 1) + 2; // in [2,10]

    // Generate distinct road coordinates in [-50,50]
    vector<int> poolX, poolY;
    for (int i = -50; i <= 50; ++i) {
        poolX.push_back(i);
        poolY.push_back(i);
    }
    shuffle(poolX.begin(), poolX.end());
    shuffle(poolY.begin(), poolY.end());
    vector<int> A(poolX.begin(), poolX.begin() + N);
    vector<int> B(poolY.begin(), poolY.begin() + M);

    // number of police
    int K = rnd.next(2, N + M);

    // determine how many on vertical (A) vs horizontal (B)
    int loV = max(0, K - M);
    int hiV = min(K, N);
    int Kv = rnd.next(loV, hiV);
    int Kh = K - Kv;

    // select which roads get police
    vector<int> idxA(N), idxB(M);
    iota(idxA.begin(), idxA.end(), 0);
    iota(idxB.begin(), idxB.end(), 0);
    shuffle(idxA.begin(), idxA.end());
    shuffle(idxB.begin(), idxB.end());
    idxA.resize(Kv);
    idxB.resize(Kh);

    // prepare sets for exclusion of intersections
    set<int> setA(A.begin(), A.end());
    set<int> setB(B.begin(), B.end());

    // build possible Y for vertical police (exclude horizontal roads)
    vector<int> possY;
    for (int y = -50; y <= 50; ++y)
        if (!setB.count(y))
            possY.push_back(y);
    shuffle(possY.begin(), possY.end());

    // build possible X for horizontal police (exclude vertical roads)
    vector<int> possX;
    for (int x = -50; x <= 50; ++x)
        if (!setA.count(x))
            possX.push_back(x);
    shuffle(possX.begin(), possX.end());

    // generate police positions
    vector<pair<int,int>> police;
    // vertical roads
    for (int i = 0; i < Kv; ++i) {
        int ai = A[idxA[i]];
        int yi = possY[i];
        police.emplace_back(ai, yi);
    }
    // horizontal roads
    for (int i = 0; i < Kh; ++i) {
        int bj = B[idxB[i]];
        int xi = possX[i];
        police.emplace_back(xi, bj);
    }

    // shuffle police order
    shuffle(police.begin(), police.end());

    // output
    println(N, M, K);
    println(A);
    println(B);
    for (auto &pr : police)
        println(pr.first, pr.second);

    return 0;
}
