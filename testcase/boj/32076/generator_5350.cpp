#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for letter distribution
    int maxW = 100;
    int t1 = rnd.next(-2, 2);
    int t2 = rnd.next(-2, 2);
    int t3 = rnd.next(-2, 2);
    // Weights for A, B, C (at least 1 each)
    int WA = rnd.wnext(maxW, t1) + 1;
    int WB = rnd.wnext(maxW, t2) + 1;
    int WC = rnd.wnext(maxW, t3) + 1;
    int total = WA + WB + WC;

    // Build 3x3 grid with weighted random letters
    vector<string> grid(3, string(3, 'A'));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int x = rnd.next(total - 1);
            if (x < WA) grid[i][j] = 'A';
            else if (x < WA + WB) grid[i][j] = 'B';
            else grid[i][j] = 'C';
        }
    }

    // Ensure at least one of each letter appears
    vector<int> pos(9);
    iota(pos.begin(), pos.end(), 0);
    shuffle(pos.begin(), pos.end());
    grid[pos[0] / 3][pos[0] % 3] = 'A';
    grid[pos[1] / 3][pos[1] % 3] = 'B';
    grid[pos[2] / 3][pos[2] % 3] = 'C';

    // Output the grid
    for (auto &row : grid) {
        printf("%s\n", row.c_str());
    }
    return 0;
}
