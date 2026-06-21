#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampPosition(long long x) {
    if (x < -100000000LL) return -100000000;
    if (x > 100000000LL) return 100000000;
    return static_cast<int>(x);
}

vector<int> makeClusteredPositions(int n) {
    vector<int> positions;
    positions.reserve(n);

    long long current = rnd.next(-1000, 1000);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            int gapMode = rnd.next(0, 4);
            if (gapMode == 0) {
                current += rnd.next(1, 2);
            } else if (gapMode <= 2) {
                current += rnd.next(3, 12);
            } else {
                current += rnd.next(50, 300);
            }
        }
        positions.push_back(clampPosition(current));
    }

    return positions;
}

vector<int> makeExtremePositions(int n) {
    vector<int> positions;
    positions.reserve(n);
    positions.push_back(-100000000);
    positions.push_back(100000000);

    while (static_cast<int>(positions.size()) < n) {
        int side = rnd.next(0, 2);
        if (side == 0) {
            positions.push_back(-100000000 + static_cast<int>(positions.size()));
        } else if (side == 1) {
            positions.push_back(100000000 - static_cast<int>(positions.size()));
        } else {
            positions.push_back(rnd.next(-20, 20));
        }
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());
    }

    return positions;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? rnd.next(2, 4) : rnd.next(5, 20));

    vector<int> positions;
    if (mode == 1) {
        positions = makeExtremePositions(n);
    } else if (mode == 2) {
        int start = rnd.next(-50, 50);
        int gap = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            positions.push_back(start + i * gap);
        }
    } else {
        positions = makeClusteredPositions(n);
    }

    sort(positions.begin(), positions.end());
    positions.erase(unique(positions.begin(), positions.end()), positions.end());
    n = static_cast<int>(positions.size());

    vector<int> costs(n);
    for (int i = 0; i < n; ++i) {
        int pattern = rnd.next(0, 4);
        if (pattern == 0) {
            costs[i] = 1;
        } else if (pattern == 1) {
            costs[i] = rnd.next(2, 20);
        } else if (pattern == 2) {
            costs[i] = rnd.next(9000, 10000);
        } else {
            costs[i] = rnd.next(1, 10000);
        }
    }

    int minCost = *min_element(costs.begin(), costs.end());
    long long totalCost = 0;
    for (int cost : costs) totalCost += cost;

    int bMode = rnd.next(0, 4);
    int budget;
    if (bMode == 0) {
        budget = minCost;
    } else if (bMode == 1) {
        budget = rnd.next(minCost, min(10000000, minCost + 30));
    } else if (bMode == 2) {
        budget = static_cast<int>(min<long long>(10000000, totalCost));
    } else {
        budget = rnd.next(minCost, 10000000);
    }

    vector<pair<int, int>> bombs;
    bombs.reserve(n);
    for (int i = 0; i < n; ++i) {
        bombs.push_back({positions[i], costs[i]});
    }
    if (mode == 3 || rnd.next(0, 1) == 1) {
        shuffle(bombs.begin(), bombs.end());
    }

    vector<int> outputPositions;
    vector<int> outputCosts;
    outputPositions.reserve(n);
    outputCosts.reserve(n);
    for (auto [position, cost] : bombs) {
        outputPositions.push_back(position);
        outputCosts.push_back(cost);
    }

    println(n);
    println(outputPositions);
    println(outputCosts);
    println(budget);

    return 0;
}
