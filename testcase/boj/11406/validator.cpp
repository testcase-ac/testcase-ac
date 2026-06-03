#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    vector<int> wants = inf.readInts(n, 1, 100, "a");
    inf.readEoln();

    vector<int> stocks = inf.readInts(m, 1, 100, "b");
    inf.readEoln();

    int total_wants = accumulate(wants.begin(), wants.end(), 0);
    int total_stocks = accumulate(stocks.begin(), stocks.end(), 0);
    ensuref(total_wants == total_stocks,
            "sum of A must equal sum of B, got %d and %d",
            total_wants,
            total_stocks);

    for (int i = 0; i < m; ++i) {
        inf.readInts(n, 0, 100, "c");
        inf.readEoln();
    }

    inf.readEof();
}
