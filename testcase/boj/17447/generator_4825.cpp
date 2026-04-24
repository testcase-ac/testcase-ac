#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Land size
    int N = rnd.next(3, 10);
    int maxM = (N - 1) * (N - 1);
    int M = rnd.next(1, min(maxM, 20));

    // Ensure at least one lion and one brown if possible
    int Ppos, Pneg;
    if (M > 1) {
        Ppos = rnd.next(1, M - 1);
        Pneg = M - Ppos;
    } else {
        Ppos = 1;
        Pneg = 0;
    }

    // Value distribution hyper-parameters
    int tPos = rnd.next(-2, 2);
    int tNeg = rnd.next(-2, 2);
    int posValMax = rnd.wnext(100, tPos) + 1;  // [1..100]
    int negValMax = rnd.wnext(100, tNeg) + 1;  // [1..100]

    // Generate all possible interior cells and shuffle
    vector<pair<int,int>> cells;
    for (int x = 1; x < N; ++x)
        for (int y = 1; y < N; ++y)
            cells.emplace_back(x, y);
    shuffle(cells.begin(), cells.end());

    // Assign statues
    vector<tuple<int,int,int>> statues;
    for (int i = 0; i < Ppos; ++i) {
        int x = cells[i].first, y = cells[i].second;
        int v = rnd.next(1, posValMax);
        statues.emplace_back(x, y, v);
    }
    for (int i = 0; i < Pneg; ++i) {
        int x = cells[Ppos + i].first, y = cells[Ppos + i].second;
        int v = -rnd.next(1, negValMax);
        statues.emplace_back(x, y, v);
    }
    shuffle(statues.begin(), statues.end());

    // Output
    println(N, M);
    for (auto &t : statues) {
        int x, y, v;
        tie(x, y, v) = t;
        println(x, y, v);
    }
    return 0;
}
