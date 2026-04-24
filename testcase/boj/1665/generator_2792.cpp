#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: maximum coordinate
    int Cmax = (rnd.next(0, 1) == 0 ? rnd.next(10, 20) : rnd.next(20, 100));
    // Maximum number of segments
    int maxSeg = min(Cmax / 2, 10);
    int N = rnd.next(1, maxSeg);
    int M = rnd.next(1, maxSeg);

    // Function to generate a coordinate in [1, Cmax], skewed or uniform
    auto randCoord = [&]() {
        if (rnd.next(0, 1) == 0)
            return rnd.wnext(Cmax, -1) + 1;  // skewed towards smaller
        else
            return rnd.next(1, Cmax);        // uniform
    };

    // Generate segments for A
    vector<pair<int,int>> segA;
    vector<int> ptsA(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        ptsA[i] = randCoord();
    }
    sort(ptsA.begin(), ptsA.end());
    for (int i = 0; i < N; i++) {
        segA.emplace_back(ptsA[2*i], ptsA[2*i+1]);
    }
    if (rnd.next() < 0.5) shuffle(segA.begin(), segA.end());

    // Generate segments for B
    vector<pair<int,int>> segB;
    vector<int> ptsB(2 * M);
    for (int i = 0; i < 2 * M; i++) {
        ptsB[i] = randCoord();
    }
    sort(ptsB.begin(), ptsB.end());
    for (int i = 0; i < M; i++) {
        segB.emplace_back(ptsB[2*i], ptsB[2*i+1]);
    }
    if (rnd.next() < 0.5) shuffle(segB.begin(), segB.end());

    // Output
    println(N);
    for (auto &p : segA) println(p.first, p.second);
    println(M);
    for (auto &p : segB) println(p.first, p.second);

    return 0;
}
