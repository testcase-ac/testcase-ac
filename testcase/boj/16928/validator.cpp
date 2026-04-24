#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of ladders N and snakes M
    int N = inf.readInt(1, 15, "N");
    inf.readSpace();
    int M = inf.readInt(1, 15, "M");
    inf.readEoln();

    // Teleport mapping: tele[i] = j if landing on i sends you to j
    vector<int> tele(101, 0);
    // Mark used cells (as start or end of any snake/ladder)
    vector<bool> used(101, false);

    // Read ladders
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(1, 100, "ladder_x");
        inf.readSpace();
        int y = inf.readInt(1, 100, "ladder_y");
        inf.readEoln();
        // Ladder must go up
        ensuref(x < y, "Ladder %d is invalid: start %d must be less than end %d", i+1, x, y);
        // Cannot involve cells 1 or 100
        ensuref(x != 1 && x != 100 && y != 1 && y != 100,
                "Ladder %d uses cell 1 or 100: (%d -> %d)", i+1, x, y);
        // No cell can be used twice
        ensuref(!used[x] && !used[y],
                "Ladder %d overlaps at cell %d or %d", i+1, x, y);
        used[x] = used[y] = true;
        tele[x] = y;
    }

    // Read snakes
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, 100, "snake_u");
        inf.readSpace();
        int v = inf.readInt(1, 100, "snake_v");
        inf.readEoln();
        // Snake must go down
        ensuref(u > v, "Snake %d is invalid: head %d must be greater than tail %d", i+1, u, v);
        // Cannot involve cells 1 or 100
        ensuref(u != 1 && u != 100 && v != 1 && v != 100,
                "Snake %d uses cell 1 or 100: (%d -> %d)", i+1, u, v);
        // No cell can be used twice
        ensuref(!used[u] && !used[v],
                "Snake %d overlaps at cell %d or %d", i+1, u, v);
        used[u] = used[v] = true;
        tele[u] = v;
    }

    // Now verify reachability from 1 to 100 via BFS
    vector<int> dist(101, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int d = 1; d <= 6; d++) {
            int nxt = cur + d;
            if (nxt > 100) continue;
            if (tele[nxt] != 0) nxt = tele[nxt];
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    ensuref(dist[100] != -1, "Cell 100 is not reachable from cell 1");

    inf.readEof();
    return 0;
}
