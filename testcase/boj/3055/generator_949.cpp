#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    // Register test generator with default seed handling.
    registerGen(argc, argv, 1);

    // Generate small R and C for easy manual verification.
    int R = rnd.next(2, 6);
    int C = rnd.next(2, 6);

    // Print the first line: R C
    println(R, C);

    // Prepare an R x C grid filled with '.'
    vector<string> grid(R, string(C, '.'));

    // Randomly place 'S' (the hedgehog)
    int s_r = rnd.next(0, R - 1);
    int s_c = rnd.next(0, C - 1);
    grid[s_r][s_c] = 'S';

    // Randomly place 'D' (the beaver's den), not overlapping 'S'
    while (true) {
        int d_r = rnd.next(0, R - 1);
        int d_c = rnd.next(0, C - 1);
        if (d_r == s_r && d_c == s_c) continue; // Must be distinct
        grid[d_r][d_c] = 'D';
        break;
    }

    // Place some water ('*') in empty cells
    int waterCount = rnd.next(0, (R * C) / 3);
    for (int i = 0; i < waterCount; i++) {
        int wr = rnd.next(0, R - 1);
        int wc = rnd.next(0, C - 1);
        if (grid[wr][wc] == '.') {
            grid[wr][wc] = '*';
        }
    }

    // Place some rocks ('X') in empty cells
    int rockCount = rnd.next(0, (R * C) / 3);
    for (int i = 0; i < rockCount; i++) {
        int rr = rnd.next(0, R - 1);
        int rc = rnd.next(0, C - 1);
        if (grid[rr][rc] == '.') {
            grid[rr][rc] = 'X';
        }
    }

    // Output the resulting forest map
    for(int i = 0; i < R; i++) {
        cout << grid[i] << "\n";
    }

    return 0;
}
