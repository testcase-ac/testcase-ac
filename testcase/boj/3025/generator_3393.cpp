#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small or larger board
    bool small = rnd.next(0, 1);
    int R = small ? rnd.next(1, 3) : rnd.next(4, 10);
    int C = small ? rnd.next(1, 3) : rnd.next(4, 10);

    // Hyperparameter: wall density tiers
    double dens;
    double choice = rnd.next();
    if (choice < 0.3) {
        dens = rnd.next(0.0, 0.2);
    } else if (choice < 0.6) {
        dens = rnd.next(0.2, 0.5);
    } else {
        dens = rnd.next(0.5, 0.9);
    }

    // Build grid: top row always empty so drops are valid
    vector<string> grid(R, string(C, '.'));
    for (int i = 1; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (rnd.next() < dens) {
                grid[i][j] = 'X';
            }
        }
    }

    // Number of stones to throw, at most one per column to ensure validity
    int maxN = min(20, C);
    int N = rnd.next(1, maxN);
    vector<int> cols(C);
    for (int j = 0; j < C; j++) cols[j] = j + 1;
    shuffle(cols.begin(), cols.end());
    vector<int> throws(cols.begin(), cols.begin() + N);

    // Output
    println(R, C);
    for (auto &row : grid) println(row);
    println(N);
    for (int x : throws) println(x);

    return 0;
}
