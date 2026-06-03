#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampCoord(int value, int n) {
    return max(1, min(n, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int nMode = rnd.next(6);
    int n;
    if (nMode == 0) {
        n = 1;
    } else if (nMode == 1) {
        n = 2;
    } else if (nMode <= 3) {
        n = rnd.next(3, 12);
    } else if (nMode == 4) {
        n = rnd.next(13, 100);
    } else {
        n = rnd.next(4990, 5000);
    }

    vector<pair<int, int>> corners = {
        {1, 1},
        {1, n},
        {n, 1},
        {n, n},
    };

    int x, y;
    int posMode = rnd.next(7);
    if (n == 1 || posMode == 0) {
        tie(x, y) = rnd.any(corners);
    } else if (posMode == 1) {
        x = rnd.next(1, n);
        y = rnd.any(vector<int>{1, n});
    } else if (posMode == 2) {
        x = rnd.any(vector<int>{1, n});
        y = rnd.next(1, n);
    } else if (posMode == 3) {
        x = (n + 1) / 2;
        y = (n + 2) / 2;
    } else if (posMode == 4) {
        x = clampCoord(rnd.next(2, max(2, n - 1)), n);
        y = clampCoord(rnd.next(2, max(2, n - 1)), n);
    } else {
        x = rnd.next(1, n);
        y = rnd.next(1, n);
    }

    println(n);
    println(x, y);
    return 0;
}
