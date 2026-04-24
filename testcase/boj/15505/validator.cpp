#include "testlib.h"
#include <algorithm>
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // We'll store the beauties for 4 colors: 0=red,1=blue,2=green,3=yellow
    vector<vector<vector<long long>>> beauty(4,
        vector<vector<long long>>(N, vector<long long>(M)));

    // Read the 4 blocks
    for (int c = 0; c < 4; c++) {
        const char* name;
        if (c == 0) name = "red";
        else if (c == 1) name = "blue";
        else if (c == 2) name = "green";
        else name = "yellow";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                beauty[c][i][j] = inf.readLong(0LL, 1000000000LL,
                                               // name each entry as e.g. "red[2][3]"
                                               (string(name) +
                                                "[" + to_string(i) +
                                                "][" + to_string(j) + "]").c_str());
                if (j + 1 < M) inf.readSpace();
            }
            inf.readEoln();
        }
    }

    // Check the guaranteed bound: the maximum total beauty does not exceed 2,100,000,000.
    // We compute an upper bound by summing, for each cell, the maximum beauty over colors.
    long long sum_max = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            long long m = beauty[0][i][j];
            for (int c = 1; c < 4; c++) {
                m = max(m, beauty[c][i][j]);
            }
            // Check for overflow in sum_max
            sum_max += m;
            ensuref(sum_max >= 0,
                    "Overflow in computing sum of per-cell maxima at cell (%d,%d)", i, j);
        }
    }
    ensuref(sum_max <= 2100000000LL,
            "Guaranteed maximum beauty bound violated: sum of per-cell maxima = %lld exceeds 2100000000",
            sum_max);

    inf.readEof();
    return 0;
}
