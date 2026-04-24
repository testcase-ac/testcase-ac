#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions and cut counts
    // Constraints: 1 ≤ r < n ≤ 18, 1 ≤ s < m ≤ 18
    // Since r ≥ 1 ⇒ n ≥ 2; similarly, m ≥ 2
    int n = inf.readInt(2, 18, "n");
    inf.readSpace();
    int m = inf.readInt(2, 18, "m");
    inf.readSpace();
    int r = inf.readInt(1, n - 1, "r");
    inf.readSpace();
    int s = inf.readInt(1, m - 1, "s");
    inf.readEoln();

    // Read the grid: n rows of m non-negative integers ≤ 2e6
    for (int i = 0; i < n; i++) {
        // We name each row token for clearer error messages
        vector<int> row = inf.readInts(m, 0, 2000000, ("a_row_" + to_string(i)).c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
