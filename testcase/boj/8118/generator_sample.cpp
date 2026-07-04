#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int squareId(int n, int row, int col) {
    return row * n + col + 1;
}

vector<int> allSquares(int n) {
    vector<int> squares;
    squares.reserve(n * n);
    for (int i = 1; i <= n * n; ++i) {
        squares.push_back(i);
    }
    return squares;
}

vector<int> paritySquares(int n, int parity) {
    vector<int> squares;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if ((row + col) % 2 == parity) {
                squares.push_back(squareId(n, row, col));
            }
        }
    }
    return squares;
}

void addUnique(vector<int>& removed, int square) {
    if (find(removed.begin(), removed.end(), square) == removed.end()) {
        removed.push_back(square);
    }
}

int randomOdd(int lo, int hi) {
    int count = (hi - lo) / 2 + 1;
    return lo + 2 * rnd.next(count);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode == 1) {
        n = randomOdd(5, 11);
    } else if (mode == 2) {
        n = randomOdd(13, 25);
    } else if (mode == 3) {
        n = randomOdd(31, 49);
    } else {
        n = randomOdd(3, 49);
    }

    vector<int> removed;
    if (mode == 4) {
        vector<int> corners = {1, n, n * (n - 1) + 1, n * n};
        shuffle(corners.begin(), corners.end());
        removed.assign(corners.begin(), corners.begin() + 2);
        vector<int> edges;
        for (int i = 1; i <= n; ++i) {
            edges.push_back(i);
            edges.push_back(n * (n - 1) + i);
            edges.push_back(squareId(n, i - 1, 0));
            edges.push_back(squareId(n, i - 1, n - 1));
        }
        shuffle(edges.begin(), edges.end());
        for (int square : edges) {
            addUnique(removed, square);
            if ((int)removed.size() == 3) {
                break;
            }
        }
    } else if (mode == 5) {
        int center = n / 2;
        vector<int> nearCenter;
        for (int row = max(0, center - 1); row <= min(n - 1, center + 1); ++row) {
            for (int col = max(0, center - 1); col <= min(n - 1, center + 1); ++col) {
                nearCenter.push_back(squareId(n, row, col));
            }
        }
        shuffle(nearCenter.begin(), nearCenter.end());
        removed.assign(nearCenter.begin(), nearCenter.begin() + 3);
    } else if (mode == 6) {
        vector<int> even = paritySquares(n, 0);
        vector<int> odd = paritySquares(n, 1);
        shuffle(even.begin(), even.end());
        shuffle(odd.begin(), odd.end());
        removed = {even[0], even[1], odd[0]};
    } else if (mode == 7) {
        vector<int> even = paritySquares(n, 0);
        vector<int> odd = paritySquares(n, 1);
        shuffle(even.begin(), even.end());
        shuffle(odd.begin(), odd.end());
        removed = {even[0], odd[0], odd[1]};
    } else {
        vector<int> squares = allSquares(n);
        shuffle(squares.begin(), squares.end());
        removed.assign(squares.begin(), squares.begin() + 3);
    }

    shuffle(removed.begin(), removed.end());
    println(n, removed[0], removed[1], removed[2]);
    return 0;
}
