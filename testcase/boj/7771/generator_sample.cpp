#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cells;
    cells.reserve(100);

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cells.emplace_back(i, j);
            }
        }
        shuffle(cells.begin(), cells.end());
    } else if (mode == 1) {
        vector<int> rows(10), cols(10);
        iota(rows.begin(), rows.end(), 0);
        iota(cols.begin(), cols.end(), 0);
        shuffle(rows.begin(), rows.end());
        shuffle(cols.begin(), cols.end());

        for (int r = 0; r < 10; ++r) {
            bool reverseRow = rnd.next(0, 1);
            for (int c = 0; c < 10; ++c) {
                int colIndex = reverseRow ? 9 - c : c;
                cells.emplace_back(rows[r], cols[colIndex]);
            }
        }
    } else if (mode == 2) {
        vector<int> rows(10), cols(10);
        iota(rows.begin(), rows.end(), 0);
        iota(cols.begin(), cols.end(), 0);
        shuffle(rows.begin(), rows.end());
        shuffle(cols.begin(), cols.end());

        for (int r = 0; r < 10; ++r) {
            for (int c = 0; c < 10; ++c) {
                int colIndex = (r % 2 == 0) ? c : 9 - c;
                cells.emplace_back(rows[r], cols[colIndex]);
            }
        }
    } else if (mode == 3) {
        for (int sum = 0; sum <= 18; ++sum) {
            vector<pair<int, int>> diagonal;
            for (int i = 0; i < 10; ++i) {
                int j = sum - i;
                if (0 <= j && j < 10) {
                    diagonal.emplace_back(i, j);
                }
            }
            if (rnd.next(0, 1)) {
                reverse(diagonal.begin(), diagonal.end());
            }
            cells.insert(cells.end(), diagonal.begin(), diagonal.end());
        }
    } else if (mode == 4) {
        vector<pair<int, int>> corners = {
            {0, 0}, {0, 9}, {9, 0}, {9, 9}
        };
        shuffle(corners.begin(), corners.end());

        vector<vector<pair<int, int>>> buckets(4);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                int best = 0;
                int bestDist = 100;
                for (int k = 0; k < 4; ++k) {
                    int dist = abs(i - corners[k].first) + abs(j - corners[k].second);
                    if (dist < bestDist) {
                        bestDist = dist;
                        best = k;
                    }
                }
                buckets[best].emplace_back(i, j);
            }
        }
        for (auto& bucket : buckets) {
            shuffle(bucket.begin(), bucket.end());
            cells.insert(cells.end(), bucket.begin(), bucket.end());
        }
    } else {
        for (int band = 0; band < 5; ++band) {
            vector<pair<int, int>> block;
            for (int i = band * 2; i < band * 2 + 2; ++i) {
                for (int j = 0; j < 10; ++j) {
                    block.emplace_back(i, j);
                }
            }
            shuffle(block.begin(), block.end());
            cells.insert(cells.end(), block.begin(), block.end());
        }
    }

    vector<vector<int>> grid(10, vector<int>(10));
    for (int round = 1; round <= 100; ++round) {
        auto [i, j] = cells[round - 1];
        grid[i][j] = round;
    }

    if (rnd.next(0, 1)) {
        for (int i = 0; i < 10; ++i) {
            for (int j = i + 1; j < 10; ++j) {
                swap(grid[i][j], grid[j][i]);
            }
        }
    }

    int rotation = rnd.next(0, 3);
    while (rotation--) {
        vector<vector<int>> nextGrid(10, vector<int>(10));
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                nextGrid[j][9 - i] = grid[i][j];
            }
        }
        grid = nextGrid;
    }

    for (int i = 0; i < 10; ++i) {
        println(grid[i]);
    }

    return 0;
}
