#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeBase(int k) {
    vector<int> base(k);
    int value = rnd.next(0, 30);
    for (int i = 0; i < k; ++i) {
        value += rnd.next(0, 8);
        base[i] = value;
    }
    return base;
}

vector<vector<int>> makeDominanceChain(int n, int k) {
    vector<int> base = makeBase(k);
    vector<vector<int>> rows(n, vector<int>(k));
    int gap = rnd.next(1, 12);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            rows[i][j] = base[j] + (n - i) * gap + rnd.next(0, 2);
        }
    }
    return rows;
}

vector<vector<int>> makeCrossingRows(int n, int k) {
    vector<vector<int>> rows(n, vector<int>(k));
    for (int i = 0; i < n; ++i) {
        int left = 10 + i * rnd.next(2, 8);
        int right = 10 + (n - 1 - i) * rnd.next(2, 8);
        for (int j = 0; j < k; ++j) {
            int blend = k == 1 ? left : (left * (k - 1 - j) + right * j) / (k - 1);
            rows[i][j] = blend + rnd.next(0, 3);
        }
    }
    return rows;
}

vector<vector<int>> makeTiesAndPlateaus(int n, int k) {
    vector<vector<int>> rows(n, vector<int>(k));
    vector<int> pattern = makeBase(k);
    for (int i = 0; i < n; ++i) {
        int shift = (i / 2) * rnd.next(0, 4);
        for (int j = 0; j < k; ++j) {
            rows[i][j] = pattern[j] + shift;
            if (rnd.next(0, 3) == 0) {
                rows[i][j] = pattern[j];
            }
        }
    }
    return rows;
}

vector<vector<int>> makeExtremeRows(int n, int k) {
    vector<vector<int>> rows(n, vector<int>(k));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if ((i + j + rnd.next(0, 1)) % 2 == 0) {
                rows[i][j] = rnd.next(0, 20);
            } else {
                rows[i][j] = 1000000 - rnd.next(0, 20);
            }
        }
    }
    return rows;
}

vector<vector<int>> makeRandomRows(int n, int k) {
    vector<vector<int>> rows(n, vector<int>(k));
    int lo = rnd.next(0, 100);
    int hi = rnd.next(lo, lo + 300);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            rows[i][j] = rnd.next(lo, hi);
        }
    }
    return rows;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int totalCells = 0;
    int targetCells = rnd.next(80, 220);
    vector<vector<vector<int>>> cases;

    while (totalCells < targetCells && static_cast<int>(cases.size()) < 20) {
        int remaining = 2500 - totalCells;
        int k = rnd.next(1, min(8, remaining));
        int maxN = min(18, remaining / k);
        int n = rnd.next(1, maxN);
        int mode = rnd.next(0, 4);

        vector<vector<int>> rows;
        if (mode == 0) {
            rows = makeDominanceChain(n, k);
        } else if (mode == 1) {
            rows = makeCrossingRows(n, k);
        } else if (mode == 2) {
            rows = makeTiesAndPlateaus(n, k);
        } else if (mode == 3) {
            rows = makeExtremeRows(n, k);
        } else {
            rows = makeRandomRows(n, k);
        }

        shuffle(rows.begin(), rows.end());
        cases.push_back(rows);
        totalCells += n * k;
    }

    println(static_cast<int>(cases.size()));
    for (const auto& rows : cases) {
        println(static_cast<int>(rows.size()), static_cast<int>(rows[0].size()));
        for (const auto& row : rows) {
            println(row);
        }
    }

    return 0;
}
