#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> dims;
    for (int n = 1; n <= 9; ++n) {
        for (int m = 1; m <= 9; ++m) {
            int cells = n * m;
            if (2 <= cells && cells <= 9) {
                dims.push_back({n, m});
            }
        }
    }

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> candidates;
    for (auto dim : dims) {
        int n = dim.first;
        int m = dim.second;
        int cells = n * m;

        if (mode == 0 && cells <= 3) {
            candidates.push_back(dim);
        } else if (mode == 1 && (n == 1 || m == 1)) {
            candidates.push_back(dim);
        } else if (mode == 2 && n > 1 && m > 1 && cells <= 6) {
            candidates.push_back(dim);
        } else if (mode == 3 && cells == 9) {
            candidates.push_back(dim);
        } else if (mode == 4 && n <= m) {
            candidates.push_back(dim);
        } else if (mode == 5 && n >= m) {
            candidates.push_back(dim);
        }
    }

    if (candidates.empty()) {
        candidates = dims;
    }

    auto dim = rnd.any(candidates);
    println(dim.first, dim.second);

    return 0;
}
