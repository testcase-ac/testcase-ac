#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    vector<vector<int>> graph(n);
    for (int movie = 1; movie <= m; ++movie) {
        int count = inf.readInt(2, n, "movie_size");
        vector<bool> seen(n, false);
        vector<int> cows;
        cows.reserve(count);

        for (int j = 0; j < count; ++j) {
            inf.readSpace();
            int cow = inf.readInt(1, n, "cow");
            --cow;

            // CHECK: the statement describes each movie line as a set of cows, so a cow
            // cannot appear twice in the same movie.
            ensuref(!seen[cow], "cow %d appears more than once in movie %d", cow + 1, movie);
            seen[cow] = true;
            cows.push_back(cow);
        }
        inf.readEoln();

        for (int i = 1; i < count; ++i) {
            graph[cows[0]].push_back(cows[i]);
            graph[cows[i]].push_back(cows[0]);
        }
    }

    vector<bool> visited(n, false);
    queue<int> q;
    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        ensuref(visited[i], "cow %d has no relationship path to cow 1", i + 1);
    }

    inf.readEof();
}
