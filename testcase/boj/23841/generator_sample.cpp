#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

char randomColor(int paletteSize) {
    return char('A' + rnd.next(0, paletteSize - 1));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> halfWidths = {1, 2, 3, 4, 5, 6};
    if (rnd.next(5) == 0) halfWidths.push_back(rnd.next(7, 25));

    int n = rnd.next(1, 12);
    if (rnd.next(8) == 0) n = rnd.next(13, 50);
    int half = rnd.any(halfWidths);
    int m = half * 2;

    int mode = rnd.next(0, 4);
    int paletteSize = rnd.next(1, 26);
    int sideBias = rnd.next(0, 2);
    double paintProb = rnd.next(0.15, 0.85);

    vector<string> board(n, string(m, '.'));
    for (int i = 0; i < n; ++i) {
        double rowProb = paintProb;
        if (mode == 1) rowProb = rnd.next(0.05, 0.35);
        if (mode == 2) rowProb = rnd.next(0.65, 1.0);
        if (mode == 3) rowProb = (i % 2 == 0 ? rnd.next(0.15, 0.45) : rnd.next(0.55, 0.95));

        for (int j = 0; j < half; ++j) {
            if (rnd.next() > rowProb) continue;

            int side = sideBias;
            if (mode == 4 || rnd.next(3) == 0) side = rnd.next(0, 1);
            int col = (side == 0 ? j : m - 1 - j);
            board[i][col] = randomColor(paletteSize);
        }
    }

    println(n, m);
    for (const string& row : board) println(row);

    return 0;
}
