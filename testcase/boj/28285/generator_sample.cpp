#include "testlib.h"

#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

int rowLength(int n, int row) {
    return 2 * n - 1 - abs(row - n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(20, 1000);
    } else {
        n = rnd.next(2, 12);
    }

    vector<pair<int, int>> candidates;
    candidates.push_back({1, 1});
    candidates.push_back({n, 1});
    candidates.push_back({n, n});
    candidates.push_back({n, 2 * n - 1});
    candidates.push_back({2 * n - 1, 1});
    candidates.push_back({n, rnd.next(1, 2 * n - 1)});

    int upperRow = rnd.next(1, n);
    candidates.push_back({upperRow, rnd.next(1, rowLength(n, upperRow))});

    int lowerRow = rnd.next(n, 2 * n - 1);
    candidates.push_back({lowerRow, rnd.next(1, rowLength(n, lowerRow))});

    int randomRow = rnd.next(1, 2 * n - 1);
    candidates.push_back({randomRow, rnd.next(1, rowLength(n, randomRow))});

    pair<int, int> start = rnd.any(candidates);
    println(n, start.first, start.second);

    return 0;
}
