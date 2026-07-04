#include "testlib.h"

#include <algorithm>
#include <array>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int snapshot = 0;
    while (true) {
        int r = inf.readInt(0, 40, "R");
        inf.readSpace();
        int c = inf.readInt(0, 40, "C");
        inf.readEoln();

        if (r == 0 && c == 0) {
            break;
        }
        ensuref(1 <= r && 1 <= c, "snapshot dimensions must both be positive or both be zero");

        ++snapshot;
        setTestCase(snapshot);

        vector<string> grid(r);
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
            grid[i] = inf.readLine(format("[a-z.]{%d}", c), format("row_%d", i + 1));
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

        int highest = -1;
        for (int id = 0; id < 26; ++id) {
            if (seen[id]) {
                highest = id;
            }
        }
        for (int id = 0; id <= highest; ++id) {
            ensuref(seen[id], "labels must be dense, missing '%c'", char('a' + id));
        }

        vector<vector<int>> above(26);
        array<int, 26> indegree{};
        for (int paper = 0; paper <= highest; ++paper) {
            for (int i = min_row[paper]; i <= max_row[paper]; ++i) {
                for (int j = min_col[paper]; j <= max_col[paper]; ++j) {
                    char top = grid[i][j];
                    ensuref(top != '.',
                            "desktop cell inside visible bounding box of paper '%c' at row %d column %d",
                            char('a' + paper), i + 1, j + 1);
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
        int visible_papers = highest + 1;
        for (int id = 0; id <= highest; ++id) {
            if (indegree[id] == 0) {
                q.push(id);
            }
        }

        int ordered = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            ++ordered;
            for (int next = 0; next <= highest; ++next) {
                if (!edge[cur][next]) {
                    continue;
                }
                --indegree[next];
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        ensuref(ordered == visible_papers, "paper-overlap precedence graph must be acyclic");
    }

    inf.readEof();
}
