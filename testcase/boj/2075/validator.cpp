#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1500, "N");
    inf.readEoln();

    // Read the N x N matrix
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        // Name for error messages for this row
        string rowName = "a_row_" + to_string(i+1);
        vector<int> row = inf.readInts(N, -1000000000, 1000000000, rowName.c_str());
        for (int j = 0; j < N; j++)
            a[i][j] = row[j];
        inf.readEoln();
    }

    // Check the strictly increasing property down each column:
    // a[i][j] > a[i-1][j]
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ensuref(a[i][j] > a[i-1][j],
                    "a[%d][%d] = %d is not greater than a[%d][%d] = %d",
                    i+1, j+1, a[i][j],
                    i,   j+1, a[i-1][j]);
        }
    }

    // Check all values are distinct
    vector<long long> vals;
    vals.reserve((size_t)N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            vals.push_back(a[i][j]);
    sort(vals.begin(), vals.end());
    for (size_t i = 1; i < vals.size(); i++) {
        ensuref(vals[i] != vals[i-1],
                "Duplicate value detected: %lld", vals[i]);
    }

    // Final EOF check
    inf.readEof();
    return 0;
}
