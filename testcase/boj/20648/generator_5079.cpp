#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of cows
    int N = rnd.next(1, 10);

    // Hyper-parameter: coordinate range scale
    vector<int> ranges = {20, 100000, 1000000000};
    int R = rnd.any(ranges);

    // Hyper-parameter: pattern of coordinates
    // 0: grid both, 1: grid x random y, 2: random x grid y, 3: random both
    int pattern = rnd.next(0, 3);

    vector<int> xs, ys;
    // Generate x coordinates
    if (pattern == 0 || pattern == 1) {
        // grid: 0,1,2,...,N-1
        for (int i = 0; i < N; ++i) xs.push_back(i);
    } else {
        // random unique in [0..R]
        set<int> sx;
        while ((int)sx.size() < N) {
            sx.insert(rnd.next(0, R));
        }
        xs.assign(sx.begin(), sx.end());
    }
    // Generate y coordinates
    if (pattern == 0 || pattern == 2) {
        for (int i = 0; i < N; ++i) ys.push_back(i);
    } else {
        set<int> sy;
        while ((int)sy.size() < N) {
            sy.insert(rnd.next(0, R));
        }
        ys.assign(sy.begin(), sy.end());
    }

    // Shuffle coordinates independently to break any alignment
    shuffle(xs.begin(), xs.end());
    shuffle(ys.begin(), ys.end());

    // Pair them up
    vector<pair<int,int>> pts;
    for (int i = 0; i < N; ++i) {
        pts.emplace_back(xs[i], ys[i]);
    }
    // Finally shuffle the point order
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
