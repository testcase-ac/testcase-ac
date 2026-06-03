#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> dim(11, 1);
    int shape = rnd.next(5);
    if (shape == 0) {
        dim[0] = rnd.next(1, 12);
    } else if (shape == 1) {
        dim[0] = rnd.next(2, 7);
        dim[1] = rnd.next(2, 6);
    } else if (shape == 2) {
        dim[0] = rnd.next(2, 5);
        dim[1] = rnd.next(2, 4);
        dim[2] = rnd.next(2, 3);
    } else {
        int active = rnd.next(3, 7);
        vector<int> axes(11);
        iota(axes.begin(), axes.end(), 0);
        shuffle(axes.begin(), axes.end());
        int cells = 1;
        for (int i = 0; i < active; ++i) {
            int hi = cells <= 32 ? 3 : 2;
            dim[axes[i]] = rnd.next(2, hi);
            cells *= dim[axes[i]];
        }
    }

    int cells = 1;
    for (int x : dim)
        cells *= x;

    vector<int> grid(cells, 0);
    int mode = rnd.next(5);

    if (mode == 0) {
        fill(grid.begin(), grid.end(), 1);
    } else if (mode == 1) {
        fill(grid.begin(), grid.end(), 0);
        grid[rnd.next(cells)] = 1;
    } else if (mode == 2) {
        fill(grid.begin(), grid.end(), -1);
        int first = rnd.next(cells);
        int second = rnd.next(cells);
        while (cells > 1 && second == first)
            second = rnd.next(cells);
        grid[first] = 1;
        grid[second] = 0;
    } else {
        double empty_prob = mode == 3 ? rnd.next(0.10, 0.35) : rnd.next(0.35, 0.65);
        double ripe_prob = mode == 3 ? rnd.next(0.10, 0.35) : rnd.next(0.03, 0.20);
        bool has_tomato = false;
        bool has_ripe = false;
        for (int i = 0; i < cells; ++i) {
            if (rnd.next() < empty_prob) {
                grid[i] = -1;
            } else {
                has_tomato = true;
                grid[i] = rnd.next() < ripe_prob ? 1 : 0;
                has_ripe = has_ripe || grid[i] == 1;
            }
        }
        if (!has_tomato)
            grid[rnd.next(cells)] = 1;
        if (!has_ripe)
            grid[rnd.next(cells)] = 1;
    }

    println(dim);
    for (int row = 0; row < cells / dim[0]; ++row) {
        vector<int> line;
        for (int col = 0; col < dim[0]; ++col)
            line.push_back(grid[row * dim[0] + col]);
        println(line);
    }

    return 0;
}
