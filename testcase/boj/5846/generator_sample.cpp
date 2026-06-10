#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int clampHeight(int x) {
    return max(0, min(1000000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 14);
    }

    vector<vector<int>> h(n, vector<int>(n));
    int base = rnd.next(0, 1000000);

    if (mode == 0) {
        int span = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                h[i][j] = rnd.next(2) ? base : span;
            }
        }
    } else if (mode == 1) {
        int value = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            fill(h[i].begin(), h[i].end(), value);
        }
    } else if (mode == 2) {
        int maxStepSum = 1000000 / max(1, n - 1);
        int stepSum = rnd.next(0, maxStepSum);
        int stepRow = rnd.next(0, stepSum);
        int stepCol = stepSum - stepRow;
        int start = rnd.next(0, 1000000 - (n - 1) * (stepRow + stepCol));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                h[i][j] = start + i * stepRow + j * stepCol;
            }
        }
    } else if (mode == 3) {
        int low = rnd.next(0, 900000);
        int high = rnd.next(low, 1000000);
        int stripe = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool useHigh = ((i / stripe) + (j / stripe)) % 2;
                h[i][j] = useHigh ? high : low;
            }
        }
    } else if (mode == 4) {
        int regionA = rnd.next(0, 1000000);
        int regionB = rnd.next(0, 1000000);
        int splitRow = rnd.next(1, n - 1);
        int splitCol = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool inCorner = i < splitRow && j < splitCol;
                bool inOpposite = i >= splitRow && j >= splitCol;
                h[i][j] = (inCorner || inOpposite) ? regionA : regionB;
            }
        }
    } else {
        int centers = rnd.next(2, min(6, n * n));
        vector<pair<int, int>> points;
        vector<int> values;
        for (int k = 0; k < centers; ++k) {
            points.push_back({rnd.next(n), rnd.next(n)});
            values.push_back(rnd.next(0, 1000000));
        }
        int noise = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int best = 0;
                int bestDist = n * n;
                for (int k = 0; k < centers; ++k) {
                    int dist = abs(i - points[k].first) + abs(j - points[k].second);
                    if (dist < bestDist) {
                        bestDist = dist;
                        best = k;
                    }
                }
                h[i][j] = clampHeight(values[best] + rnd.next(-noise, noise));
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(h[i]);
    }

    return 0;
}
