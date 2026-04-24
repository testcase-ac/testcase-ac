#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // total number of puyos, keep it small for hand-checkability
    int total = rnd.next(0, 20);
    // prepare a list of column indices, each repeated up to 12 times (max height)
    vector<int> colList;
    for (int c = 0; c < 6; c++)
        for (int i = 0; i < 12; i++)
            colList.push_back(c);
    shuffle(colList.begin(), colList.end());
    // assign heights per column
    vector<int> height(6, 0);
    for (int i = 0; i < total; i++)
        height[colList[i]]++;
    // initialize empty grid
    vector<string> grid(12, string(6, '.'));
    // colors
    vector<char> colors = {'R','G','B','P','Y'};
    // hyperparameter: choose uniform or biased color distribution
    bool uniformMode = rnd.next() < 0.5;
    char biasColor = rnd.any(colors);
    // fill the grid with gravity: bottom-up per column
    for (int c = 0; c < 6; c++) {
        for (int j = 0; j < height[c]; j++) {
            int r = 11 - j;
            char col;
            if (uniformMode) {
                col = rnd.any(colors);
            } else {
                if (rnd.next() < 0.4)
                    col = biasColor;
                else
                    col = rnd.any(colors);
            }
            grid[r][c] = col;
        }
    }
    // output 12 lines of 6 characters
    for (int r = 0; r < 12; r++)
        println(grid[r]);
    return 0;
}
