#include "testlib.h"

#include <array>
#include <vector>
using namespace std;

using Pattern = array<int, 8>;

vector<Pattern> patterns;

void buildPatterns(Pattern& current, int index) {
    if (index == 8) {
        patterns.push_back(current);
        return;
    }

    for (int value = -1; value <= 1; ++value) {
        current[index] = value;
        buildPatterns(current, index + 1);
    }
}

int patternSum(const Pattern& pattern) {
    int sum = 0;
    for (int value : pattern) {
        sum += value;
    }
    return sum;
}

bool canFinish(const array<int, 8>& current, const array<int, 8>& target, int remainingRows) {
    for (int c = 0; c < 8; ++c) {
        int needed = target[c] - current[c];
        if (needed < -remainingRows || needed > remainingRows) {
            return false;
        }
    }
    return true;
}

bool searchRows(const array<vector<Pattern>, 8>& rowCandidates,
                const array<int, 8>& targetColumns,
                int row,
                array<int, 8>& currentColumns) {
    if (row == 8) {
        return currentColumns == targetColumns;
    }

    int remainingRows = 7 - row;
    for (const Pattern& pattern : rowCandidates[row]) {
        for (int c = 0; c < 8; ++c) {
            currentColumns[c] += pattern[c];
        }

        if (canFinish(currentColumns, targetColumns, remainingRows) &&
            searchRows(rowCandidates, targetColumns, row + 1, currentColumns)) {
            return true;
        }

        for (int c = 0; c < 8; ++c) {
            currentColumns[c] -= pattern[c];
        }
    }

    return false;
}

bool isReachable(const array<array<int, 8>, 8>& delta) {
    for (const Pattern& firstRow : patterns) {
        int firstRowSum = patternSum(firstRow);
        array<int, 8> targetColumns{};
        bool validTarget = true;

        for (int c = 0; c < 8; ++c) {
            targetColumns[c] = delta[0][c] + firstRow[c] - firstRowSum;
            if (targetColumns[c] < -8 || targetColumns[c] > 8) {
                validTarget = false;
                break;
            }
        }
        if (!validTarget) {
            continue;
        }

        array<vector<Pattern>, 8> rowCandidates;
        for (int r = 0; r < 8; ++r) {
            for (const Pattern& pattern : patterns) {
                int rowSum = patternSum(pattern);
                bool fits = true;
                for (int c = 0; c < 8; ++c) {
                    if (rowSum + targetColumns[c] - pattern[c] != delta[r][c]) {
                        fits = false;
                        break;
                    }
                }
                if (fits) {
                    rowCandidates[r].push_back(pattern);
                }
            }
            if (rowCandidates[r].empty()) {
                validTarget = false;
                break;
            }
        }
        if (!validTarget) {
            continue;
        }

        array<int, 8> currentColumns{};
        if (searchRows(rowCandidates, targetColumns, 0, currentColumns)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    Pattern current{};
    buildPatterns(current, 0);

    int m = inf.readInt(30, 40, "M");
    inf.readEoln();

    array<array<int, 8>, 8> delta{};
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            int production = inf.readInt(1, 55, "production");
            delta[r][c] = production - m;
            if (c == 7) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(isReachable(delta), "production grid cannot be produced by valid sprayer placements");

    inf.readEof();
}
