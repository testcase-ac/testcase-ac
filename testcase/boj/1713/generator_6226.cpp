#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of frames
    int N = rnd.next(1, 20);
    // Total recommendations
    int R = rnd.next(1, 60);

    // Build a pool of distinct student IDs
    vector<int> allStu(100);
    iota(allStu.begin(), allStu.end(), 1);
    shuffle(allStu.begin(), allStu.end());
    int P = rnd.next(1, min(R, 15));
    vector<int> pool(allStu.begin(), allStu.begin() + P);

    // Choose some heavy-hitter students
    int H = rnd.next(1, min(P, N));
    vector<int> temp = pool;
    shuffle(temp.begin(), temp.end());
    // Mark heavy hitters
    vector<bool> isHeavy(101, false);
    for (int i = 0; i < H; ++i) {
        isHeavy[temp[i]] = true;
    }

    // Build weighted sampling list
    vector<int> wpool;
    for (int id : pool) {
        int w = isHeavy[id] ? rnd.next(5, 10) : rnd.next(1, 3);
        for (int k = 0; k < w; ++k)
            wpool.push_back(id);
    }

    // Generate recommendation sequence
    vector<int> recs;
    recs.reserve(R);
    for (int i = 0; i < R; ++i) {
        recs.push_back(rnd.any(wpool));
    }

    // Output
    println(N);
    println(R);
    println(recs);

    return 0;
}
