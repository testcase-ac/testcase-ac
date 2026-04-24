#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    // Read the N pictures, each of size 5 x 7
    vector<vector<string>> pic(N, vector<string>(5));
    for (int i = 0; i < N; i++) {
        for (int r = 0; r < 5; r++) {
            // Each line must be exactly 7 characters, each either '.' or 'X'
            pic[i][r] = inf.readLine("[.X]{7}", "row");
        }
    }

    // Compute pairwise differences and find the minimum
    int min_diff = 5 * 7 + 1;
    int count_min = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int diff = 0;
            for (int r = 0; r < 5; r++) {
                for (int c = 0; c < 7; c++) {
                    if (pic[i][r][c] != pic[j][r][c]) diff++;
                }
            }
            if (diff < min_diff) {
                min_diff = diff;
                count_min = 1;
            } else if (diff == min_diff) {
                count_min++;
            }
        }
    }

    // There must be exactly one pair attaining the minimum difference
    ensuref(count_min == 1,
            "There must be exactly one pair with the minimal difference; found %d pairs with diff = %d",
            count_min, min_diff);

    inf.readEof();
    return 0;
}
