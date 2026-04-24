#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of rows
    int R;
    if (rnd.next() < 0.7) {
        R = rnd.next(10, 15);
    } else {
        R = rnd.next(16, 20);
    }
    // Hyper-parameter for number of columns
    int C;
    if (rnd.next() < 0.7) {
        C = rnd.next(10, 15);
    } else {
        C = rnd.next(16, 25);
    }

    // Choose 9 distinct rows for the kayaks
    vector<int> rows(R);
    iota(rows.begin(), rows.end(), 0);
    shuffle(rows.begin(), rows.end());
    rows.resize(9);

    // Bias for kayak placement: negative = near start, zero = uniform, positive = near finish
    vector<int> biases = {-2, -1, 0, 1, 2};
    int bias = rnd.any(biases);

    // Prepare empty grid with 'S' and 'F'
    vector<string> grid(R, string(C, '.'));
    for (int i = 0; i < R; i++) {
        grid[i][0] = 'S';
        grid[i][C - 1] = 'F';
    }

    // Place each kayak (length 3) for teams 1..9
    int maxOffset = C - 4; // 0-based offset from column 1
    for (int t = 1; t <= 9; t++) {
        int r = rows[t-1];
        int off = rnd.wnext(maxOffset, bias);
        int start = 1 + off;
        char mark = char('0' + t);
        for (int k = 0; k < 3; k++) {
            grid[r][start + k] = mark;
        }
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
