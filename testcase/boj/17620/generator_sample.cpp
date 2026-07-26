#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 8);
    vector<vector<int>> walls(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        walls[0][i] |= 1;
        walls[n - 1][i] |= 4;
        if (i != 0) walls[i][0] |= 8;
        if (i != n - 1) walls[i][n - 1] |= 2;
    }

    int mode = rnd.next(0, 2);
    if (mode == 1) {
        for (int r = 0; r + 1 < n; ++r) {
            int opening = (r % 2 == 0 ? n - 1 : 0);
            for (int c = 0; c < n; ++c) {
                if (c != opening && rnd.next(2)) {
                    walls[r][c] |= 4;
                    walls[r + 1][c] |= 1;
                }
            }
        }
    } else if (mode == 2) {
        for (int c = 0; c + 1 < n; ++c) {
            int opening = (c % 2 == 0 ? n - 1 : 0);
            for (int r = 0; r < n; ++r) {
                if (r != opening && rnd.next(2)) {
                    walls[r][c] |= 2;
                    walls[r][c + 1] |= 8;
                }
            }
        }
    }

    println(n);
    for (const auto& row : walls) println(row);

    vector<pair<int, int>> cells;
    for (int r = 1; r <= n; ++r)
        for (int c = 1; c <= n; ++c)
            cells.push_back({r, c});
    shuffle(cells.begin(), cells.end());

    int m = rnd.next(1, min(n * n, 12));
    int labelCount = rnd.next(1, min(m, 5));
    vector<int> labels(n * n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());
    labels.resize(labelCount);

    vector<int> values;
    for (int i = 0; i < m; ++i) {
        values.push_back(i < labelCount ? labels[i] : rnd.any(labels));
    }
    vector<int> order(m);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    println(m);
    for (int i : order) println(cells[i].first, cells[i].second, values[i]);

    int t = labelCount == 1 ? 1 : rnd.next(1, 20);
    vector<int> sequence;
    while (static_cast<int>(sequence.size()) < t) {
        int value = rnd.any(labels);
        if (sequence.empty() || sequence.back() != value) sequence.push_back(value);
    }
    println(t);
    println(sequence);
}
