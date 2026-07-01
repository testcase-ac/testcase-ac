#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> bandPermutation(int n) {
    vector<int> groups(n);
    iota(groups.begin(), groups.end(), 0);
    shuffle(groups.begin(), groups.end());

    vector<int> order;
    order.reserve(n * n);
    for (int group : groups) {
        vector<int> inside(n);
        iota(inside.begin(), inside.end(), 0);
        shuffle(inside.begin(), inside.end());
        for (int offset : inside) {
            order.push_back(group * n + offset);
        }
    }
    return order;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> smallN = {2, 3, 4, 5};
    vector<int> mediumN = {6, 7, 8, 9, 10, 12};
    int mode = rnd.next(0, 4);
    int n = mode <= 2 ? rnd.any(smallN) : rnd.any(mediumN);
    int side = n * n;

    vector<int> rowOrder = bandPermutation(n);
    vector<int> colOrder = bandPermutation(n);

    vector<int> symbols(side);
    iota(symbols.begin(), symbols.end(), 1);
    shuffle(symbols.begin(), symbols.end());

    println(n);
    for (int outRow = 0; outRow < side; ++outRow) {
        vector<int> line;
        line.reserve(side);
        int row = rowOrder[outRow];
        for (int outCol = 0; outCol < side; ++outCol) {
            int col = colOrder[outCol];
            int baseValue = (row * n + row / n + col) % side;
            line.push_back(symbols[baseValue]);
        }
        println(line);
    }

    return 0;
}
