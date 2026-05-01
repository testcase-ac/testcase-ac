#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for number of columns K
    int type = rnd.next(0, 3);
    int K;
    if (type == 0) {
        K = 1;                      // edge case: single column
    } else if (type == 1) {
        K = rnd.next(2, 5);         // small K
    } else if (type == 2) {
        K = rnd.next(6, 10);        // medium K
    } else {
        K = rnd.next(11, 20);       // large K
    }
    // Determine number of rows R so that K * R <= 200
    int maxR = min(20, 200 / K);
    int R = rnd.next(1, maxR);      // at least one row
    int L = K * R;
    // Generate original message S of length L
    string S;
    S.reserve(L);
    for (int i = 0; i < L; i++) {
        S += char(rnd.next('a', 'z'));
    }
    // Fill grid column by column, top-down, left-right
    vector<vector<char>> grid(R, vector<char>(K));
    int pos = 0;
    for (int c = 0; c < K; c++) {
        for (int r = 0; r < R; r++) {
            grid[r][c] = S[pos++];
        }
    }
    // Read out encrypted string E: row by row, zigzag
    string E;
    E.reserve(L);
    for (int r = 0; r < R; r++) {
        if (r % 2 == 0) {
            for (int c = 0; c < K; c++) E += grid[r][c];
        } else {
            for (int c = K - 1; c >= 0; c--) E += grid[r][c];
        }
    }
    // Output the test case
    println(K);
    println(E);
    return 0;
}
