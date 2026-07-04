#include "testlib.h"

#include <algorithm>
#include <array>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Rect {
    int r1;
    int c1;
    int r2;
    int c2;
};

bool validSnapshot(const vector<string>& grid, int labels) {
    int r = int(grid.size());
    int c = int(grid[0].size());

    array<int, 26> min_row;
    array<int, 26> max_row;
    array<int, 26> min_col;
    array<int, 26> max_col;
    array<bool, 26> seen{};
    min_row.fill(r);
    max_row.fill(-1);
    min_col.fill(c);
    max_col.fill(-1);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            char ch = grid[i][j];
            if (ch == '.') {
                continue;
            }
            int id = ch - 'a';
            seen[id] = true;
            min_row[id] = min(min_row[id], i);
            max_row[id] = max(max_row[id], i);
            min_col[id] = min(min_col[id], j);
            max_col[id] = max(max_col[id], j);
        }
    }

    for (int id = 0; id < labels; ++id) {
        if (!seen[id]) {
            return false;
        }
    }

    vector<vector<int>> above(26);
    array<int, 26> indegree{};
    for (int paper = 0; paper < labels; ++paper) {
        for (int i = min_row[paper]; i <= max_row[paper]; ++i) {
            for (int j = min_col[paper]; j <= max_col[paper]; ++j) {
                char top = grid[i][j];
                if (top == '.') {
                    return false;
                }
                int top_id = top - 'a';
                if (top_id != paper) {
                    above[top_id].push_back(paper);
                }
            }
        }
    }

    bool edge[26][26] = {};
    for (int from = 0; from < 26; ++from) {
        for (int to : above[from]) {
            if (!edge[from][to]) {
                edge[from][to] = true;
                ++indegree[to];
            }
        }
    }

    queue<int> q;
    for (int id = 0; id < labels; ++id) {
        if (indegree[id] == 0) {
            q.push(id);
        }
    }

    int ordered = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++ordered;
        for (int next = 0; next < labels; ++next) {
            if (!edge[cur][next]) {
                continue;
            }
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    return ordered == labels;
}

vector<string> makeSnapshot() {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int mode = rnd.next(0, 3);
        int r = rnd.next(3, mode == 3 ? 12 : 9);
        int c = rnd.next(3, mode == 3 ? 14 : 10);
        int labels = rnd.next(1, min(8, r * c));
        vector<Rect> rects(labels);

        for (int id = 0; id < labels; ++id) {
            if (mode == 0) {
                int h = rnd.next(1, min(r, 4));
                int w = rnd.next(1, min(c, 5));
                int r1 = rnd.next(0, r - h);
                int c1 = rnd.next(0, c - w);
                rects[id] = {r1, c1, r1 + h - 1, c1 + w - 1};
            } else if (mode == 1) {
                int margin = min({id, r / 2, c / 2});
                rects[id] = {rnd.next(0, margin), rnd.next(0, margin),
                             rnd.next(max(0, r - 1 - margin), r - 1),
                             rnd.next(max(0, c - 1 - margin), c - 1)};
            } else if (mode == 2) {
                int h = rnd.next(1, min(r, 3));
                int w = rnd.next(1, min(c, 6));
                int r1 = rnd.next(0, r - h);
                int c1 = rnd.next(0, c - w);
                if (rnd.next(0, 1) == 0) {
                    r1 = rnd.next(0, r - 1);
                    h = 1;
                } else {
                    c1 = rnd.next(0, c - 1);
                    w = 1;
                }
                rects[id] = {r1, c1, r1 + h - 1, c1 + w - 1};
            } else {
                int band = rnd.next(0, 3);
                int r1 = rnd.next(0, r - 1);
                int r2 = rnd.next(r1, min(r - 1, r1 + 4));
                int c1 = rnd.next(0, c - 1);
                int c2 = rnd.next(c1, min(c - 1, c1 + 6));
                if (band == 0) {
                    c1 = 0;
                } else if (band == 1) {
                    c2 = c - 1;
                } else if (band == 2) {
                    r1 = 0;
                } else {
                    r2 = r - 1;
                }
                rects[id] = {r1, c1, r2, c2};
            }
        }

        vector<int> order(labels);
        for (int i = 0; i < labels; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());

        vector<string> grid(r, string(c, '.'));
        for (int id : order) {
            char ch = char('a' + id);
            for (int i = rects[id].r1; i <= rects[id].r2; ++i) {
                for (int j = rects[id].c1; j <= rects[id].c2; ++j) {
                    grid[i][j] = ch;
                }
            }
        }

        if (validSnapshot(grid, labels)) {
            return grid;
        }
    }

    return vector<string>{"a"};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int snapshots = rnd.next(2, 5);
    for (int tc = 0; tc < snapshots; ++tc) {
        vector<string> grid = makeSnapshot();
        println(int(grid.size()), int(grid[0].size()));
        for (const string& row : grid) {
            println(row);
        }
    }
    println(0, 0);
    return 0;
}
