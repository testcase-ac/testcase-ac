#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeRow(int n, int mode, int rowIndex, double verticalProbability) {
    string row;
    row.reserve(n);

    for (int col = 0; col < n; ++col) {
        char value = 'H';
        if (mode == 0) {
            value = rnd.next() < verticalProbability ? 'V' : 'H';
        } else if (mode == 1) {
            value = (rowIndex + col) % 2 == 0 ? 'H' : 'V';
        } else if (mode == 2) {
            value = rowIndex % 2 == 0 ? 'H' : 'V';
        } else if (mode == 3) {
            value = col % 2 == 0 ? 'V' : 'H';
        } else {
            value = rnd.next(0, 9) == 0 ? 'V' : 'H';
        }
        row.push_back(value);
    }

    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(3, 7);
    vector<int> sizes = {1, 2, rnd.next(3, 8), rnd.next(9, 16)};
    shuffle(sizes.begin(), sizes.end());

    for (int tc = 0; tc < testCount; ++tc) {
        int n;
        if (tc < (int)sizes.size()) {
            n = sizes[tc];
        } else {
            n = rnd.next(1, 20);
        }

        int mode = rnd.next(0, 4);
        double verticalProbability = rnd.next(0.15, 0.85);

        println(n);
        for (int row = 0; row < 2 * n - 1; ++row) {
            println(makeRow(n, mode, row, verticalProbability));
        }
    }

    return 0;
}
