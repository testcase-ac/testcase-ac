#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of columns
    int N = rnd.next(1, 10);

    // Hyper-parameter: maximum position range
    int maxL = N + rnd.next(0, 5);

    // Generate distinct positions
    vector<int> positions(maxL);
    iota(positions.begin(), positions.end(), 1);
    shuffle(positions.begin(), positions.end());
    positions.resize(N);
    sort(positions.begin(), positions.end());

    // Hyper-parameter: max height
    int maxH = rnd.next(1, 20);
    // Hyper-parameter: bias for heights
    int t = rnd.next(-3, 3);

    // Build columns
    vector<pair<int,int>> cols;
    for (int x : positions) {
        int h = rnd.wnext(maxH, t) + 1;
        cols.emplace_back(x, h);
    }

    // Hyper-parameter: shuffle output order
    if (rnd.next(0, 1) == 1) {
        shuffle(cols.begin(), cols.end());
    }

    // Output
    println(N);
    for (auto &p : cols) {
        println(p.first, p.second);
    }

    return 0;
}
