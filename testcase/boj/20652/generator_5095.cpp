#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cows
    int N = rnd.next(2, 10);
    // Ensure at least one north and one east
    int kNorth = rnd.next(1, N - 1);
    int kEast = N - kNorth;

    // Coordinate range hyper-parameter
    int maxCoord = rnd.next(N, N + 10);

    // Generate N distinct x- and y-coordinates in [0..maxCoord]
    vector<int> xs(maxCoord + 1), ys(maxCoord + 1);
    iota(xs.begin(), xs.end(), 0);
    iota(ys.begin(), ys.end(), 0);
    shuffle(xs.begin(), xs.end());
    shuffle(ys.begin(), ys.end());
    xs.resize(N);
    ys.resize(N);

    // Assign directions
    vector<char> dir;
    dir.insert(dir.end(), kNorth, 'N');
    dir.insert(dir.end(), kEast,  'E');
    shuffle(dir.begin(), dir.end());

    // Randomize input order
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    // Output
    println(N);
    for (int i : order) {
        println(dir[i], xs[i], ys[i]);
    }

    return 0;
}
