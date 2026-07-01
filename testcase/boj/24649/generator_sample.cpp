#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const vector<pair<int, int>> kQ = {
    {0, 0}, {0, 1}, {0, 2},
    {1, 0},         {1, 2},
    {2, 0}, {2, 1}, {2, 2},
                    {3, 2},
                    {4, 2},
};

const vector<pair<int, int>> kF = {
    {0, 0}, {0, 1}, {0, 2},
    {1, 0},
    {2, 0}, {2, 1},
    {3, 0},
    {4, 0},
};

void draw(vector<string>& grid, int top, int left,
          const vector<pair<int, int>>& shape) {
    for (auto [di, dj] : shape) {
        grid[top + di][left + dj] = '#';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int rowBlocks = rnd.next(1, 4);
    int colBlocks = rnd.next(1, 6);
    int n = rowBlocks * 5 + rnd.next(0, 3);
    int m = colBlocks * 3 + rnd.next(0, 4);

    vector<int> rowStarts;
    vector<int> colStarts;
    for (int i = 0; i < rowBlocks; ++i) {
        rowStarts.push_back(i * 5);
    }
    for (int j = 0; j < colBlocks; ++j) {
        colStarts.push_back(j * 3);
    }

    vector<string> grid(n, string(m, '.'));
    vector<pair<int, int>> slots;
    for (int top : rowStarts) {
        for (int left : colStarts) {
            slots.emplace_back(top, left);
        }
    }
    shuffle(slots.begin(), slots.end());

    int mode = rnd.next(0, 4);
    int maxLetters = (int)slots.size();
    int letters;
    if (mode == 0) {
        letters = rnd.next(0, min(maxLetters, 2));
    } else if (mode == 1) {
        letters = rnd.next(1, maxLetters);
    } else if (mode == 2) {
        letters = maxLetters;
    } else {
        letters = rnd.wnext(maxLetters + 1, -2);
    }

    for (int i = 0; i < letters; ++i) {
        auto [top, left] = slots[i];
        bool makeQ = rnd.next(0, 1) == 1;
        draw(grid, top, left, makeQ ? kQ : kF);
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
