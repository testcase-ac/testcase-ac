#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> ascendingValues(int n) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = i + 1;
    }
    return values;
}

void applyLocalSwaps(vector<int>& values, int h, int w, int attempts) {
    for (int t = 0; t < attempts; ++t) {
        int r = rnd.next(h);
        int c = rnd.next(w);
        vector<int> neighbours;
        if (r > 0) {
            neighbours.push_back((r - 1) * w + c);
        }
        if (r + 1 < h) {
            neighbours.push_back((r + 1) * w + c);
        }
        if (c > 0) {
            neighbours.push_back(r * w + c - 1);
        }
        if (c + 1 < w) {
            neighbours.push_back(r * w + c + 1);
        }
        swap(values[r * w + c], values[rnd.any(neighbours)]);
    }
}

vector<int> snakeLayout(int h, int w) {
    vector<int> values(h * w);
    int cur = 1;
    for (int r = 0; r < h; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < w; ++c) {
                values[r * w + c] = cur++;
            }
        } else {
            for (int c = w - 1; c >= 0; --c) {
                values[r * w + c] = cur++;
            }
        }
    }
    return values;
}

vector<int> highLowLayout(int n) {
    vector<int> values;
    int lo = 1;
    int hi = n;
    while (lo <= hi) {
        values.push_back(lo++);
        if (lo <= hi) {
            values.push_back(hi--);
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int h;
    int w;
    if (mode == 0) {
        h = rnd.next(2, 4);
        w = rnd.next(2, 7);
    } else if (mode == 1) {
        h = rnd.next(2, 7);
        w = rnd.next(2, 4);
    } else if (mode == 5) {
        h = rnd.next(8, 16);
        w = rnd.next(8, 16);
    } else {
        h = rnd.next(2, 10);
        w = rnd.next(2, 10);
    }

    int n = h * w;
    vector<int> values;
    if (mode == 0) {
        values = ascendingValues(n);
    } else if (mode == 1) {
        values = snakeLayout(h, w);
    } else if (mode == 2) {
        values = highLowLayout(n);
    } else {
        values = ascendingValues(n);
        shuffle(values.begin(), values.end());
    }

    if (mode == 0 || mode == 1 || mode == 2) {
        applyLocalSwaps(values, h, w, rnd.next(0, max(1, n / 4)));
    } else if (mode == 4) {
        sort(values.begin(), values.end());
        applyLocalSwaps(values, h, w, rnd.next(n / 2, n));
    }

    println(h, w);
    for (int r = 0; r < h; ++r) {
        vector<int> row;
        for (int c = 0; c < w; ++c) {
            row.push_back(values[r * w + c]);
        }
        println(row);
    }

    return 0;
}
