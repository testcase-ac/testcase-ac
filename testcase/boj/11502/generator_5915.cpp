#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 15);
    println(T);

    const int low = 7, high = 999;
    int offsetCount = (high - low) / 2; // number of odd steps
    vector<int> tCandidates = {-2, -1, 0, 1, 2};
    vector<int> Ks;
    Ks.reserve(T);

    for (int i = 0; i < T; ++i) {
        int t = rnd.any(tCandidates);
        int r = rnd.wnext(offsetCount + 1, t);
        int K = low + 2 * r;
        Ks.push_back(K);
    }

    // Occasionally force edge values
    if (rnd.next(0, 1) == 1) {
        vector<int> lowEdge = {7, 9, 11};
        vector<int> highEdge = {995, 997, 999};
        if (T >= 1) Ks[0] = rnd.any(lowEdge);
        if (T >= 2) Ks[1] = rnd.any(highEdge);
    }

    for (int k : Ks) println(k);

    return 0;
}
