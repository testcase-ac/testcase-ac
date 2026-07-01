#include "testlib.h"

#include <set>
#include <string>
#include <vector>
using namespace std;

static int countInversions(const vector<int>& values) {
    int inversions = 0;
    for (int i = 0; i < (int)values.size(); ++i) {
        for (int j = i + 1; j < (int)values.size(); ++j) {
            if (values[i] > values[j]) {
                ++inversions;
            }
        }
    }
    return inversions;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<string> seen;
    vector<int> numbers;
    int xCount = 0;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            string token = inf.readToken("[1-8]|X", "cell");
            ensuref(seen.insert(token).second,
                    "duplicate cell token at row %d, column %d: %s",
                    row + 1, col + 1, token.c_str());

            if (token == "X") {
                ++xCount;
            } else {
                numbers.push_back(token[0] - '0');
            }

            if (col == 2) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(xCount == 1, "expected exactly one X, found %d", xCount);
    ensuref((int)numbers.size() == 8, "expected exactly eight numbered tiles");

    int inversions = countInversions(numbers);
    ensuref(inversions % 2 == 0,
            "8-puzzle state is not solvable, inversion count is %d", inversions);

    inf.readEof();
}
