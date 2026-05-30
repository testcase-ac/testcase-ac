#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

static int lit(int var, bool value) {
    return value ? var + 1 : -(var + 1);
}

static bool litSatisfied(int literal, const vector<int>& assignment) {
    int var = abs(literal) - 1;
    int value = literal > 0 ? 1 : 0;
    return assignment[var] == value;
}

static bool litRejected(int literal, const vector<int>& assignment) {
    int var = abs(literal) - 1;
    int value = literal > 0 ? 1 : 0;
    return assignment[var] != -1 && assignment[var] != value;
}

static bool satisfiable(const vector<vector<int>>& clauses, vector<int>& assignment) {
    while (true) {
        bool changed = false;
        for (const vector<int>& clause : clauses) {
            bool satisfied = false;
            int unassigned = 0;
            int lastLiteral = 0;
            for (int literal : clause) {
                if (litSatisfied(literal, assignment)) {
                    satisfied = true;
                    break;
                }
                if (!litRejected(literal, assignment)) {
                    ++unassigned;
                    lastLiteral = literal;
                }
            }
            if (satisfied) {
                continue;
            }
            if (unassigned == 0) {
                return false;
            }
            if (unassigned == 1) {
                int var = abs(lastLiteral) - 1;
                int value = lastLiteral > 0 ? 1 : 0;
                if (assignment[var] != -1 && assignment[var] != value) {
                    return false;
                }
                if (assignment[var] == -1) {
                    assignment[var] = value;
                    changed = true;
                }
            }
        }
        if (!changed) {
            break;
        }
    }

    int bestClause = -1;
    int bestSize = 1000000;
    for (int i = 0; i < (int)clauses.size(); ++i) {
        bool satisfied = false;
        int unresolved = 0;
        for (int literal : clauses[i]) {
            if (litSatisfied(literal, assignment)) {
                satisfied = true;
                break;
            }
            if (!litRejected(literal, assignment)) {
                ++unresolved;
            }
        }
        if (!satisfied && unresolved < bestSize) {
            bestSize = unresolved;
            bestClause = i;
        }
    }
    if (bestClause == -1) {
        return true;
    }

    for (int literal : clauses[bestClause]) {
        if (litRejected(literal, assignment)) {
            continue;
        }
        vector<int> next = assignment;
        int var = abs(literal) - 1;
        next[var] = literal > 0 ? 1 : 0;
        if (satisfiable(clauses, next)) {
            assignment = next;
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 100, "R");
    inf.readSpace();
    int s = inf.readInt(1, 100, "S");
    inf.readEoln();

    vector<string> grid;
    string pattern = "[Tn#.]{" + to_string(s) + "}";
    for (int i = 0; i < r; ++i) {
        string row = inf.readToken(pattern, "row");
        grid.push_back(row);
        inf.readEoln();
    }

    vector<vector<int>> towerId(r, vector<int>(s, -1));
    int towerCount = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            if (grid[i][j] == 'T') {
                towerId[i][j] = towerCount++;
            }
        }
    }

    const int dr[4] = {0, 1, 0, -1};
    const int dc[4] = {-1, 0, 1, 0};
    vector<vector<int>> clauses;
    auto directionLiteral = [](int tower, int dir) {
        int horizontal = 2 * tower;
        int vertical = 2 * tower + 1;
        if (dir == 0) {
            return lit(horizontal, false);
        }
        if (dir == 2) {
            return lit(horizontal, true);
        }
        if (dir == 3) {
            return lit(vertical, false);
        }
        return lit(vertical, true);
    };

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            if (grid[i][j] != 'T') {
                continue;
            }
            int tower = towerId[i][j];
            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + dr[dir];
                int nj = j + dc[dir];
                bool hitsTower = false;
                while (0 <= ni && ni < r && 0 <= nj && nj < s && grid[ni][nj] != '#') {
                    if (grid[ni][nj] == 'T') {
                        hitsTower = true;
                        break;
                    }
                    ni += dr[dir];
                    nj += dc[dir];
                }
                if (hitsTower) {
                    clauses.push_back({-directionLiteral(tower, dir)});
                }
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            if (grid[i][j] != 'n') {
                continue;
            }
            vector<int> clause;
            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + dr[dir];
                int nj = j + dc[dir];
                while (0 <= ni && ni < r && 0 <= nj && nj < s && grid[ni][nj] != '#') {
                    if (grid[ni][nj] == 'T') {
                        int tower = towerId[ni][nj];
                        clause.push_back(directionLiteral(tower, (dir + 2) % 4));
                        break;
                    }
                    ni += dr[dir];
                    nj += dc[dir];
                }
            }
            sort(clause.begin(), clause.end());
            clause.erase(unique(clause.begin(), clause.end()), clause.end());
            clauses.push_back(clause);
        }
    }

    vector<int> assignment(2 * towerCount, -1);
    ensuref(satisfiable(clauses, assignment), "map must have a valid tower orientation assignment");

    inf.readEof();
}
