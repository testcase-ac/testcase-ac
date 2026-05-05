#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 15, "N");
    inf.readEoln();

    // 2. Read N lines, each with N digits (0-9)
    vector<string> price(N);
    for (int i = 0; i < N; ++i) {
        price[i] = inf.readToken("[0-9]{"+to_string(N)+"," + to_string(N) + "}", "price_row");
        inf.readEoln();
    }

    // 3. Validate that price[i][j] is a digit 0-9 for all i,j
    for (int i = 0; i < N; ++i) {
        ensuref((int)price[i].size() == N, "Row %d does not have exactly N=%d digits", i+1, N);
        for (int j = 0; j < N; ++j) {
            ensuref(price[i][j] >= '0' && price[i][j] <= '9', "price[%d][%d] is not a digit 0-9", i+1, j+1);
        }
    }

    // 4. No further constraints are specified in the statement.
    //    - No symmetry, no diagonal, no further global property.
    //    - The only global property is that the answer always exists (i.e., at least 2).
    //      But this is not a property to check in the input, but a property of the solution.

    inf.readEof();
}
