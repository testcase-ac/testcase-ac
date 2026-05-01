#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of matrices
    int N = rnd.next(1, 10);
    vector<pair<int,int>> dims(N);

    // Pattern of dimensions:
    // 0 = fully random,
    // 1 = non-decreasing second dimension,
    // 2 = non-increasing second dimension,
    // 3 = zigzag (asc on odd, desc on even steps)
    int pattern = rnd.next(0, 3);

    if (pattern == 0) {
        // Fully random r and c
        dims[0].first = rnd.next(1, 100);
        dims[0].second = rnd.next(1, 100);
        for (int i = 1; i < N; i++) {
            dims[i].first = dims[i-1].second;
            dims[i].second = rnd.next(1, 100);
        }
    }
    else if (pattern == 1) {
        // Non-decreasing second dimension
        dims[0].first = rnd.next(1, 50);
        dims[0].second = rnd.next(dims[0].first, 100);
        for (int i = 1; i < N; i++) {
            dims[i].first = dims[i-1].second;
            dims[i].second = rnd.next(dims[i].first, 100);
        }
    }
    else if (pattern == 2) {
        // Non-increasing second dimension
        dims[0].first = rnd.next(50, 100);
        dims[0].second = rnd.next(1, dims[0].first);
        for (int i = 1; i < N; i++) {
            dims[i].first = dims[i-1].second;
            dims[i].second = rnd.next(1, dims[i].first);
        }
    }
    else {
        // Zigzag pattern: ascend on odd, descend on even steps
        dims[0].first = rnd.next(1, 100);
        dims[0].second = rnd.next(1, 100);
        for (int i = 1; i < N; i++) {
            dims[i].first = dims[i-1].second;
            if (i % 2 == 1) {
                dims[i].second = rnd.next(dims[i].first, 100);
            } else {
                dims[i].second = rnd.next(1, dims[i].first);
            }
        }
    }

    // Output
    println(N);
    for (auto &p : dims) {
        println(p.first, p.second);
    }

    return 0;
}
