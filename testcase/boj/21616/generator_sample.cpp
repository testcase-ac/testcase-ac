#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = 1;
    int n = 1;

    if (mode == 0) {
        m = rnd.next(1, 5);
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        m = rnd.next(1, 2);
        n = rnd.any(vector<int>{1, rnd.next(2, 30), rnd.next(1000, 5000000 / m)});
    } else if (mode == 2) {
        n = rnd.next(1, 2);
        m = rnd.any(vector<int>{1, rnd.next(2, 30), rnd.next(1000, 5000000 / n)});
    } else if (mode == 3) {
        m = rnd.next(2, 2000);
        n = rnd.next(1, 5000000 / m);
    } else {
        m = rnd.next(1, 20);
        n = rnd.next(1, 20);
    }

    int k = rnd.next(1, 60);
    vector<pair<char, int>> strokes;
    strokes.reserve(k);

    vector<int> favoriteRows;
    vector<int> favoriteCols;
    int rowFavorites = min(m, rnd.next(1, min(m, 4)));
    int colFavorites = min(n, rnd.next(1, min(n, 4)));
    for (int i = 0; i < rowFavorites; ++i) favoriteRows.push_back(rnd.next(1, m));
    for (int i = 0; i < colFavorites; ++i) favoriteCols.push_back(rnd.next(1, n));

    for (int i = 0; i < k; ++i) {
        bool useRow;
        if (m == 1 && n > 1) {
            useRow = rnd.next(0, 4) == 0;
        } else if (n == 1 && m > 1) {
            useRow = rnd.next(0, 4) != 0;
        } else {
            useRow = rnd.next(0, 1) == 0;
        }

        if (useRow) {
            int row = rnd.next(0, 3) == 0 ? rnd.any(favoriteRows) : rnd.next(1, m);
            strokes.push_back({'R', row});
        } else {
            int col = rnd.next(0, 3) == 0 ? rnd.any(favoriteCols) : rnd.next(1, n);
            strokes.push_back({'C', col});
        }
    }

    if (rnd.next(0, 1) == 0) {
        shuffle(strokes.begin(), strokes.end());
    }

    println(m);
    println(n);
    println(k);
    for (const auto& stroke : strokes) {
        println(string(1, stroke.first), stroke.second);
    }

    return 0;
}
