#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    vector<vector<char>> horizontal(n, vector<char>(n - 1));
    vector<vector<char>> vertical(n - 1, vector<char>(n));
    vector<int> indegree(n * n, 0);

    auto addEdge = [&](int from, int to) {
        ++indegree[to];
    };

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n - 1; ++c) {
            string sign = inf.readToken("[<>]", "R_rc");
            horizontal[r][c] = sign[0];

            int left = r * n + c;
            int right = left + 1;
            if (horizontal[r][c] == '>') {
                addEdge(left, right);
            } else {
                addEdge(right, left);
            }

            if (c + 1 == n - 1) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    for (int r = 0; r < n - 1; ++r) {
        for (int c = 0; c < n; ++c) {
            string sign = inf.readToken("[<>]", "C_rc");
            vertical[r][c] = sign[0];

            int upper = r * n + c;
            int lower = (r + 1) * n + c;
            if (vertical[r][c] == '>') {
                addEdge(upper, lower);
            } else {
                addEdge(lower, upper);
            }

            if (c + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < n * n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int cell = q.front();
        q.pop();
        ++visited;

        int r = cell / n;
        int c = cell % n;

        if (c + 1 < n) {
            int next = cell + 1;
            bool outgoing = horizontal[r][c] == '>';
            if (outgoing && --indegree[next] == 0) {
                q.push(next);
            }
        }
        if (c > 0) {
            int next = cell - 1;
            bool outgoing = horizontal[r][c - 1] == '<';
            if (outgoing && --indegree[next] == 0) {
                q.push(next);
            }
        }
        if (r + 1 < n) {
            int next = cell + n;
            bool outgoing = vertical[r][c] == '>';
            if (outgoing && --indegree[next] == 0) {
                q.push(next);
            }
        }
        if (r > 0) {
            int next = cell - n;
            bool outgoing = vertical[r - 1][c] == '<';
            if (outgoing && --indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    ensuref(visited == n * n, "inequality graph must be acyclic");
    inf.readEof();
}
