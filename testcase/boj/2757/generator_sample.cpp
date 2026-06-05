#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int kLimit = 300000000;

int randomNear(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(kLimit, center + radius);
    return rnd.next(lo, hi);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> columnAnchors = {
        1, 2, 25, 26, 27, 28, 51, 52, 53,
        701, 702, 703, 704,
        17575, 17576, 17577, 17578,
        kLimit - 2, kLimit - 1, kLimit,
    };
    vector<int> rowAnchors = {
        1, 2, 3, 26, 52, 53, 999, 1000,
        kLimit - 2, kLimit - 1, kLimit,
    };

    vector<pair<int, int>> cases;
    int anchorCases = rnd.next(4, 9);
    for (int i = 0; i < anchorCases; ++i) {
        cases.push_back({rnd.any(rowAnchors), rnd.any(columnAnchors)});
    }

    int randomCases = rnd.next(4, 12);
    for (int i = 0; i < randomCases; ++i) {
        int mode = rnd.next(0, 4);
        int row;
        int column;
        if (mode == 0) {
            row = rnd.next(1, 100);
            column = rnd.next(1, 100);
        } else if (mode == 1) {
            row = randomNear(rnd.any(rowAnchors), 3);
            column = randomNear(rnd.any(columnAnchors), 3);
        } else if (mode == 2) {
            row = rnd.next(1, kLimit);
            column = rnd.next(1, 1000);
        } else {
            row = rnd.next(1, kLimit);
            column = rnd.next(1, kLimit);
        }
        cases.push_back({row, column});
    }

    shuffle(cases.begin(), cases.end());

    for (const auto& cell : cases) {
        printf("R%dC%d\n", cell.first, cell.second);
    }
    printf("R0C0\n");

    return 0;
}
