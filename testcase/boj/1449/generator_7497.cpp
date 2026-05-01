#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Maximum possible leak position
    int Pmax = rnd.next(1, 30);
    // Number of leaks
    int N = rnd.next(1, min(Pmax, 20));
    // Distribution type: 0 = uniform, 1 = clusters, 2 = consecutive block
    int distType = rnd.next(0, 2);

    vector<int> pos;
    if (distType == 0) {
        // Uniform distinct positions
        vector<int> pool(Pmax);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        pos.assign(pool.begin(), pool.begin() + N);
    } else if (distType == 1) {
        // Clustered positions
        set<int> s;
        while ((int)s.size() < N) {
            int center = rnd.next(1, Pmax);
            int offset = rnd.next(0, 4) - 2; // in [-2,2]
            int x = center + offset;
            if (x < 1) x = 1;
            if (x > Pmax) x = Pmax;
            s.insert(x);
        }
        for (int x : s) pos.push_back(x);
    } else {
        // Consecutive block
        int start = rnd.next(1, Pmax - N + 1);
        for (int i = 0; i < N; i++) {
            pos.push_back(start + i);
        }
    }
    // Shuffle to get unsorted input
    shuffle(pos.begin(), pos.end());

    // Determine tape length hyper-parameter
    int vl = *min_element(pos.begin(), pos.end());
    int vh = *max_element(pos.begin(), pos.end());
    int span = vh - vl + 1; // minimum span to cover all leaks
    int tapeType = rnd.next(0, 3);
    int L;
    switch (tapeType) {
        case 0:
            L = 1;
            break;
        case 1:
            L = rnd.next(1, min(5, 1000));
            break;
        case 2:
            L = rnd.next(1, span);
            break;
        default:
            L = rnd.next(span, span + 5);
            break;
    }

    // Output
    println(N, L);
    println(pos);

    return 0;
}
