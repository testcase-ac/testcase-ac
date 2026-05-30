#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    char kind;
    int row;
    int col;

    bool operator<(const Edge& other) const {
        return tie(kind, row, col) < tie(other.kind, other.row, other.col);
    }
};

struct Cell {
    int row;
    int col;
    array<Edge, 6> edges;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    long long totalSpecial = 0;

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100, "n");
        inf.readSpace();
        int m = inf.readInt(2, 100, "m");
        inf.readEoln();

        int h = 4 * n + 3;
        int w = 6 * m + 3;

        vector<string> grid(h);
        for (int r = 0; r < h; ++r) {
            grid[r] = inf.readLine("[^]*", "line");
            ensuref((int)grid[r].size() <= w,
                    "case %d line %d has length %d, expected at most %d",
                    tc, r + 1, (int)grid[r].size(), w);
            ensuref(grid[r].empty() || grid[r].back() != ' ',
                    "case %d line %d has trailing spaces", tc, r + 1);
        }

        auto at = [&](int r, int c) -> char {
            return c < (int)grid[r].size() ? grid[r][c] : ' ';
        };

        vector<string> role(h, string(w, '\0'));
        vector<Cell> cells;
        cells.reserve(n * m);
        map<Edge, int> incidentCount;

        auto mark = [&](int r, int c, char kind) {
            ensuref(0 <= r && r < h && 0 <= c && c < w,
                    "internal geometry coordinate out of range: (%d, %d)", r, c);
            ensuref(role[r][c] == '\0' || role[r][c] == kind,
                    "conflicting honeycomb roles at line %d col %d", r + 1, c + 1);
            role[r][c] = kind;
        };

        auto addHorizontal = [&](array<Edge, 6>& edges, int idx, int r, int c) {
            for (int d = 0; d < 3; ++d) {
                mark(r, c + d, '-');
            }
            edges[idx] = {'-', r, c};
            incidentCount[edges[idx]]++;
        };

        auto addDiagonal = [&](array<Edge, 6>& edges, int idx, int r, int c, char kind) {
            mark(r, c, kind);
            edges[idx] = {kind, r, c};
            incidentCount[edges[idx]]++;
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cr = 2 + 4 * i + 2 * (j % 2);
                int cc = 4 + 6 * j;

                mark(cr - 2, cc - 2, '+');
                mark(cr - 2, cc + 2, '+');
                mark(cr, cc - 4, '+');
                mark(cr, cc, '*');
                mark(cr, cc + 4, '+');
                mark(cr + 2, cc - 2, '+');
                mark(cr + 2, cc + 2, '+');

                Cell cell;
                cell.row = cr;
                cell.col = cc;
                addHorizontal(cell.edges, 0, cr - 2, cc - 1);
                addHorizontal(cell.edges, 1, cr + 2, cc - 1);
                addDiagonal(cell.edges, 2, cr - 1, cc - 3, '/');
                addDiagonal(cell.edges, 3, cr - 1, cc + 3, '\\');
                addDiagonal(cell.edges, 4, cr + 1, cc - 3, '\\');
                addDiagonal(cell.edges, 5, cr + 1, cc + 3, '/');
                cells.push_back(cell);
            }
        }

        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                char actual = at(r, c);
                char expected = role[r][c];
                if (expected == '\0') {
                    ensuref(actual == ' ',
                            "case %d line %d col %d must be space, found '%c'",
                            tc, r + 1, c + 1, actual);
                } else if (expected == '+') {
                    ensuref(actual == '+',
                            "case %d line %d col %d must be '+', found '%c'",
                            tc, r + 1, c + 1, actual);
                } else if (expected == '*') {
                    ensuref(actual == ' ' || actual == '*',
                            "case %d line %d col %d must be a cell center, found '%c'",
                            tc, r + 1, c + 1, actual);
                    if (actual == '*') {
                        ++totalSpecial;
                        ensuref(totalSpecial <= 3000,
                                "total number of special cells exceeded 3000");
                    }
                } else if (expected == '-') {
                    ensuref(actual == ' ' || actual == '-',
                            "case %d line %d col %d must be horizontal edge space or '-', found '%c'",
                            tc, r + 1, c + 1, actual);
                } else if (expected == '/') {
                    ensuref(actual == ' ' || actual == '/',
                            "case %d line %d col %d must be diagonal edge space or '/', found '%c'",
                            tc, r + 1, c + 1, actual);
                } else {
                    ensuref(actual == ' ' || actual == '\\',
                            "case %d line %d col %d must be diagonal edge space or '\\', found '%c'",
                            tc, r + 1, c + 1, actual);
                }
            }
        }

        auto isBlocked = [&](const Edge& edge) -> bool {
            if (edge.kind == '-') {
                char a = at(edge.row, edge.col);
                char b = at(edge.row, edge.col + 1);
                char c = at(edge.row, edge.col + 2);
                ensuref((a == '-' && b == '-' && c == '-') ||
                                (a == ' ' && b == ' ' && c == ' '),
                        "case %d horizontal edge at line %d col %d must be all '-' or all spaces",
                        tc, edge.row + 1, edge.col + 1);
                return a == '-';
            }
            return at(edge.row, edge.col) == edge.kind;
        };

        for (const auto& [edge, count] : incidentCount) {
            ensuref(count == 1 || count == 2,
                    "case %d edge at line %d col %d has invalid incident count %d",
                    tc, edge.row + 1, edge.col + 1, count);
            ensuref(count != 1 || isBlocked(edge),
                    "case %d boundary edge at line %d col %d must be untraversable",
                    tc, edge.row + 1, edge.col + 1);
        }

        for (const Cell& cell : cells) {
            if (at(cell.row, cell.col) == '*') {
                continue;
            }
            for (const Edge& edge : cell.edges) {
                ensuref(isBlocked(edge),
                        "case %d non-special cell centered at line %d col %d has a traversable edge at line %d col %d",
                        tc, cell.row + 1, cell.col + 1, edge.row + 1, edge.col + 1);
            }
        }
    }

    inf.readEof();
}
